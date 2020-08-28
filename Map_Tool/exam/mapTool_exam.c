#include "../engine/core.h"
// #include "../engine/ui_base.h"
#include "../engine/text_Lable.h"
#include "../engine/button.h"
// #include "../engine/input_text.h"
#include "../engine/tile.h"
#include "../engine/cmd_parser.h"

tDE_S_Core *g_pEngineCore;
SDL_Window *g_pWindow;
SDL_Texture *g_pTileSet;
TTF_Font *g_pFont;
S_TextLable *g_pPreviewLabel;
S_BUTTON *g_pBtnExit;
S_BUTTON *g_pBtnSave;
S_BUTTON *g_pBtnLoad;
S_BUTTON *g_pBtnNew;
// S_INPUT_TEXT *g_pInputText;
SDL_Texture *g_pCharTexture;

Uint16 g_worldMap_Layer_1[225];     // 15 x 15 크기
int size_WorldMap = sizeof(g_worldMap_Layer_1) / sizeof(Uint16);
int worldMap_LineNum;           //맵이 정사각형일 경우 맵의 한 변 길이 (루트)

void callbackExitButtonPush(S_BUTTON *pBtn) {
    SDL_Event _evt;
    _evt.type = SDL_QUIT;
    SDL_PushEvent(&_evt);
}

void callbackSaveButtonPush(S_BUTTON *pBtn) {
    char *pFileName = "Save_file.map";
    SDL_RWops *rw = SDL_RWFromFile(pFileName, "wb");
    SDL_RWwrite(rw, g_worldMap_Layer_1, sizeof(Uint16), size_WorldMap);
    SDL_RWclose(rw);
    printf("Save Complete \n");
}

void callbackLoadButtonPush(S_BUTTON *pBtn) {
    char *pFileName = "Save_file.map";
    SDL_RWops *rw = SDL_RWFromFile(pFileName, "rb");
    SDL_RWread(rw, g_worldMap_Layer_1, sizeof(Uint16), size_WorldMap);
    SDL_RWclose(rw);
    printf("Load Complete \n");
}

// // characters.png의 x 좌표 리턴
// int CharMove_X_Location(int x_num) {
//     static SDL_bool num_Plus = SDL_TRUE;

//     if (x_num == 0) {
//         num_Plus = SDL_TRUE;
//     }
//     else if (x_num == 2) {
//         num_Plus = SDL_FALSE;
//     }

//     if (num_Plus == SDL_TRUE) {
//         return ++x_num;
//     }
//     else {
//         return --x_num;
//     }
// }

// //캐릭 움직임
// void CharMoveAnimation(SDL_Renderer *pRender, SDL_Point char_Pos, int x_Location, int y_Location) {
//     SDL_Rect srcRt = {16 *(3 + x_Location), 16 * y_Location, 16, 16};
//     SDL_Rect dstRt = {char_Pos.x *32, char_Pos.y *32, 16 *2, 16 *2};
//     SDL_RenderCopy(pRender, g_pCharTexture, &srcRt, &dstRt);
// }

Uint16 g_nSelectTileIndex = 0;

