#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "functions.h"  

void theboard(board *b)
{
    for(int i=0; i<BOARD_SIZE; i++)
    {
        for(int j=0; j<BOARD_SIZE; j++)
        {
            b->pegs[i][j]=empty_peg;
        }
    }
}

void printing(board *b)
{
    printf("\n    ");
    printf("0");
    for(int col=1; col<9; col++)
    {
        printf(" %2d", col);
    }
    for(int col=9; col<BOARD_SIZE-1; col++)
    {
        printf(" %2d", col);
    }
    printf(" 23");
    printf("\n");
    printf(" 0   |");
    for(int col=1; col<BOARD_SIZE; col++)
    {
        printf(" %c ", b->pegs[0][col]);
    }
    printf("|\n");
    printf("    +");
    for(int col=0; col<BOARD_SIZE; col++)
    {
        printf("---");
    }
    printf("+");    
    printf("\n");
    for(int row=1; row<BOARD_SIZE-1; row++)
    {
        printf("%2d . |", row);
        for(int col=1; col<BOARD_SIZE; col++)
        {
            printf(" %c ", b->pegs[row][col]);
        }
        printf("| . \n");
    }
    printf("    +");
    for(int col=0; col<BOARD_SIZE; col++)
    {
        printf("---");
    }
    printf("+\n");
    printf("23   |");
    for(int col=1; col<BOARD_SIZE; col++)
    {
        printf(" %c ", b->pegs[23][col]);
    }
    printf("| \n");
}

//switching between the players
player switchie(player p_player)
{
    if(p_player==red_player)
    {
        return black_player;
    }
    else
    {
        return red_player;
    }
}
//now we start checking for if links are possible
typedef struct position{
    int row;
    int col;
}position; 

typedef struct link
{
    position a;
    position b;
}link;

#define MAX_LINK 10000 //you cant put a semicolon here????
link link_arr[MAX_LINK];
int num_of_links=0; //initially, then keep adding into array 

int linking(position p1, position p2)
{
    int dist_r=abs(p1.row-p2.row);
    int dist_c=abs(p1.col-p2.col);
    int acceptable[2][2]={{1,2},{2,1}}; //acceptable moves (kinghts moves)
    return (dist_r==acceptable[0][0] && dist_c==acceptable[0][1]) || (dist_r==acceptable[1][0] && dist_c==acceptable[1][1]);
    //checks if it moved those coordinates (treat everyhting like the tiny rect)
}

int if_same(peg a, peg b)
{
    switch (a)
    {
        case red_peg: return b==red_peg;
        case black_peg: return b==black_peg;
        default: return 0;
    }
}

//corssing isnt allowed, so we make sure there arent any intersection, which means the path of coordinates

int orientation(position p, position q, position r) 
{
    int val = (q.col - p.col)*(r.row - q.row) - (q.row - p.row)*(r.col - q.col); //this is basically the formula using dets but in code form
    if (val == 0) return 0;          // collinear
    if(val>0) return 1;
    else return 2;     // clockwise or counterclockwise
}
// int are_we_crossing(position a, position b, position c, position d) 
// {
//     //check combo of every possible corssing possible when first AB is line then CD is line
//     int o1 = orientation(a, b, c);
//     int o2 = orientation(a, b, d);
//     int o3 = orientation(c, d, a);
//     int o4 = orientation(c, d, b);

//     return (o1 != o2 && o3 != o4);


// int can_we_link(board *b, position p1, position p2) {

//     // 1. Check they belong to same player
//     if (if_same(b->pegs[p1.row][p1.col], b->pegs[p2.row][p2.col])==0)
//         return 0;

//     // 2. Knight move requirement
//     if (linking(p1, p2)==0)
//         return 0;

//     // 3. Check crossing with all previous links
//     for (int i = 0; i < num_of_links; i++) 
//     {
//         if (are_we_crossing(p1, p2, link_arr[i].a, link_arr[i].b))
//             return 0;
//     }

//     return 1; // Link is legal
// }

