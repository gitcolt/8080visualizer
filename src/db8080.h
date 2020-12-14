#include <ncurses.h>

#define BLACK 1
#define RED 2
#define GREEN 3
#define YELLOW 4
#define BLUE 5
#define MAGENTA 6
#define CYAN 7
#define WHITE 8

#define LABEL_X_OFFSET 2

struct Flags {
  WINDOW* win;
  WINDOW* s_win;
  WINDOW* z_win;
  WINDOW* a_win;
  WINDOW* p_win;
  WINDOW* c_win;
};

struct Registers {
  WINDOW* win;
  WINDOW* a_win;
  WINDOW* b_win;
  WINDOW* c_win;
  WINDOW* d_win;
  WINDOW* e_win;
  WINDOW* h_win;
  WINDOW* l_win;
};

struct Memory {
  WINDOW* win;
  WINDOW* bytes_pad;
  unsigned char* buf;
  int bytes_starty;
  int bytes_startx;
  int pad_offset;
  int pad_content_height;
  int stride;
  int cursory;
  int cursorx;
};
