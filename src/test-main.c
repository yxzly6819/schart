#include"shart.h"

#include<stdio.h>
#include<stdlib.h>

int main(){
    for (int i = 0; i < 10; i++){
        for (int i = 0; i < 10; i++){
            draw_blank(BG_COLORS[5]);
        }
        printf("\n");
    }
}