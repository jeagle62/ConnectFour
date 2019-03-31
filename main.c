#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <locale.h>
#include <math.h>
#include <setjmp.h>
#include <signal.h>
#include <stdarg.h>
#include <stddef.h>

//declare globals
int p1Wins=0;
int p2Wins=0;
int aiMode=2;
//declare graph
struct graph{
    //adjacency matrix
    char** adjmat;
    //rows
    int row;
    //columns
    int col;
    //max digits to print
    int dig;
    //current player
    //R for 1st p, Y for 2nd p
    char player;

}board;


//function declarations
void printBoard(struct graph board);
struct graph dropPiece(struct graph board, char player);
struct graph aiDropPiece(struct graph board, int loc);
int checkWin(struct graph board, char player);
int isValid(struct graph board, int crow, int ccol);
int soloPlay(struct graph board);
int multiPlay(struct graph board);
int aiPlay(struct graph board);
int calcScore(struct graph board);
struct graph fixBoard(struct graph board, int loc);

//finished, untested
void printBoard(struct graph board){
    //print numbers above board
    printf(" ");
    for(int n=0;n<board.col;n++){
      if(n<10){
        printf(" %i ",n);
      }
      else{
        printf(" %i",n);
      }
    }
    printf("\n");
    //print top of board
    for(int t=0;t<board.col;t++){
        printf("---");
    }
    //aligning with sides
    printf("--");
    printf("\n");
    for(int r=0;r<board.row;r++){
        //print left edge of board
        printf("|");
        for(int c=0;c<board.col;c++)
        {
            printf(" %c ",board.adjmat[r][c]);
        }
        //print right edge of board
        printf("|\n");
    }

    //print bottom of board
    for(int b=0;b<board.col;b++){
        printf("---");
    }
    //aligning with sides
    printf("--\n");
    return;
}

struct graph dropPiece(struct graph board, char player){
    //never call dropPiece on a full board or it cannot exit the method.
    int loc,check;
    char space;
    ChooseLoc:
    printf("%c player, select a column.\n",player);
    check=scanf("%i",&loc);
    //eat the trailing newline char
    scanf("%c",&space);
    //read input from user into mode
    if(check!=1){
        printf("Error - not an integer. Please re-enter the value.\n\n");
        goto ChooseLoc;
    }
    else if(loc>=0&&loc<board.col){
        if(board.adjmat[0][loc]!=' '){
            printf("Invalid input - column full. Please try again.\n\n");
            goto ChooseLoc;
        }
        for(int x=board.row-1;x>-1;x--){
            if(board.adjmat[x][loc]==' '){
                board.adjmat[x][loc]=player;
                return board;
            }
        }
    }
    else{
        printf("Invalid input, please try again.\n");
        goto ChooseLoc;
    }
    return board;
}

int isValid(struct graph board, int crow, int ccol){
    if(crow<board.row&&crow>=0){
        if(ccol<board.col&&ccol>=0){
            return 1;
        }
    }
    return 0;
}

