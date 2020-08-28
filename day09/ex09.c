#include <stdio.h>

int main() {
    char input_str[8];

    int i;
    for (int i=0; i<7; i++) {
        char _c = getchar();
        printf("input char : %c \n", _c);
        input_str[i] = _c;
    }

    input_str[i] = 0x00;

    printf("%s \n", input_str);

    //if (!gets(input_str)) {
    //    printf("input cancel \n");
    //}
    //else {
    //    printf("%s \n", input_str);
    //}

    return 0;
}