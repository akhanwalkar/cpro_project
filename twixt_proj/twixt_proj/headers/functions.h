#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#define BOARD_SIZE 24
#define MAX_LINK 10000 //you cant put a semicolon here????

typedef enum{
    red_peg='r',
    black_peg='b',
    empty_peg='.',
}peg;

typedef enum{
    red_player,
    black_player,
}player;

typedef struct board{
    peg pegs[BOARD_SIZE][BOARD_SIZE];
}board;

typedef struct position{
    int row;
    int col;
}position; 

typedef struct link
{
    position a;
    position b;
}link;

void theboard(board *b);
void printing(board *b);
player switchie(player p_player);
int linking(position p1, position p2);
int if_same(peg a, peg b);
int orientation(position p, position q, position r);
void link_them(position p1, position p2);
int if_link_exists(int r1, int c1, int r2, int c2);
int links_intersect(int r1, int c1, int r2, int c2, int r3, int c3, int r4, int c4);
int can_add_link(int r1, int c1, int r2, int c2);
int is_valid_position(int row, int col);
void auto_link(board* board, int row, int col, peg p1);
int get_link_options(int row, int col, peg player_peg, position options[8]);
int check_red_winner_dp(board* b);
int check_black_winner_dp(board* b);
int check_winner(board* b, peg player_peg);
void display_help();
int get_player_input(int* row, int* col);

#endif