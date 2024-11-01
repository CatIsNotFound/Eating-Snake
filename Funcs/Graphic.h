#define HIDE_CURSOR "\033[?25l"
#define SHOW_CURSOR "\033[?25h"
#define CLEAR_SCR "\033[2J"
#define MOVE_TO_LEFT_TOP "\033[2;2H"

#ifndef EATINGSNAKE_GRAPHIC_H
#define EATINGSNAKE_GRAPHIC_H
// 设定蛇的外观
enum SnakeLooks {
    SNAKE_HEAD_1 = 'O',
    SNAKE_BODY_1 = '0',
    SNAKE_HEAD_2 = '0',
    SNAKE_BODY_2 = 'o',
};

// 设定方向
enum Direction {
    D_UP = 1,
    D_DOWN = 2,
    D_LEFT = 3,
    D_RIGHT = 4,
};

// 设定蛇
struct Snake {
    SnakeLooks head;
    SnakeLooks body;
    int init_lives;
    int lives;
    int init_length;
    int length;
    int max_length;
    Direction move;
    int x, y;
};
// 设定块
enum BlockType {
    EMPTY = ' ',
    FOOD = '*',
    HEART = 'H',
    SNAKE_H = 'O',
    SNAKE_B = 'o',
};

// 游戏地图：设定大小
struct Map {
    int width, height;
};

#endif //EATINGSNAKE_GRAPHIC_H
void show_first_screen();
void create_Map(const Map& map);
void clear_screen();
void destroy();
void refresh(const Map& map);
void move_Cursor(int X, int Y);
void init_block(BlockType &blocks);
void draw_block(int X, int Y, BlockType blockType);
void draw_snake(int X, int Y, Snake snake, bool is_head);
void erase_snake_tail(int X, int Y, Snake snake);
void clean_blocks(const Map& map);
void show_hearts(const Snake &);