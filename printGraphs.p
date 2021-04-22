set term qt 0
set style line 5 lt rgb "cyan" lw 5 pt 5
set label "K=3.5e05"  font ",12" at 8,5
set xlabel "Generation Number"  font ",12"
set ylabel "Fitness"  font ",12"
plot 'output.txt' using 1:2 title 'Gen vs Avg Fitness' with linespoints, 'output.txt' using 1:3 title 'Gen vs Max Fitness' with linespoints
set term qt 1
unset label
set label "K=3.5e05" font ",15" at 45,10
set xlabel "Theta"  font ",15"
set ylabel "Singlet product yield (PhiS)"  font ",15"
plot 'phi.txt' using 1:2 title 'Phi vs Theta' with linespoints