#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <string.h>

const Uint16 WINDOW_WIDTH = 640;
const Uint16 WINDOW_HEIGHT = 480;
SDL_Window *g_pWindow;
SDL_Renderer *g_pRenderer;

typedef struct
{
  SDL_Rect m_rect;
  SDL_Color m_color;
} _S_MyRect;

int doTokenize(char *szBuf, char (*szBufToken)[32]);

int main(int argc, char *argv[]) {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
  {
    printf("error initializing SDL: %s\n", SDL_GetError());
    return 1;
  }

  g_pWindow = SDL_CreateWindow("GAME", // creates a window
                               SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED,
                               WINDOW_WIDTH, WINDOW_HEIGHT, 0);

  if (!g_pWindow)
  {
    printf("error initializing SDL window: %s\n", SDL_GetError());
    return 1;
  }

  //Initialize SDL_mixer
  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
  {
    printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
    return 1;
  }

  Mix_Music *music = Mix_LoadMUS("../adv/sdl/res/nj4_2.ogg");

  if (!music)
  {
    printf("Failed to load music SDL_mixer Error: %s\n", Mix_GetError());
  }

  g_pRenderer = SDL_CreateRenderer(g_pWindow, -1, SDL_RENDERER_ACCELERATED);

  SDL_bool bLoop = SDL_TRUE;

  SDL_Rect _rects[32];
  SDL_Color _rect_colors[32];

  // _S_MyRect _myrect[32];

  Uint16 _rect_count = 0;

  Sint32 nInputFSM = 0;

  while (bLoop) {
    SDL_SetRenderDrawColor(g_pRenderer, 0, 0, 0, 1);
    SDL_RenderClear(g_pRenderer);

    for (int i = 0; i < _rect_count; i++) {
      SDL_SetRenderDrawColor(g_pRenderer, _rect_colors[i].r, _rect_colors[i].g, _rect_colors[i].b,
                             _rect_colors[i].a);
      // SDL_Rect _rt = {100, 100, 64, 64};
      SDL_RenderFillRect(g_pRenderer, &_rects[i]);
    }

    SDL_RenderPresent(g_pRenderer);

    static char strBuf[32] = {
        0,
    };
    SDL_Event _event;
    while (SDL_PollEvent(&_event)) {
      switch (_event.type) {
      case SDL_TEXTINPUT: {
        strcat(strBuf, _event.text.text);
        printf("%s \r", strBuf);
      }
        break;
      case SDL_KEYDOWN:
        {
            char sel_Menu;

        printf("1. Rect Addition\n");
        printf("2. Rect Delete\n");
        printf("=========================\n");
        sel_Menu = getchar();
        rewind(stdin);
        printf("\n");

        switch (sel_Menu) {
          case 1:
            {
                static char szTokens[16][32];
            if (_event.key.keysym.sym == SDLK_RETURN) {
              if (nInputFSM == 0) {
                printf("input msg : \n");
                SDL_StartTextInput();
                nInputFSM = 1;
              }
              else if (nInputFSM == 1) {
                //입력완료
                int _numToken = doTokenize(strBuf, szTokens);

                if (!strcmp(szTokens[0], "quit")) {
                  bLoop = SDL_FALSE;
                }
                else if (!strcmp(szTokens[0], "dr")) {
                  //dr 100 100 120 120 255 0 0 255
                  //dr x y w h r g b a
                  SDL_Rect _rt = {atoi(szTokens[1]), atoi(szTokens[2]),
                                  atoi(szTokens[3]), atoi(szTokens[4])};
                  Uint8 r = atoi(szTokens[5]);
                  Uint8 g = atoi(szTokens[6]);
                  Uint8 b = atoi(szTokens[7]);
                  Uint8 a = atoi(szTokens[8]);

                  SDL_Rect *pRect = &_rects[_rect_count];
                  *pRect = _rt;
                  SDL_Color *pColor = &_rect_colors[_rect_count];

                  pColor->r = r;
                  pColor->g = g;
                  pColor->b = b;
                  pColor->a = a;

                  _rect_count++;
                }
              }
            }
            else if (_event.key.keysym.sym == SDLK_BACKSPACE) {
                int _count = strlen(strBuf);

                 //버퍼에 값이 존재 할때만...
                if (_count > 0) {
                  _count--;
                  strBuf[_count] = 0x00;
                  printf("%s \r", strBuf);
                }
            }
            else if (!strcmp(szTokens[0], "pl")) {
              Mix_PlayMusic(music, -1);
            }
            
            //clear 
            strBuf[0] = 0x00;
            nInputFSM = 0;
            SDL_StopTextInput();
          }
        }
            }
            break;
          case 2:
            break;
          case SDL_QUIT:
            bLoop = SDL_FALSE;
            break;
          default:
            break;
        }
     }
  }

  SDL_DestroyRenderer(g_pRenderer);
  SDL_DestroyWindow(g_pWindow);
  SDL_Quit();
  return 0;
}