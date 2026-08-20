#include"shart.h"

#include<stdio.h>
#include<stdlib.h>

int main(){
    int numbers[] = {5, 4, 3, 2, 1, 3, 8, 3, 5, 2, 7, 1, 0, 5};
    int n = sizeof(numbers) / sizeof(numbers[0]);

    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (numbers[j] < numbers[min_idx]) {
                min_idx = j;
            }
        }

        if (min_idx != i) {
            int temp = numbers[i];
            numbers[i] = numbers[min_idx];
            numbers[min_idx] = temp;
        }

        draw_chart(numbers, n);
        delay_ms(550);
    }

    draw_chart(numbers, n);
}