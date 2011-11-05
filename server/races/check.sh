for i in `cat races.txt `; do ls $i.txt ${i}_d.txt 2>&1 1>/dev/null; done
