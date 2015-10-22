####################################################################################
# Gnuplot 4.6 script for plotting multiple groups of 3 bars in a barchart.
####################################################################################

### plot setup
#set terminal pngcairo transparent enhanced font "inconsolata,10" fontscale 1.0 size 500, 350 
set terminal pngcairo size 800,600 enhanced font 'Liberation Mono,10' background "#002b36"
set output 'test.png'
COLORS = "red green gray"
STARTCOL=2
ENDCOL=4
GAPSIZE=5

NCOL=ENDCOL-STARTCOL+1
BOXWIDTH=1./(GAPSIZE+NCOL)

### legend
set key bmargin center horizontal Left reverse noenhanced autotitles columnhead nobox

### barchart layout - axis + grid
#set border 3 front linetype -1 linewidth 1.000
set boxwidth BOXWIDTH absolute
set style fill solid 1.00 border lt -1
set grid nopolar
set grid noxtics nomxtics ytics nomytics noztics nomztics \
 nox2tics nomx2tics noy2tics nomy2tics nocbtics nomcbtics
set grid layerdefault linetype 0 linewidth 1.000,  linetype 0 linewidth 1.000
set xzeroaxis linetype 0 linewidth 1.000
set yzeroaxis linetype 0 linewidth 1.000
set zzeroaxis linetype 0 linewidth 1.000

### Set tics and histograms
set style histogram clustered gap 4 title  offset character 2, 0.25, 0
set datafile missing '-'
set style data histograms
set xtics border in scale 0,0 nomirror rotate by -45  offset character 0, 0, 0 autojustify
set xtics  norangelimit font ",8"
set xtics ()
set ytics border in scale 0,0 mirror norotate  offset character 0, 0, 0 autojustify
set ztics border in scale 0,0 nomirror norotate  offset character 0, 0, 0 autojustify
set cbtics border in scale 0,0 mirror norotate  offset character 0, 0, 0 autojustify
set rtics axis in scale 0,0 nomirror norotate  offset character 0, 0, 0 autojustify

### titles and labels
set title "income\_vs\_expenses\n(Extra info here?)" 
#set xlabel "(Note: )" 
set xlabel  offset character 0, -2, 0 font "" textcolor lt -1 norotate
set ylabel "Value (EUR)" 

#x = 0.0
#i = 23
### plotting
plot for [COL=STARTCOL:ENDCOL] 'test.dat' u COL:xtic(1) w histogram title columnheader(COL) lc rgb word(COLORS, COL), \
    for [COL=STARTCOL:ENDCOL] 'test.dat' u (column(0)+BOXWIDTH*(COL-STARTCOL+GAPSIZE/2+1)-0.5):COL:COL notitle w labels
