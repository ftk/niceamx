model=400; IFS=$'\n' ; for i in $(grep -o '"[^"]*"' vehs.inc ); do 
echo vehicle_info $model $i; let model++; 
done > vehicles.txt


cat carcolors.dat | sort | tr -d ':' > carcols.dat


join -2 1 -1 2 -a 1 vehicles.txt carcols.dat | awk -F',? *' '{a=NF-2;if($a != "#") a=NF+1; printf "%s %d ", $2, $1; for(i=3;i<a;i++){printf "%s ", $i} print f "\n"}' > vehicles_colors.txt
 
 
awk -F'\\[|\\]|= |;[ \t]*// *' '/=/{printf "vehicle_mod %d %d \"%s\"\n", $2 + 400, $6, $7}' vmods_u.inc > vehicles_mod.txt
 