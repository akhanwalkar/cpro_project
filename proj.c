#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define size 24
//thought process cuz what
//each peg will either go red or black or stay empty, can do that via enums
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
    peg pegs[size][size];
}board;
void theboard(board *b)
{
    for(int i=0; i<size; i++)
    {
        for(int j=0; j<size; j++)
        {
            b->pegs[i][j]=empty_peg;
        }
    }
}
void printing(board *b)
{
    printf("\n    ");
    printf("1 ");
    for(int col=1; col<9; col++)
    {
        printf(" %2d", col+1);
    }
    for(int col=9; col<size-1; col++)
    {
        printf(" %2d", col+1);
    }
    printf(" 24");
    printf("\n");
    printf(" 1   |");
    for(int col=1; col<size; col++)
    {
        printf(" %c ", b->pegs[0][col]);
    }
    printf("|\n");
    printf("    +");
    for(int col=0; col<size; col++)
    {
        printf("---");
    }
    printf("+");    
    printf("\n");
    for(int row=1; row<size-1; row++)
    {
        printf("%2d . |", row+1);
        for(int col=1; col<size; col++)
        {
            printf(" %c ", b->pegs[row][col]);
        }
        printf("| . \n");
    }
    printf("    +");
    for(int col=0; col<size; col++)
    {
        printf("---");
    }
    printf("+\n");
    printf("24   |");
    for(int col=1; col<size; col++)
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

int main()
{
    board pegboard;
    theboard(&pegboard);
    player curr_player=red_player;
    int row, col;
    printf("welcome to twixt, to quit please press ctrl c on your keyboard\n");
    printf("player1=red, player2= black\n");
    printf("player1 plays first\n");
    while(1)
    {
        printing(&pegboard);
        if(curr_player==red_player)
        {
            printf("player1 enter coordinates: ");
        }
        else
        {
            printf("player2 enter coordinates: ");
        }
        scanf("%d %d", &row, &col);
        if(row==1 || row== 24 || col==1 || col ==24)
        {
            printf("inavlid inputs, cant use until completing board, try again \n");
            continue;
        }
        if(row>size || col>size || row<0 || col <0)
        {
            printf("invalid input, choose a value in range\n");
            continue; //cuz now whats the point of it continuing
        }
        if(pegboard.pegs[row][col]!=empty_peg)
        {
            printf("already occupied peg, choose another\n");
            continue;
        }
        if(curr_player==red_player)
        {
            pegboard.pegs[row-1][col-1]=red_peg;
        }
        else
        {
            pegboard.pegs[row-1][col-1]=black_peg;
        }
        curr_player=switchie(curr_player);
    }
    return 0;
}
