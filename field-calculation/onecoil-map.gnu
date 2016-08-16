set xlabel "Position y/metres"
set ylabel "Position z/metres"
#set xrange [0.1:.65]
#set yrange [0.1:1.4]
Bscale = 1E3*1E4 # convert T => mG

set term postscript eps color blacktext "CM Roman, Times New Roman, Serif" 24 size 5,5
set pm3d

set view map
#set size square
set palette rgbformulae 22,13,10
set nokey

set output "onecoilBmap.ps"
set title "Single coil magnetic field magnitude/mG"
splot "onecoil.txt" using 2:3:(sqrt($4**2+$5**2+$6**2)*Bscale)

set output "onecoilBXmap.ps"
set title "Single coil magnetic field x-component/mG"
splot "onecoil.txt" using 2:3:($4*Bscale)

set output "onecoilBYmap.ps"
set title "Single coil magnetic field y-component/mG"
splot "onecoil.txt" using 2:3:($5*Bscale)

set output "onecoilBZmap.ps"
set title "Single coil magnetic field z-component/mG"
splot "onecoil.txt" using 2:3:($6*Bscale)
