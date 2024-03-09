all: src/main.c src/impl.c
	gcc src/main.c src/impl.c -o build/main -funsigned-char -ansi
install: all
	cp build/main /usr/bin/cfd
