// Game
// 所有游戏流程都在这里
// 导入
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <thread>
#include <mutex>
#include "Game.h"
#include "Graphic.h"
#include "Control.h"
using namespace std;

// 全局区
bool is_paused;
bool is_dead;
bool is_running;
bool refresh_once = false;
struct Map map;
struct Snake p_snake;
int snake_length = 0;
int speed = 100;
BlockType blocks[100][100];
mutex mutex_f, mutex_i;
struct Pos {
    int x, y;
};
Pos snakeBodies[1000000];

// 初始化随机数
void init_random() {
    srand(time(0));
}

// 生成随机整数
int random_num(int min, int max) {
    int t = (rand() % (max - min + 1)) + min;
    return t;
}

// 设置延时
void sleep(int ms) {
//    time_t start_time = time(NULL);
//    while (time(NULL) - start_time < seconds);
    this_thread::sleep_for(chrono::milliseconds (ms));
}

void init_game(int map_height, int map_width) {
    show_first_screen();
    getchar();
    cout << "  -> Starting Game...";
    is_running = true;
    sleep(1000);
    p_snake = {SNAKE_HEAD_2, SNAKE_BODY_2, 5, 0, 5, 5, 99};
    Map t_map = {map_height, map_width};
    for (int i = 0; i < t_map.height; ++i) {
        for (int j = 0; j < t_map.width; ++j) {
            init_block(blocks[i][j]);
        }
    }
    map = t_map;
    start_game(p_snake);
    thread keep_thread(keep);
    thread input_thread(keep_input);
    input_thread.join();
    keep_thread.join();
}

void start_game(Snake &snake) {
    init_random();
    create_Map(map);
    clear_blocks();
    snake_init(snake);
    snake_born(snake);
    refresh_once = true;
    sleep(1000);
    is_paused = false;
    is_dead = false;
    generate_food(snake);
}

void quit_game() {
    is_paused = true;
    sleep(100);
    is_running = false;
    clear_screen();
    cout << "Quitting Game....";
    sleep(1000);
    destroy();
    exit(0);
}

// 持续循环游戏
void keep() {
    while (is_running) {
        lock_guard<mutex> guard(mutex_f);
        if (!is_paused && !is_dead) {
            sleep(speed);
            update_snake_position(p_snake);
        }
        if (refresh_once) {
            sleep(speed);
            update_snake_position(p_snake);
            refresh_once = false;
        }
    }
}

// 持续等待用户输入
void keep_input() {
    while (is_running) {
        lock_guard<mutex> lockGuard(mutex_i);
        wait_key();
        sleep(50);
    }
}

// 暂停或继续游戏
void paused_or_resume_game() {
    if (is_paused && !is_dead) {
        clear_screen();
        create_Map(map);
        refresh(map);
        show_hearts(p_snake);
        refresh_once = true;
        sleep(1000);
        is_paused = false;
    }
    else if (!is_paused && !is_dead){
        is_paused = true;
        sleep(100);
        clear_screen();
        cout << "                GAME PAUSED                " << endl;
        cout << " ------------------------------------------" << endl;
        cout << "   Press SPACE again to resume the game.";
    }
}

void snake_init(Snake &snake) {
    snake.length = snake.init_length;
    snake.lives = snake.init_lives;
}

// 复活/出生蛇并随机初始化位置与方向
void snake_born(Snake &snake) {
    int w = map.width, h = map.height;
    int x = random_num(3, h - 2);
    int y = random_num(3, w - 2);
    snake.x = x; snake.y = y;
    snake_length = snake.init_length;
    snake.length = snake.init_length;
    for (int i = 0; i < snake_length + 9999; ++i) {
        snakeBodies[i].x = x;
        snakeBodies[i].y = y;
    }
    draw_snake(x + 2, y + 2, snake, true);
    blocks[x][y] = SNAKE_H;
    int direction = random_num(1, 4);
    switch (direction % 4) {
        case 0:
            snake.move = D_UP;
            break;
        case 1:
            snake.move = D_DOWN;
            break;
        case 2:
            snake.move = D_LEFT;
            break;
        case 3:
            snake.move = D_RIGHT;
            break;
    }
    show_hearts(snake);
}

// 蛇死了
void snake_dead(Snake &snake) {
    is_paused = true;
    sleep(500);
    clean_blocks(map);
    for (int i = 0; i < map.height; ++i) {
        for (int j = 0; j < map.width; ++j) {
            if (blocks[i][j] == SNAKE_H || blocks[i][j] == SNAKE_B) {
                init_block(blocks[i][j]);
            }
        }
    }
    if (snake.lives < 2) {
        is_dead = true;
        sleep(1000);
        game_over();
        return;
    } else {
        snake.lives--;
        clear_blocks();
        clear_screen();
        create_Map(map);
        refresh(map);
        show_hearts(snake);
        snake_born(snake);
        generate_food(snake);
        refresh_once = true;
        sleep(1000);
        is_paused = false;
    }
}

// 游戏结束后要做的处理
void game_over() {
    clear_screen();
    cout << "                  GAME OVER" << endl;
    cout << " --------------------------------------------" << endl;
    cout << "     Press \'r\' to restart the game. :(";
}

// 触发蛇因吃撑而死的结局
void secret_ending() {
    clear_screen();
    cout << "                   SECRET ENDING" << endl;
    cout << " -----------------------------------------------" << endl;
    cout << "   Your snake is dead from eating too much. :)" << endl;
    cout << "   Press \'r\' to restart the game.";
}

