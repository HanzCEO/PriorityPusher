build:
	$(CC) -Wall -pedantic -o prioritypusher utils.c todo.c main.c

debug:
	valgrind -s --leak-check=full ./prioritypusher

clean:
	rm -f `find -path '*~' | tr '\n' ' '`
