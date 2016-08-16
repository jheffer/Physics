set title "AOM0 beam profile"
set xlabel "Distance from PBS z/mm"
set ylabel "e^{-2} intensity radius r(x)/{/Symbol m}m"
set fit errorvariables
#set bars 0
l = 780.241209686E-9 # wavelength/m
dz = 0 + 12.5 # mm
pxScale = 2*5.6

# FIT
label_r = 'w_y(x) = r_0(1+[(M^2{/Symbol l}[x-x_0])/({/Symbol p}r_0^2)]^2)^{1/2}'
r_y(x) = r_y * sqrt(1 + ( ((M_y**2)*l*(x-x_y)*1e-3)/(GPVAL_pi*(r_y*1e-6)**2) )**2)
r_z(x) = r_z * sqrt(1 + ( ((M_z**2)*l*(x-x_z)*1e-3)/(GPVAL_pi*(r_z*1e-6)**2) )**2)
x_y = 300;	r_y = +30;	M_y = sqrt(1.1)
x_z = 300;	r_z = -30;	M_z = sqrt(1.1)
fit r_y(x) "radii.txt" using ($1+dz):(abs($2)*pxScale):($3*pxScale) via x_y,r_y,M_y
chi_x = FIT_WSSR; ndf_x = FIT_NDF
fit r_z(x) "radii.txt" using ($1+dz):(-abs($4)*pxScale):($5*pxScale) via x_z,r_z,M_z
chi_y = FIT_WSSR; ndf_y = FIT_NDF

# IDEAL CURVE
r_ideal_x(x) = r_y * sqrt(1 + ( (l*(x-x_y)*10**-3)/(GPVAL_pi*(r_y*10**-6)**2) )**2)
r_ideal_y(x) = r_z * sqrt(1 + ( (l*(x-x_z)*10**-3)/(GPVAL_pi*(r_z*10**-6)**2) )**2)
xR_ideal_x = (GPVAL_pi * ((r_y*10**-6)**2)/l) * 10**3
xR_ideal_y = (GPVAL_pi * ((r_z*10**-6)**2)/l) * 10**3

# MARKERS: WAIST & RAYLEIGH RANGE
set arrow from x_y,0 to x_y,r_y lt rgb "#DD4411" nohead
set arrow from x_z,0 to x_z,r_z lt rgb "#44DD11" nohead
xR_y = (GPVAL_pi * (r_y*10**-6)**2)/(l*M_y**2) * 10**3
xR_z = (GPVAL_pi * (r_z*10**-6)**2)/(l*M_z**2) * 10**3
set arrow from x_y+xR_y,0 to x_y+xR_y,r_y*2**0.5 lt rgb "#FFAA77" nohead
set arrow from x_y-xR_y,0 to x_y-xR_y,r_y*2**0.5 lt rgb "#FFAA77" nohead
set arrow from x_z+xR_z,0 to x_z+xR_z,r_z*2**0.5 lt rgb "#77FFAA" nohead
set arrow from x_z-xR_z,0 to x_z-xR_z,r_z*2**0.5 lt rgb "#77FFAA" nohead
set arrow from x_y-xR_ideal_x,0 to x_y-xR_ideal_x,r_y*2**0.5 lt rgb "#DDDDDD" nohead
set arrow from x_y+xR_ideal_x,0 to x_y+xR_ideal_x,r_y*2**0.5 lt rgb "#DDDDDD" nohead
set arrow from x_z-xR_ideal_y,0 to x_z-xR_ideal_y,r_z*2**0.5 lt rgb "#DDDDDD" nohead
set arrow from x_z+xR_ideal_y,0 to x_z+xR_ideal_y,r_z*2**0.5 lt rgb "#DDDDDD" nohead

# FIT INFO LABELS
fit_info_x = sprintf("y-axis, 5.6 {/Symbol m}m/pixel\n\
x_0 = %.2f +/- %.2f mm (%.2f%%)\nw_0 = %.2f +/- %.2f {/Symbol m}m (%.2f%%)\nz_R = ({/Symbol p}r_0^2)/({/Symbol l}M^2) = %.2f mm\nM^2 = %.2f +/- %.2f (%.2f%%)\n{/Symbol C}^2/{/Symbol n} = %.1f/%.1i",x_y, x_y_err, 100*x_y_err/x_y, r_y, r_y_err, 100*r_y_err/r_y, xR_y,M_y**2, 2*M_y_err,100*2*M_y_err/M_y**2, chi_x, ndf_x)
fit_info_y = sprintf("z-axis, 5.6 {/Symbol m}m/pixel\nx_0 = %.2f +/- %.2f mm (%.2f%%)\n\
w_0 = %.2f +/- %.2f {/Symbol m}m (%.2f%%)\nz_R = ({/Symbol p}r_0^2)/({/Symbol l}M^2) = %.2f mm\nM^2 = %.2f +/- %.2f (%.2f%%)\n{/Symbol C}^2/{/Symbol n} = %.1f/%.1i",x_z, x_z_err, 100*x_z_err/x_z, -r_z, r_z_err, -100*r_z_err/r_z, xR_z,M_z**2, 2*M_z_err,100*2*M_z_err/M_z**2, chi_y, ndf_y)
set label fit_info_x at 300, -300
set label fit_info_y at 10, 250
#set label "Fit z > 9 mm" at 6.5, 20

# PLOT
set output "profile.ps"
set size 1.0, 0.61
#set tmargin at screen 0.6
set terminal postscript portrait enhanced mono solid lw 1 "CM Roman, Times New Roman, Serif" 15
plot "radii.txt" using ($1+dz):(abs($2)*pxScale):($3*pxScale) with errorbars t "" pt 0 ps 0.1,\
r_y(x) t label_r lt rgb "#DD4411",\
"radii.txt" using ($1+dz):(-abs($4)*pxScale):($5*pxScale) with errorbars t "" pt 0 ps 0.1,\
r_z(x) t "r_z(x)" lt rgb "#44DD11",\
r_ideal_x(x) t "M = 1" lt rgb "#DDDDDD",\
r_ideal_y(x) t "" lt rgb "#DDDDDD"
#set terminal x11
#set size 1,1
