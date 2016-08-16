for f in Images/[0-9]*ms/[0-9]*ms/??.bmp; do
   # mv $f `printf %04d.%s ${a%.*} ${a##*.}`
   echo $f
   path="$(echo "$f" | cut -c1-15)"
   echo $path
   num="$(echo "$f" | cut -c16-17)"
   echo $num
   newname=$path"0"$num".bmp"
   echo "Rename to: "$newname
   mv "$f" "$newname"
done
