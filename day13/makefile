ex01 : ex01.c
	gcc -o $@.exe $^
ex02 : ex02.c
	gcc -o $@.exe $^
ex03 : ex03.c
	gcc -o $@.exe $^
ex04_rel : ex04.c
	gcc -o $@.exe $^
ex04_debug : ex04.c
	gcc -o $@.exe $^ -D __DEBUG__
ex05 : ex05.c
	gcc -o $@.exe $^
ex06 : ex06.c ../engine/util.c
	gcc -o $@.exe $^ -l mingw32 -l SDL2main -l SDL2
ex07 : ex07.c ../engine/util.c ../engine/button.c
	gcc -o $@.exe $^ -l mingw32 -l SDL2main -l SDL2
ex08 : ex08.c ../engine/util.c ../engine/button.c
	gcc -o $@.exe $^ -l mingw32 -l SDL2main -l SDL2