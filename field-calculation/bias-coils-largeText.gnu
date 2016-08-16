# Square coils
# Should look like this, twice, Eq. 9:
# http://www.physicspages.com/2013/04/11/magnetic-field-of-square-current-loop/

set title "83 cm square coils, 83 cm apart,\n20 turns, 1 A (y = 0, z = 0)"
set xlabel "Position x/m"
set xtics 0.4
set xrange [-0.5:0.5]
set ylabel "Magnetic field strength/Gauss"
set ytics 0.1
set yrange [-0.05:0.35]

set output "bias-coils-largeText.ps"
set size 1.0, 1/1.61803398875
set terminal postscript portrait enhanced solid lw 1 "CM Roman, Times New Roman, Serif" 24

Bscale = 1E4 # convert T => G
a = 0.83 # coil size/m
S = 0.83 # coil spacing/m
I = 1 # current/A
N = 1*20
u0 = 4*pi*1e-7 # permability free space/(Tm/A)
Be = 0.49 # earth's magnetic field (total)/G

# coil positions
x1 = -S/2
x2 = +S/2
set arrow from x1,graph 0 to x1, graph 1 nohead lt rgb "#999999"
set arrow from x2,graph 0 to x2, graph 1 nohead lt rgb "#999999"

# square coil theory
B1x(x) = Bscale * (4*a**2*u0*I*N) / (pi*sqrt(2*a**2 + 4*(x-x1)**2)*(a**2 + 4*(x-x1)**2))
B2x(x) = Bscale * (4*a**2*u0*I*N) / (pi*sqrt(2*a**2 + 4*(x-x2)**2)*(a**2 + 4*(x-x2)**2))
Bx(x) = B1x(x) + B2x(x)

myLabel = sprintf("B_x(0) = %.1f mG\nB_x(5 mm) = %.1f mG\nB_x(0)/B_x(1 cm) = %.2f%",1E3*Bx(0),1E3*Bx(0.01),100*Bx(0)/Bx(0.005))
#set label myLabel at graph 0.05, graph 0.3

plot \
Bx(x) t "B_{x(theory)}" lt rgb "red",\
"largecube.txt" u 1:(sqrt($4**2+$5**2+$6**2)*Bscale) t "|B|" pt 7 ps 0.2,\
"largecube.txt" u 1:($4*Bscale) t "B_x" pt 7 ps 0.2 lt rgb "red",\
"largecube.txt" u 1:($5*Bscale) t "B_y" pt 7 ps 0.2 lt rgb "green",\
"largecube.txt" u 1:($6*Bscale) t "B_z" pt 7 ps 0.2 lt rgb "blue"

#Be t "|B_{Earth}|" lt rgb "#660066",\