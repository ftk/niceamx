import math;
import random;
import os;


dist = 3


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

def distance(x, y, z):
	return math.sqrt(x*x + y*y + z*z)

with open("places.ini", 'r') as places:
	inf = open("navigation.in", 'w')
	for line in places:
		if line[1] == '=':
			inf.write(line[2:-1] + ' ')
		else:
			inf.write('\n')
	inf.close()
	
os.system("navigation 1 un")

with open("navigation.out", 'r') as out:
	start = out.readline().split();
	start2 = out.readline().split();
	
	startx, starty, startz = float(start[0]), float(start[1]), float(start[2])
	
	
	angle = math.atan2(float(start2[0])- startx, float(start2[1])- starty)
	
	p1x = startx + dist * math.sin(angle - math.pi/2)
	p1y = starty + dist * math.cos(angle - math.pi/2)
	
	p2x = startx + dist * math.sin(angle + math.pi/2)
	p2y = starty + dist * math.cos(angle + math.pi/2)
	
	rot = math.degrees(-angle)
	
	random.seed()
	
	index = open("index.txt", 'r+')
	idx = int(index.read())
	index.seek(0)
	index.write(str(idx+1))
	
	filename = "un_autogen" + str(idx);
	
	with open("races/" + filename + ".txt", 'w') as outf:
		out.seek(0)
		ox, oy, oz = 0.0, 0.0, 0.0
		for line in out:
			arr = line.split()
			x, y, z = float(arr[0]), float(arr[1]), float(arr[2])
			if distance(x-ox, y-oy, z-oz) > 50.0:
				outf.write("%.2f %.2f %.2f\n" % (x, y, z))
				ox, oy, oz = x, y, z
		
		if not (x == ox and y == oy and z == oz): # write last line
			outf.write("%.2f %.2f %.2f\n" % (x, y, z))
	
	with open("races/" + filename + "_d.txt", 'w') as outd:
		outd.write(str(cars[random.randrange(len(cars))]))
		outd.write("\n")
		
		fmt = "%03.2f %03.2f %03.2f %03.1f\n"
	
		outd.write(fmt % (p1x, p1y, startz + 1, rot))
		outd.write(fmt % (p2x, p2y, startz + 1, rot))
	
	with open("races/races.txt", 'a') as races:
		races.write("\n")
		races.write(filename)
		