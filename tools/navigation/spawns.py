
def parse_ini(ini):
	with open(ini, 'r') as places:
		result = ""
		for line in places:
			if line[1] == '=':
				result += line[2:-1] + ' '
			else:
				result += '\n'
		return result 


tpos = parse_ini("places.ini").split()

tx, ty, tz = float(tpos[0]),float(tpos[1]),float(tpos[2])

#print(tx,ty,tz)


#os.system("navigation 1 un export")



with open("navigation.out", 'r') as out:
	result = ""
	for line in out:
		pos = line.split()
		x,y,z = float(pos[0]),float(pos[1]),float(pos[2])
		
		if (x-tx)*(x-tx) + (y-ty)*(y-ty) < 60*60:
			result += line
	print(result)
