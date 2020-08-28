#include <stdio.h>

int main() {
    int score = 90;
    char grade = ' ';

    if(score >= 90) {
        grade = 'A';
    }
    else if (score >= 80) {
        grade = 'B';
    }
    else {
        grade = 'F';
    }

    printf("grade : %c", grade);

}