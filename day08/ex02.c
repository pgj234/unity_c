#include <stdio.h>
#include <SDL2/SDL.h>

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL : %s \n", SDL_GetError());
        return 1;
    }

    int num = 5;

    for(int i=0; i < num; i++){
        for(int j=num -1; j > i; j--){
	    printf(" ");
        }
		    
        for(int j=0; j < (i*2) +1; j++){
	        printf("*");
        }
        printf("\n");
    }
	
    for(int i=1; i < num; i++){
        for(int j=0; j < i; j++){
	        printf(" ");
        }
	
        for(int j= num*2 -1; j > i*2; j--){
            printf("*");
        }
        printf("\n");
    }

    SDL_Quit();
    return 0;
}