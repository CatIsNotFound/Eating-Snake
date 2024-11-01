#include "Graphic.h"
#ifndef EATINGSNAKE_GAME_H
#define EATINGSNAKE_GAME_H

#endif //EATINGSNAKE_GAME_H
void init_game(int, int);
void init_random();
int random_num(int min, int max);
void sleep(int);
void start_game(Snake&);
void game_over();
void secret_ending();
void reset_game(Snake&);
void retry_game();
void quit_game();
void keep();
void keep_input();
void paused_or_resume_game();
void snake_init(Snake&);
void snake_born(Snake&);
void snake_dead(Snake&);
void generate_food(Snake&);
void update_snake_position(Snake&);
void command_direction(int);
bool snake_touched_events(Snake&);
void snake_ate_food(Snake&);
void snake_add_heart(Snake&);
void snake_touched_border(Snake&);
void snake_touched_self(Snake&);
void snake_full(Snake&);
void reset_blocks();
void clear_blocks();