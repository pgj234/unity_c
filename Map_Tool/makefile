maptool : mapTool.c ../engine/core.c ../engine/tile.c ../engine/button.c ../engine/text_Lable.c ../engine/cmd_parser.c ../engine/util.c
	gcc -o $@ $^ -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf

game : game.c ../engine/core.c ../engine/tile.c ../engine/button.c ../engine/text_Lable.c ../engine/cmd_parser.c ../engine/util.c
	gcc -o $@ $^ -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -l SDL2_mixer