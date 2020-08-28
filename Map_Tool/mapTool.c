#include "../engine/core.h"
#include "../engine/tile.h"
#include "../engine/cmd_parser.h"

tDE_S_Core *g_pEngineCore;
SDL_Texture *g_pTileSet;
Uint16 g_nSelectTileIndex = 0;

Sint16 g_attrMap_Layer_1[225];
Sint16 g_worldMap_Layer_1[225];     // 15 x 15 크기
int size_WorldMap = sizeof(g_worldMap_Layer_1) / sizeof(Uint16);
int worldMap_LineNum;       //월드맵 변 칸 길이 변수

int tileSize = 32;

SDL_bool g_bDrawGrid = SDL_TRUE;
Sint16 g_nCurrentAttr = 0;

SDL_Rect g_rtTilePalette = {600, 0, 160, 250};
SDL_Rect g_rtWorldMap = {0, 0, 480, 480};

S_TextLable *g_pPreviewLabel;
S_TextLable *g_pHelpLabel;
// S_INPUT_TEXT *g_pInfoText;
S_BUTTON *g_pBtnExit;
S_BUTTON *g_pBtnSave;
S_BUTTON *g_pBtnLoad;
S_BUTTON *g_pBtnNew;

Uint16 nInputFSM = 0;

SDL_bool bLoop = SDL_TRUE;

void callbackExitButtonPush(S_BUTTON *pBtn) {
    SDL_Event _evt;
    _evt.type = SDL_QUIT;
    SDL_PushEvent(&_evt);
}

void callbackSaveButtonPush(S_BUTTON *pBtn) {
    char *pFileName = "MapToolSave.map";
    SDL_RWops *rw = SDL_RWFromFile(pFileName, "wb");
    SDL_RWwrite(rw, g_worldMap_Layer_1, sizeof(Uint16), size_WorldMap);
    SDL_RWclose(rw);
    printf("Save Complete \n");
}

void callbackLoadButtonPush(S_BUTTON *pBtn) {
    char *pFileName = "MapToolSave.map";
    SDL_RWops *rw = SDL_RWFromFile(pFileName, "rb");
    SDL_RWread(rw, g_worldMap_Layer_1, sizeof(Uint16), size_WorldMap);
    SDL_RWclose(rw);
    printf("Load Complete \n");
}

void callbackNewButtonPush(S_BUTTON *pBtn) {
    for (int i=0; i<size_WorldMap; i++) {
        g_attrMap_Layer_1[i] = -1;
        g_worldMap_Layer_1[i] = -1;
    }
}

void Render() {
    SDL_Renderer *pRender = g_pEngineCore->m_pRender;
      SDL_SetRenderDrawColor(pRender, 50, 50, 50, 0xff);
      SDL_RenderClear(pRender);

      //월드맵 기본 배경색
      SDL_Rect worldMap_BackGroundColor = {0, 0, 480, 480};
      SDL_SetRenderDrawColor(pRender, 0x1f, 0x1f, 0x1f, 0xf1);
      SDL_RenderFillRect(pRender, &worldMap_BackGroundColor);

      //미리보는 선택된 타일
      putTile(pRender, g_pTileSet, 21, 0, g_nSelectTileIndex, 16, 5, 2);

      g_pPreviewLabel->m_fpRender(g_pPreviewLabel, pRender);
      g_pHelpLabel->m_fpRender(g_pHelpLabel, pRender);
    //   g_pInfoText->m_pTextTexture
      g_pBtnSave->m_fpRender(g_pBtnSave, pRender);
      g_pBtnLoad->m_fpRender(g_pBtnLoad, pRender);
      g_pBtnExit->m_fpRender(g_pBtnExit, pRender);
      g_pBtnNew->m_fpRender(g_pBtnNew, pRender);

      //600,100
      {
        //팔래트 렌더링
        SDL_SetRenderDrawColor(pRender, 0xa1, 0xa1, 0xa1, 0x10);
        SDL_RenderDrawRect(pRender, &g_rtTilePalette);

        SDL_Rect _dstRt = {600, 100, 80 * 2, 80 * 2};
        SDL_RenderCopy(pRender, g_pTileSet, NULL, &_dstRt);
      }

      //월드맵 렌더링
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
}