void link_them(position p1, position p2) {
    link_arr[num_of_links].a = p1;
    link_arr[num_of_links].b = p2;
    num_of_links++;
}
// Check if a link already exists between two positions
int if_link_exists(int r1, int c1, int r2, int c2) {
    for (int i = 0; i < num_of_links; i++) {
        link l = link_arr[i];
        if ((l.a.row == r1 && l.a.col == c1 &&
             l.b.row == r2 && l.b.col == c2) ||
            (l.a.row == r2 && l.a.col == c2 &&
             l.b.row == r1 && l.b.col == c1)) {
            return 1;
        }
    }
    return 0;
}
// Check if two line segments intersect
// Line segment 1: (r1,c1) to (r2,c2)
// Line segment 2: (r3,c3) to (r4,c4)
//this was orginal crossing, but there arent 3 points, its two so use the same logic as u do for mathematically to check if points are on the same
//side of line or not

// int are_we_crossing(position a, position b, position c, position d) 
// {
//     //check combo of every possible corssing possible when first AB is line then CD is line
//     int o1 = orientation(a, b, c);
//     int o2 = orientation(a, b, d);
//     int o3 = orientation(c, d, a);
//     int o4 = orientation(c, d, b);

//     return (o1 != o2 && o3 != o4);
// }

int links_intersect(int r1, int c1, int r2, int c2, int r3, int c3, int r4, int c4) {
    // Same line, not an intersection
    if ((r1 == r3 && c1 == c3 && r2 == r4 && c2 == c4) ||
        (r1 == r4 && c1 == c4 && r2 == r3 && c2 == c3)) {
        return 0;
    }
    
    // Check if they collinear
    if ((r1 == r3 && c1 == c3) || (r1 == r4 && c1 == c4) ||
        (r2 == r3 && c2 == c3) || (r2 == r4 && c2 == c4)) {
        return 0;  // Sharing endpoint is ok
    }
    
    // Use cross product to check intersection
    // Vector cross product method
    double x1 = c1, y1 = r1;
    double x2 = c2, y2 = r2;
    double x3 = c3, y3 = r3;
    double x4 = c4, y4 = r4;
    
    double denom = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    
    if (fabs(denom) < 1e-10) {
        // Parallel or coincident
        return 0;
    }
    
    double t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / denom;
    double u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / denom;
    
    // Check if intersection point is within both line segments
    if (t > 0 && t < 1 && u > 0 && u < 1) {
        return 1;  // They intersect
    }
    
    return 0;
}
// Check if a new link can be added (doesn't cross existing links)
int can_add_link(int r1, int c1, int r2, int c2) {
    // Check if link already exists
    if (if_link_exists(r1, c1, r2, c2)) {
        return 0;
    }
    
    // Check against all existing links
    for (int i = 0; i < num_of_links; i++) {
        link l = link_arr[i];
        
        if (links_intersect(r1, c1, r2, c2, l.a.row, l.a.col, l.b.row, l.b.col)) {
            return 0;  // Would cross an existing link
        }
    }
    
    return 1;
}


// Check if a position is within board bounds
int is_valid_position(int row, int col) {
    return (row >= 1 && row < BOARD_SIZE && col >= 1 && col < BOARD_SIZE);
}
void auto_link(board* board, int row, int col, peg p1) {
    // All possible knight moves (8 directions)
    int acceptable_moves[8][2] = {
        {-2, -1}, {-2, 1}, {-1, -2}, {-1, 2},
        {2, -1}, {2, 1}, {1, -2}, {1, 2}
    };
    
    int links_added = 0;
    
    // Check all 8 possible knight moves
    printf("link made with %d, %d\n", row, col);
    for (int i = 0; i < 8; i++) {
        int new_row = row + acceptable_moves[i][0];
        int new_col = col + acceptable_moves[i][1];
        // Check if target position has a peg of the same player
        if (is_valid_position(new_row, new_col) && board->pegs[new_row][new_col] == p1) {   
            // Try to add the link
            if (can_add_link(row, col, new_row, new_col)) {
                links_added++;
                link_them((position){row, col}, (position){new_row, new_col});
            }
        }
    }
    
    if (links_added > 0) {
        printf("link made! %d links added\n", links_added);
    }
}

int get_link_options(int row, int col, peg player_peg, position options[8]) {
    int count = 0;
    //checking for any valid link in surrounding

    for (int i = 0; i < num_of_links; i++) {
        link l = link_arr[i];
        
        if (l.a.row == row && l.a.col == col) {
            // Other end is at l.b
            options[count].row = l.b.row;
            options[count].col = l.b.col;
            count++;
        } else if (l.b.row == row && l.b.col == col) {
            // Other end is at l.a
            options[count].row = l.a.row;
            options[count].col = l.a.col;
            count++;
        }
    }
    
    return count;
}

