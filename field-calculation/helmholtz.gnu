set title "Helmholtz coils, radius 0.5 m, 1 A (y = 0, z = 0)"
set xlabel "Position x/coil radius"
set ylabel "Magnetic field strength/mG"
#set xrange [-0.5:0.5]

Bscale = 1E3*1E4 # convert T => mG

set output "helmholtz.ps"
set size 1.0, 1/1.61803398875
set terminal postscript portrait enhanced solid lw 1 "CM Roman, Times New Roman, Serif" 16

R = 0.5; x1 = -0.5*R; x2 = +0.5*R

# coil pos +/- coil radius
set arrow from x1-R,graph 0 to x1-R, graph 1 nohead lt rgb "#dddddd"
set arrow from x1+R,graph 0 to x1+R, graph 1 nohead lt rgb "#dddddd"
set arrow from x2-R,graph 0 to x2-R, graph 1 nohead lt rgb "#dddddd"
set arrow from x2+R,graph 0 to x2+R, graph 1 nohead lt rgb "#dddddd"

# coil positions
set arrow from x1,graph 0 to x1, graph 1 nohead lt rgb "#999999"
set arrow from x2,graph 0 to x2, graph 1 nohead lt rgb "#999999"

p\
"helmholtz.txt" u 1:(($2==0 & $3==0) ? (sqrt($4**2+$5**2+$6**2)*Bscale):NaN) t "|B|" pt 7,\
"helmholtz.txt" u 1:(($2==0 & $3==0) ? ($4*Bscale):NaN) t "B_x" pt 7 lt rgb "red",\
"helmholtz.txt" u 1:(($2==0 & $3==0) ? ($5*Bscale):NaN) t "B_y" pt 7 lt rgb "green",\
"helmholtz.txt" u 1:(($2==0 & $3==0) ? ($6*Bscale):NaN) t "B_z" pt 7 lt rgb "blue"
