PARALLEL_FLAGS= -fopenmp
CFLAGS = -O0 $(PARALLEL_FLAGS)

clean:
	find . -maxdepth 1 -type f -executable -delete
	rm -f *.o
0: sum
	for i in 1000 100000 10000000; do \
		./sum $$i ; \
	done
1: sum1
	for i in 1000 100000 10000000; do \
		for j in 2 4 8; do \
			./sum $$i $$j ; \
		done \
	done
2: sum2
	for i in 1000 100000 10000000; do \
		for j in 2 4 8; do \
			./sum2 $$i $$j ; \
		done \
	done
3: sum3
	for i in 1000 100000 10000000; do \
		for j in 2 4 8; do \
			./sum3 $$i $$j ; \
		done \
	done

