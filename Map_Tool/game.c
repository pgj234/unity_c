#include "../engine/core.h"
#include "../engine/tile.h"
#include "../engine/cmd_parser.h"
#include <time.h>
// #include "../engine/layer.h"

tDE_S_Core *g_pEngineCore;
int worldmap_size = 225;

Sint16 g_WorldMap[225];
Sint16 g_AttrLayer[225];
Sint16 g_ObjLayer[225];

Sint16 g_WorldMap_obj_layer[225] = {0,};

int line_Num;

SDL_Texture *g_pTileSet;
SDL_Texture *g_pCharTexture;

S_BUTTON *g_pBtnExit;

SDL_Point g_PlayerPos;

int g_nGameLogicFsm = 0;

typedef struct __stage {
    char *fileName;
    SDL_Point m_respawnPos;
    char *introMsg;
} S_Stage_Info;

S_Stage_Info g_stage_info[] = {
    {"l1.map", {1, 1}, "here is silent room"},
    {"l2.map", {1, 2}, "here is more silent room"},
    {"end", {0, 0}, "you win game"}
};
int g_nCurrentStageNumber = 0;

SDL_bool keyTable[8] = {SDL_FALSE,};

SDL_bool door_Switch = SDL_FALSE;
SDL_bool timer_Switch = SDL_FALSE;

int char_X_Num = 1;
int char_Y_Location = 0;

void callbackExitButtonPush(S_BUTTON *pBtn) {
    SDL_Event _evt;
    _evt.type = SDL_QUIT;
    SDL_PushEvent(&_evt);
}

int Door_Timer() {
    static clock_t door_Time_Start = 0;
    static clock_t door_Time_End = 0;

    if (timer_Switch == SDL_FALSE && door_Switch == SDL_TRUE) {
        timer_Switch = SDL_TRUE;

        door_Time_Start = clock() / CLOCKS_PER_SEC;
    }

    if (door_Switch == SDL_TRUE) {
        door_Time_End = clock() / CLOCKS_PER_SEC;
    }

    printf("Timer : %d\n", door_Time_End - door_Time_Start);
    return door_Time_End - door_Time_Start;
}

int CharMove_X_Location(int x_num) {
    static SDL_bool num_Plus = SDL_TRUE;

    if (x_num == 0) {
        num_Plus = SDL_TRUE;
    }
    else if (x_num == 2) {
        num_Plus = SDL_FALSE;
    }

    if (num_Plus == SDL_TRUE) {
        return ++x_num;
    }
    else {
        return --x_num;
    }
}

void doGameLogic() {
    memset(g_ObjLayer, 0, worldmap_size * sizeof(Uint16));

    switch (g_nGameLogicFsm) {
            case 0 :
                printf("start game? (press key)\n");
                g_nGameLogicFsm = 1;
                g_nCurrentStageNumber = 0;
                break;
            case 1 :
                if (keyTable[0]) {
                    printf("here is silent room ... (press key)\n");
                    g_nGameLogicFsm = 2;
                }
                break;
            case 2 :
                if (keyTable[0]) {      //키가 눌러졌는지 검사
                    keyTable[0] = SDL_FALSE;
                    g_nGameLogicFsm = 5;
                }
                break;
            case 5 :
                if (keyTable[0]) {      //키가 눌러졌는지 검사
                    keyTable[0] = SDL_FALSE;

                    S_Stage_Info *pStgInfo = &g_stage_info[g_nCurrentStageNumber];
                    // printf("%s \n", pStgInfo->introMsg);

                    //게임 시작 준비
                    Sint16 *map[2] = {g_WorldMap, g_AttrLayer};
                    loadMap(pStgInfo->fileName, map);

                    //플레이어 정보 초기화
                    g_PlayerPos = pStgInfo->m_respawnPos;

                    g_nGameLogicFsm = 10;
                }
                break;
            case 10 :           // 플레이
                {
                    SDL_Point oldPos = g_PlayerPos;

                    //타이머 초과시 문 닫기
                    if (door_Switch == SDL_TRUE && Door_Timer() > 15) {
                        for (int i=0; i<worldmap_size; i++) {
                            if (g_AttrLayer[i] == 2) {
                                g_WorldMap[i] = 21;
                                g_AttrLayer[i] = 3; //벽으로 만들기

                                door_Switch = SDL_FALSE;
                                timer_Switch = SDL_FALSE;

                                break;
                            }
                        }
                    }

                    if (keyTable[1]) {      // left
                        keyTable[1] = SDL_FALSE;
                        g_PlayerPos.x--;
                    }
                    else if (keyTable[2]) {      // Right
                        keyTable[2] = SDL_FALSE;
                        g_PlayerPos.x++;
                    }
                    else if (keyTable[3]) {      // Up
                        keyTable[3] = SDL_FALSE;
                        g_PlayerPos.y--;
                    }
                    else if (keyTable[4]) {      // Down
                        keyTable[4] = SDL_FALSE;
                        g_PlayerPos.y++;
                    }

                    //충돌처리
                    Sint16 _attr = g_AttrLayer[g_PlayerPos.x + (g_PlayerPos.y*line_Num)];
                    if (_attr == 1 || _attr == 3) {   //벽
                        g_PlayerPos = oldPos;
                    }
                    else if (_attr == 2) {  //비상구
                        // g_PlayerPos = oldPos;
                        //다음 스테이지로 가는 처리
                        g_nGameLogicFsm = 11;
                    }
                    else if (_attr == 4) {  //스위치
                        for (int i=0; i<worldmap_size; i++) {
                            if (g_AttrLayer[i] == 3) {
                                g_WorldMap[i] = 22;
                                g_AttrLayer[i] = 2; //문으로 만들기
                                break;
                            }
                        }
                    }
                    else if (_attr == 5) {  //타이머 스위치
                        for (int i=0; i<worldmap_size; i++) {
                            if (g_AttrLayer[i] == 3) {
                                g_WorldMap[i] = 22;
                                g_AttrLayer[i] = 2; //문으로 만들기

                                door_Switch = SDL_TRUE;                                
                                break;
                            }
                        }
                    }

                    //속성 처리
                    {
                        g_ObjLayer[g_PlayerPos.y * line_Num + g_PlayerPos.x] =1;
                    }
                }
                break;
            case 11 :   //next
                g_nCurrentStageNumber++;
                S_Stage_Info *pInfoStg = &g_stage_info[g_nCurrentStageNumber];
                printf("%s \n", pInfoStg->introMsg);

                if (!strcmp("end", pInfoStg->fileName)) {
                    g_nGameLogicFsm = 20;
                }
                else {
                    g_nGameLogicFsm = 5;
                }
                break;
            case 20 :
                printf("game over\n");
                g_nGameLogicFsm++;
                break;
            case 21 :
                break;
        }
}