int check_red_winner_dp(board* b) {
    int dp[BOARD_SIZE][BOARD_SIZE];
    memset(dp, 0, sizeof(dp));
    //all are valid to begin with
    for (int row = 1; row < BOARD_SIZE - 1; row++) {
        if (b->pegs[row][1] == red_peg) {
            dp[row][1] = 1;
        }
    }

    int changed = 1;
    while (changed) {
        changed = 0;
        
        // Checking all positions
        for (int i = 1; i < BOARD_SIZE - 1; i++) {
            for (int j = 1; j < BOARD_SIZE - 1; j++) {
                if (dp[i][j] || b->pegs[i][j] != red_peg) {
                    continue;
                }
                position options[8];
                int option_count = get_link_options(i, j, red_peg, options);
                
                for (int k = 0; k < option_count; k++) {
                    int nr = options[k].row;
                    int nc = options[k].col;
                    
                    if (dp[nr][nc]) {
                        dp[i][j] = 1;
                        changed = 1;
                        break;
                    }
                }
            }
        }
    }
    
    for (int row = 1; row < BOARD_SIZE - 1; row++) {
        if (dp[row][22]) {
            return 1;  // red win
        }
    }
    
    return 0;
}

int check_black_winner_dp(board* b) {
    int dp[BOARD_SIZE][BOARD_SIZE];
    memset(dp, 0, sizeof(dp));
    
    for (int col = 1; col < BOARD_SIZE - 1; col++) {
        if (b->pegs[1][col] == black_peg) {
            dp[1][col] = 1;
        }
    }
    int changed = 1;
    while (changed) {
        changed = 0;
        
        for (int i = 1; i < BOARD_SIZE - 1; i++) {
            for (int j = 1; j < BOARD_SIZE - 1; j++) {
                // Skip if already reachable or not a BLACK peg
                if (dp[i][j] || b->pegs[i][j] != black_peg) {
                    continue;
                }

                position options[8];
                int option_count = get_link_options(i, j, black_peg, options);
                
                for (int k = 0; k < option_count; k++) {
                    int nr = options[k].row;
                    int nc = options[k].col;
                    
                    if (dp[nr][nc]) {
                        dp[i][j] = 1;
                        changed = 1;
                        break;
                    }
                }
            }
        }
    }
    
    for (int col = 1; col < BOARD_SIZE - 1; col++) {
        if (dp[22][col]) {
            return 1;  //black
        }
    }
    return 0;
}

int check_winner(board* b, peg player_peg) {
    if (player_peg == red_peg) {
        return check_red_winner_dp(b);
    } else if (player_peg == black_peg) {
        return check_black_winner_dp(b);
    }
    return 0;
}


// Function to display help during game
void display_help() {
    printf("\n");
    printf("QUICK REFERENCE:\n");
    printf("────────────────\n");
    printf("• Input format: <row> <col>  (e.g., 5 10)\n");
    printf("• Board range: 0-23 for both row and column\n");
    printf("• Commands:\n");
    printf("  - 'help' : Show this help\n");
    printf("  - 'quit' : Exit game\n");
    printf("\n");
    printf("WINNING:\n");
    printf("────────\n");
    printf("• RED: Connect left to right via linked pegs\n");
    printf("• BLACK: Connect topA to bottom via linked pegs\n");
    printf("• Links = Knight's move (chess) between your pegs\n");
    printf("• Links auto-connect when valid\n");
    printf("\n");
}
// Function to get player input
int get_player_input(int* row, int* col) {
    char input[100];
    
    printf("Enter coordinates (row col): ");
    
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return -1; 
    }

    input[strcspn(input, "\n")] = 0;

    if (strcmp(input, "quit") == 0 || strcmp(input, "q") == 0) {
        return -1;
    }
    
    if (strcmp(input, "help") == 0 || strcmp(input, "h") == 0) {
        display_help();
        return 0; 
    }

    if (sscanf(input, "%d %d", row, col) != 2) {
        printf("Invalid input! Please enter two numbers: row col\n");
        return 0;
    }
    return 1; 
}
