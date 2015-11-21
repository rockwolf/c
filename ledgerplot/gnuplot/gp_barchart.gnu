####################################################################################
# Gnuplot 4.6 script for plotting multiple groups of 3 bars in a barchart.
# This part is dynamic and can be altered to influence the look of the graph.
####################################################################################

### main code
GAPSIZE = 3
NCOL = ENDCOL-STARTCOL+1
BOXWIDTH = 2./(GAPSIZE+NCOL)

### barchart layout
set style fill solid 0.75 border lt -1
#set boxwidth BOXWIDTH absolute

### Set tics and histograms
# Note: I can not use GAPSIZE below, for some reason... hardcoded value is used instead
set style histogram clustered gap 3 title offset character 1, 0.25, 0
set datafile missing '-'
set style data histograms
set xtics border in scale 0,0 nomirror rotate by -45  offset character 0, 0, 0 autojustify
set xtics  norangelimit font ",8"
set xtics ()
set ytics border in scale 0,0 mirror norotate  offset character 0, 0, 0 autojustify
set ztics border in scale 0,0 nomirror norotate  offset character 0, 0, 0 autojustify
set cbtics border in scale 0,0 mirror norotate  offset character 0, 0, 0 autojustify
set rtics axis in scale 0,0 nomirror norotate  offset character 0, 0, 0 autojustify
