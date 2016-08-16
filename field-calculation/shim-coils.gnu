set title "North/south shim coils: 83 cm x 180 cm, spacing 83 cm,\n20 turns, 0.553 A (y = 0, z = 0)"
set xlabel "Position x/m"
set ylabel "Magnetic field strength/Gauss"
#set xrange [-0.01:0.01]

set output "shim-coils.ps"
set size 1.0, 1/1.61803398875
set terminal postscript portrait enhanced solid lw 1 "CM Roman, Times New Roman, Serif" 16

Bscale = 1E4 # convert T => G
a = 0.83 # coil side size/m
b = 1.8 # coil side size/m
S = 0.83 # coil spacing/m
I = 0.553 # current/A
N = 1*20
u0 = 4*pi*1e-7 # permability free space/(Tm/A)
Be = 0.17982 # earth's magnetic field (total)/G

# coil positions
x1 = -S/2
x2 = +S/2
set arrow from x1,graph 0 to x1, graph 1 nohead lt rgb "#999999"
set arrow from x2,graph 0 to x2, graph 1 nohead lt rgb "#999999"

# 2mu_0*I*b/(pi*a*sqrt(a^2+b^2)) + 2mu_0*I*a/(pi*b*sqrt(a^2+b^2))
# Reference https://www.physicsforums.com/threads/magnetic-field-from-rectangular-current-loop.120083/
#B1x(x) = Bscale * ( 2*u0*I*b/(pi*a*sqrt(a**2+b**2)) + 2*u0*I*a/(pi*b*sqrt(a**2+b**2)) )
# square coil theory
#B1x(x) = Bscale * (4*a**2*u0*I*N) / (pi*sqrt(2*a**2 + 4*(x-x1)**2)*(a**2 + 4*(x-x1)**2))
#B2x(x) = Bscale * (4*a**2*u0*I*N) / (pi*sqrt(2*a**2 + 4*(x-x2)**2)*(a**2 + 4*(x-x2)**2))
#Bx(x) = B1x(x) + B2x(x)
#myLabel = sprintf("B_x(0) = %f G\nB_x(5 mm) = %f G\nB_x(0)/B_x(1 cm) = %f%",Bx(0),Bx(0.01),100*Bx(0)/Bx(0.005))
#set label myLabel at graph 0.05, graph 0.3

plot \
Be t "|B_{Earth (N/S)}|" lt rgb "#660066",\
"shim-coils.txt" u 1:(sqrt($4**2+$5**2+$6**2)*Bscale) t "|B|" pt 7 ps 0.2,\
"shim-coils.txt" u 1:($4*Bscale) t "B_x" pt 7 ps 0.2 lt rgb "red",\
"shim-coils.txt" u 1:($5*Bscale) t "B_y" pt 7 ps 0.2 lt rgb "green",\
"shim-coils.txt" u 1:($6*Bscale) t "B_z" pt 7 ps 0.2 lt rgb "blue"

#Bx(x) t "B_{x(theory)}" lt rgb "red",\
