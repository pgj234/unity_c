#include <stdio.h>
#include <SDL2/SDL.h>

int main(int argc, char *argv[]) {
    int num;     //입력받는 값

    printf("input number : ");
    scanf("%d", &num);

    for (int i=0; i<8; i++) {
        int _status = num & (0x80 >> i);

        if (_status) {
            printf("1");
        }
        else {
            printf("0");
        }
    }

    return 0;
}