#include "../engine/core.h"
#include "../engine/tile.h"
#include "../engine/cmd_parser.h"

tDE_S_Core *g_pEngineCore;
SDL_Texture *g_pTileSet;
Uint16 g_nSelectTileIndex = 0;

Uint16 g_worldMap_Layer_1[225];     // 15 x 15 크기
int size_WorldMap = sizeof(g_worldMap_Layer_1) / sizeof(Uint16);
int worldMap_LineNum;

SDL_bool g_bDrawGrid = SDL_TRUE;

int main(int argc, char *argv[]) {
    worldMap_LineNum = SDL_sqrt(size_WorldMap);     // 월드맵 변 칸 길이 (루트)

    for (int i = 0; i < size_WorldMap; i++) {
      g_worldMap_Layer_1[i] = -1;
    }

    g_pEngineCore = tDE_setup_1("maptool", 800, 600, 0);
    g_pTileSet = tDE_util_loadTexture(g_pEngineCore, "../res/dungeon.png");

    SDL_bool bLoop = SDL_TRUE;

    while (bLoop) {
      SDL_Renderer *pRender = g_pEngineCore->m_pRender;
      SDL_SetRenderDrawColor(pRender, 0, 0, 0, 1);
      SDL_RenderClear(pRender);

      //select tile
      putTile(pRender, g_pTileSet, 21, 0, g_nSelectTileIndex, 16, 5, 2);

      //440,100
      {
        //팔래트 랜디링
        SDL_SetRenderDrawColor(pRender, 0xff, 0xff, 0xff, 0xff);
        SDL_Rect _rtTemp;
        _rtTemp.x = 600;
        _rtTemp.y = 0;
        _rtTemp.w = 160;
        _rtTemp.h = 350;
        SDL_RenderDrawRect(pRender, &_rtTemp);

        SDL_Rect _dstRt = {600, 100, 80 * 2, 80 * 2};
        SDL_RenderCopy(pRender, g_pTileSet, NULL, &_dstRt);
      }

      

      //render world map
      {
        SDL_SetRenderDrawColor(pRender, 0xff, 0xff, 0xff, 0xff);
        // SDL_RenderDrawLine(pRender,0,0,256,0);
        // SDL_RenderDrawLine(pRender,256,0,256,256);
        // SDL_RenderDrawLine(pRender,256,256,0,256);
        // SDL_RenderDrawLine(pRender,0,256,0,0);
        SDL_Rect _rtTemp;
        _rtTemp.x = 0;
        _rtTemp.y = 0;
        _rtTemp.w = 480;
        _rtTemp.h = 480;
        SDL_RenderDrawRect(pRender, &_rtTemp);

        for (int i = 0; i < size_WorldMap; i++) {
            Sint16 _index = g_worldMap_Layer_1[i];

            if (_index != -1) {
                putTile(pRender, g_pTileSet, i % worldMap_LineNum, i / worldMap_LineNum, _index, 16, 5, 2);
            }
        }
      }

      SDL_RenderPresent(pRender);

      SDL_Event _event;
    
      while (SDL_PollEvent(&_event)) {
          static char szBuf[225];
          static Uint16 nInputFSM = 0;

          switch (_event.type) {
              case SDL_MOUSEMOTION:
                {
                  printf("%4d%4d\r", _event.motion.x, _event.motion.y);
                }
                break;
              case SDL_MOUSEBUTTONDOWN:
                {
                  printf("%8d\r", _event.button.button);
        
                  if (_event.button.button == 1) {    //마우스 좌클릭
                      //팔래트처리
                      {
                      int _x = (_event.motion.x - 600) / 32;
                      int _y = (_event.motion.y - 100) / 32;

                      if ((_x >= 0 && _y >= 0) && (_x < 5 && _y < 5)) {
                          g_nSelectTileIndex = _y * 5 + _x;
                      }

                      // printf("%4d%4d\r", _x, _y);
                      }
                    //월드멥처리
                    {
                    int _x = (_event.motion.x) / 32;
                    int _y = (_event.motion.y) / 32;

                    if (_x < worldMap_LineNum && _y < worldMap_LineNum) {
                        int _tileIndex = _y * worldMap_LineNum + _x;
                        // printf("%8d \r",_tileIndex);
                        g_worldMap_Layer_1[_tileIndex] = g_nSelectTileIndex;
                        printf("%4d%4d%4d\r", _x, _y, _tileIndex);
                      }
                    }
                  }
                  else if (_event.button.button == 3) {   //마우스 우클릭 
                      {
                        int _x = (_event.motion.x) / 32;
                        int _y = (_event.motion.y) / 32;

                        if (_x < worldMap_LineNum && _y < worldMap_LineNum) {
                            int _tileIndex = _y * worldMap_LineNum + _x;
                            g_worldMap_Layer_1[_tileIndex] = -1;
                        }
                      }
                  }
                }
                break;
            case SDL_KEYDOWN:
            //printf("%d \n", _event.key.keysym.scancode);
                {          
                    switch (nInputFSM) {
                        case 0: //대기상태
                          {
                            if (_event.key.keysym.sym == SDLK_RETURN) {
                                printf("input cmd => \n");
                                nInputFSM = 1; //입력 상태로 전이
                            }
                          }
                          break;
                        case 1: //입력 상태
                          {
                            if(_event.key.keysym.sym == SDLK_RETURN) {
                                nInputFSM = 0; //대기 상태로 전이 
                                // printf("\n%s\n",szBuf);
                                //cmd parser
                                {
                                    parseCmd(szBuf);
                                }

                                szBuf[0] = 0x00;  //문자열 클리어 
                            }            
                            else if(_event.key.keysym.sym == SDLK_BACKSPACE) {
                                int _len = strlen(szBuf);
                                szBuf[_len-1] = 0x00;
                                printf("%s  \r",szBuf);
                            }
                          }
                          break;          
                        default:
                          break;
                    }
                }
                break;
            case SDL_TEXTINPUT:
                {
                  if(nInputFSM == 1) {
                    strcat(szBuf,_event.text.text);
                    printf("%s  \r",szBuf);
                  }
                }
                break;
            case SDL_QUIT:
                bLoop = SDL_FALSE;
                break;
            default:
                break;
          }
      }
    }

    SDL_DestroyTexture(g_pTileSet);
    tDE_closeCore(g_pEngineCore);

    SDL_Quit();
  
    return 0;
}