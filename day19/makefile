maptool : mapTool_exam.c ../engine/core.c ../engine/tile.c ../engine/cmd_parser.c
	gcc -o $@ $^ -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf

game : game.c ../engine/core.c ../engine/tile.c
	gcc -o $@ $^ -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf