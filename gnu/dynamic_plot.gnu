set terminal png size 800, 600
set output 'dynamic_graphic.png'

set title "Mochila 0-1 com Programação Dinâmica"
set xlabel "Instância N"
set ylabel "Tempo de Execução"

plot "../dynamic_results.txt" using 1:2 with linespoints title "Programação Dinâmica"
