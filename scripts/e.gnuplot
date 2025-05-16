set terminal pdfcairo size 7, 3
set output "img/e.pdf"

# Hacemos 4 gráficas
set multiplot layout 1, 2

# Margen general
dy = .05
dx = .03
first_dx = .1
first_dy = .1
last_dx  = .03
last_dy  = .15
lenx = (1 - first_dx - last_dx - dx) / 2
leny = (1 - first_dy - last_dy)

set yrange [0:1.1]
set logscale x

# Izquierda
set grid ytics xtics mxtics
set title "Magnetización"
set ylabel "Autocorrelacion normalizada"
set xlabel "Distancia [pasos MC]"
set xtics format "%g"
set xrange [1:3000]
set key bottom left
set tmargin at screen 1 - first_dy 
set bmargin at screen 1 - first_dy - leny
set lmargin at screen     first_dx
set rmargin at screen     first_dx + lenx
plot "data/e2m.txt"     with lines linewidth 2 title "T = 2",\
     "data/e22m.txt"    with lines linewidth 2 title "T = 2.2",\
     "data/e22676m.txt" with lines linewidth 2 title "T = 2.2676",\
     "data/e25m.txt"    with lines linewidth 2 title "T = 2.5",\
     "data/e33m.txt"    with lines linewidth 2 title "T = 3.3"

# Derecha
set title "Energía"
set xrange [1:300]
set ylabel ""
set ytics format ""
set key top right
set tmargin at screen 1 - first_dy
set bmargin at screen 1 - first_dy - leny
set lmargin at screen     first_dx + lenx + dx
set rmargin at screen     first_dx + lenx + dx + lenx
plot "data/e2e.txt"     with lines linewidth 2 title "T = 2",\
     "data/e22e.txt"    with lines linewidth 2 title "T = 2.2",\
     "data/e22676e.txt" with lines linewidth 2 title "T = 2.2676",\
     "data/e25e.txt"    with lines linewidth 2 title "T = 2.5",\
     "data/e33e.txt"    with lines linewidth 2 title "T = 3.3"

