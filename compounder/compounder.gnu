####################################################################################
# Gnuplot 4.6 script for plotting multiple groups of 3 bars in a barchart.
# This part is dynamic and can be altered to influence the look of the graph.
####################################################################################

### plot setup
set terminal pngcairo size 800,600 enhanced font 'Liberation Mono,10' background "#002b36"
set output 'result.png'
COLORS = "red green blue"
STARTCOL = 2
ENDCOL = 4
set border 3 front linetype -1 linewidth 1.000 linecolor rgb "gold"

### titles and labels
set title "compounding" textcolor rgb "gold"
set xlabel "Year" 
set xlabel  offset character 0, -2, 0 font "" textcolor rgb "gold"  norotate
set ylabel "Value (EUR)" 
set ylabel textcolor rgb "gold"
set grid lc "gray"

####################################################################################
# Gnuplot 4.6 script for plotting multiple groups of 3 bars in a barchart.
# This part is static and can not be altered.
####################################################################################

### legend
set key bmargin center horizontal Left reverse noenhanced autotitles columnhead nobox textcolor rgb "gold"

PV = 40000
R = 2000
set xrange [0:60]
set yrange [40000:300000]
f(x) = PV * (1 + 0.05)**x + (R * (1+0.05)**x - 1) / 0.05
g(x) = PV * (1 + 0.06)**x + (R * (1+0.06)**x - 1) / 0.06
h(x) = PV * (1 + 0.07)**x + (R * (1+0.07)**x - 1) / 0.07
i(x) = PV * (1 + 0.08)**x + (R * (1+0.08)**x - 1) / 0.08
j(x) = PV * (1 + 0.09)**x + (R * (1+0.09)**x - 1) / 0.09
k(x) = PV * (1 + 0.10)**x + (R * (1+0.10)**x - 1) / 0.10
plot f(x) lw 3, g(x) lw 3, h(x) lw 3, i(x) lw 3, j(x) lw 3, k(x) lw 3