int main(int argc, char *argv[]) {
    worldMap_LineNum = SDL_sqrt(size_WorldMap);     // 월드맵 변 칸 길이 (루트)

    for (int i=0; i< size_WorldMap; i++) {
        g_worldMap_Layer_1[i] = -1;
    }

    g_pEngineCore = tDE_setup_1("Game", 800, 600, 0);
    g_pTileSet = tDE_util_loadTexture(g_pEngineCore, "../res/basictiles.png");
    g_pCharTexture = tDE_util_loadTexture(g_pEngineCore, "../res/characters.png");

    TTF_Init();
    g_pFont = TTF_OpenFont("../res/font/NanumMyeongjo.ttf", 24);
    g_pPreviewLabel = myui_createLable(g_pEngineCore->m_pRender, 585, 50, 0, L"타일 미리보기", g_pFont);

    g_pBtnSave = myui_createButton(g_pEngineCore->m_pRender, 20, 540, 96, 48, 1, L"Save", g_pFont, callbackSaveButtonPush);
    g_pBtnLoad = myui_createButton(g_pEngineCore->m_pRender, 185, 540, 96, 48, 2, L"Load", g_pFont, callbackLoadButtonPush);
    g_pBtnExit = myui_createButton(g_pEngineCore->m_pRender, 350, 540, 96, 48, 3, L"종료", g_pFont, callbackExitButtonPush);

    SDL_bool click_Ing_Left = SDL_FALSE;
    SDL_bool click_Ing_Right = SDL_FALSE;

    //Initialize SDL_ttf
    if (TTF_Init() == -1) {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        return 0;
    }
    // else {
    //     printf("SDL_ttf initialize Ok!  \n");
    // }

    SDL_Point char_Position = {0, 0};
    int char_X_Num = 1;
    int char_Y_Location = 0;

    SDL_bool bLoop = SDL_TRUE;

    //게임 루프
    while (bLoop) {
        SDL_Renderer *pRender = g_pEngineCore->m_pRender;
        SDL_SetRenderDrawColor(pRender, 0, 0, 0, 1);    //전체 기본배경색
        SDL_RenderClear(pRender);

        SDL_SetRenderDrawColor(pRender, 30, 30, 30, 1); // 월드맵 기본배경색
        SDL_Rect worldBackRect = {0, 0, 32 * worldMap_LineNum, 32 * worldMap_LineNum};
        SDL_RenderFillRect(pRender, &worldBackRect);

        putTile(pRender, g_pTileSet, 20, 0, g_nSelectTileIndex);

        g_pPreviewLabel->m_fpRender(g_pPreviewLabel, pRender);
        g_pBtnSave->m_fpRender(g_pBtnSave, pRender);
        g_pBtnLoad->m_fpRender(g_pBtnLoad, pRender);
        g_pBtnExit->m_fpRender(g_pBtnExit, pRender);
        g_pBtnNew->m_fpRender(g_pBtnNew, pRender);
        // g_pInputText->m_base.m_fpRender(g_pInputText, g_pRenderer);
        
        {
            SDL_Rect dstRt = {530, 130, 128 * 2, 240 * 2};
            SDL_RenderCopy(pRender, g_pTileSet, NULL, &dstRt);
        }

    //render world map
    {
        for (int i=0; i<size_WorldMap; i++) {
            int _index = g_worldMap_Layer_1[i];

            if (_index != -1) {
                putTile(pRender, g_pTileSet, i%worldMap_LineNum, i/worldMap_LineNum, _index);
            }
        }
    }

    CharMoveAnimation(pRender, char_Position, char_X_Num, char_Y_Location);

    SDL_RenderPresent(pRender);

    SDL_Event _event;

    //좌클릭 상태 (월드맵 처리)
    {
        if (click_Ing_Left == SDL_TRUE) {
            int _x = (_event.motion.x) / 32;
            int _y = (_event.motion.y) / 32;

            if (_x < worldMap_LineNum && _y < worldMap_LineNum) {
                int _tileIndex = _y*worldMap_LineNum + _x;
                g_worldMap_Layer_1[_tileIndex] = g_nSelectTileIndex;
                printf("%4d%4d%4d\r", _x, _y), _tileIndex;
            }
        }
    }

    //우클릭 상태 (월드맵 타일 삭제)
    {
        if (click_Ing_Right == SDL_TRUE) {
            int _x = (_event.motion.x) /32;
            int _y = (_event.motion.y) /32;

            if (_x<worldMap_LineNum && _y<worldMap_LineNum) {
                int _tileIndex = _y*worldMap_LineNum + _x;
                g_worldMap_Layer_1[_tileIndex] = -1;
            }
        }
    }

        while (SDL_PollEvent(&_event)) {
            g_pBtnSave->m_base.m_fpDoEvent(g_pBtnSave, &_event);
            g_pBtnLoad->m_base.m_fpDoEvent(g_pBtnLoad, &_event);
            g_pBtnExit->m_base.m_fpDoEvent(g_pBtnExit, &_event);
            g_pBtnNew->m_base.m_fpDoEvent(g_pBtnNew, &_event);
            // g_pInputText->m_base.m_fpDoEvent(g_pInputText, &_event);

            switch (_event.type) {

                case SDL_MOUSEMOTION:
                {
                    // printf("%4d%4d\r", _event.motion.x, _event.motion.y);

                }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    {                                                                // 좌클릭
                        if (_event.button.button == 1) {
                                                                    // 팔레트 처리
                            int _x = (_event.motion.x - 530) /32;
                            int _y = (_event.motion.y - 130) /32;

                            if ((_x >= 0 && _y >= 0) && (_x<8 && _y<15)) {
                                g_nSelectTileIndex = _y * 8 + _x;
                            }

                            click_Ing_Left = SDL_TRUE;
                        }
                                                                // 우클릭
                        else if (_event.button.button == 3) {
                                click_Ing_Right = SDL_TRUE;
                        }
                    }
                    break;
                case SDL_KEYDOWN:
                    // printf("%d \n", _event.key.keysym.scancode);
                    // 82 Up, 81 Down, 80 Left, 79 Right
                    if (_event.key.keysym.scancode == 79) {         // 오른쪽
                        if (char_Position.x < worldMap_LineNum -1) {
                            char_Position.x += 1;
                        }

                        char_X_Num = CharMove_X_Location(char_X_Num);

                        char_Y_Location = 2;
                    }
                    else if (_event.key.keysym.scancode == 80) {        // 왼쪽
                        if (char_Position.x > 0) {
                            char_Position.x -= 1;
                        }

                        char_X_Num = CharMove_X_Location(char_X_Num);

                        char_Y_Location = 1;
                    }
                    else if (_event.key.keysym.scancode == 81) {        // 아래
                        if (char_Position.y < worldMap_LineNum -1) {
                            char_Position.y += 1;
                        }

                        char_X_Num = CharMove_X_Location(char_X_Num);

                        char_Y_Location = 0;
                    }
                    else if (_event.key.keysym.scancode == 82) {        // 위
                        if (char_Position.y > 0) {
                            char_Position.y -= 1;
                        }

                        char_X_Num = CharMove_X_Location(char_X_Num);

                        char_Y_Location = 3;
                    }
                    
                    // if (_event.key.keysym.sym == SDLK_RETURN) {
                    //     if (nInputFSM == 0) {
                    //         printf("input msg : ");
                    //         SDL_StartTextInput();
                    //         nInputFSM = 1;
                    //     }
                    //     else if (nInputFSM == 1) {
                    //         static char szTokens[8][32];

                    //         int _numToken = doTokenize(strBuf,szTokens);

                    //         if (strcmp(szTokens[0], "quit") == 0) {
                    //             bLoop = SDL_FALSE;
                    //         }
                    //         else if (strcmp(szTokens[0], "save") == 0) {

                    //             //save file.map
                    //             // char *pFileName = szTokens[1];
                    //             // SDL_RWops *rw = SDL_RWFromFile(pFileName, "wb");
                    //             // SDL_RWwrite(rw, g_worldMap_Layer_1, sizeof(Uint16), size_WorldMap);
                    //             // SDL_RWclose(rw);
                    //         }
                    //         else if (strcmp(szTokens[0], "load") == 0) {
                    //             //load file.map
                    //             // char *pFileName = szTokens[1];
                    //             // SDL_RWops *rw = SDL_RWFromFile(pFileName, "rb");
                    //             // SDL_RWread(rw, g_worldMap_Layer_1, sizeof(Uint16), size_WorldMap);
                    //             // SDL_RWclose(rw);
                    //         }

                    //         printf("\n%s\n", strBuf);
                    //         strBuf[0] = 0x00;
                    //         SDL_StopTextInput();
                    //         nInputFSM = 0;
                    //     }
                    // }
                    // break;
                case SDL_MOUSEBUTTONUP:
                    if (_event.button.button == 1) {        // 좌클릭 뗌
                        click_Ing_Left = SDL_FALSE;
                    }
                    else if (_event.button.button == 3) {     //우클릭 뗌
                        click_Ing_Right = SDL_FALSE;
                    }
                    break;
                case SDL_TEXTINPUT:
                    //strcat(strBuf, _event.text.text);
                    break;
                case SDL_QUIT:
                    bLoop = SDL_FALSE;
                    break;
                default:
                    break;
            }
        }
    }

    g_pBtnExit->m_base.m_fpDestroy(g_pBtnExit);
    g_pBtnLoad->m_base.m_fpDestroy(g_pBtnLoad);
    g_pBtnSave->m_base.m_fpDestroy(g_pBtnSave);
    g_pBtnNew->m_base.m_fpDestroy(g_pBtnNew);
    g_pPreviewLabel->m_base.m_fpDestroy(g_pPreviewLabel);
    TTF_CloseFont(g_pFont);

    SDL_DestroyTexture(g_pTileSet);

    tDE_closeCore(g_pEngineCore);

    SDL_Quit();

    return 0;
}