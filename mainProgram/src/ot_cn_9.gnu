set terminal pngcairo
set output "ot_cn9.png"
unset key
#set xrange[-40000:200000]
#set yrange[130:0]
set xlabel "Crossing Number"
set ylabel "#Thrackles Max"
plot  "cnot9_cn.out" using 2:3 pt 7,\
      "plot_validot9.dat" pt 6 ps 2
