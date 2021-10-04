BASEGRIND=valgrind -s --leak-check=full ./prioritypusher
CCFLAGS=-DDEBUG -Wall -pedantic -g

build:
	$(CC) $(CCFLAGS) -o prioritypusher persistence.c utils.c todo.c main.c

debug:
	$(BASEGRIND)

debug-new:
	$(BASEGRIND) new < testnew.txt

debug-list:
	$(BASEGRIND) list

test-all: debug-new
	$(BASEGRIND) list
	$(BASEGRIND) list -d

clean:
	rm -f `find -path '*~' | tr '\n' ' '`
