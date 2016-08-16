set title "3 pairs of coils: 5 cm radius, 20 cm spacing, 20 turns\nI = [10 mA, 10 mA, 10 mA]\n(y = 0, z = 0)"
set xlabel "Position x/m"
set ylabel "Magnetic field strength/mG"

set output "coils-3D.ps"
set size 1.0, 1/1.61803398875
set terminal postscript portrait enhanced solid lw 1 "CM Roman, Times New Roman, Serif" 16

Bscale = 1E3*1E4 # convert T => mG
x1 = -0.10; x2 = +0.10; R = 0.05

# coil positions
set arrow from x1,graph 0 to x1, graph 1 nohead lt rgb "#999999"
set arrow from x2,graph 0 to x2, graph 1 nohead lt rgb "#999999"

# Fit to find field uniformity in trap region (doesn't work)
#f(x) = a*x**2 + b*x + c
#a = 1e4
#b = 1e-30
#c = 20
#fit [-0.05:0.05] f(x) "coils-3D.txt" u 1:(($2==0 & $3==0) ? (sqrt($4**2+$5**2+$6**2)*Bscale):NaN) via a,b,c

# Plot only where y=0 and z=0
plot\
"coils-3D.txt" u 1:(($2==0 & $3==0) ? (sqrt($4**2+$5**2+$6**2)*Bscale):NaN) t "|B|" pt 7 ps 0.2,\
"coils-3D.txt" u 1:(($2==0 & $3==0) ? ($4*Bscale):NaN) t "B_x" pt 7 ps 0.2 lt rgb "red",\
"coils-3D.txt" u 1:(($2==0 & $3==0) ? ($5*Bscale):NaN) t "B_y" pt 7 ps 0.2 lt rgb "green",\
"coils-3D.txt" u 1:(($2==0 & $3==0) ? ($6*Bscale):NaN) t "B_z" pt 7 ps 0.2 lt rgb "blue"
