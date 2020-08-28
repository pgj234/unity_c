#include <stdio.h>
#include <malloc.h>
#include <string.h>

char *getName() {
    char buf[32];
    gets(buf);

    char *pName = (char *)malloc(strlen(buf) +1);

    strcpy(pName, buf);

    return pName;
}

void getName2(char **ppName) {
    char buf[32];
    gets(buf);
    *ppName = (char *)malloc(strlen(buf) +1);
    strcpy(*ppName, buf);
}

int main() {
    char *pmyName = getName();
    printf("%s \n", pmyName);
    free(pmyName);
    
    getName(&pmyName);
    printf("%s \n", pmyName);
    free(pmyName);
}