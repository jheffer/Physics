# Plot the temperature as a function of molasses duration

######   Options   ######
set title "Molasses temperature"
set xlabel "Molasses duration/ms"
set ylabel "Temperature/{/Symbol m}K"
set xrange [0:]
set yrange [0:]
set key left
yscale = 1E6 # K/uK

######   Fit   ######
fx(x) = ax + bx*x + cx*(x-x0x)**2
fy(x) = ay + by*x + cy*(x-x0y)**2
ax = 50
ay = 50
bx = 10
by = 10
cx = 1
cy = 1
x0x = 1
x0y = 1
fit fx(x) data using 1:($2*yscale):($3*yscale) via ax,bx,cx,x0x
fit fy(x) data using 1:($4*yscale):($5*yscale) via ay,by,cy,x0y

######   Label   ######


######   Plot   ######
set output "temp/temp-mol.ps"
set size 1.0, 0.6
set terminal postscript portrait enhanced mono solid lw 1 "CM Roman, Times New Roman, Serif" 12
plot data using 1:($2*yscale):($3*yscale) with yerrorbars t "x-axis" pt 7 ps 0.5 lt rgb "#44aa44", fx(x) t "" lt rgb "#44aa44", \
     data using 1:($4*yscale):($5*yscale) with yerrorbars t "y-axis" pt 7 ps 0.5 lt rgb "#aa44aa", fy(x) t "" lt rgb "#aa44aa"