int checkWin(struct graph board, char player){
    for(int r=0;r<board.row;r++){
        for(int c=0;c<board.col;c++){
            //if player's token in location
            if(board.adjmat[r][c]==player){
                //check left
                if(isValid(board,r,c-1)==1&&board.adjmat[r][c-1]==player){
                    if(isValid(board,r,c-2)==1&&board.adjmat[r][c-2]==player){
                        if(isValid(board,r,c-3)==1&&board.adjmat[r][c-3]==player){
                            printf("%c wins!\n",player);
                            if(player=='X'){
                                p1Wins++;
                                printf("Score:\nP1: %i\tP2: %i\n\n",p1Wins,p2Wins);
                            }
                            else{
                                p2Wins++;
                                printf("Score:\nP1: %i\tP2: %i\n\n",p1Wins,p2Wins);
                            }
                            return 1;
                        }
                    }
                }
                //check right
                if(isValid(board,r,c+1)==1&&board.adjmat[r][c+1]==player){
                    if(isValid(board,r,c+2)==1&&board.adjmat[r][c+2]==player){
                        if(isValid(board,r,c+3)==1&&board.adjmat[r][c+3]==player){
                            printf("%c wins!\n",player);
                            if(player=='X'){
                                p1Wins++;
                                printf("Score:\nP1: %i\tP2: %i\n\n",p1Wins,p2Wins);
                            }
                            else{
                                p2Wins++;
                                printf("Score:\nP1: %i\tP2: %i\n\n",p1Wins,p2Wins);
                            }
                            return 1;
                        }
                    }
                }
                //check up
                if(isValid(board,r-1,c)==1&&board.adjmat[r-1][c]==player){
                    if(isValid(board,r-2,c)==1&&board.adjmat[r-2][c]==player){
                        if(isValid(board,r-3,c)==1&&board.adjmat[r-3][c]==player){
                            printf("%c wins!\n",player);
                            if(player=='X'){
                                p1Wins++;
                                printf("Score:\nP1: %i\tP2: %i\n\n",p1Wins,p2Wins);
                            }
                            else{
                                p2Wins++;
                                printf("Score:\nP1: %i\tP2: %i\n\n",p1Wins,p2Wins);
                            }
                            return 1;
                        }
                    }
                }
                //check down
                if(isValid(board,r+1,c)==1&&board.adjmat[r+1][c]==player){
                    if(isValid(board,r+2,c)==1&&board.adjmat[r+2][c]==player){
                        if(isValid(board,r+3,c)==1&&board.adjmat[r+3][c]==player){
                            printf("%c wins!\n",player);
                            if(player=='X'){
                                p1Wins++;
                                printf("Score:\nP1: %i\tP2: %i\n\n",p1Wins,p2Wins);
                            }
                            else{
                                p2Wins++;
                                printf("Score:\nP1: %i\tP2: %i\n\n",p1Wins,p2Wins);
                            }
                            return 1;
                        }
                    }
                }
                //check up right diagonal
                if(isValid(board,r-1,c+1)==1&&board.adjmat[r-1][c+1]==player){
                    if(isValid(board,r-2,c+2)==1&&board.adjmat[r-2][c+2]==player){
                        if(isValid(board,r-3,c+3)==1&&board.adjmat[r-3][c+3]==player){
                           printf("%c wins!\n",player);
                            if(player=='X'){
                                p1Wins++;
                                printf("Score:\nP1: %i\tP2: %i\n\n",p1Wins,p2Wins);
                            }
                            else{
                                p2Wins++;
                                printf("Score:\nP1: %i\tP2: %i\n\n",p1Wins,p2Wins);
                            }
                            return 1;
                        }
                    }
                }
                //check up left diagonal
                if(isValid(board,r-1,c-1)==1&&board.adjmat[r-1][c-1]==player){
                    if(isValid(board,r-2,c-2)==1&&board.adjmat[r-2][c-2]==player){
                        if(isValid(board,r-3,c-3)==1&&board.adjmat[r-3][c-3]==player){
                            printf("%c wins!\n",player);
                            if(player=='X'){
                                p1Wins++;
                                printf("Score:\nP1: %i\tP2: %i\n\n",p1Wins,p2Wins);
                            }
                            else{
                                p2Wins++;
                                printf("Score:\nP1: %i\tP2: %i\n\n",p1Wins,p2Wins);
                            }
                            return 1;
                        }
                    }
                }
                //check down right diagonal
                if(isValid(board,r+1,c+1)==1&&board.adjmat[r+1][c+1]==player){
                    if(isValid(board,r+2,c+2)==1&&board.adjmat[r+2][c+2]==player){
                        if(isValid(board,r+3,c+3)==1&&board.adjmat[r+3][c+3]==player){
                            printf("%c wins!\n",player);
                            if(player=='X'){
                                p1Wins++;
                                printf("Score:\nP1: %i\tP2: %i\n\n",p1Wins,p2Wins);
                            }
                            else{
                                p2Wins++;
                                printf("Score:\nP1: %i\tP2: %i\n\n",p1Wins,p2Wins);
                            }
                            return 1;
                        }
                    }
                }
                //check down left diagonal
                if(isValid(board,r+1,c-1)==1&&board.adjmat[r+1][c-1]==player){
                    if(isValid(board,r+2,c-2)==1&&board.adjmat[r+2][c-2]==player){
                        if(isValid(board,r+3,c-3)==1&&board.adjmat[r+3][c-3]==player){
                            printf("%c wins!\n",player);
                            if(player=='X'){
                                p1Wins++;
                                printf("Score:\nP1: %i\tP2: %i\n\n",p1Wins,p2Wins);
                            }
                            else{
                                p2Wins++;
                                printf("Score:\nP1: %i\tP2: %i\n\n",p1Wins,p2Wins);
                            }
                            return 1;
                        }
                    }
                }

            }

        }
    }
    for(int d=0;d<board.col;d++){
        //if all other checks do not succeed and there is space in the top row, continue playing
        if(board.adjmat[0][d]==' '){
            return 0;
        }
    }

    printf("\nThe game is a draw.\n");
    return 1;
}

