all:
	$(CC) -std=c99 -mwindows -o a.exe kilo.c

clean:
	rm -f a.exe

