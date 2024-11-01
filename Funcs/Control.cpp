/* Control */
/* 键盘控制 */
#include <iostream>
#include <conio.h>
#include "Control.h"
#include "Game.h"
using namespace std;

// 判定玩家按下的键是否为设定键
bool is_right_key(const char key, const char set_key) {
    return (key == set_key);
}

// 设定退出
void is_quit(const char key, const char set_key) {
    if (key == set_key) {
        quit_game();
    }
}

// 等待输入
void wait_key() {
    char n;
    n = getch();
    is_quit(n, KEY_CTRL_C);
    is_quit(n, KEY_Escape);
    pause_resume(n, KEY_Space);
    send_direction(n);
    retry(n, 'r');
}

// 获取键值
char get_key(const char key) {
    return key;
}

void pause_resume(const char key, const char set_key) {
    if (key == set_key) {
        paused_or_resume_game();
    }
}

void retry(const char key, const char set_key) {
    if (key == set_key) {
        retry_game();
    }
}

void send_direction(const char key) {
    switch (key) {
        case KEY_Up:
            command_direction(1);
            break;
        case KEY_Down:
            command_direction(2);
            break;
        case KEY_Left:
            command_direction(3);
            break;
        case KEY_Right:
            command_direction(4);
            break;
        default:
            break;
    }
}

void bell() {
    cout << BELL;
}
