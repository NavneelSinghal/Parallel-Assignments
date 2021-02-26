PARALLEL_FLAGS = -fopenmp
CFLAGS = -O0 $(PARALLEL_FLAGS)

clean:
	find . -maxdepth 1 -type f -executable -delete
	rm -f *.o
0: 2018CS10360
	for i in 1000 100000 10000000; do \
		for j in 2 4 8; do \
			./2018CS10360 0 $$i $$j ; \
		done \
	done
1: 2018CS10360
	for i in 1000 100000 10000000; do \
		for j in 2 4 8; do \
			./2018CS10360 1 $$i $$j ; \
		done \
	done
