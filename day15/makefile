ex01 : ex01.c 
	gcc -o $@ $^
ex02 : ex02.c ../engine/text_Lable.c ../engine/button.c ../engine/util.c
	gcc -o $@.exe $^ -l mingw32 -l SDL2main -l SDL2 -l SDL2_image -l SDL2_ttf
ex03 : ex03.c ../engine/button.c ../engine/text_Lable.c ../engine/input_text.c
	gcc -o $@.exe $^ -l mingw32 -l SDL2main -l SDL2 -l SDL2_image -l SDL2_ttf
ex04 : ex04.c
	gcc -o $@.exe $^ -l mingw32 -l SDL2main -l SDL2 -l SDL2_image