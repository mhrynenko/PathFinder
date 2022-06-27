all: install

install: OBJECTS libmx/libmx.a
	clang -std=c11 -Wall -Werror -Wextra -Wpedantic -o pathfinder obj/*.o libmx/libmx.a

OBJECTS:
	mkdir -p obj
	clang -std=c11 -Wall -Werror -Wextra -Wpedantic -c src/*.c
	mv *.o obj/

libmx/libmx.a: 
	make -sC libmx

clean:
	make clean -sC libmx
	rm -rfd obj

uninstall:
	rm -rf pathfinder
	rm -rfd obj
	make uninstall -sC libmx

reinstall:
	make uninstall
	make
