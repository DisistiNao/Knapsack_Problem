set terminal png size 800, 600
set output '../graphics/bnb_graphic.png'

set title "Mochila 0-1 com Branch and Bound"
set xlabel "Instância N"
set ylabel "Tempo de Execução"

plot "../results/bnb_results.txt" using 1:2 with linespoints title "Solução"
