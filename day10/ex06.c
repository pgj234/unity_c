#include <stdio.h>
#include <SDL2/SDL.h>
#include <string.h>

const Uint16 WINDOW_WIDTH = 640;
const Uint16 WINDOW_HEIGHT = 480;
SDL_Window *gWindow;

int main(int argc, char *argv[])
{
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
  {
    printf("error initializing SDL: %s\n", SDL_GetError());
    return 1;
  }

  gWindow = SDL_CreateWindow("GAME", // creates a window
                             SDL_WINDOWPOS_CENTERED,
                             SDL_WINDOWPOS_CENTERED,
                             WINDOW_WIDTH, WINDOW_HEIGHT, 0);

  if (!gWindow)
  {
    printf("error initializing SDL window: %s\n", SDL_GetError());
    return 1;
  }

  static char strBuf[32] = {0,};

  SDL_bool bLoop = SDL_TRUE;
  int nInputFSM = 0;    //0 -> ready, 1 -> text input

  while (bLoop)
  {
    SDL_Event _event;
    while (SDL_PollEvent(&_event))
    {
      switch (_event.type)
      {
      case SDL_KEYDOWN:
        //printf("%d %d\n", _event.key.keysym.scancode, _event.key.keysym.sym);
        if (_event.key.keysym.sym == SDLK_RETURN) {
            if (nInputFSM == 0) {
                printf("input msg : ");
                SDL_StartTextInput();
                nInputFSM = 1;
            }
            else if (nInputFSM == 1) {
                if (strcmp(strBuf, "quit") ==0) {
                    bLoop = SDL_FALSE;
                }
                
                printf("\n%s \n", strBuf);
                strBuf[0] = 0x00;
                SDL_StopTextInput();
                nInputFSM = 0;
            }
        }
        else if (_event.key.keysym.sym == SDLK_SPACE) {
            printf("%s\n", strBuf);
            strBuf[0] = 0x00;
            SDL_StopTextInput();
        }
        break;
      case SDL_TEXTINPUT:
        {
            strcat(strBuf, _event.text.text);
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

  SDL_DestroyWindow(gWindow);
  SDL_Quit();
  return 0;
}