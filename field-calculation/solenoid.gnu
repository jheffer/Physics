set title "Square coil solenoid: cube sides 83 cm spaced 30 cm,\n18 turns, 1 A (y = 0, z = 0)"
set xlabel "Position x/m"
set ylabel "Magnetic field strength/Gauss"
#set xrange [-0.01:0.01]

set output "solenoid.ps"
set size 1.0, 1/1.61803398875
set terminal postscript portrait enhanced solid lw 1 "CM Roman, Times New Roman, Serif" 16

Bscale = 1E4 # convert T => G
a = 0.83 # coil size/m
S = 0.3 # coil spacing/m
I = 1 # current/A
N = 1*18
u0 = 4*pi*1e-7 # permability free space/(Tm/A)
Be = 18510.5*1e-9*Bscale # earth's magnetic field (total)/G

# coil positions
x0 = -S/2
x1 = 0
x2 = +S/2
set arrow from x0,graph 0 to x0, graph 1 nohead lt rgb "#999999"
set arrow from x1,graph 0 to x1, graph 1 nohead lt rgb "#999999"
set arrow from x2,graph 0 to x2, graph 1 nohead lt rgb "#999999"

# square coil theory
B0x(x) = Bscale * (4*a**2*u0*I*N) / (pi*sqrt(2*a**2 + 4*(x-x0)**2)*(a**2 + 4*(x-x0)**2))
B1x(x) = Bscale * (4*a**2*u0*I*N) / (pi*sqrt(2*a**2 + 4*(x-x1)**2)*(a**2 + 4*(x-x1)**2))
B2x(x) = Bscale * (4*a**2*u0*I*N) / (pi*sqrt(2*a**2 + 4*(x-x2)**2)*(a**2 + 4*(x-x2)**2))
Bx(x) = B0x(x) + B1x(x) + B2x(x)

myLabel = sprintf("B_x(0) = %.3f mG\nB_x(5 mm) = %.3f mG\n{/Symbol D}B(5 mm) = %.3f%",1e3*Bx(0),1e3*Bx(0.005),100*abs(1-Bx(0)/Bx(0.005)))
set label myLabel at graph 0.05, graph 0.6

plot \
Bx(x) t "B_{x(theory)}" lt rgb "red",\
Be t "|B_{Earth}|" lt rgb "#cc44cc",\
"solenoid.txt" u 1:(sqrt($4**2+$5**2+$6**2)*Bscale) t "|B|" pt 7 ps 0.2,\
"solenoid.txt" u 1:($4*Bscale) t "B_x" pt 7 ps 0.2 lt rgb "red",\
"solenoid.txt" u 1:($5*Bscale) t "B_y" pt 7 ps 0.2 lt rgb "green",\
"solenoid.txt" u 1:($6*Bscale) t "B_z" pt 7 ps 0.2 lt rgb "blue"
