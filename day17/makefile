ex01_all : ex01 ex01_run
ex02_all : ex02 ex02_run

ex01 : ex01.c
	gcc -o $@.exe $^
ex01_run : 
	ex01.exe

ex02 : ex02.c ../engine/core.c
	gcc -o $@.exe $^ -l mingw32 -l SDL2main -l SDL2 -l SDL2_image -l SDL2_ttf
ex02_run : 
	ex02.exe