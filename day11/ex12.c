#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

const Uint16 WINDOW_WIDTH = 640;
const Uint16 WINDOW_HEIGHT = 480;
SDL_Window *g_pWindow;

int main(int argc, char *argv[])
{
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

  Mix_Music *music = Mix_LoadMUS("../res/.wav");

  if (!music)
  {
    printf("Failed to load music SDL_mixer Error: %s\n", Mix_GetError());
  }

  Mix_Chunk *gScratch = Mix_LoadWAV("../res/.wav");
  if (gScratch == NULL)
  {
    printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
  }

  Mix_Chunk *gHigh = Mix_LoadWAV("../res/.wav");
  if (gHigh == NULL)
  {
    printf("Failed to load high sound effect! SDL_mixer Error: %s\n", Mix_GetError());
    // success = false;
  }

  SDL_bool bLoop = SDL_TRUE;
  while (bLoop)
  {
    SDL_Event _event;
    while (SDL_PollEvent(&_event))
    {
      switch (_event.type)
      {
      case SDL_KEYDOWN:
        printf("%d \n", _event.key.keysym.scancode);
        switch (_event.key.keysym.scancode)
        {
        case 30:
          Mix_PlayMusic(music, -1);
          break;
        case 31:
          Mix_PlayChannel(-1, gScratch, 0);
          break;
        case 32:
          Mix_PlayChannel(-1, gHigh, 0);
          break;

        default:
          break;
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

  Mix_FreeChunk(gScratch);
  SDL_DestroyWindow(g_pWindow);
  SDL_Quit();
  return 0;
}