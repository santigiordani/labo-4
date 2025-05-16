set terminal pdfcairo size 8, 6
set output "img/b_bis.pdf"

# Hacemos 4 gráficas
set multiplot layout 2, 2

# Margen general
dy = .05
dx = .1
first_dx = .08
first_dy = .05
last_dx  = .03
last_dy  = .1
lenx = (1 - first_dx - last_dx - dx) / 2
leny = (1 - first_dy - last_dy - dy) / 2

set xrange [2.25:2.29]

# Arriba a la izquierda
set ylabel "Magnetización absoluta"
set xtics format ""
set grid
set tmargin at screen 1 - first_dy
set bmargin at screen 1 - first_dy - leny
set lmargin at screen     first_dx
set rmargin at screen     first_dx + lenx
plot "data/b_chico.txt"   using 1:($2 / 100)  with linespoints linewidth 1 title "n = 10",\
     "data/b_mediano.txt" using 1:($2 / 400)  with linespoints linewidth 1 title "n = 20",\
     "data/b_grande.txt"  using 1:($2 / 1600) with linespoints linewidth 1 title "n = 40"

# Arriba a la derecha
set ylabel "Energía"
set tmargin at screen 1 - first_dy
set bmargin at screen 1 - first_dy - leny
set lmargin at screen     first_dx + lenx + dx
set rmargin at screen     first_dx + lenx + dx + lenx
plot "data/b_chico.txt"   using 1:($3 / 100)  with linespoints linewidth 1 title "n = 10",\
     "data/b_mediano.txt" using 1:($3 / 400)  with linespoints linewidth 1 title "n = 20",\
     "data/b_grande.txt"  using 1:($3 / 1600) with linespoints linewidth 1 title "n = 40"

# Abajo a la izquierda
set ylabel "Susceptibilidad"
set xlabel "Temperatura reducida"
set xtics format "%g"
set tmargin at screen 1 - first_dy - leny - dy
set bmargin at screen 1 - first_dy - leny - dy - leny
set lmargin at screen     first_dx
set rmargin at screen     first_dx + lenx
plot "data/b_chico.txt"   using 1:($4 / 100  / 100)  with linespoints linewidth 1 title "n = 10",\
     "data/b_mediano.txt" using 1:($4 / 400  / 400)  with linespoints linewidth 1 title "n = 20",\
     "data/b_grande.txt"  using 1:($4 / 1600 / 1600) with linespoints linewidth 1 title "n = 40"

# Abajo a la derecha
set ylabel "Calor específico"
set tmargin at screen 1 - first_dy - leny - dy
set bmargin at screen 1 - first_dy - leny - dy - leny
set lmargin at screen     first_dx + lenx + dx
set rmargin at screen     first_dx + lenx + dx + lenx
plot "data/b_chico.txt"   using 1:($5 / 100)  with linespoints linewidth 1 title "n = 10",\
     "data/b_mediano.txt" using 1:($5 / 400)  with linespoints linewidth 1 title "n = 20",\
     "data/b_grande.txt"  using 1:($5 / 1600) with linespoints linewidth 1 title "n = 40"
