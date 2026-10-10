#include "tic_tac_toe.h"

/*
600 *600
0 | 1 | 2
--+---+--
3 | 4 | 5
--+---+--
6 | 7 | 8
une case = 200 pixel

*/
int get_clicked_cell(int x, int y)
{

   int col = x / 200;
    int row = y / 200;
    int res=row * 3 + col;
    return res;
}

void handle_click(int board[3][3], int row, int col, int *player)
{
    // case occup
    if (board[row][col] != 0)
    {
        return;
    }

  
    board[row][col] = *player;

    if (*player == 1)
    {
        *player = 2;
    }
    else
    {
        *player = 1;
    }
}

int is_board_full(int board[3][3])
{
 for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            if (board[row][col] == 0)
            {
                return 0;
            }
        }
    }
    return 1;
}

int check_winner(int board[3][3])
{
    for (int row = 0; row < 3; row++)
    {
        if (board[row][0] != 0 &&board[row][0] == board[row][1] && board[row][1] == board[row][2])
        {
            return board[row][0];
        }
    }

    for (int col = 0; col < 3; col++)
    {
        if (board[0][col] != 0 && board[0][col] == board[1][col] && board[1][col] == board[2][col])
        {
            return board[0][col];
        }
    }
    // "\""
    if (board[0][0] != 0 && board[0][0] == board[1][1] && board[1][1] == board[2][2])
    {
        return board[0][0];
    }

    if (board[0][2] != 0 && board[0][2] == board[1][1] &&board[1][1] == board[2][0])
    {
        return board[0][2];
    }

    
    return 0;
}