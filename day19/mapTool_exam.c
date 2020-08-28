#include "../engine/core.h"
#include "../engine/tile.h"
#include "../engine/cmd_parser.h"

tDE_S_Core *g_pEngineCore;
SDL_Texture *g_pTileSet;
Uint16 g_nSelectTileIndex = 0;

Sint16 g_attrMap_Layer_1[225];
Sint16 g_worldMap_Layer_1[225];     // 15 x 15 크기
int size_WorldMap = sizeof(g_worldMap_Layer_1) / sizeof(Uint16);
int worldMap_LineNum;

int tileSize = 32;

SDL_bool g_bDrawGrid = SDL_TRUE;
Sint16 g_nCurrentAttr = 0;

SDL_Rect g_rtTilePalette = {600, 0, 160, 350};
SDL_Rect g_rtWorldMap = {0, 0, 480, 480};

int main(int argc, char *argv[]) {
    worldMap_LineNum = SDL_sqrt(size_WorldMap);     // 월드맵 변 칸 길이 (루트)

    // for (int i = 0; i < size_WorldMap; i++) {
    //   g_worldMap_Layer_1[i] = -1;
    // }
    memset(g_worldMap_Layer_1, -1, sizeof(Sint16) * size_WorldMap);
    memset(g_attrMap_Layer_1, 0, sizeof(Sint16) * size_WorldMap);

    // setup_cmd_parser(g_worldMap_Layer_1);
    g_pEngineCore = tDE_setup_1("maptool", 800, 600, 0);
    g_pTileSet = tDE_util_loadTexture(g_pEngineCore, "../res/dungeon.png");

    SDL_bool bLoop = SDL_TRUE;

    while (bLoop) {
      SDL_Renderer *pRender = g_pEngineCore->m_pRender;
      SDL_SetRenderDrawColor(pRender, 0, 0, 0, 1);
      SDL_RenderClear(pRender);

      //select tile
      putTile(pRender, g_pTileSet, 21, 0, g_nSelectTileIndex, 16, 5, 2);

      //600,100
      {
        //팔래트 렌더링
        SDL_SetRenderDrawColor(pRender, 0xff, 0xff, 0xff, 0xff);
        // SDL_Rect _rtTemp;
        // _rtTemp.x = 600;
        // _rtTemp.y = 0;
        // _rtTemp.w = 160;
        // _rtTemp.h = 350;
        SDL_RenderDrawRect(pRender, &g_rtTilePalette);

        SDL_Rect _dstRt = {600, 100, 80 * 2, 80 * 2};
        SDL_RenderCopy(pRender, g_pTileSet, NULL, &_dstRt);
      }

      

      //render world map
      SDL_SetRenderDrawColor(pRender, 0xff, 0xff, 0xff, 0xff);
      // SDL_Rect _rtTemp;
      // _rtTemp.x = 0;
      // _rtTemp.y = 0;
      // _rtTemp.w = 480;
      // _rtTemp.h = 480;
      SDL_RenderDrawRect(pRender, &g_rtWorldMap);

      for (int i = 0; i < size_WorldMap; i++) {
          Sint16 _index = g_worldMap_Layer_1[i];

          if (_index != -1) {
              putTile(pRender, g_pTileSet, i % worldMap_LineNum, i / worldMap_LineNum, _index, 16, 5, 2);
          }
      }

      for (int i=0; i< size_WorldMap; i++) {
        SDL_SetRenderDrawBlendMode(pRender, SDL_BLENDMODE_BLEND);
          Sint16 _index = g_attrMap_Layer_1[i];
          if (_index == 1) {    //벽
              SDL_SetRenderDrawColor(pRender, 0xff, 0xff, 0xff, 0x80);
              SDL_Rect _rt = {(i%worldMap_LineNum)*tileSize, (i/worldMap_LineNum)*tileSize, tileSize, tileSize};
              SDL_RenderFillRect(pRender, &_rt);
          }
          else if (_index == 2) {   //비상구
              SDL_SetRenderDrawColor(pRender, 0x00, 0xff, 0x00, 0x80);
              SDL_Rect _rt = {(i%worldMap_LineNum)*tileSize, (i/worldMap_LineNum)*tileSize, tileSize, tileSize};
              SDL_RenderFillRect(pRender, &_rt);
          }
          else if (_index == 3) {   //숨겨진 문
              SDL_SetRenderDrawColor(pRender, 0xff, 0x00, 0x00, 0x80);
              SDL_Rect _rt = {(i%worldMap_LineNum)*tileSize, (i/worldMap_LineNum)*tileSize, tileSize, tileSize};
              SDL_RenderFillRect(pRender, &_rt);
          }
          else if (_index == 4) {   //스위치
              SDL_SetRenderDrawColor(pRender, 0xff, 0xff, 0x00, 0x80);
              SDL_Rect _rt = {(i%worldMap_LineNum)*tileSize, (i/worldMap_LineNum)*tileSize, tileSize, tileSize};
              SDL_RenderFillRect(pRender, &_rt);
          }
          else if (_index == 5) {   //타이머 스위치
              SDL_SetRenderDrawColor(pRender, 0x00, 0xff, 0xff, 0x80);
              SDL_Rect _rt = {(i%worldMap_LineNum)*tileSize, (i/worldMap_LineNum)*tileSize, tileSize, tileSize};
              SDL_RenderFillRect(pRender, &_rt);
          }
          
          SDL_SetRenderDrawBlendMode(pRender, SDL_BLENDMODE_NONE);
      }

      //그리드 그리기
      if(g_bDrawGrid) {
        for (int ix = 0; ix < worldMap_LineNum; ix++) {
          SDL_SetRenderDrawColor(pRender, 0xff, 0xff, 0x00, 0xff);
          SDL_RenderDrawLine(pRender, ix * tileSize, 0, ix * tileSize, 480);
        }
        for (int iy = 0; iy < worldMap_LineNum; iy++) {
          SDL_SetRenderDrawColor(pRender, 0xff, 0xff, 0x00, 0xff);
          SDL_RenderDrawLine(pRender, 0, iy*tileSize, 480, iy*tileSize);
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
                    SDL_Point m_pt = {_event.motion.x, _event.motion.y};
                
                    if (_event.button.button == 1) {
                        if (SDL_PointInRect(&m_pt, &g_rtWorldMap) && !g_bDrawGrid) {
                            putMap(m_pt.x / tileSize, m_pt.y / tileSize, g_nSelectTileIndex, g_worldMap_Layer_1, worldMap_LineNum);
                        }
                    }
                    else if (_event.button.button == 4 && !g_bDrawGrid) {     //우 클릭
                        if (SDL_PointInRect(&m_pt, &g_rtWorldMap)) {
                            putMap(m_pt.x / tileSize, m_pt.y / tileSize, -1, g_worldMap_Layer_1, worldMap_LineNum);
                        }
                    }
                }
                break;
              case SDL_MOUSEBUTTONDOWN:
                {
                  SDL_Point mousePt = {_event.motion.x, _event.motion.y};
                  printf("%8d\r", _event.button.button);
        
                  if (_event.button.button == 1) {    //마우스 좌클릭

                      if (SDL_PointInRect(&mousePt, &g_rtTilePalette)) {        //팔레트 처리
                          int _x = (_event.motion.x - 600) / tileSize;
                          int _y = (_event.motion.y - 100) / tileSize;

                          if ((_x >= 0 && _y >= 0) && (_x < 5 && _y < 5)) {
                              g_nSelectTileIndex = _y * 5 + _x;
                          }
                      }
                      else if (SDL_PointInRect(&mousePt, &g_rtWorldMap)) {      //월드맵 처리
                          int _x = (_event.motion.x) / tileSize;
                          int _y = (_event.motion.y) / tileSize;

                          if (g_bDrawGrid) {      //속성 바꾸기
                              g_attrMap_Layer_1[_x + _y * worldMap_LineNum] = g_nCurrentAttr;

                              printf("%3d, %3d, %3d, %3d\r", _x, _y, g_attrMap_Layer_1[_x, + _y * worldMap_LineNum], g_worldMap_Layer_1[_x + _y * worldMap_LineNum]);
                          }
                          else {
                              putMap(_x, _y, g_nSelectTileIndex, g_worldMap_Layer_1, worldMap_LineNum);
                          }
                      }
                  }
                  else if (_event.button.button == 3) {   //마우스 우클릭 
                      if (SDL_PointInRect(&mousePt, &g_rtWorldMap)) {
                          int _x = (_event.motion.x) / tileSize;
                          int _y = (_event.motion.y) / tileSize;
                          putMap(_x, _y, -1, g_worldMap_Layer_1, worldMap_LineNum);   //지우개
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
                            else if (_event.key.keysym.sym == SDLK_g) {
                                g_bDrawGrid = !g_bDrawGrid;
                            }
                            else if (_event.key.keysym.sym == SDLK_1) {
                                parseCmd("brush change 1");
                            }
                            else if (_event.key.keysym.sym == SDLK_2) {
                                parseCmd("brush change 2");
                            }
                            else if (_event.key.keysym.sym == SDLK_3) {
                                parseCmd("brush change 3");
                            }
                            else if (_event.key.keysym.sym == SDLK_4) {
                                parseCmd("brush change 4");
                            }
                            else if (_event.key.keysym.sym == SDLK_5) {
                                parseCmd("brush change 5");
                            }
                            else if (_event.key.keysym.sym == SDLK_0) {
                                parseCmd("brush change 0");
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
                if(nInputFSM == 1) {
                    strcat(szBuf,_event.text.text);
                    printf("%s  \r",szBuf);
                }
                break;
            case SDL_USEREVENT :
                if (strcmp(_event.user.data1, "brush change") == 0) {
                    g_nCurrentAttr = _event.user.code;
                    printf("change brush %d \n", g_nCurrentAttr);
                }
                else if (strcmp(_event.user.data1, "save") == 0) {
                    char *pFileName = ((char *)_event.user.data1 +16);

                    // SDL_RWops *rw = SDL_RWFromFile(pFileName, "wb");
                    // SDL_RWwrite(rw, g_worldMap_Layer_1, sizeof(Uint16), size_WorldMap);
                    // SDL_RWwrite(rw, g_attrMap_Layer_1, sizeof(Uint16), size_WorldMap);
                    // SDL_RWclose(rw);
                    Sint16 *map[2] = {g_worldMap_Layer_1, g_attrMap_Layer_1};
                    saveMap(pFileName, map);

                    printf("save file name %s \n", pFileName);
                }
                else if (strcmp(_event.user.data1, "load") == 0) {
                    char *pFileName = ((char *)_event.user.data1 +16);
                    Sint16 *map[2] = {g_worldMap_Layer_1, g_attrMap_Layer_1};
                    loadMap(pFileName, map);

                    // SDL_RWops *rw = SDL_RWFromFile(pFileName, "wb");
                    // SDL_RWwrite(rw, g_worldMap_Layer_1, sizeof(Uint16), size_WorldMap);
                    // SDL_RWwrite(rw, g_attrMap_Layer_1, sizeof(Uint16), size_WorldMap);
                    // SDL_RWclose(rw);
                }
                else if (strcmp(_event.user.data1, "new") == 0) {
                    memset(g_worldMap_Layer_1, -1, 256);
                    memset(g_attrMap_Layer_1, 0, 256);
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