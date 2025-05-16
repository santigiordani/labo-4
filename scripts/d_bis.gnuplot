set terminal pdfcairo size 7, 3
set output "img/d_bis.pdf"

# Hacemos 4 gráficas
set multiplot layout 1, 2

# Margen general
dy = .05
dx = .1
first_dx = .1
first_dy = .05
last_dx  = .03
last_dy  = .15
lenx = (1 - first_dx - last_dx - dx) / 2
leny = (1 - first_dy - last_dy)

# Variables
Tc = 2.2676
beta = 1/8
gamma = 7/4

# Izquierda
set grid
set ylabel "Magnetización absoluta"
set xlabel "Temperatura reducida"
set xtics format "%g"
set yrange [0.3:1.1]
set xrange [2:2.5]
set key bottom left
set tmargin at screen 1 - first_dy 
set bmargin at screen 1 - first_dy - leny
set lmargin at screen     first_dx
set rmargin at screen     first_dx + lenx
plot "data/b_chico.txt"   using 1:($2 / 100)  with linespoints linewidth 1 title "n = 10",\
     "data/b_mediano.txt" using 1:($2 / 400)  with linespoints linewidth 1 title "n = 20",\
     "data/b_grande.txt"  using 1:($2 / 1600) with linespoints linewidth 1 title "n = 40",\
     (Tc - x)**(.125) linewidth 2 title "(T_{c} - T)^{0.125}"

# Derecha
set ylabel "Susceptibilidad"
unset yrange
set key top left
set tmargin at screen 1 - first_dy
set bmargin at screen 1 - first_dy - leny
set lmargin at screen     first_dx + lenx + dx
set rmargin at screen     first_dx + lenx + dx + lenx
plot "data/b_chico.txt"   using 1:($4/(100 * 100))   with linespoints linewidth 1 title "n = 10",\
     "data/b_mediano.txt" using 1:($4/(400 * 400))   with linespoints linewidth 1 title "n = 20",\
     "data/b_grande.txt"  using 1:($4/(1600 * 1600)) with linespoints linewidth 1 title "n = 40",\
     abs((x - Tc))**(-1.75) / (750000000) linewidth 2 title "(T - T_{c})^{-1.75}"

     #"data/b_grande.txt"  using 1:($4/(1600 * 1600)) with lines linewidth 2 title "n = 40",\
