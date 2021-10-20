all:
	gcc -g *.c -o ./bin/program -lm

clean:
	rm ./bin/*