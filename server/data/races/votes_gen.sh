for i in un_*.txt
do
	t1="${i##*_}"
	name="${t1%.*}"
	echo "gvote_add \"Race: $name\" load_race \"data/races/$i\""
done