void DoEvent() {
    SDL_Event _event;

    while (SDL_PollEvent(&_event)) {
        static char szBuf[225];

        g_pBtnSave->m_fpDoEvent(g_pBtnSave, &_event);
        g_pBtnLoad->m_fpDoEvent(g_pBtnLoad, &_event);
        g_pBtnExit->m_fpDoEvent(g_pBtnExit, &_event);
        g_pBtnNew->m_fpDoEvent(g_pBtnNew, &_event);

        switch (_event.type) {
        case SDL_MOUSEMOTION:
            {
                SDL_Point m_pt = {_event.motion.x, _event.motion.y};

                if (_event.button.button == 1) {
                    if (SDL_PointInRect(&m_pt, &g_rtWorldMap) && !g_bDrawGrid) {
                        putMap(m_pt.x / tileSize, m_pt.y / tileSize, g_nSelectTileIndex, g_worldMap_Layer_1, worldMap_LineNum);
                    }
                }
                else if (_event.button.button == 4 && !g_bDrawGrid) { //우 클릭
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

                if (_event.button.button == 1) { //마우스 좌클릭

                    if (SDL_PointInRect(&mousePt, &g_rtTilePalette)) { //팔레트 처리
                        int _x = (_event.motion.x - 600) / tileSize;
                        int _y = (_event.motion.y - 100) / tileSize;

                        if ((_x >= 0 && _y >= 0) && (_x < 5 && _y < 5)) {
                            g_nSelectTileIndex = _y * 5 + _x;
                        }
                    }
                    else if (SDL_PointInRect(&mousePt, &g_rtWorldMap)) { //월드맵 처리
                        int _x = (_event.motion.x) / tileSize;
                        int _y = (_event.motion.y) / tileSize;

                        if (g_bDrawGrid) { //속성 바꾸기
                            g_attrMap_Layer_1[_x + _y * worldMap_LineNum] = g_nCurrentAttr;

                            printf("%3d, %3d, %3d, %3d\r", _x, _y, g_attrMap_Layer_1[_x, +_y * worldMap_LineNum], g_worldMap_Layer_1[_x + _y * worldMap_LineNum]);
                        }
                        else {
                            putMap(_x, _y, g_nSelectTileIndex, g_worldMap_Layer_1, worldMap_LineNum);
                        }
                    }
                }
                else if (_event.button.button == 3) { //마우스 우클릭
                    if (SDL_PointInRect(&mousePt, &g_rtWorldMap)) {
                        int _x = (_event.motion.x) / tileSize;
                        int _y = (_event.motion.y) / tileSize;
                        putMap(_x, _y, -1, g_worldMap_Layer_1, worldMap_LineNum); //지우개
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
                        if (_event.key.keysym.sym == SDLK_RETURN) {
                            nInputFSM = 0; //대기 상태로 전이
                            // printf("\n%s\n",szBuf);
                            //cmd parser
                            {
                                parseCmd(szBuf);
                            }

                            szBuf[0] = 0x00; //문자열 클리어
                        }
                        else if (_event.key.keysym.sym == SDLK_BACKSPACE) {
                            int _len = strlen(szBuf);
                            szBuf[_len - 1] = 0x00;
                            printf("%s  \r", szBuf);
                        }
                    }
                    break;
                default:
                    break;
                }
            }
            break;
        case SDL_TEXTINPUT:
            if (nInputFSM == 1) {
                strcat(szBuf, _event.text.text);
                printf("%s  \r", szBuf);
            }
            break;
        case SDL_USEREVENT:
            if (strcmp(_event.user.data1, "brush change") == 0) {
                g_nCurrentAttr = _event.user.code;
                printf("change brush %d \n", g_nCurrentAttr);
            }
            else if (strcmp(_event.user.data1, "save") == 0) {
                char *pFileName = ((char *)_event.user.data1 + 16);

                Sint16 *map[2] = {g_worldMap_Layer_1, g_attrMap_Layer_1};
                saveMap(pFileName, map);

                printf("save file name %s \n", pFileName);
            }
            else if (strcmp(_event.user.data1, "load") == 0) {
                char *pFileName = ((char *)_event.user.data1 + 16);
                Sint16 *map[2] = {g_worldMap_Layer_1, g_attrMap_Layer_1};
                loadMap(pFileName, map);
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

int main(int argc, char *argv[]) {
    worldMap_LineNum = SDL_sqrt(size_WorldMap);     // 월드맵 변 칸 길이 (루트)

    memset(g_worldMap_Layer_1, -1, sizeof(Sint16) * size_WorldMap);
    memset(g_attrMap_Layer_1, 0, sizeof(Sint16) * size_WorldMap);

    SDL_Color infoTextColorFg = {200, 200, 200, 250};
    SDL_Color infoTextColorBg = {30, 30, 30, 250};

    // setup_cmd_parser(g_worldMap_Layer_1);
    g_pEngineCore = tDE_setup_1("MapTool", 800, 600, 0);
    g_pTileSet = tDE_util_loadTexture(g_pEngineCore, "../res/dungeon.png");

    g_pPreviewLabel = createLable(g_pEngineCore->m_pRender, 630, 50, 0, L"선택된 타일", g_pEngineCore->m_pDefaultFont);
    g_pHelpLabel = createLable(g_pEngineCore->m_pRender, 30, 570, 0, L"0 : Erase,   1 : Wall,   2 : Escape,   3 : Hidden Door,   4 : Switch,   5 : Timer Switch", g_pEngineCore->m_pDefaultFont);
    // g_pInfoText = myui_createInputText(g_pEngineCore->m_pRender, 250, 130, 300, 40, 0, g_pEngineCore->m_pDefaultFont, infoTextColorFg, infoTextColorBg);

    g_pBtnNew = createButton(g_pEngineCore->m_pRender, 20, 500, 96, 48, 3, L"New", g_pEngineCore->m_pDefaultFont, callbackNewButtonPush);
    g_pBtnSave = createButton(g_pEngineCore->m_pRender, 670, 300, 96, 48, 1, L"Save", g_pEngineCore->m_pDefaultFont, callbackSaveButtonPush);
    g_pBtnLoad = createButton(g_pEngineCore->m_pRender, 670, 400, 96, 48, 2, L"Load", g_pEngineCore->m_pDefaultFont, callbackLoadButtonPush);
    g_pBtnExit = createButton(g_pEngineCore->m_pRender, 670, 500, 96, 48, 3, L"종료", g_pEngineCore->m_pDefaultFont, callbackExitButtonPush);

    while (bLoop) {

        Render();

        DoEvent();
    }

    g_pBtnExit->m_fpDestroy(g_pBtnExit);
    g_pBtnLoad->m_fpDestroy(g_pBtnLoad);
    g_pBtnSave->m_fpDestroy(g_pBtnSave);
    g_pBtnNew->m_fpDestroy(g_pBtnNew);
    g_pHelpLabel->m_fpDestroy(g_pHelpLabel);
    g_pPreviewLabel->m_fpDestroy(g_pPreviewLabel);

    SDL_DestroyTexture(g_pTileSet);
    tDE_closeCore(g_pEngineCore);

    SDL_Quit();

    return 0;
}