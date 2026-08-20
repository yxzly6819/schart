/***************************************************************************************
* Copyright (c) 2014-2024 Zihao Yu, Nanjing University
*
* NEMU is licensed under Mulan PSL v2.
* You can use this software according to the terms and conditions of the Mulan PSL v2.
* You may obtain a copy of Mulan PSL v2 at:
*          http://license.coscl.org.cn/MulanPSL2
*
* THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
* EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
* MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
*
* See the Mulan PSL v2 for more details.
***************************************************************************************/

#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>
#include <stdlib.h>

#define ANSI_FG_BLACK   "\033[1;30m"
#define ANSI_FG_RED     "\033[1;31m"
#define ANSI_FG_GREEN   "\033[1;32m"
#define ANSI_FG_YELLOW  "\033[1;33m"
#define ANSI_FG_BLUE    "\033[1;34m"
#define ANSI_FG_MAGENTA "\033[1;35m"
#define ANSI_FG_CYAN    "\033[1;36m"
#define ANSI_FG_WHITE   "\033[1;37m"
#define ANSI_BG_BLACK   "\033[1;40m"
#define ANSI_BG_RED     "\033[1;41m"
#define ANSI_BG_GREEN   "\033[1;42m"
#define ANSI_BG_YELLOW  "\033[1;43m"
#define ANSI_BG_BLUE    "\033[1;44m"
#define ANSI_BG_MAGENTA "\033[1;45m"
#define ANSI_BG_CYAN    "\033[1;46m"
#define ANSI_BG_WHITE   "\033[1;47m"
#define ANSI_NONE       "\033[0m"


#define ANSI_FMT(str, fmt) fmt str ANSI_NONE

#define Log(format, ...) \
    do { \
        printf(ANSI_FMT("[%s:%d %s] " format, ANSI_FG_BLUE) "\n", \
               __FILE__, __LINE__, __func__, ##__VA_ARGS__); \
    } while (0)


#define Assert(cond, format, ...) \
    do { \
        if (!(cond)) { \
            fprintf(stderr, ANSI_FMT(format, ANSI_FG_RED) "\n", ##__VA_ARGS__); \
            fflush(stderr); \
            abort(); \
        } \
    } while (0)


#define panic(format, ...) Assert(0, format, ##__VA_ARGS__)

#define TODO() panic("please implement me")

#endif