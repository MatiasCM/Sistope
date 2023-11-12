CFLAGS = -Wall -g

all: lab2 broker worker

lab2: lab2.c
	gcc $(CFLAGS) -o lab2 lab2.c

broker: broker.c
	gcc $(CFLAGS) -o broker broker.c

worker: worker.c
	gcc $(CFLAGS) -o worker worker.c -lm

clear:
	rm -f lab2 broker worker