void renderGame() {
    SDL_SetRenderDrawColor(g_pEngineCore->m_pRender, 0x00, 0x40, 0xff, 0xff);
    SDL_RenderClear(g_pEngineCore->m_pRender);

    g_pBtnExit->m_fpRender(g_pBtnExit, g_pEngineCore->m_pRender);

    //월드맵 렌더링
    drawWorld(g_pEngineCore->m_pRender,
              g_pTileSet, 16, 5, 2, //타일셋 정보
              0, 0,                 //그려질 위치
              line_Num, g_WorldMap  //월드맵 정보
    );

    //오브젝트 레이어 렌더링
    {
        Sint16 *map = g_ObjLayer;

        for (int i = 0; i < worldmap_size; i++) {
            Sint16 _index = map[i];

            if (_index != -1) {
                if (_index == 1) {
                    //캐릭터 그리기
                    int x = i % line_Num;
                    int y = i / line_Num;
                    putTile(g_pEngineCore->m_pRender, g_pCharTexture, x, y, (char_X_Num +3) + (char_Y_Location *12), 16, 12, 2);
                }
            }
        }
    }

    SDL_RenderPresent(g_pEngineCore->m_pRender);
}

SDL_bool bLoop = SDL_TRUE;

void doEvent() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        g_pBtnExit->m_fpDoEvent(g_pBtnExit, &event);

        switch (event.type) {
        case SDL_KEYUP:
            if (event.key.keysym.sym == SDLK_SPACE) {
                keyTable[0] = SDL_TRUE;
            }
            else if (event.key.keysym.scancode == SDL_SCANCODE_LEFT) {
                keyTable[1] = SDL_TRUE;

                char_X_Num = CharMove_X_Location(char_X_Num);

                char_Y_Location = 1;
            }
            else if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
                keyTable[2] = SDL_TRUE;

                char_X_Num = CharMove_X_Location(char_X_Num);

                char_Y_Location = 2;
            }
            else if (event.key.keysym.scancode == SDL_SCANCODE_UP) {
                keyTable[3] = SDL_TRUE;

                char_X_Num = CharMove_X_Location(char_X_Num);

                char_Y_Location = 3;
            }
            else if (event.key.keysym.scancode == SDL_SCANCODE_DOWN) {
                keyTable[4] = SDL_TRUE;

                char_X_Num = CharMove_X_Location(char_X_Num);

                char_Y_Location = 0;
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

int main(int argc, char **argv) {
    line_Num = ((int)SDL_sqrt(worldmap_size));

    g_PlayerPos.x =1;
    g_PlayerPos.y =1;

    g_pEngineCore = tDE_setup_1("game", 600, 600, 0);
    g_pTileSet = tDE_util_loadTexture(g_pEngineCore, "../res/dungeon.png");
    g_pCharTexture = tDE_util_loadTexture(g_pEngineCore, "../res/characters.png");

    g_pBtnExit = createButton(g_pEngineCore->m_pRender, 490, 540, 96, 48, 3, L"종료", g_pEngineCore->m_pDefaultFont, callbackExitButtonPush);

    //Initialize SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        return 1;
    }

    Mix_Music *music = Mix_LoadMUS("bgm.ogg");

    if (!music) {
        printf("Failed to load music SDL_mixer Error: %s\n", Mix_GetError());
    }

    Mix_PlayMusic(music, -1);

    // loadMap("./l1.map", g_WorldMap);

    memset(g_WorldMap, -1, worldmap_size * sizeof(Uint16));

    while (bLoop) {
        //게임 로직
        doGameLogic();

        //렌더링
        renderGame();

        //이벤트 처리
        doEvent();
    }

    g_pBtnExit->m_fpDestroy(g_pBtnExit);
    SDL_DestroyTexture(g_pTileSet);
    tDE_closeCore(g_pEngineCore);

    return 0;
}