set terminal png size 800, 600
set output '../graphics/backtrack_graphic.png'

set title "Mochila 0-1 com Backtrack"
set xlabel "Instância N"
set ylabel "Tempo de Execução"

plot "../results/backtrack_results.txt" using 1:2 with linespoints title "Solução"
