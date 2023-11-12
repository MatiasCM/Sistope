CFLAGS = -Wall -g

all: lab2 broker worker

lab2: lab2.c
	gcc $(CFLAGS) -o lab2 lab2.c -lm

broker: broker.c fbroker.c fbroker.h
	gcc $(CFLAGS) -o broker broker.c fbroker.c -lm

worker: worker.c
	gcc $(CFLAGS) -o worker worker.c fworker.c -lm

clear:
	rm -f lab2 broker worker