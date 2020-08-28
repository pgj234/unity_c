#include <stdio.h>

int main() {
    int year = 2020;
    int month = 12;
    int day = 31;

    day++;

    if (day > 31) {
        month++;
        day = 1;

        if (month > 12) {
            year++;
            month = 1;
        }
    }

    printf("%4d-%02d-%02d \n", year, month, day);
}