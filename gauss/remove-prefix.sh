for name in Images/10ms/?ms/image*.bmp
do
    path="$(echo "$name" | cut -c1-16)"
    frame="$(echo "$name" | cut -c29-)"
    newname=$path$frame
#    echo $path
#    echo $frame
    echo $newname
    mv "$name" "$newname"
done
