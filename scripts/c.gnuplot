set terminal pdfcairo
set output 'img/c.pdf'

# Títulos y ejes
set xlabel "Magnetización"
set ylabel "Frecuencia"

# Barras verticales tipo histograma
set style data histogram
set style histogram clustered gap 1
set style fill solid 0.5 border -1

# Generar histogramas con binning personalizado
bin_width = 10
bin(x,width) = width * floor(x/width + 0.5)

# Definir colores y estilos
set boxwidth bin_width
set style fill transparent solid .3 noborder
set key top left

# Dibujar los histogramas superpuestos
plot \
    'data/c_baja.txt' using (bin($1,bin_width)):(1) smooth freq with boxes lc rgb "blue" title "T^{*} = 2.2", \
    'data/c_alta.txt' using (bin($1,bin_width)):(1) smooth freq with boxes lc rgb "red" title "T^{*} = 2.3"
