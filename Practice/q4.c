#include <stdio.h>
#include <malloc.h>
#include <memory.h>

typedef struct _s_data {

char name[8];
short x;
short y;
short w;
short h;

} _S_Data;

int main() {
    _S_Data *buf = malloc(sizeof(_S_Data));
    
    FILE *fp = fopen("q4.dat", "rb");

    while(fgets(buf, sizeof(_S_Data), fp)) {
        printf("%s  %d %d %d %d \n", buf->name, buf->x, buf->y, buf->w, buf->h);
    }

    free(buf);

    fclose(fp);

    return 0;
}