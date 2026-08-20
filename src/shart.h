#ifndef SHART_H
#define SHART_H

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

#define max(a,b) ((a)>(b)?a:b)

const char* FG_COLORS[16] = {
    "\033[30m",   // 0: 黑色
    "\033[31m",   // 1: 红色
    "\033[32m",   // 2: 绿色
    "\033[33m",   // 3: 黄色
    "\033[34m",   // 4: 蓝色
    "\033[35m",   // 5: 品红
    "\033[36m",   // 6: 青色
    "\033[37m",   // 7: 白色
    "\033[90m",   // 8: 亮黑（灰）
    "\033[91m",   // 9: 亮红
    "\033[92m",   // 10: 亮绿
    "\033[93m",   // 11: 亮黄
    "\033[94m",   // 12: 亮蓝
    "\033[95m",   // 13: 亮品红
    "\033[96m",   // 14: 亮青
    "\033[97m"    // 15: 亮白
};

const char* BG_COLORS[16] = {
    "\033[40m",   // 0: 黑
    "\033[41m",   // 1: 红（推荐高亮）
    "\033[42m",   // 2: 绿
    "\033[43m",   // 3: 黄/棕
    "\033[44m",   // 4: 蓝（推荐默认柱色）
    "\033[45m",   // 5: 品红
    "\033[46m",   // 6: 青
    "\033[47m",   // 7: 白
    "\033[100m",  // 8: 亮黑（灰）
    "\033[101m",  // 9: 亮红
    "\033[102m",  // 10: 亮绿
    "\033[103m",  // 11: 亮黄
    "\033[104m",  // 12: 亮蓝
    "\033[105m",  // 13: 亮品红
    "\033[106m",  // 14: 亮青
    "\033[107m"   // 15: 亮白
};

const char* COLOR_RESET = "\033[0m";



#define BUF_HOR 1280
#define BUF_VER 80

#define PILLAR_WIDE 4
#define PILLAR_HEIGHT 30

char screen_buf[BUF_VER][BUF_HOR] = {};

static inline void draw_blank(const char* color){
    printf("%s %s", color, COLOR_RESET);
    return;
}

void clear_screen() {
    printf("\033[2J\033[H");
    fflush(stdout);
}

int draw_chart(int* numbers, int n){
    memset(screen_buf, 0, sizeof(screen_buf));

    clear_screen();

    int max_number = 0;
    double* ratio_numbers = malloc(sizeof(double) * n);
    for (int i = 0; i < n; ++i){
        max_number = max(max_number, numbers[i]);
    }

    for (int i = 0; i < n; ++i){
        ratio_numbers[i] = (double)numbers[i] / (double)max_number;
    }

    int cursors[BUF_VER] = {0};

    for (int i = 0; i < PILLAR_HEIGHT; ++i){
        for (int j = 0; j < n; ++j){
            double ratio_pillar = (double)(PILLAR_HEIGHT - i) / (double)PILLAR_HEIGHT;
            
            int written = 0;
            for (int k = 0; k < PILLAR_WIDE; ++k){
                if (ratio_numbers[j] > ratio_pillar){
                    written = sprintf(screen_buf[i] + cursors[i],"%s %s",BG_COLORS[1],COLOR_RESET);
                    cursors[i] += written;
                
                }
                else{
                    written = sprintf(screen_buf[i] + cursors[i],"%s %s",BG_COLORS[2],COLOR_RESET);
                    cursors[i] += written;
                }
            }
            
        }
    }
    fflush(stdout);
    for (int i = 0; i < PILLAR_HEIGHT; ++i){
        printf("%s\n", screen_buf[i]);
    }

    return 0;
}

void delay_ms(int ms) {
    struct timespec ts;
    ts.tv_sec = ms / 1000;
    ts.tv_nsec = (ms % 1000) * 1000000;
    nanosleep(&ts, NULL);
}
#endif 