int soloPlay(struct graph board){

    board = dropPiece(board,board.player);
    printBoard(board);
    if(checkWin(board,board.player)==1){
        return 1;
    }
    //ternary operator to switch players
    //if player = 0, then set player to 1, else set player to 0
    board.player = (board.player=='X') ? (board.player = 'O') : (board.player = 'X');
    //call until there is a win
    soloPlay(board);
    //here to prevent infinite loop, should never be accessed
    return 0;

}

int multiPlay(struct graph board){
    if(board.player=='X'){
        printf("Player 1's move:\n");
    }
    else{
        printf("Player 2's move:\n");
    }
    board = dropPiece(board,board.player);
    printBoard(board);
    if(checkWin(board,board.player)==1){
        return 1;
    }
    //ternary operator to switch players
    //if player = 0, then set player to 1, else set player to 0
    board.player = (board.player=='X') ? (board.player = 'O') : (board.player = 'X');
    //call until there is a win
    multiPlay(board);
    //here to prevent infinite loop, should never be accessed
    return 0;

}

int aiPlay(struct graph board){
    int score,tempscore,move;
    struct graph tempboard;
    score = 0;
    tempscore = 0;
    if(board.player=='X'){
        //printf("Player 1's move:\n");
        board = dropPiece(board,board.player);
    }
    else{
        /*if(aiMode==2)
        {
            //normal mode
            printf("AI's move:\n");
            for(int x=0;x<board.col;x++)
            {
                if(board.adjmat[0][x]==' ')
                {
                    tempscore = calcScore(aiDropPiece(board,x));
                    board = fixBoard(board,x);
                    //if new board better than other iterations, assign it as the new iteration
                    if(tempscore>score)
                    {
                        score = tempscore;
                        move = x;
                    }
                }
            }

        //ai makes its actual move
        board = aiDropPiece(board,move);
        }
        else if(aiMode==1)
        {
            //easy mode
            printf("AI's move:\n");
            //randomly select a valid column
            int loc = rand() % board.col-1;
            //if random column does not work, iterate from that point until a valid column is selected
            while(loc<board.col-1&&board.adjmat[0][loc]!=0)
            {
                loc++;
                if(loc==board.col)
                {
                    loc=0;
                }
            }
            board = aiDropPiece(board,move);
        }
        else if(aiMode==0)
        {
            //helpful mode
            printf("AI's move:\n");
            for(int x=0;x<board.col;x++)
            {
            if(board.adjmat[0][x]==' ')
            {
                tempscore = calcScore(aiDropPiece(board,x));
                board = fixBoard(board,x);
                //if new board better than other iterations, assign it as the new iteration
                if(tempscore<score)
                {
                    score = tempscore;
                    move = x;
                }
            }
        }

        //ai makes its actual move
        board = aiDropPiece(board,move);*/

        printf("AI's move:\n");
            for(int x=0;x<board.col;x++){
                if(board.adjmat[0][x]==' '){
                    tempscore = calcScore(aiDropPiece(board,x));
                    board = fixBoard(board,x);
                    //if new board better than other iterations, assign it as the new iteration
                    if(tempscore>score){
                        score = tempscore;
                        move = x;
                    }
                }
            }

        //ai makes its actual move
        board = aiDropPiece(board,move);

    }

    printBoard(board);
    if(checkWin(board,board.player)==1){
        return 1;
    }
    //ternary operator to switch players
    //if player = 0, then set player to 1, else set player to 0
    board.player = (board.player=='X') ? (board.player = 'O') : (board.player = 'X');
    //call until there is a win
    aiPlay(board);
    //here to prevent infinite loop, should never be accessed
    return 0;
}

