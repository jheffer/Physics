show variables

# Options
set title title
set xlabel "Pixel"
set ylabel "Brightness"

# Fit
set fit errorvariables
#f(x) = I0 * exp( -((x-x0)**2)/(2*sig**2) ) + Ba + Bb*x
f(x) = I0 * exp( -((x-x0)**2)/(2*sig**2) ) + Ba
Ba = 1E3
Bb = 1E-1
fit f(x) datafile using 1:2 via I0, x0, sig, Ba

bg(x) = Ba

# Label
#fitLabel = sprintf("I_0 = %E +/- %E\nx_0 = %E +/- %E\n{/Symbol s} = %E +/- %E\nB_a = %E +/- %E\nB_b = %E +/- %E",I0,I0_err,x0,x0_err,sig,sig_err,Ba,Ba_err,Bb,Bb_err)
#set label fitLabel at graph 0.05, graph 0.9

# Plot
set output psname
set size 1.0, 0.6
set terminal postscript portrait enhanced mono solid lw 1 "CM Roman, Times New Roman, Serif" 16
plot datafile using 1:2 t "" pt 7 ps 0.4, f(x) t "I_0exp( -((x-x_0)^2)/(2{/Symbol s}^2) ) + B_a + B_bx", bg(x) t ""

# Write results to file
set print outfile
print sprintf("%E",abs(sig)) # sigma
set print outfile2
print sprintf("%E",abs(sig_err)) # sigma error
