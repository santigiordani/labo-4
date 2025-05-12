set terminal pdfcairo size 6, 6
set output "img/a.pdf"

# Hacemos 6 gráficas
set multiplot layout 3, 2

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
leny = (1 - first_dy - last_dy - 2 * dy) / 3

# set xtics format "10^{%T}"
# set ytics format "10^{%T}"

set xrange [0:10000]
set xtics (0, 2000, 4000, 6000, 8000, 10000)

# Arriba a la izquierda
set ylabel "T^{*} = 2"
set title "Energía ⟨E⟩"
set xtics format ""
set yrange [-4000:0]
set tmargin at screen 1 - first_dy
set bmargin at screen 1 - first_dy - leny
set lmargin at screen     first_dx
set rmargin at screen     first_dx + lenx
plot "data/a_2_cold_E.txt" with lines linewidth .1 linecolor rgb "blue" title "Cold start",\
     "data/a_2_hot_E.txt"  with lines linewidth .1 linecolor rgb "red"  title "Hot start"

# Arriba a la derecha
unset ylabel
set title "Magnetización ⟨M⟩"
set yrange [-2000:2000]
set tmargin at screen 1 - first_dy
set bmargin at screen 1 - first_dy - leny
set lmargin at screen     first_dx + lenx + dx
set rmargin at screen     first_dx + lenx + dx + lenx
plot "data/a_2_cold_M.txt" with lines linewidth .1 linecolor rgb "blue" title "Cold start",\
     "data/a_2_hot_M.txt"  with lines linewidth .1 linecolor rgb "red"  title "Hot start"

# Medio a la izquierda
unset title
set ylabel "T^{*} = 2.2676"
set yrange [-3000:0]
set tmargin at screen 1 - first_dy - leny - dy
set bmargin at screen 1 - first_dy - leny - dy - leny
set lmargin at screen     first_dx
set rmargin at screen     first_dx + lenx
plot "data/a_22_cold_E.txt" with lines linewidth .1 linecolor rgb "blue" title "Cold start",\
     "data/a_22_hot_E.txt"  with lines linewidth .1 linecolor rgb "red"  title "Hot start"

# Medio a la derecha
unset ylabel
set yrange [-2000:2000]
set tmargin at screen 1 - first_dy - leny - dy
set bmargin at screen 1 - first_dy - leny - dy - leny
set lmargin at screen     first_dx + lenx + dx
set rmargin at screen     first_dx + lenx + dx + lenx
plot "data/a_22_cold_M.txt" with lines linewidth .1 linecolor rgb "blue" title "Cold start",\
     "data/a_22_hot_M.txt"  with lines linewidth .1 linecolor rgb "red"  title "Hot start"

# Abajo a la izquierda
set yrange [-2000:0]
set ylabel "T^{*} = 3.3"
set xtics format "%g"
set xlabel "Número de pasos MC"
set tmargin at screen 1 - first_dy - leny - dy - leny - dy
set bmargin at screen 1 - first_dy - leny - dy - leny - dy - leny
set lmargin at screen     first_dx
set rmargin at screen     first_dx + lenx
plot "data/a_33_cold_E.txt" with lines linewidth .1 linecolor rgb "blue" title "Cold start",\
     "data/a_33_hot_E.txt"  with lines linewidth .1 linecolor rgb "red"  title "Hot start"

# Abajo a la derecha
unset ylabel
set yrange [-2000:2000]
set tmargin at screen 1 - first_dy - leny - dy - leny - dy
set bmargin at screen 1 - first_dy - leny - dy - leny - dy - leny
set lmargin at screen     first_dx + lenx + dx
set rmargin at screen     first_dx + lenx + dx + lenx
plot "data/a_33_cold_M.txt" with lines linewidth .1 linecolor rgb "blue" title "Cold start",\
     "data/a_33_hot_M.txt"  with lines linewidth .1 linecolor rgb "red"  title "Hot start"
