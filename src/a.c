#include "a.h"
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>
#include <time.h>

WINDOW* create_win (int height, int width, int starty, int startx, short color) {
  WINDOW* win;
  win = newwin(height, width, starty, startx);
  wattron(win, COLOR_PAIR(color));
  box(win, ACS_VLINE, ACS_HLINE);
  wattroff(win, COLOR_PAIR(color));
  wrefresh(win);
  return win;
}

WINDOW* create_derwin (WINDOW* parent, int height, int width, int starty, int startx, short color) {
  WINDOW* win;
  win = derwin(parent, height, width, starty, startx);
  wattron(win, COLOR_PAIR(color));
  box(win, ACS_VLINE, ACS_HLINE);
  wattroff(win, COLOR_PAIR(color));
  wrefresh(win);
  return win;
}

void destroy_win (WINDOW* win) {
  wborder(win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
  wrefresh(win);
  delwin(win);
}

void set_flag (struct Flags* flags, char ch, int on) {
  WINDOW* win;
  switch(ch) {
    case 's':
      win = flags->s_win; break;
    case 'z':
      win = flags->z_win; break;
    case 'a':
      win = flags->a_win; break;
    case 'p':
      win = flags->p_win; break;
    case 'c':
      win = flags->c_win; break;
  }
  wattron(win, on ? COLOR_PAIR(RED) : COLOR_PAIR(WHITE));
  wattron(win, A_BOLD);
  mvwaddch(win, 1, 1, toupper(ch));
  wattroff(win, on ? COLOR_PAIR(RED) : COLOR_PAIR(WHITE));
  wattroff(win, A_BOLD);
  wrefresh(win);
}


struct Flags* create_flags_win (int starty, int startx) {
  WINDOW* win = create_win(5, 23, starty, startx, CYAN);
  mvwprintw(win, 0, LABEL_X_OFFSET, "Flags");
  wrefresh(win);

  struct Flags* flags = malloc(sizeof(struct Flags));
  flags->win = win;
  flags->s_win = create_derwin(win, 3, 3, 1,  2, MAGENTA);
  flags->z_win = create_derwin(win, 3, 3, 1,  6, MAGENTA);
  flags->a_win = create_derwin(win, 3, 3, 1, 10, MAGENTA);
  flags->p_win = create_derwin(win, 3, 3, 1, 14, MAGENTA);
  flags->c_win = create_derwin(win, 3, 3, 1, 18, MAGENTA);

  set_flag(flags, 's', 0);
  set_flag(flags, 'z', 0);
  set_flag(flags, 'a', 0);
  set_flag(flags, 'p', 0);
  set_flag(flags, 'c', 0);

  return flags;
}

void set_register (struct Registers* regs, char ch, int val) {
  WINDOW* win;
  switch(ch) {
    case 'a':
      win = regs->a_win; break;
    case 'b':
      win = regs->b_win; break;
    case 'c':
      win = regs->c_win; break;
    case 'd':
      win = regs->d_win; break;
    case 'e':
      win = regs->e_win; break;
    case 'h':
      win = regs->h_win; break;
    case 'l':
      win = regs->l_win; break;
  }

  mvwprintw(win, 1, 1+1, "%X", val);
  wrefresh(win);
}

struct Registers* create_registers_win (int starty, int startx) {
  WINDOW* win = create_win(14, 22, starty, startx, YELLOW);
  mvwprintw(win, 0, LABEL_X_OFFSET, "Registers");
  wrefresh(win);

  struct Registers* regs = malloc(sizeof(struct Registers));
  regs->win = win;
  regs->a_win = create_derwin(win, 3, 6,  1,  5, BLUE);
  regs->b_win = create_derwin(win, 3, 6,  4,  5, BLUE);
  regs->c_win = create_derwin(win, 3, 6,  4, 11, BLUE);
  regs->d_win = create_derwin(win, 3, 6,  7,  5, BLUE);
  regs->e_win = create_derwin(win, 3, 6,  7, 11, BLUE);
  regs->h_win = create_derwin(win, 3, 6, 10,  5, BLUE);
  regs->l_win = create_derwin(win, 3, 6, 10, 11, BLUE);

  int x, y;
  getparyx(regs->a_win, y, x);
  mvwaddch(win, y + 1, x - 2, 'A');
  wrefresh(win);
  getparyx(regs->b_win, y, x);
  mvwaddch(win, y + 1, x - 2, 'B');
  wrefresh(win);
  getparyx(regs->c_win, y, x);
  mvwaddch(win, y + 1, x + 7, 'C');
  wrefresh(win);
  getparyx(regs->d_win, y, x);
  mvwaddch(win, y + 1, x - 2, 'D');
  wrefresh(win);
  getparyx(regs->e_win, y, x);
  mvwaddch(win, y + 1, x + 7, 'E');
  wrefresh(win);
  getparyx(regs->h_win, y, x);
  mvwaddch(win, y + 1, x - 2, 'H');
  wrefresh(win);
  getparyx(regs->l_win, y, x);
  mvwaddch(win, y + 1, x + 7, 'L');
  wrefresh(win);

  wattron(regs->a_win, COLOR_PAIR(GREEN) | A_BOLD);
  wattron(regs->b_win, COLOR_PAIR(GREEN) | A_BOLD);
  wattron(regs->c_win, COLOR_PAIR(GREEN) | A_BOLD);
  wattron(regs->d_win, COLOR_PAIR(GREEN) | A_BOLD);
  wattron(regs->e_win, COLOR_PAIR(GREEN) | A_BOLD);
  wattron(regs->h_win, COLOR_PAIR(GREEN) | A_BOLD);
  wattron(regs->l_win, COLOR_PAIR(GREEN) | A_BOLD);

  set_register(regs, 'a', 0xFF);
  set_register(regs, 'b', 0xFF);
  set_register(regs, 'c', 0xFF);
  set_register(regs, 'd', 0xFF);
  set_register(regs, 'e', 0xFF);
  set_register(regs, 'h', 0xFF);
  set_register(regs, 'l', 0xFF);

  return regs;
}

void update_mem_cursor (struct Memory* mem, int y, int x) { 
  int scroll;
  unsigned char prev_val = mem->buf[mem->cursory * 16 + mem->cursorx];
  if (y > 15) {
    y = 15;
    scroll = 1;
    if (mem->pad_offset + 16 < mem->pad_content_height)
      mem->pad_offset++;
  } else if (y < 0) {
    y = 0;
    scroll = -1;
    if (!mem->pad_offset == 0)
      mem->pad_offset--;
  } else {
    scroll = 0;
  }

  if (x > 15) {
    x = 15;
  } else if (x < 0) {
    x = 0;
  }

  wattroff(mem->win, A_REVERSE);
  wattron(mem->win, A_BOLD);
  unsigned char val = mem->buf[y * 16 + x];
  mvwprintw(mem->win, mem->cursory + mem->bytes_starty, mem->cursorx * mem->stride + mem->bytes_startx, "%02X", prev_val);

  wattron(mem->win, A_REVERSE);
  mvwprintw(mem->win, y + mem->bytes_starty, x * mem->stride + mem->bytes_startx, "%02X", val);
  wattroff(mem->win, A_REVERSE);

  mem->cursory = y;
  mem->cursorx = x;

  int winy, winx;
  getbegyx(mem->win, winy, winx);
  prefresh(mem->bytes_pad, mem->pad_offset, 0, winy + mem->bytes_starty, winx + mem->bytes_startx, winy + mem->bytes_starty + 15, winx + mem->bytes_startx + 16*mem->stride);
  wrefresh(mem->win);
}

struct Memory* create_mem_win (int starty, int startx) {
  struct Memory* mem = malloc(sizeof(struct Memory));
  mem->win = create_win(20, 59, starty, startx, RED);
  mvwprintw(mem->win, 0, LABEL_X_OFFSET, "Memory");
  mem->stride = 3;
  mem->bytes_starty = 3;
  mem->bytes_startx = 4;
  mem->pad_offset = 0;
  mvwaddstr(mem->win, 1, mem->bytes_startx, " 0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F");
  wrefresh(mem->win);

  size_t buf_size = 300;
  mem->buf = malloc(sizeof(unsigned char) * buf_size);

  srand(time(NULL));
  for (int i = 0; i < buf_size; i++) {
    mem->buf[i] = i % 0xFF;
  }

  mem->pad_content_height = buf_size/16;
  mem->bytes_pad = newpad(mem->pad_content_height, 16 * 3);

  wattron(mem->bytes_pad, A_BOLD);
  int row;
  for (int i = 0; i < buf_size; i++) {
    row = i / 16;
    int col = i % 16;
    unsigned char val = mem->buf[i];
    mvwprintw(mem->bytes_pad, row, col * mem->stride, "%02X ", val);
  }
  wattroff(mem->bytes_pad, A_BOLD);
  int y, x;
  getbegyx(mem->win, y, x);

  mem->cursory = 0;
  mem->cursorx = 0;
  update_mem_cursor(mem, mem->cursory, mem->cursorx);

  return mem;
}

void init () {
  initscr();
  noecho();
  keypad(stdscr, 1);
  curs_set(0);
  start_color();
  use_default_colors();
  init_pair(BLACK, COLOR_BLACK, -1);
  init_pair(RED, COLOR_RED, -1);
  init_pair(GREEN, COLOR_GREEN, -1);
  init_pair(YELLOW, COLOR_YELLOW, -1);
  init_pair(BLUE, COLOR_BLUE, -1);
  init_pair(MAGENTA, COLOR_MAGENTA, -1);
  init_pair(CYAN, COLOR_CYAN, -1);
  init_pair(WHITE, COLOR_WHITE, -1);
  refresh();
}

int main (int argc, char** argv) {
  init();

  struct Flags* flags = create_flags_win(0, 0);
  set_flag(flags, 'z', 1);

  struct Registers* regs = create_registers_win(6, 0);

  struct Memory* mem = create_mem_win(0, 23);

  int ch;
  while ((ch = getch()) != 'q') {
    switch (ch) {
      case KEY_UP:
      case 'k':
        update_mem_cursor(mem, mem->cursory - 1, mem->cursorx);
        break;
      case KEY_DOWN:
      case 'j':
        update_mem_cursor(mem, mem->cursory + 1, mem->cursorx);
        break;
      case KEY_LEFT:
      case 'h':
        update_mem_cursor(mem, mem->cursory, mem->cursorx - 1);
        break;
      case KEY_RIGHT:
      case 'l':
        update_mem_cursor(mem, mem->cursory, mem->cursorx + 1);
        break;
    }
  }

  endwin();
}
