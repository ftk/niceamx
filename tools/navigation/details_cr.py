import math;
import random;
import os;


dist = 3


cars = [
	400,401,402,404,405,
	445,458,461,466,467,
	521,540,542,543,
	597,598,599,
	409,410,411,412,
	468,474,478,479,489,
	546,547,549,551,
	555,559,600,
	420,426,436,438,439,
	492,496,507,516,
	561,562,565,566,576,
	580,581,596
]

with open("places.ini", 'r') as places:
	inf = open("navigation.in", 'w')
	places.readline()
	inf.write(places.readline()[2:-1] + ' ')
	inf.write(places.readline()[2:-1] + ' ')
	inf.write(places.readline()[2:-1] + '\n')
	places.readline()
	inf.write(places.readline()[2:-1] + ' ')
	inf.write(places.readline()[2:-1] + ' ')
	inf.write(places.readline()[2:-1] + '\n')
	inf.close()
	
os.system("navigation")

with open("navigation.out", 'r') as out:
	start = out.readline().split();
	start2 = out.readline().split();
	
	startx, starty, startz = float(start[0]), float(start[1]), float(start[2])
	
	
	angle = math.atan2(float(start2[0])- startx, float(start2[1])- starty)
	
	p1x = startx + dist * math.cos(angle - math.pi/2)
	p1y = starty + dist * math.sin(angle - math.pi/2)
	
	p2x = startx + dist * math.cos(angle + math.pi/2)
	p2y = starty + dist * math.sin(angle + math.pi/2)
	
	rot = (angle) * 180 / math.pi
	
	random.seed()
	
	index = open("index.txt", 'r+')
	idx = int(index.read())
	index.seek(0)
	index.write(str(idx+1))
	
	filename = "cr_autogen" + str(idx);
	
	with open(filename + ".txt", 'w') as outf:
		out.seek(0)
		outf.write(out.read())
	
	with open(filename + "_d.txt", 'w') as outd:
		outd.write(str(cars[random.randrange(len(cars))]))
		outd.write("\n")
		
		fmt = "%03.2f %03.2f %03.2f %03.1f\n"
	
		outd.write(fmt % (p1x, p1y, startz + 1, rot))
		outd.write(fmt % (p2x, p2y, startz + 1, rot))
	
	with open("races.txt", 'a') as races:
		races.write("\n")
		races.write(filename)
		