int calcScore(struct graph board){
    int score;
    //1 pt for each white space a token is touching, another 1 for one token in a row, 1+4 for 5 pts for 2 in a row, 1+4+13 for 18 for 3 in a row (unblocked ends, for possible wins in the future)
    //same scoring but negative when talking about player's tokens

    //very similar to checkWin, but does not return board state or declare win
    for(int r=0;r<board.row;r++){
        for(int c=0;c<board.col;c++){
            //if AI's token in location
            if(board.adjmat[r][c]=='O'){
                //check left
                if(isValid(board,r,c-1)==1&&board.adjmat[r][c-1]=='O'){
                    if(isValid(board,r,c-2)==1&&board.adjmat[r][c-2]=='O'){
                        if(isValid(board,r,c-3)==1&&board.adjmat[r][c-3]=='O'){
                            //return max positive score (winning move)
                            return 100000;
                        }
                        //if 3 tokens in a row with an empty space after
                        else if(isValid(board,r,c-3)==1&&board.adjmat[r][c-3]==' '){
                            score+=18;
                        }
                    }
                    //if 2 tokens in a row with an empty space after
                    else if(isValid(board,r,c-2)==1&&board.adjmat[r][c-2]==' '){
                        score+=5;
                    }
                }
                else if(isValid(board,r,c-1)==1&&board.adjmat[r][c-1]==' '){
                    score+=1;
                }

                //check right
                if(isValid(board,r,c+1)==1&&board.adjmat[r][c+1]=='O'){
                    if(isValid(board,r,c+2)==1&&board.adjmat[r][c+2]=='O'){
                        if(isValid(board,r,c+3)==1&&board.adjmat[r][c+3]=='O'){
                            //return max positive score (winning move)
                            return 100000;
                        }
                        else if(isValid(board,r,c+3)==1&&board.adjmat[r][c+3]==' '){
                            score+=18;
                        }
                    }
                    else if(isValid(board,r,c+2)==1&&board.adjmat[r][c+2]==' '){
                        score+=5;
                    }
                }
                else if(isValid(board,r,c+2)==1&&board.adjmat[r][c+2]==' '){
                    score+=1;
                }

                //check up
                if(isValid(board,r-1,c)==1&&board.adjmat[r-1][c]=='O'){
                    if(isValid(board,r-2,c)==1&&board.adjmat[r-2][c]=='O'){
                        //if space above 3 tiles open, win possible this turn
                        if(isValid(board,r-3,c)==1&&board.adjmat[r-3][c]=='O'){
                            //return max positive score (winning move)
                            return 100000;
                        }
                        else if(isValid(board,r-3,c)==1&&board.adjmat[r-3][c]==' '){
                            score+=18;
                        }
                    }
                    else if(isValid(board,r-2,c)==1&&board.adjmat[r-2][c]==' '){
                        score+=5;
                    }
                }
                else if(isValid(board,r-3,c)==1&&board.adjmat[r-3][c]==' '){
                    score+=1;
                }

                //check up right diagonal
                if(isValid(board,r-1,c+1)==1&&board.adjmat[r-1][c+1]=='O'){
                    if(isValid(board,r-2,c+2)==1&&board.adjmat[r-2][c+2]=='O'){
                        if(isValid(board,r-3,c+3)==1&&board.adjmat[r-3][c+3]=='O'){
                            //return max positive score (winning move)
                            return 100000;
                        }
                        else if(isValid(board,r-3,c+3)==1&&board.adjmat[r-3][c+3]==' '){
                            score+=18;
                        }
                    }
                    else if(isValid(board,r-2,c+2)==1&&board.adjmat[r-2][c+2]==' '){
                        score+=5;
                    }
                }
                else if(isValid(board,r-1,c+1)==1&&board.adjmat[r-1][c+1]==' '){
                    score+=1;
                }

                //check up left diagonal
                if(isValid(board,r-1,c-1)==1&&board.adjmat[r-1][c-1]=='O'){
                    if(isValid(board,r-2,c-2)==1&&board.adjmat[r-2][c-2]=='O'){
                        if(isValid(board,r-3,c-3)==1&&board.adjmat[r-3][c-3]=='O'){
                            //return max positive score (winning move)
                            return 100000;
                        }
                        else if(isValid(board,r-3,c-3)==1&&board.adjmat[r-3][c-3]==' '){
                            score+=18;
                        }
                    }
                    else if(isValid(board,r-2,c-2)==1&&board.adjmat[r-2][c-2]==' '){
                        score+=5;
                    }
                }
                else if(isValid(board,r-1,c-1)==1&&board.adjmat[r-1][c-1]==' '){
                    score+=1;
                }

                //check down right diagonal
                if(isValid(board,r+1,c+1)==1&&board.adjmat[r+1][c+1]=='O'){
                    if(isValid(board,r+2,c+2)==1&&board.adjmat[r+2][c+2]=='O'){
                        if(isValid(board,r+3,c+3)==1&&board.adjmat[r+3][c+3]=='O'){
                            //return max positive score (winning move)
                            return 100000;
                        }
                        else if(isValid(board,r+3,c+3)==1&&board.adjmat[r+3][c+3]==' '){
                            score+=18;
                        }
                    }
                    else if(isValid(board,r+2,c+2)==1&&board.adjmat[r+2][c+2]==' '){
                        score+=5;
                    }
                }
                else if(isValid(board,r+2,c+2)==1&&board.adjmat[r+2][c+2]==' '){
                    score+=1;
                }

                //check down left diagonal
                if(isValid(board,r+1,c-1)==1&&board.adjmat[r+1][c-1]=='O'){
                    if(isValid(board,r+2,c-2)==1&&board.adjmat[r+2][c-2]=='O'){
                        if(isValid(board,r+3,c-3)==1&&board.adjmat[r+3][c-3]=='O'){
                           //return max positive score (winning move)
                            return 100000;
                        }
                        else if(isValid(board,r+3,c-3)==1&&board.adjmat[r+3][c-3]==' '){
                            score+=18;
                        }
                    }
                    else if(isValid(board,r+2,c-2)==1&&board.adjmat[r+2][c-2]==' '){
                        score+=5;
                    }
                }
                else if(isValid(board,r+2,c-2)==1&&board.adjmat[r+2][c-2]==' '){
                    score+=1;
                }

            }
            //if player's token in location
            else if(board.adjmat[r][c]=='X'){
                //check left
                if(isValid(board,r,c-1)==1&&board.adjmat[r][c-1]=='X'){
                    if(isValid(board,r,c-2)==1&&board.adjmat[r][c-2]=='X'){
                        //if winning space for red is empty and it's the bottom row, red can win on next move
                        if(r==board.row-1&&isValid(board,r,c-3)&&board.adjmat[r][c-3]==' '){
                            return -100000;
                        }
                        //else if space beneath winning space for red is full, red can win on next move
                        else if(isValid(board,r+1,c-3)==1&&board.adjmat[r+1][c-3]!=' '&&isValid(board,r,c-3)&&board.adjmat[r][c-3]==' '){
                            //return min score (losing move)
                            return -100000;
                        }
                        //if 3 tokens in a row with an empty space after
                        else if(isValid(board,r,c-3)==1&&board.adjmat[r][c-3]==' '){
                            score-=18;
                        }
                    }
                    //if 2 tokens in a row with an empty space after
                    else if(isValid(board,r,c-2)==1&&board.adjmat[r][c-2]==' '){
                        score-=5;
                    }
                }
                else if(isValid(board,r,c-1)==1&&board.adjmat[r][c-1]==' '){
                    score-=1;
                }

                //check right
                if(isValid(board,r,c+1)==1&&board.adjmat[r][c+1]=='X'){
                    if(isValid(board,r,c+2)==1&&board.adjmat[r][c+2]=='X'){
                        //if winning space for red is empty and it's the bottom row, red can win on next move
                        if(r==board.row&&isValid(board,r,c+3)&&board.adjmat[r][c+3]==' '){
                            return -100000;
                        }
                        //else if space beneath winning space for red is full, red can win on next move
                        else if(isValid(board,r+1,c+3)==1&&board.adjmat[r+1][c+3]!=' '&&isValid(board,r,c+3)&&board.adjmat[r][c+3]==' '){
                            //return min score (losing move)
                            return -100000;
                        }
                        else if(isValid(board,r,c+3)==1&&board.adjmat[r][c+3]==' '){
                            score-=18;
                        }
                    }
                    else if(isValid(board,r,c+2)==1&&board.adjmat[r][c+2]==' '){
                        score-=5;
                    }
                }
                else if(isValid(board,r,c+1)==1&&board.adjmat[r][c+1]==' '){
                    score-=1;
                }

                //check up
                if(isValid(board,r-1,c)==1&&board.adjmat[r-1][c]=='X'){
                    if(isValid(board,r-2,c)==1&&board.adjmat[r-2][c]=='X'){
                        if(isValid(board,r-3,c)==1&&board.adjmat[r-3][c]==' '){
                            //return min score (losing move)
                            return -100000;
                        }
                        else if(isValid(board,r-3,c)==1&&board.adjmat[r-3][c]==' '){
                            score-=18;
                        }
                    }
                    else if(isValid(board,r-2,c)==1&&board.adjmat[r-2][c]==' '){
                        score-=5;
                    }
                }
                else if(isValid(board,r-1,c)==1&&board.adjmat[r-1][c]==' '){
                    score-=1;
                }

                //check up right diagonal
                if(isValid(board,r-1,c+1)==1&&board.adjmat[r-1][c+1]=='X'){
                    if(isValid(board,r-2,c+2)==1&&board.adjmat[r-2][c+2]=='X'){
                        //if space beneath red winning space is full, win possible this turn for red
                        if(isValid(board,r-2,c+3)==1&&board.adjmat[r-2][c+3]!=' '&&isValid(board,r-3,c+3)==1&&board.adjmat[r-3][c+3]==' '){
                            //return min score (losing move)
                            return -100000;
                        }
                        else if(isValid(board,r-3,c+3)==1&&board.adjmat[r-3][c+3]==' '){
                            score-=18;
                        }
                    }
                    else if(isValid(board,r-2,c+2)==1&&board.adjmat[r-2][c+2]==' '){
                        score-=5;
                    }
                }
                else if(isValid(board,r-1,c+1)==1&&board.adjmat[r-1][c+1]==' '){
                    score-=1;
                }
                //check up left diagonal
                if(isValid(board,r-1,c-1)==1&&board.adjmat[r-1][c-1]=='X'){
                    if(isValid(board,r-2,c-2)==1&&board.adjmat[r-2][c-2]=='X'){
                        if(isValid(board,r-2,c-3)==1&&board.adjmat[r-2][c-3]!=' '&&isValid(board,r-3,c-3)&&board.adjmat[r-3][c-3]==' '){
                            //return min score (losing move)
                            return -100000;
                        }
                        else if(isValid(board,r-3,c-3)==1&&board.adjmat[r-3][c-3]==' '){
                            score-=18;
                        }
                    }
                    else if(isValid(board,r-2,c-2)==1&&board.adjmat[r-2][c-2]==' '){
                        score-=5;
                    }
                }
                else if(isValid(board,r-1,c-1)==1&&board.adjmat[r-1][c-1]==' '){
                    score-=1;
                }

                //check down right diagonal
                if(isValid(board,r+1,c+1)==1&&board.adjmat[r+1][c+1]=='X'){
                    if(isValid(board,r+2,c+2)==1&&board.adjmat[r+2][c+2]=='X'){
                        //if on bottom row for last check
                        if(r+3==board.row-1&&isValid(board,r+3,c+3)==1&&board.adjmat[r+3][c+3]==' '){
                            //return min score (losing move)
                            return -100000;
                        }
                        else if(isValid(board,r+4,c+3)==1&&board.adjmat[r+4][c+3]!=' '&&isValid(board,r+3,c+3)==1&&board.adjmat[r+3][c+3]==' '){
                            //return min score (losing move)
                            return -100000;
                        }
                        else if(isValid(board,r+3,c+3)==1&&board.adjmat[r+3][c+3]==' '){
                            score-=18;
                        }
                    }
                    else if(isValid(board,r+2,c+2)==1&&board.adjmat[r+2][c+2]==' '){
                        score-=5;
                    }
                }
                else if(isValid(board,r+2,c+2)==1&&board.adjmat[r+2][c+2]==' '){
                    score-=1;
                }

                //check down left diagonal
                if(isValid(board,r+1,c-1)==1&&board.adjmat[r+1][c-1]=='X'){
                    if(isValid(board,r+2,c-2)==1&&board.adjmat[r+2][c-2]=='X'){
                        //if on bottom row for last check
                        if(r+3==board.row-1&&isValid(board,r+3,c+3)==1&&board.adjmat[r+3][c+3]==' '){
                            //return min score (losing move)
                            return -100000;
                        }
                        else if(isValid(board,r+4,c-3)==1&&board.adjmat[r+4][c-3]!=' '&&isValid(board,r+3,c-3)==1&&board.adjmat[r+3][c-3]==' '){
                            //return min score (losing move)
                            return -100000;
                        }
                        else if(isValid(board,r+3,c-3)==1&&board.adjmat[r+3][c-3]==' '){
                            score-=18;
                        }
                    }
                    else if(isValid(board,r+2,c-2)==1&&board.adjmat[r+2][c-2]==' '){
                        score-=5;
                    }
                }
                else if(isValid(board,r+2,c-2)==1&&board.adjmat[r+2][c-2]==' '){
                    score-=1;
                }
            }

        }
    }
    return score;
}

