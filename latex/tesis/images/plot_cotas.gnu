#set terminal wxt size 350,262 enhanced font 'Verdana,10' persist
# png
set terminal pngcairo size 600,600 enhanced font 'Verdana,10'
set output 'plot_cotas.png'

# Axes
set style line 101 lc rgb '#808080' lt 1
set border 3 back ls 101
set tics nomirror out scale 0.75
# Grid
set style line 102 lc rgb'#808080' lt 0 lw 1
set grid back ls 102
# Key
set key right bottom
# Line styles
set style line 1 linecolor rgb '#0060ad' linetype 1 linewidth 2 dashtype 7
set style line 2 linecolor rgb '#dd181f' linetype 1 linewidth 2 dashtype 8
# X range
set xrange [3:10]
f(x) = x - floor(sqrt(2*x + (1/4)) + (1/2)) #WEIRD PLOT TRY WITH MATHEMATICA
g(x) = x - floor(sqrt(2*x + (1/4)) - (1/2))

plot f(x) title 'Cota inferior' with lines linestyle 1, \
g(x) title 'Cota superior' with lines linestyle 2
