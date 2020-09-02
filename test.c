#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char ss[10] = "hello";
    int ad[5] = {1,2,3,4,5};

    char *s1 = "hello"; 
    char *s2 = malloc(sizeof(char) * (strlen(s1)));    

    printf("ss : %lu\n", sizeof(ss));    // char(1byte) * 10 = 10
    printf("ad : %lu\n", sizeof(ad));    // int(4byte) * 5 = 20

    
    printf("s1 : %lu\n", sizeof(s1));
    printf("s2 : %lu\n", sizeof(s2));

    strcpy(s2, s1);   


    printf("%s\n", s2);  

    free(s2);   

    return 0;
}