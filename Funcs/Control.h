#define KEY_Escape 27
#define KEY_CTRL_C 3
#define KEY_Up 'w'
#define KEY_Down 's'
#define KEY_Left 'a'
#define KEY_Right 'd'
#define KEY_Space 32
#define BELL '\a'

bool is_right_key(const char key, const char set_key);
void is_quit(const char key, const char set_key);
void pause_resume(const char key, const char set_key);
void retry(const char key, const char set_key);
void wait_key();
char get_key(const char key);
void send_direction(const char key);
void bell();