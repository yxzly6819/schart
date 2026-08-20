#ifndef SCHART_H
#define SCHART_H

#include"common.h"
#include"debug.h"

#define max(a,b) ((a)>(b)?a:b)

const char* BG_COLORS[16] = {
    "\033[40m",   // 0: 黑
    "\033[41m",   // 1: 红
    "\033[42m",   // 2: 绿
    "\033[43m",   // 3: 黄/棕
    "\033[44m",   // 4: 蓝
    "\033[45m",   // 5: 品红
    "\033[46m",   // 6: 青
    "\033[47m",   // 7: 白
    "\033[100m",  // 8: 亮黑
    "\033[101m",  // 9: 亮红
    "\033[102m",  // 10: 亮绿
    "\033[103m",  // 11: 亮黄
    "\033[104m",  // 12: 亮蓝
    "\033[105m",  // 13: 亮品红
    "\033[106m",  // 14: 亮青
    "\033[107m"   // 15: 亮白
};

const char* COLOR_RESET = "\033[0m";

#define BUF_HOR 51200
#define BUF_VER 800

char screen_buf[BUF_VER][BUF_HOR] = {};

int screen_wide, screen_height;

int ft_color = 13;
int bk_color = 4;

void home_cursor() {
    printf("\033[H");
    fflush(stdout);
}

int draw_chart(int* numbers, int n){
    const int PILLAR_HEIGHT = screen_height;
    const int PILLAR_WIDE = screen_wide / n ;

    Assert(PILLAR_WIDE, "SCREEN NOT WIDE ENOUGH!\n");
    
    memset(screen_buf, 0, sizeof(screen_buf));

    home_cursor();

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
                    written = sprintf(screen_buf[i] + cursors[i],"%s %s",BG_COLORS[ft_color],COLOR_RESET);
                    cursors[i] += written;
                
                }
                else{
                    written = sprintf(screen_buf[i] + cursors[i],"%s %s",BG_COLORS[bk_color],COLOR_RESET);
                    cursors[i] += written;
                }
            }
            
        }
    }
    for (int i = 0; i < PILLAR_HEIGHT; ++i){
        printf("%s\n", screen_buf[i]);
    }
    free(ratio_numbers);

    return 0;
}

void delay_ms(int ms) {
    struct timespec ts;
    ts.tv_sec = ms / 1000;
    ts.tv_nsec = (ms % 1000) * 1000000;
    nanosleep(&ts, NULL);
}

void init_schart(){
    struct winsize w;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == 0) {
        screen_wide = w.ws_col;
        screen_height = w.ws_row;
    } else {
        panic("ioctl\n");
    }

    fflush(stdout);
}

void end_schart(){
    printf("\033[?25h");
}

void set_bk_color_number(int n){
    if (n > 15){
        Log("Number overflow, kept default.\n");
        return;
    }
    bk_color = n;
}

void set_ft_color_number(int n){
    if (n > 15){
        Log("Number overflow, kept default.\n");
        return;
    }
    ft_color = n;
}
#endif 