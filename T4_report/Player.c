//
// Created by juanm on 12/12/2021.
//
#include "Player.h"
#include "stdio.h"
#include <stdlib.h>
#include <stdbool.h>


struct Player create_new_player(int penguins)
{
    struct Player p;
    p.penguins_size = 0;
    p.wasted_penguins_size = 0;
    p.current_score = 0;
    p.penguins = malloc(penguins*sizeof *p.penguins);
    p.wasted_penguins = malloc(penguins*sizeof *p.wasted_penguins);
    return p;
}
void change_player(int *currentPlayer){

    if (*currentPlayer == 0){
        *currentPlayer = 1;
    }else if(*currentPlayer == 1){
        *currentPlayer = 0;
    }
}

void save_penguin_coordinates(struct Player* p, int x, int y){
    p->penguins[p->penguins_size].x = x;
    p->penguins[p->penguins_size].y = y;
    p->penguins_size += 1;

}

void change_penguin_coordinates(struct Player *p, struct Penguin penguin, int x, int y)
{
    int i;
    for(i = 0; i < p->penguins_size; i++)
    {
        if(p->penguins[i].x == penguin.x && p->penguins[i].y == penguin.y)
        {
            p->penguins[i].x = x;
            p->penguins[i].y = y;
            break;
        }
    }
}

void collect_fish(struct Board board, struct Player *p, int x, int y){
    p->current_score += board.field[y][x];
}

bool can_current_player_move(struct Board board, int *current_player,struct Player p1, struct Player p2, int key )
{
    bool result = true;
    if((*current_player) == 1)
    {
        result = check_penguins(board,&p1);
    }
    else if ((*current_player) == 0)
    {
        result = check_penguins(board,&p2);
    }
    if(result == false && key == 1)
    {
        change_player(current_player);
        return can_current_player_move(board, current_player,p1,p2,2);
    }
    return result;
}


bool check_penguins(struct Board board, struct  Player *p)
{
    bool result = false;
    int i,x,y;
    for( i = 0 ; i < p->penguins_size; i++)
    {
        x = p->penguins[i].x;
        y = p->penguins[i].y;
        if(!check_selected_penguin(board,x,y))
        {
            p->wasted_penguins[p->wasted_penguins_size].x = x;
            p->wasted_penguins[p->wasted_penguins_size].y = y;
            printf("WASTED PENGUIN : \n x -%d y - %d\n.", p->wasted_penguins[p->wasted_penguins_size].x, p->wasted_penguins[p->wasted_penguins_size].y);
            p->wasted_penguins_size++;
        }
        else
        {
            result = true;
        }
    }
    return result;
}


int move_penguin(struct Board board,int currentPlayer, int x, int y){
    int fish = board.field[y][x] - '0';
    printf("INT : %d", fish);
    if(currentPlayer == 0)
    {
        board.field[y][x] = 'a';
    }
    if (currentPlayer == 1)
    {
        board.field[y][x] = 'A';
    }
    return fish;
}

void determine_winner(struct Player p1, struct Player p2){

    printf("\nPlayer 1 score: %d", p1.current_score);
    printf("\nPlayer 2 score: %d", p2.current_score);

    if(p1.current_score > p2.current_score){
        printf("\nPlayer 1 was the winner!!!\n");
    }else if(p1.current_score < p2.current_score){
        printf("\nPlayer 2 was the winner!!!\n");
    }else{
        printf("\nIt was a draw!!\n");
    }
}
