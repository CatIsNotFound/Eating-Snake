/* Graphic.cpp */
/* 绘制图形库 */
#include <iostream>
#include "Graphic.h"
#include "Game.h"
using namespace std;

// 初始化地图
void create_Map(const Map &map) {
    clear_screen();
    int W = map.width + 2;
    int H = map.height + 2;
    for (int i = 0; i < H; ++i) {
        move_Cursor(i + 2, 2);
        for (int j = 0; j < W; ++j) {
            if (i == 0 && j == 0) {
                cout << "+" ;
            }
            else if (i == 0 && j == W - 1) {
                cout << "+" ;
            }
            else if (i == H - 1 && j == 0) {
                cout << "+" ;
            }
            else if (i == H - 1 && j == W - 1) {
                cout << "+" ;
            }
            else if (!i || i == H - 1) {
                cout << "-" ;
            }
            else if (j == 0 || j == W - 1) {
                cout << "|" ;
            }
            else {
                cout << " " ;
            }
        }
    }
}

// 清屏
void clear_screen() {
    system(CLEAR_SCR);
    system(HIDE_CURSOR);
    system(MOVE_TO_LEFT_TOP);
}

// 退出前执行销毁
void destroy() {
    system(CLEAR_SCR);
    system(HIDE_CURSOR);
    system(MOVE_TO_LEFT_TOP);
}

// 刷新画面
void refresh(const Map& map) {
//    clean_blocks(map);
    reset_blocks();
}

// 移动光标
void move_Cursor(int X, int Y) {
    cout << "\033[" << X << ";" << Y << "H";
}

// 初始化块内容
void init_block(BlockType &blocks) {
    blocks = EMPTY;
}

// 在指定位置绘制块
void draw_block(int X, int Y, BlockType blockType) {
    move_Cursor(X, Y);
    cout << blockType;
}

// 在指定位置绘制蛇
void draw_snake(int X, int Y, Snake snake, bool is_head) {
    move_Cursor(X, Y);
    cout << (is_head ? (char)snake.head : (char)snake.body);
}

// 擦除蛇尾
void erase_snake_tail(int X, int Y, Snake snake) {
    move_Cursor(X, Y);
    cout << (char)EMPTY;
}

void clean_blocks(const Map& map) {
    for (int i = 1; i < map.height + 1; ++i) {
        move_Cursor(i + 2, 3);
        for (int j = 2; j < map.width + 1; ++j) {
            cout << (char)EMPTY;
        }
    }
}

void show_hearts(const Snake &snake) {
    move_Cursor(1, 3);
    cout << "       ";
    move_Cursor(1, 3);
    cout << "H: " << snake.lives << " E: " << snake.length << "/" << snake.max_length << "    ";
}



// 显示游戏首页
void show_first_screen() {
    clear_screen();
    move_Cursor(2, 1);
    cout << " -----------------------------------------------------------------------" << endl;
    cout << "  EEEEE   A   TTTTT III N   N  GGG         SSSS N   N   A   K   K EEEEE" << endl;
    cout << "  E      A A    T    I  NN  N G           S     NN  N  A A  K  K  E"     << endl;
    cout << "  EEEE  AAAAA   T    I  N N N G GG         SSS  N N N AAAAA KKK   EEEE"  << endl;
    cout << "  E     A   A   T    I  N  NN G   G           S N  NN A   A K  K  E"     << endl;
    cout << "  EEEEE A   A   T   III N   N  GGG        SSSS  N   N A   A K   K EEEEE" << endl;
    cout << " -----------------------------------------------------------------------" << endl;
    cout << "                           Eating Snake Ver 1.0" << endl;
    cout << "                       >> Press ENTER key to start. <<" << endl << endl;
    cout << "                      Copyright (C) 2024 CatIsNotFound" << endl << endl;
    cout << " ------------------------------- How To play ---------------------------" << endl;
    cout << "                              Press ESC to quit." << endl;
    cout << "                       Press SPACE to pause or resume." << endl;
    cout << "                Press 'w' 'a' 's' 'd' to control snake direction." << endl;
    cout << " -----------------------------------------------------------------------" << endl << endl;
    cout << " ---------------------------- YOUR DESTINATION -------------------------" << endl;
    cout << "                      Please help the snake eat 99 snacks. " << endl;
    cout << " -----------------------------------------------------------------------" << endl << endl;
}

