#ifndef TERMINAL_H
#define TERMINAL_H

#define ANSI_RESET "\033[0m"
#define ANSI_FG_GREEN "\033[32m"
#define ANSI_FG_YELLOW "\033[93m"
#define ANSI_FG_ORANGE "\033[38;5;208m"
#define ANSI_FG_RED "\033[31m"
#define ANSI_FG_GRAY "\033[90m"

// erases the end of the line before going to the next one, so nothing from
// the previous drawing stays on screen
#define NEWLINE "\033[K\n"

void clear_screen(void);
void cursor_home(void);
void clear_below(void);
void move_cursor(int row, int col);
void hide_cursor(void);
void show_cursor(void);
int raw_mode_on(void);
void raw_mode_off(void);

#endif // TERMINAL_H
