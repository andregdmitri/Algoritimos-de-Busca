1a: 
	gcc -g exercicio1a.c -lm -o 1a
	./1a

1b: 
	gcc -g exercicio1b.c -lm -o 1b
	./1b

1c: 
	gcc -g exercicio1c.c -lm -o 1c
	./1c

1d: 
	gcc -g exercicio1d.c -lm -o 1d
	./1d

2a: 
	gcc -g exercicio2a.c -lm -o 2a
	./2a

2b: 
	gcc -g exercicio2b.c -lm -o 2b
	./2b

2c: 
	gcc -g exercicio2c.c -lm -o 2c
	./2c

make clean:
	rm 1a 1b 1c 1d 2a 2b 2c