//unused, previously used in AI but found to cause suboptimal AI placement
int adjBlanks(struct graph board, int r, int c){
    //sum all blank spaces adjacent to given location
    int sum=0;
    for(int x=-1;x<2;x++){
        for(int y=-1;y<2;y++){
            if(isValid(board,r+x,c+y)==1&&board.adjmat[r+x][c+y]==' '){
                sum++;
            }
        }
    }
    return sum;
}

struct graph aiDropPiece(struct graph board, int loc){
        for(int x=board.row-1;x>-1;x--){
            if(board.adjmat[x][loc]==' '){
                board.adjmat[x][loc]='O';
                return board;
            }
        }
    return board;
}

struct graph fixBoard(struct graph board, int loc){
        for(int x=0;x<board.row;x++){
            if(board.adjmat[x][loc]!=' '){
                board.adjmat[x][loc]=' ';
                return board;
            }
        }
    return board;
}

int main(){
    //declare variables
    int row,col,mode,check;
    char space;

    //borrowed code from https://stackoverflow.com/questions/21073714/safe-way-to-determine-the-maximum-integer-value-without-resorting-to-limits-h
    //setting max_int without using limits.h
    int max_int = (unsigned int) -1 >> 1;

    //print welcome message with first menu
    printf("Welcome to Connect Four!\nWhich mode would you like to play?\n");
    Menu1:
    printf("1 - Solo Play\n2 - Multiplayer\n3 - Versus Computer\n\n4 - Exit\n");\
    check=scanf("%i",&mode);
    //eat the trailing newline char
    scanf("%c",&space);
    //read input from user into mode

    if(check!=1){
        printf("Error - not an integer. Please re-enter your selection.\n\n");
        goto Menu1;
    }
    //if no expected input
    if(!(mode==1||mode==2||mode==3||mode==4)){
        printf("Invalid selection, please try again.\n");
        goto Menu1;
    }
    //define Rows for value check
    Rows:
    printf("Please enter the number of rows: ");
    check=(int)scanf("%i",&row);
    //eat the trailing newline char
    scanf("%c",&space);
    //read input from user into mode
    if(check!=1){
        printf("Error - not an integer. Please re-enter the value.\n\n");
        goto Rows;
    }

    //if larger than 0 and less than max value
    if(row<1 || row > max_int){
        //"Invalid row size, please try again."
        printf("Invalid row size, please try again.\n");
        goto Rows;
    }
    //define Columns for value check
    Columns:
    printf("Please enter the number of columns: ");
    check=scanf("%i",&col);
    //eat the trailing newline char
    scanf("%c",&space);
    if(check!=1){
        printf("Error - not an integer. Please re-enter the value.\n\n");
        goto Columns;
    }
    //if larger than 0 and less than max value
    if(col<1 || col > max_int){
        //"Invalid column size, please try again."
        printf("Invalid column size, please try again.\n");
        goto Columns;
    }
    //if board not big enough for four in a row
    if(row<=3&&col<=3){
        printf("Invalid board size - four in a row impossible. Please try again.\n");
        goto Rows;
    }
    if(row>35||col>35){printf("\nDue to the size of the board, the display may be misaligned.\n\n");}
    //initialize board
    struct graph* temp = &board;
    //load row and col into board
    board.row=row;
    board.col=col;
    //load max number of digits into board
    board.dig=0;
    //player one to start on board
    board.player='X';
    while(col>10){
        col/=10;
        board.dig++;
    }
    //allocate memory for one matrix dimension of arrays
    //dynamic allocation using a pointer to pointers
    board.adjmat = (char**)malloc(board.row* sizeof(char*));
    //allocate memory for the each array in the matrix
    for(int x=0;x<board.row;x++){
        //pointer to each row then allocates col * max int size on machine
        //equivalent to *(board.adjmat+x) = ...;
        board.adjmat[x] = (char*)malloc(board.col* sizeof(char));
    }
    //fill matrix to initialize cells
    for(int r=0;r<board.row;r++){
        for(int c=0;c<board.col;c++){
            board.adjmat[r][c] = ' ';
        }
    }
    //launch correct game mode
    char rematch;
    switch(mode){
        case 1: printBoard(board);
                soloPlay(board);
                printf("Enter R to rematch, anything else to quit.\n");
                check=scanf("%c",&rematch);
                if(rematch=='R'){
                    goto Rows;
                }
                break;
        case 2: printBoard(board);
                multiPlay(board);
                printf("Enter R to rematch, anything else to quit.\n");
                check=scanf("%c",&rematch);
                if(rematch=='R'){
                    goto Rows;
                }
                break;
        case 3: /*AiDiff:
                check=scanf("%i",&aiMode);
                //eat the trailing newline char
                scanf("%c",&space);
                //read input from user into mode
                if(check!=1)
                {
                    printf("Error - not an integer. Please re-enter your selection.\n\n");
                    goto AiDiff;
                }*/
                printBoard(board);
                aiPlay(board);
                printf("Enter R to rematch, anything else to quit.\n");
                check=scanf("%c",&rematch);
                if(rematch=='R'){
                    goto Rows;
                }
                break;
        case 4: printf("\nThank you for playing, have a nice day!");
                return 0;

        default: break;
    }

    //free memory allocated to board, clearing states
    free(board.adjmat[0]);
    free(board.adjmat);
    return 0;
}
