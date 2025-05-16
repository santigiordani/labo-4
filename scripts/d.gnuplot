set terminal pdfcairo
set output "img/d.pdf"

set grid

set xrange [2.24:2.29]
set ylabel "Cumulantes de Binder"
set xlabel "Temperatura"
plot "data/d3_chico.txt"   using 1:6 with linespoints pointsize 0.5 title "n = 10",\
     "data/d3_mediano.txt" using 1:6 with linespoints pointsize 0.5 title "n = 20",\
     "data/d3_grande.txt"  using 1:6 with linespoints pointsize 0.5 title "n = 40"