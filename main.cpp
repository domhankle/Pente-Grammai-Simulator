///Domenic Hankle
///UIN: 01202552
///Pente Grammai - Final Project CS 250
//Comments in this shade indicate debugging lines

///Header files
#include <iostream>
#include <cstdlib>
#include <time.h>
#include "Board.h"
#include "Referee.h"
#include "Player.h"

using namespace std;

///Function Declarations
void PopulateBoard(Board& board, Player& player1, Player& player2);
void Play();
void SwapPlayer(Player& playerL, Player& playerN, Player& currentPlayer);
void DisplayStats(Player& playerL, Player& playerN, Player& currentPlayer, int& diceRoll);
void DisplayWinner(Player& currentPlayer);
void Introduction(int& startingPlayer);
int RollDice();
int CoinFlip();

///Main
int main()
{
    ///Call Play()
    Play();
    return 0;
}

///Play()
void Play()
{
    ///Variable and object declarations/initializations
    srand(time(NULL));

    Player currentPlayer;
    int startingPlayer;
    char pieceSelection;
    int diceRoll;

    char p1Arr[5] = {'A', 'B', 'C', 'D', 'E'};
    char p2Arr[5] = {'1', '2', '3', '4', '5'};

    Player playerL("L", p1Arr);
    Player playerN("N", p2Arr);

    Board board;

    Referee official(startingPlayer);

    PopulateBoard(board, playerL, playerN);

    ///Initializes the starting player.
    switch(startingPlayer)
    {
        case 0:
            currentPlayer = playerN;
            break;
        case 1:
            currentPlayer = playerL;
            break;
    }

    ///Game Loop
    ///This do-while loop encapsulates the whole game, each turn is confined to this single loop.
    ///This loop will repeat until someone has a score of 5 and wins the game.
    do
    {

        ///Get a random value 1-6 by calling RollDice()
        diceRoll = RollDice();

        ///Draw the current state of the board to the screen.
        board.DrawBoard();

        ///Display current stats of the game.
        DisplayStats(playerL, playerN, currentPlayer, diceRoll);

        ///This block of code receives user input, determines whether it is valid or not, and reprompts the user if necessary.
        userSelection:

            cout << "Select a piece (Enter p or P to Pass if you have no options): ";
            cin >> pieceSelection;
            cin.sync();

            if(toupper(pieceSelection) == 'P')
            {
                cin.sync();
                if(currentPlayer.LegalMoveExists(board, official, diceRoll))
                {
                    goto userSelection;
                }
            }
            else if(!official.LegalPosition(board.GetBoardValuePos(toupper(pieceSelection)), diceRoll, board) || cin.bad()
                    || !currentPlayer.MarkerExists(toupper(pieceSelection)))
            {
                /*if(!cin.good())
                {
                    cerr << "cin is bad!" << endl;
                }*/
                cin.clear();
                cin.sync();
                official.PrintMessage("That is not a legal move, try again!");
                goto userSelection;
            }


        ///If the user did not successfully pass the turn, adjust the state of the board by moving the selected piece..
        if(toupper(pieceSelection) != 'P')
        {
            currentPlayer.MoveMarker(toupper(pieceSelection), diceRoll, board);
        }

        ///Update the score of the current player who's turn it is.
        currentPlayer.UpdateScore(board);


        ///Determine whether or not the player earned an extra turn.
        ///The else statement is if they did earn an extra turn.
        ///In the else statement,the code reinitializes our two player objects with their updated scores.
        if(official.TurnChange(currentPlayer.GetScore(), board, toupper(pieceSelection)))
        {
            //cerr << "Swapped Players" << endl;
            SwapPlayer(playerL, playerN, currentPlayer);
        }
        else
        {
            if(currentPlayer == playerL)
            {
                //cerr << "Player L TURN" << endl;
                playerL = currentPlayer;
                /*cerr << "Current Player Score: " << currentPlayer.GetScore() << endl
                     << "Player L Score: " << playerL.GetScore() << endl;*/
            }
            else if(currentPlayer == playerN)
            {
                //cerr << "Player N TURN" << endl;
                playerN = currentPlayer;
                /*cerr << "Current Player Score: " << currentPlayer.GetScore() << endl
                     << "Player N Score: " << playerN.GetScore() << endl;*/
            }
        }

        ///Clear the screen.
        system("CLS");

    }
    while(currentPlayer.GetScore() < 5);


    ///Draw the final state of the board.
    board.DrawBoard();

    ///Display the winner of the game.
    DisplayWinner(currentPlayer);
}

///PopulateBoard - Initializes the original state of a board by passing in two player objects.
void PopulateBoard(Board& board, Player& player1, Player& player2)
{
    for(int i = 0; i < 5; i++)
    {
        board.SetBoardValue(i, player2.GetMarker(i));
        board.SetBoardValue(9 - i, player1.GetMarker(i));
    }

}

///RollDice - Returns a random int from values 1 - 6.
int RollDice()
{
    return (rand() % 6) + 1;
}

///SwapPlayer - Changes which players turn it is utilizing operator overloading found in the Player class.
void SwapPlayer(Player& playerL, Player& playerN, Player& currentPlayer)
{
    if(currentPlayer == playerN)
    {
        playerN = currentPlayer;
        currentPlayer = playerL;
    }
    else if(currentPlayer == playerL)
    {
        playerL = currentPlayer;
        currentPlayer = playerN;
    }
}

///DisplayStats - Displays the important values of the current state of the game.
void DisplayStats(Player& playerL, Player& playerN, Player& currentPlayer, int& diceRoll)
{
        cout << endl;

        cout << "Player L Score: " << playerL.GetScore() << endl
             << "Player N Score: " << playerN.GetScore() << endl
             << "Player Turn: ";

        cout << currentPlayer.GetName() <<  endl << endl
             << "Roll: " << diceRoll << endl;
}

///DisplayWinner - Displays the winner of the game at the end of the program.
void DisplayWinner(Player& currentPlayer)
{
    cout << endl
         << "Congratulations Player " << currentPlayer.GetName() << ", you win!" << endl;
}