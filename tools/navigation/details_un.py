import math;
import random;
import os;
import binascii;

dist = 4


cars = [
	400,401,402,404,405,409,410,411,412,415,
	419,420,421,426,436,438,439,442,
	445,448,451,458,461,463,466,467,
	468,474,475,477,478,482,489,490,491,
	492,494,496,504,505,506,507,516,
	517,518,521,526,527,529,
	533,534,536,540,542,543,545,
	546,547,549,550,551,552,555,558,559,
	560,561,562,565,566,567,576,
	579,580,581,585,587,589,596,597,598,
	599,600,602,603,604,605,609,612,613
]

random.seed()

def distance(x, y, z):
	return math.sqrt(x*x + y*y + z*z)

def turn(x, y):
	return math.atan2(x, y) * 180 / math.pi

def diff(t1, t2):
	return math.fabs(t1 - t2)

def fwrite(fp, s):
	return fp.write(bytes(str(s), 'ascii'))

def parse_ini(ini):
	with open(ini, 'r') as places:
		result = ""
		for line in places:
			if line[1] == '=':
				result += line[2:-1] + ' '
			else:
				result += '\n'
		return result



race_contents = parse_ini("places.ini")

crc = binascii.crc32(bytes(race_contents, 'ascii')) & 0xffff
print("race hash: %x" % crc)
open("races/autogen_src_%x.txt" % crc, 'w').write(race_contents)
open("navigation.in", 'w').write(race_contents)

filename = "un_autogen_%x" % crc;

os.system("navigation 1 un")

with open("navigation.out", 'r') as out:
	start = out.readline().split();
	start2 = out.readline().split();
	
	startx, starty, startz = float(start[0]), float(start[1]), float(start[2])
	
	
	angle = math.atan2(float(start2[0]) - startx, float(start2[1]) - starty)
	
	p1x = startx + dist * math.sin(angle - math.pi/2)
	p1y = starty + dist * math.cos(angle - math.pi/2)
	
	p2x = startx + dist * math.sin(angle + math.pi/2)
	p2y = starty + dist * math.cos(angle + math.pi/2)
	
	rot = math.degrees(-angle)
	
	
	with open("races/" + filename + ".txt", 'wb') as outf:
		fwrite(outf, cars[random.randrange(len(cars))])
		fwrite(outf, '\n')
		
		fmt = "%03.2f %03.2f %03.2f %03.1f\n"
		
		fwrite(outf, fmt % (p1x, p1y, startz + 1, rot))
		fwrite(outf, fmt % (p2x, p2y, startz + 1, rot))
		
		fwrite(outf, "10.0\n10.0\n")
		
		
		out.seek(0)
		ox, oy, oz = 0.0, 0.0, 0.0
		pturn = 1000.0
		for line in out:
			arr = line.split()
			x, y, z = float(arr[0]), float(arr[1]), float(arr[2])
			if distance(x-ox, y-oy, z-oz) > 130.0 or diff(pturn, turn(x-ox, y-oy)) > 20.0:
				fwrite(outf, "%.2f %.2f %.2f\n" % (x, y, z))
				pturn = turn(x-ox, y-oy)
				ox, oy, oz = x, y, z
				print(pturn)
		
		if not (x == ox and y == oy and z == oz): # write last line
			fwrite(outf, "%.2f %.2f %.2f\n" % (x, y, z))
	
	
	with open("races/races.txt", 'ab') as races:
		fwrite(races, filename)
		fwrite(races, '\n')
