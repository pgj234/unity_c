#include <stdio.h>
#include <malloc.h>
#include <memory.h>

typedef struct _s_data {

short a;
short b;
int c;

char d1;
char d2;
char d3;
char d4;
char d5;

} _S_Data;

_S_Data *data;

int main() {
    data = malloc(sizeof(_S_Data));

    FILE *fp = fopen("q3.dat", "rb");
    fread(data, sizeof(_S_Data), 1, fp);

    data->a = *((short *)data);
    data->b = *((short *)data +1);
    data->c = *((int *)data +1);

    printf("%x %x %x\n", data->a, data->b, data->c);

    int result = data->a + data->b + data->c;

    printf("a+b+c : %x\n", result);

    printf("==============================\n");

    data->d1 = *((char *)data +8);
    data->d2 = *((char *)data +9);
    data->d3 = *((char *)data +10);
    data->d4 = *((char *)data +11);
    data->d5 = *((char *)data +12);

    printf("%x %x %x %x %x\n", data->d1, data->d2, data->d3, data->d4, data->d5);

    int result2 = data->d1 + data->d2 + data->d3 + data->d4 + data->d5;

    printf("d1+d2+d3+d4+d5 : %x", result2);

    return 0;
}