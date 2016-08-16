set title "Single coil (y = 0, z = 0)"
set xlabel "Position x/metres"
set ylabel "Magnetic field strength/mG"
#set xrange [-0.5:0.5]

Bscale = 1E3*1E4 # convert T => mG

set output "onecoil.ps"
set term postscript eps color blacktext "CM Roman, Times New Roman, Serif" 24 size 5,5

x1 = 0
set arrow from x1,graph 0 to x1, graph 1 nohead lt rgb "#333366"

p "onecoil.txt" u 1:(($2==0 & $3==0) ? (sqrt($4**2+$5**2+$6**2)*Bscale):NaN) t "" pt 7
