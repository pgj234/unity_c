#include "../engine/core.h"
#include "../engine/tile.h"
#include "../engine/cmd_parser.h"
#include "../engine/layer.h"

tDE_S_Core *g_pEngineCore;
int worldmap_size = 225;

Sint16 g_WorldMap[225];

Sint16 g_WorldMap_obj_layer[225] = {0,};

int line_Num;

SDL_Texture *g_pTileSet;
SDL_Texture *g_pTileSet2;

SDL_Point g_PlayerPos;

int main(int argc, char **argv) {
    line_Num = ((int)SDL_sqrt(worldmap_size));

    g_PlayerPos.x =1;
    g_PlayerPos.y =1;

    g_pEngineCore = tDE_setup_1("game", 800, 600, 0);
    g_pTileSet = tDE_util_loadTexture(g_pEngineCore, "../res/dungeon.png");
    g_pTileSet2 = tDE_util_loadTexture(g_pEngineCore, "../res/gb_ft_rpg_tile_set.png");

    loadMap("./l1.map", g_WorldMap);

    SDL_bool bLoop = SDL_TRUE;

    while (bLoop) {
        SDL_SetRenderDrawColor(g_pEngineCore->m_pRender, 0x00, 0x00, 0xff, 0xff);
        SDL_RenderClear(g_pEngineCore->m_pRender);

        //월드맵 그리기
        drawWorld(g_pEngineCore->m_pRender,
                g_pTileSet, 16, 5, 2, //타일셋 정보
                0, 0,                 //그려질 위치
                line_Num, g_WorldMap         //월드맵 정보
        );

        // Object layer 재설정
        {
            memset(g_WorldMap_obj_layer, 0, worldmap_size*sizeof(Uint16));
            g_WorldMap_obj_layer[g_PlayerPos.y*line_Num + g_PlayerPos.x] = 1;
        }

        Sint16 *map = g_WorldMap_obj_layer;

        for (int i=0; i<worldmap_size; i++) {
            Sint16 _index = map[i];

            if (_index != -1) {
                if (_index == 1) {
                    //캐릭터 그리기
                    int x = i%line_Num;
                    int y = i/line_Num;
                    putTile(g_pEngineCore->m_pRender, g_pTileSet2, x, y, 190, 16, 10, 2);
                }
            }
        }

        SDL_RenderPresent(g_pEngineCore->m_pRender);

        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_KEYUP:
                    {
                        SDL_Point _oldPos = g_PlayerPos;

                        if (event.key.keysym.scancode == SDL_SCANCODE_LEFT) {
                            g_PlayerPos.x--;
                        }
                        else if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
                            g_PlayerPos.x++;
                        }
                        else if (event.key.keysym.scancode == SDL_SCANCODE_UP) {
                            g_PlayerPos.y--;
                        }
                        else if (event.key.keysym.scancode == SDL_SCANCODE_DOWN) {
                            g_PlayerPos.y++;
                        }

                        Sint16 _attr = g_WorldMap_attr_layer[g_PlayerPos.x + (g_PlayerPos.y * 15)];

                        if (_attr == 1) {   //갈 수 없는 곳
                            g_PlayerPos = _oldPos;
                        }
                        else if (_attr == 2) {
                            //다음 레벨로
                            g_PlayerPos.x =1;
                            g_PlayerPos.y =1;
                            loadMap("l2.map", g_WorldMap);
                        }
                    }
                    break;
                case SDL_QUIT:
                    bLoop = SDL_FALSE;
                    break;
            }
        }
    }

    SDL_DestroyTexture(g_pTileSet);
    tDE_closeCore(g_pEngineCore);

    return 0;
}