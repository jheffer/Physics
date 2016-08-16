# Options
set title "Atom cloud brightness"
set xlabel "Frame number"
set ylabel "Integrated brightness"

# Plot
set output psname
set size 1.0, 0.6
set terminal postscript portrait enhanced mono solid lw 1 "CM Roman, Times New Roman, Serif" 16
plot datafile u 1:2 t "" w l

#show variables
