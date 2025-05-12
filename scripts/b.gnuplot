set terminal pdfcairo size 6, 6
set output "img/b.pdf"

# Hacemos 4 gráficas
set multiplot layout 2, 2

# set logscale x
set grid

# Margen general
dy = .02
dx = .08
first_dx = .12
first_dy = .05
last_dx  = .02
last_dy  = .1
lenx = (1 - first_dx - last_dx - dx) / 2
leny = (1 - first_dy - last_dy - dy) / 2

# set xtics format "10^{%T}"
# set ytics format "10^{%T}"

# Arriba a la izquierda
set tmargin at screen 1 - first_dy
set bmargin at screen 1 - first_dy - leny
set lmargin at screen     first_dx
set rmargin at screen     first_dx + lenx
plot "data/b.txt" using 1:2 title "Magnetización absoluta"

# Arriba a la derecha
set tmargin at screen 1 - first_dy
set bmargin at screen 1 - first_dy - leny
set lmargin at screen     first_dx + lenx + dx
set rmargin at screen     first_dx + lenx + dx + lenx
plot "data/b.txt" using 1:3 title "Energía"

# Abajo a la izquierda
set tmargin at screen 1 - first_dy - leny - dy
set bmargin at screen 1 - first_dy - leny - dy - leny
set lmargin at screen     first_dx
set rmargin at screen     first_dx + lenx
plot "data/b.txt" using 1:4 title "Susceptibilidad"

# Abajo a la derecha
set tmargin at screen 1 - first_dy - leny - dy
set bmargin at screen 1 - first_dy - leny - dy - leny
set lmargin at screen     first_dx + lenx + dx
set rmargin at screen     first_dx + lenx + dx + lenx
plot "data/b.txt" using 1:5 title "Calor específico"
