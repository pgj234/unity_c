#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string.h>

int doTokenize(char *szBuf, char szBufToken[][32]);
void putTile(SDL_Renderer *pRenderer, SDL_Texture *pTex,Uint16 _x,Uint16 _y, Uint16 _index);

const Uint16 WINDOW_WIDTH = 640;
const Uint16 WINDOW_HEIGHT = 480;
SDL_Window *gWindow;
SDL_Renderer *g_pRenderer;
SDL_Texture *g_pTitleTexture;

Uint16 g_worldMap_Layer_1[64];

int main(int argc, char *argv[])
{
  for(int i=0;i<64;i++)
  {
    g_worldMap_Layer_1[i] = -1;
  }

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
  // creates a renderer to render our images
  g_pRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

  {
    // creates a surface to load an image into the main memory
    SDL_Surface *surface;

    // please provide a path for your image
    surface = IMG_Load("../res/basictiles.png");

    // loads image to our graphics hardware memory.
    SDL_Texture *tex = SDL_CreateTextureFromSurface(g_pRenderer, surface);

    // clears main-memory
    SDL_FreeSurface(surface);
    g_pTitleTexture = tex;
  }

  static char strBuf[32] = {
      0,
  };

  int nTileIndex = 0;

  SDL_bool bLoop = SDL_TRUE;
  int nInputFSM = 0; //0 -> ready , 1-> text input
  while (bLoop)
  {

    // clears the screen
    SDL_SetRenderDrawColor(g_pRenderer,0x00,0x00,0x00,0x00);
    SDL_RenderClear(g_pRenderer); 

    for(int i=0;i<64;i++) 
    {
      if(g_worldMap_Layer_1[i] != -1)
      {
        putTile(g_pRenderer,g_pTitleTexture,i%8,i/8,g_worldMap_Layer_1[i]);
      }
    }

    // putTile(g_pRenderer,g_pTitleTexture,1,1,0);
    // putTile(g_pRenderer,g_pTitleTexture,2,1,1);
    
    // for multiple rendering
    SDL_RenderPresent(g_pRenderer);

    SDL_Event _event;
    while (SDL_PollEvent(&_event))
    {
      switch (_event.type)
      {
      case SDL_KEYDOWN:
        //printf("%4d %4d \n", _event.key.keysym.scancode,_event.key.keysym.sym);
        if (_event.key.keysym.sym == SDLK_RETURN)
        {
          if (nInputFSM == 0)
          {
            printf("input msg : ");
            SDL_StartTextInput();
            nInputFSM = 1;
          }
          else if (nInputFSM == 1)
          {
            static char szTokens[8][32];
            int _numToken = doTokenize(strBuf,szTokens);

            if (strcmp(szTokens[0], "quit") == 0)
            {
              bLoop = SDL_FALSE;
            }
            else if (strcmp(szTokens[0], "setTile") == 0)
            {
              //setTile x y index
              int _x = SDL_atoi(szTokens[1]);
              int _y = SDL_atoi(szTokens[2]);
              int _index = SDL_atoi(szTokens[3]);

              g_worldMap_Layer_1[(_y*8) + _x] = _index;

              // printf("\n %d %s %s \n",_numToken,szTokens[0],szTokens[1]);
              // Uint16 _ti =  SDL_atoi(szTokens[1]);
              // nTileIndex = _ti;
              // //nTileIndex++;
            }
            else if (strcmp(szTokens[0], "save") == 0)
            {
              //save file.map
              char *pFileName = szTokens[1];
                SDL_RWops *rw = SDL_RWFromFile(pFileName, "wb");
                SDL_RWwrite(rw, g_worldMap_Layer_1, sizeof(Uint16), 64);
                SDL_RWclose(rw);

            }
            else if (strcmp(szTokens[0], "load") == 0)
            {
              char *pFileName = szTokens[1];
                SDL_RWops *rw = SDL_RWFromFile(pFileName, "rb");
                SDL_RWread(rw, g_worldMap_Layer_1, sizeof(Uint16), 64);
                SDL_RWclose(rw);
            }
            printf("\n%s\n", strBuf);
            strBuf[0] = 0x00;
            SDL_StopTextInput();
            nInputFSM = 0;
          }
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

  SDL_DestroyTexture(g_pTitleTexture);
  SDL_DestroyRenderer(g_pRenderer);

  SDL_DestroyWindow(gWindow);
  SDL_Quit();
  return 0;
}