echo -e "File\t\t\tDrop\tZero\tFlash"
for f in data/2ms/*.txt; do
  echo -e $f"\t"$(python analyse.py $f 1)"\t"$(python analyse.py $f 2)"\t"$(python analyse.py $f 3)
done
