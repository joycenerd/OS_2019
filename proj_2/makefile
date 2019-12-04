all: sched_test

sched_test: sched_test.o
	gcc sched_test.o -pthread -o sched_test

sched_test.o: sched_test.c
	gcc -pthread -c sched_test.c