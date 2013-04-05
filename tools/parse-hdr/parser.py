line = "native AddStaticVehicle(&modelid, &Float:spawn_x, &Float:spawn_y, Float:spawn_z, Float:z_angle, color1, color2, test[]);"


def parse_line(line):
	cnt = 0
	method = ""
	method_ret = ""
	
	params = []
	ctypes = []
	nline = line.replace("(", " ").replace(",", " ").replace(")", " ").replace("{Float,_}", "").replace("{&Float,_}", "")
	
	is_const = False
	to_skip = False
	for param in nline.split():
		cnt += 1
		
		if to_skip:
			to_skip = False
			continue
		
		if cnt == 1:
			if param != "native":
				break
			continue
		if param[0] == ";":
			break
			
		if param == "const":
			is_const = True
			cnt -= 1
			continue
		if param == "=":
			to_skip = True
			cnt -= 2
			continue
		
		
		t = param.split(":")
		
		if cnt == 2:
			if len(t) == 1:
				method = param
				method_ret = "int"
			else:
				method = t[1]
				method_ret = t[0].lower()
			continue
		
		ptype = "int"
		if len(t) != 1:
			ptype = t[0].lower()
			param = t[1]
		
		if param[-2:] == "[]":
			ptype = "string"
			param = param[:-2]
		
		#if ptype[0] == "{" and ptype[-1] == "}":
		#	ptype = ""
		
		if param[0] == "&":
			ptype += "&"
			param = param[1:]
		
		if ptype[0] == "&":
			ptype = ptype[1:] + "&"
			
				
		if is_const:
			ptype = "const " + ptype
			is_const = False
		
		params.append(param)
		ctypes.append(ptype)
	return method_ret, method, ctypes, params

def stringize(arr):
	s = ""
	for i in arr:
		if s != "":
			s += ", "
		s += i
	return s

def stringize_args(types, args):
	s = ""
	for i in range(0, len(types)):
		if s != "":
			s += ", "
		s += types[i]
		s += " "
		s += args[i]
	return s

def from_camel_case(s):
	r = ""
	for ch in s:
		if(ch.isupper()):
			ch = "_" + ch.lower();
		r += ch
	if r[0] == '_':
		r = r[1:]
	return r

marhs_t = []
declarations = []
declarations_cc = []

funcs = []

with open("diff.inc", "r") as f:
	for line in f:
		line = line[2:]
		method_ret, method, types, params = parse_line(line)
		if method == "":
			continue
		method_n = from_camel_case(method)
		
		#print("// " + line.strip())
		#print("pawn::marh_t<" + stringize(types) + "> " + method + "_t(\"" + method + "\", marhs);")
		marhs_t.append("pawn::marh_t<" + stringize(types) + "> " + method_n + "_t(\"" + method + "\", marhs);" + 
			" // " + line.strip())
		
		declarations_cc.append(method_ret + " " + method + " (" + stringize_args(types, params) + ");" + 
			" // " + line.strip())
		
		decl = method_ret + " " + method_n + " (" + stringize_args(types, params) + ")"
		
		declarations.append(decl + ";" + " // " + line.strip())
		
		real = decl + "\n{\n\t" + "START();\n\t" + "DEBUG_NATIVE(/*f*/" + method_n + ", /*p*/"
		
		for p in params:
			real += p
			if p != params[len(params)-1]:
				real += " SEPARATOR  "
		
		real += ");\n\t"
		
		real += "return " + method_n + "_t.call(" + stringize(params) + ");  \n}"
		
		funcs.append(real)
		
		#print(method_ret, from_camel_case(method))
		
for x in marhs_t:
	print(x)

