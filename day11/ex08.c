#include <stdio.h>

/*
struct People
{
    char id;
    int age;
    int height;
};

typedef struct People people;
*/

typedef struct
{
    char id;
    int age;
    int height;
} people;

int main() {
    people data;

    data.id = 'a';
    data.age = 32;
    data.height = 175;

    printf("%c %d %d \n", data.id, data.age, data.height);

    return 0;
}