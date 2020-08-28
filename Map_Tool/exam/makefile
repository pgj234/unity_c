mapTool_all : mapTool mapTool_run

mapTool : mapTool.c ../engine/tile.c ../engine/button.c ../engine/text_Lable.c ../engine/core.c ../engine/cmd_parser.c
	gcc -o $@.exe $^ -l mingw32 -l SDL2main -l SDL2 -l SDL2_image -l SDL2_ttf

mapTool_run : 
	./mapTool.exe