#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>

    char buf1[16];
    char buf2[16];
    char buf3[16];
    char buf4[16];
    char buf5[16];
    char buf6[16];
    /*char buf7[16];
    char buf8[16];*/

void CopyStr(char data[], int size) {
    static int i = 0;
    static int numTmp = 0;
    int cnt = 0;
    char strTmp[10] = "";

    // ',' 문자 만나기 전까지 인덱스 카운트하고 마지막일시 반복문 종료
    for (i; data[i] != ','; i++) {
        if (i == size) {
            break;
        }

        printf("%2d", cnt);         //문자형 카운트 출력
        cnt++;
    }

    //buf 문자형 변수에 넣기
    switch (i/5) {
        case 0:
            strncpy(buf1, data + numTmp, cnt);
            break;
        case 1:
            strncpy(buf2, data + numTmp, cnt);
            break;
        case 2:
            strncpy(buf3, data + numTmp, cnt);
            break;
        case 3:
            strncpy(buf4, data + numTmp, cnt);
            break;
        case 4:
            strncpy(buf5, data + numTmp, cnt);
            break;
        case 5:
            strncpy(buf6, data + numTmp, cnt);
            break;
        /*case 6:
            strncpy(buf7, data + numTmp, cnt);
            break;
        case 7 : 
            strncpy(buf8, data + numTmp, cnt);
            break;*/
        default :
            break;
    }

    strncpy(strTmp, data + numTmp, cnt);

    i += 2;
    numTmp = i;

    // 마지막일시 i -= 2
    if (i == size) {
        i -= 2;
    }
    else {
        printf("\n buf%d : %s \n\n", i/5, strTmp);              // buf 변수 대입된 문자 출력
    }
}

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL : %s \n", SDL_GetError());
        return 1;
    }

    char data[] = "kor, mat, eng, bio, phy, earth";

    for (int i=0; i<(sizeof(data)/sizeof(int)) -1; i++) {
        CopyStr(data, sizeof(data) -1);
    }
    
    SDL_Quit();
    return 0;
}