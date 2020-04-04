for method in 'i' 'u'
do
	for n in 10 100 1000
	do
		for i in 0 1 2 3 4 5 6 7 8 9
		do
			echo $method $n $i
			sudo perf stat -e L1-dcache-loads,L1-dcache-load-misses,branch-instructions,branch-misses ./atividade_1 $method $n &> ./out/$method''$n'_'$i.txt
			./out/convert < ./out/$method''$n'_'$i.txt > out/final/$method$n'_'$i.txt
		done
	done
done