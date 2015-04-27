//
//  main.cpp
//  Tic Tac Toe
//
//  Created by Peter Burgess on 2015-04-26.
//  Copyright (c) 2015 Peter Burgess. All rights reserved.
//
/*
 Simple 1 player version of tic tac toe against the computer. Limitations include
 -Player always plays as x and goes first
 -Can't set up two player mode
 
 It was just a small exercise for practice so I probably won't come back to fix the issues.
 
 */

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

void InitialiseGame(char[]);
void PrintGameBoard(char[]);
void PlayerTurn(char[], char);
bool CheckGameWon(char[], char);
void ComputerMove(char[]);
bool CheckForWinningMove(char[], char);


int main(int argc, const char * argv[]) {
    //Create game board as array
    char gameBoard[9];
    //player is either x or o
    char player;
    bool gameWon = false;
    InitialiseGame(gameBoard);
    for (int i = 0; i < 9; i++){
        if (i % 2 == 0)
            player = 'x';
        else
            player = 'o';
        PlayerTurn(gameBoard, player);
        gameWon = CheckGameWon(gameBoard, player);
        if (gameWon){
            std::cout << "Congratulations " << player << " you have won!";
            break;
        }
    }
    return 0;
}


//Sets up game board with every square empty (represented by a -). Prints out game instructions
void InitialiseGame(char gameBoard[]){
    //fill game board with - in each location
    for (int i = 0; i < 9; i++){
            gameBoard[i] = '-';
    }
    std::cout << "Instructions: Each position on the board is numbered 1 to 9, with 1 in the top left, 3 in the top right, 7 in the bottom left and 9 in the bottom right, as on a phone. When prompted, enter the number related to the position you wish to place your piece. The aim of the game is to get 3 in a row!" << std::endl;
    PrintGameBoard(gameBoard);
}

//Prints a 3x3 game board to the console. Takes a 9 element array of characters.
void PrintGameBoard(char gameBoard[]){
    for (int i = 0; i < 9; i++){
        std::cout << gameBoard[i] << " ";
        if ((i+1) % 3 == 0)         //creates a new line every 3 elements to create a 3 by 3 board
            std::cout << std::endl;
    }
    std::cout << '\n';
}

//Player places their piece on the gameboard. Input is the game board and which player's  turn it is (x or o)
void PlayerTurn(char gameBoard[], char player){
    int playerPosition; //will determine where on the board the piece is played
    while (true){
        if (player == 'o'){             //computer player always o at this point
            ComputerMove(gameBoard);
            PrintGameBoard(gameBoard);
            break;
        }
        else{
            std::cout << "Please select the position to place your " << player << ": ";
            std::cin >> playerPosition;
        
            if (playerPosition > 9 || playerPosition < 1){  //if the entered number is not on the board
                std::cout << "That is not a valid entry. Please try again" << std::endl;
            }
            else if (gameBoard[playerPosition - 1] != '-') //if the entered position has already been played
                std::cout << "That position has already been played. Please try again" << std:: endl;
            else{
                gameBoard[playerPosition - 1] = player;
                PrintGameBoard(gameBoard);
                break;
            }
        }
    }
}

//checks every possible winning combination to see if there is a winner
bool CheckGameWon(char gameBoard[], char player){
    //first check the horizontals
    if (gameBoard[0]==player && gameBoard[1]==player &&gameBoard[2]==player)
        return true;
    else if (gameBoard[3]==player && gameBoard[4]==player && gameBoard[5]==player)
        return true;
    else if (gameBoard[6]==player && gameBoard[7]==player && gameBoard[8]==player)
        return true;
    //now check verticals
    else if (gameBoard[0]==player && gameBoard[3]==player && gameBoard[6] ==player)
        return true;
    else if (gameBoard[1]==player && gameBoard[4]==player && gameBoard[7]==player)
        return true;
    else if (gameBoard[2]==player && gameBoard[5]==player && gameBoard[8]==player)
        return true;
    //now check diagonals
    else if (gameBoard[0]==player && gameBoard[4]==player && gameBoard[8]==player)
        return true;
    else if (gameBoard[2]==player && gameBoard[4]==player && gameBoard[6]==player)
        return true;
    else return false;
}

/*Input is game board array. Computer determines where to place its piece based on the following
 1)Checks if computer can win - if yes, place piece appropriately
 2)else Checks if player can win next turn - if so, blocks appropriately (always blocks the first possible winning player move if there are more than one.
 3)else Places piece on random empty square
 */
void ComputerMove(char gameBoard[]){
    srand(time(NULL));
    int playerPosition;
    bool computerMoveMade = false;
    //check for winning move for computer (and make if appropriate
    computerMoveMade = CheckForWinningMove(gameBoard, 'o');
    //check for possible winning move for player and if appropriate block it
        if (!computerMoveMade){
            computerMoveMade = CheckForWinningMove(gameBoard, 'x');
    }
    //if a move hasn't already been made, make a random move
    if (!computerMoveMade){
        while(!computerMoveMade){
            //if(computerMoveMade)
               // std::cout << "True" << std::endl;
            playerPosition = rand() % 9;
            if (gameBoard[playerPosition] == '-'){
                gameBoard[playerPosition] = 'o';
                computerMoveMade = true;
            }
        }
    }
}
/*
 Checks for potential winning move. The computer places an o either to win or to block a potential
 x win. If this is done, returns true, otherwise, does nothing and returns false.
 */
bool CheckForWinningMove(char gameBoard[], char player){
    bool computerMoveMade = false;
    //goes through every place on the board, tries placing an x or o to see if it wins. if so, places
    //an o in that spot, flags that a move has been made and exits the loop.
    for(int i = 0; i < 9; i++){
        if (gameBoard[i] == '-'){
            gameBoard[i] = player;
            if(CheckGameWon(gameBoard, player)){
                gameBoard[i] = 'o';
                computerMoveMade = true;
                break;
            }
            else{
                gameBoard[i] = '-';
            }
            
        }
    }
    return computerMoveMade;

}