// 重置游戏
void reset_game(Snake &snake) {
    if (is_dead) {
        is_paused = true;
        sleep(100);
        clear_screen();
        cout << "Restarting the game...";
        sleep(1000);
        clear_blocks();
        sleep(1000);
        start_game(snake);
    }
}


// 重置游戏
void retry_game() {
    reset_game(p_snake);
}

// 玩家命令蛇改变方向
void command_direction(int direction) {
    if (is_paused) return;
    switch (direction) {
        case 1:
            if (p_snake.move != D_DOWN && p_snake.move != D_UP) {
                p_snake.move = D_UP;
            }
            break;
        case 2:
            if (p_snake.move != D_UP && p_snake.move != D_DOWN) {
                p_snake.move = D_DOWN;
            }
            break;
        case 3:
            if (p_snake.move != D_RIGHT && p_snake.move != D_LEFT) {
                p_snake.move = D_LEFT;
            }
            break;
        case 4:
            if (p_snake.move != D_LEFT && p_snake.move != D_RIGHT) {
                p_snake.move = D_RIGHT;
            }
            break;
    }
}

// 实时更新蛇的位置
void update_snake_position(Snake &snake) {
    for (int i = snake_length - 1; i > 0; --i) {
        if (i == snake_length - 1) {
            erase_snake_tail(snakeBodies[i].x + 2, snakeBodies[i].y + 2, snake);
        }
        snakeBodies[i].x = snakeBodies[i - 1].x;
        snakeBodies[i].y = snakeBodies[i - 1].y;
        blocks[snakeBodies[i].x][snakeBodies[i].y] = SNAKE_B;
        draw_snake(snakeBodies[i].x + 2, snakeBodies[i].y + 2, snake, false);

    }
    blocks[snakeBodies[snake_length - 1].x][snakeBodies[snake_length - 1].y] = EMPTY;
    switch (snake.move) {
        case D_LEFT:
            snake.y--;
            break;
        case D_RIGHT:
            snake.y++;
            break;
        case D_UP:
            snake.x--;
            break;
        case D_DOWN:
            snake.x++;
            break;
    }
    snakeBodies[0].x = snake.x;
    snakeBodies[0].y = snake.y;
    if (snake_touched_events(snake)) {
        return;
    }
    blocks[snake.x][snake.y] = SNAKE_H;
    if (snake_length < snake.lives) {
        snake_length++;
    }
    draw_snake(snake.x + 2, snake.y + 2, snake, true);
//    // Debug info:
//    move_Cursor(0, 0);
//    cout << "Head: " << snake.x << ", " << snake.y << "; ";
//    cout << snake.move << ": ";
//    cout << "Current_Length: " << snake_length << ", Lives: " << snake.lives << "        ";
}

// 蛇触碰块事件
bool snake_touched_events(Snake &snake) {
    move_Cursor(snake.x + 2, snake.y + 2);
    if (blocks[snake.x][snake.y] == FOOD) {
        snake_ate_food(snake);
        return true;
    } else if (blocks[snake.x][snake.y] == HEART) {
        snake_add_heart(snake);
        return true;
    } else if ((snake.x > map.height || snake.x < 1) || (snake.y > map.width || snake.y < 1)) {
        snake_touched_border(snake);
        return true;
    } else if (blocks[snake.x][snake.y] == SNAKE_H || blocks[snake.x][snake.y] == SNAKE_B) {
        snake_touched_self(snake);
        return true;
    } else if (snake_length == snake.max_length) {
        snake_full(snake);
        return true;
    }
    return false;
}

void generate_food(Snake &snake) {
    bool f = true;
    do {
        int x = random_num(1, map.height);
        int y = random_num(1, map.width);
        if (blocks[x][y] == EMPTY) {
            move_Cursor(x + 2, y + 2);
            int seeds = random_num(1, 100);
            if (seeds > 6) {
                blocks[x][y] = FOOD;
                cout << (char) FOOD;
            } else {
                blocks[x][y] = HEART;
                cout << (char) HEART;
            }
            f = false;
        } else {
            f = true;
        }
    } while (f);

}

void snake_ate_food(Snake &snake) {
    blocks[snake.x][snake.y] = EMPTY;
    move_Cursor(snake.x + 2, snake.y + 2);
    cout << (char)snake.head;
    snake_length++;
    snake.length++;
    show_hearts(snake);
    generate_food(snake);
}

void snake_add_heart(Snake &snake) {
    blocks[snake.x][snake.y] = EMPTY;
    move_Cursor(snake.x + 2, snake.y + 2);
    cout << (char)snake.head;
    snake.lives++;
    show_hearts(snake);
    generate_food(snake);
}

void snake_touched_border(Snake &snake) {
    cout << "X";
    snake_dead(snake);

}

void snake_touched_self(Snake &snake) {
    cout << "X";
    snake_dead(snake);
}

// 蛇吃撑死了
void snake_full(Snake &snake) {
    cout << "%";
    is_paused = true;
    is_dead = true;
    sleep(2000);
    secret_ending();
}

// 显示块内容
void reset_blocks() {
    for (int i = 1; i < map.height + 1; ++i) {
        move_Cursor(i + 2, 3);
        for (int j = 1; j < map.width + 1; ++j) {
            if (blocks[i][j] != SNAKE_B && blocks[i][j] != SNAKE_H)
                cout << (char)blocks[i][j];
        }
    }
}

// 清空块内容
void clear_blocks() {
    for (int i = 1; i < map.height + 1; ++i) {
        move_Cursor(i + 2, 3);
        for (int j = 1; j < map.width + 1; ++j) {
            cout << (char)EMPTY;
            blocks[i][j] = EMPTY;
        }
    }
}
