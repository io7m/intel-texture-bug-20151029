main: main.c
	cc -o main -W -Wall -pedantic -std=c99 main.c -lglfw -lGL

clean:
	rm -f main
