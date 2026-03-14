#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "functions.h"
int main()
{
    board pegboard;
    theboard(&pegboard);
    player curr_player=red_player;
    int row, col;
    int switch_count=0;
    printf("welcome to twixt, to quit please press ctrl c on your keyboard\n");
    printf("player1=red, player2= black\n");
    printf("player1 plays first\n");
    int game_running=1;
    int input_result;
    while(game_running)
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
        do {
            input_result = get_player_input(&row, &col);
            
            if (input_result == -1) {
                // User wants to quit
                printf("\nThanks for playing!\n");
                return 0;
            }
        } while (input_result == 0);  // Loop until valid input

        /* commented out because we are using the get_player_input function now */
        // scanf("%d %d", &row, &col);
        if(row==0 || row== 23 || col==0 || col ==23)
        {
            printf("inavlid inputs, cant use until completing board, try again \n");
            return 0;
        }
        if(row>BOARD_SIZE || col>BOARD_SIZE || row<0 || col <0)
        {
            printf("invalid input, choose a value in range\n");
            return 0; //cuz now whats the point of it continuing
        }
        if(pegboard.pegs[row][col]!=empty_peg)
        {
            printf("already occupied peg, choose another\n");
            return 0;;
        }
        if(curr_player==red_player)
        {
            pegboard.pegs[row][col]=red_peg;
        }
        else
        {
            pegboard.pegs[row][col]=black_peg;
        }
        auto_link(&pegboard, row, col, curr_player==red_player?red_peg:black_peg);
        //check for winner
        if(check_winner(&pegboard, curr_player==red_player?red_peg:black_peg))
        {
            printf("%s won game over\n", curr_player==red_player?"red":"black");
            return 0;
        }
        /*
        if((red_count>=1 && black_count>=1) && switch_count>0);
        {
            position p1={row,col};
            position p2;
            printf("enter coordinates of second peg: ");
            scanf("%d %d", &p2.row, &p2.col);
            if(can_we_link(&pegboard, p1, p2))
            {
                link_arr[num_of_links].a=p1;
                link_arr[num_of_links].b=p2;                    
                num_of_links++;
                printf("yay you made a link!\n");
            }
            else
            {
                printf("you cant link these :( , its an invalid link\n");                
            }
        }*/
        curr_player=switchie(curr_player);
        switch_count++;
    }
    return 0;
}