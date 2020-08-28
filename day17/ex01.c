#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct __s_sheet_data {
    char name[32];
    int x;
    int y;
    int w;
    int h;
} _S_SheetData;

int parseSheet(char *str, _S_SheetData *pData) {
    char *token = strtok(str, " ");
    if (!strcmp(token, "\t<SubTexture")) {
        static char _buf[5][256];

        // name
        token = strtok(NULL, " ");
        strcpy(_buf[0], token);

        // x
        token = strtok(NULL, " ");
        strcpy(_buf[1], token);

        // y
        token = strtok(NULL, " ");
        strcpy(_buf[2], token);

        // w
        token = strtok(NULL, " ");
        strcpy(_buf[3], token);

        // h
        token = strtok(NULL, " ");
        strcpy(_buf[4], token);

        // name 파싱
        token = strtok(_buf[0], "=");
        token = strtok(NULL, ".");
        strcpy(_buf[0], token +1);
        strcpy(pData->name, _buf[0]);

        // x 파싱
        token = strtok(_buf[1], "\"");
        token = strtok(NULL, "\"");
        pData->x = atoi(token);

        // y 파싱
        token = strtok(_buf[2], "\"");
        token = strtok(NULL, "\"");
        pData->y = atoi(token);

        // w 파싱
        token = strtok(_buf[3], "\"");
        token = strtok(NULL, "\"");
        pData->w = atoi(token);

        // h 파싱
        token = strtok(_buf[4], "\"");
        token = strtok(NULL, "\"");
        pData->h = atoi(token);

        return 1;
    }

    return 0;    
}

int main() {
    static char buf[256];
    FILE *fp = fopen("../res/tanks/sheet_tanks.xml", "rt");

    _S_SheetData data;

    while (fgets(buf, sizeof(buf), fp)) {
        if (parseSheet(buf, &data)) {
            printf("%32s%5d%5d%5d%5d\n", data.name, data.x, data.y, data.w, data.h);
        }
    }

    fclose(fp);
}