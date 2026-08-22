#include"schart.h"


#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define DYNAMIC_TEST

void init_rand(){
    srand(time(NULL));
}

int chosen(int n){
    return rand() % n;
}

int main(int argc, char* argv[]){
    init_rand();

    int n;
    Assert(sscanf(argv[1],"%d", &n) != -1, "Give right argument\n");
    
    int* numbers = malloc(sizeof(int) * n);
    for (int i = 0; i < n; ++i){
        numbers[i] = chosen(n);
    }

    init_schart();

#ifdef DYNAMIC_TEST
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
            draw_chart(numbers, n);
            delay_ms(250);
        }
    }
#endif

    draw_chart(numbers, n);

    free(numbers);

    return 0;
}