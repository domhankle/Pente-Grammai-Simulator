///Referee.cpp

#include "Referee.h"

///Local module function declarations
bool SacredLineAvailable(Board& board, int start, int stop);
int CoinFlip(Referee& official);

///Constructor
Referee::Referee()
{

}

///Custom constructor - Passes in a value to determine the starting player for the game.
///Prints the instructions of the game along with ref dialogue.
Referee::Referee(int& startingPlayer)
{
    Introduction(startingPlayer);
    PrintMessage("Let's have a clean and fair match fellas ;)");
}

///Destructor - prints ref dialogue at the end of the game.
Referee::~Referee()
{
    PrintMessage("Good game guys, see you next time ;)");
}

///LegalPosition - Determines whether or not a requested movement of a piece is legal or not.
bool Referee::LegalPosition(int currentPosition, int amountToMove, Board& board)
{

    //cerr << "Position of moving piece: " << currentPosition << endl;
    //cerr << "Value of moving piece: " << board.GetBoardValue(currentPosition) << endl;

    int requestedPosition = currentPosition + amountToMove;

    if(requestedPosition >= 10)
    {
        requestedPosition -= 10;
    }

    //cerr << "Requested Position to Move To: " << requestedPosition << endl;
    //cerr << "Value at requested position: " << board.GetBoardValue(requestedPosition) << endl;

    if(board.GetBoardValue(requestedPosition) != ' ' && requestedPosition == 2)
    {
        return SacredLineAvailable(board, 4, 8);
    }
    else if(board.GetBoardValue(requestedPosition) != ' ' && requestedPosition == 7)
    {
        return SacredLineAvailable(board, 0, 4);
    }
    else if(board.GetBoardValue(requestedPosition) == ' ')
    {
        return true;
    }

    //cerr << "Not a legal position!" << endl;
    return false;
}

///TurnChange - Determines whether or not a  player gets an extra turn or not.
bool Referee::TurnChange(int score, Board& board, char moveToCheck)
{
    if(score < 5 && board.GetBoardValuePos(moveToCheck) != 2 && board.GetBoardValuePos(moveToCheck) != 7)
    {
        return true;
    }

    return false;
}

///SacredLineAvailable - Determines whether or not there is available space on the sacred line.
bool SacredLineAvailable(Board& board, int start, int stop)
{
    for(int i = start; i < stop; i++)
    {
        if(board.GetSacredLineValue(i) == ' ')
        {
            return true;
        }
    }

    return false;
}

///Introduction - Prints instructions and context on the game Pente Grammai. Also calls CoinFlip() to determine who starts the game.
void Referee::Introduction(int& startingPlayer)
{
    cout << "Welcome to Pente Grammai! This is an Ancient Greek board game that is suited for two players." << endl
         << "The goal of the game is to get all of your pieces on the vertical line of the opposite side you start." << endl
         << "A dice is rolled to randomly decide how many spaces one of your pieces can move. All pieces move in a " << endl
         << "counter clockwise direction. Note that you cannot move a piece to a location that is already occupied." << endl
         << "If you land on the Sacred Line, you will get an extra turn! A coin will be flipped now to decide the starting player!" << endl << endl
         << "Flipping coin..." << endl;

    startingPlayer = CoinFlip(*this);
}

///CoinFlip - Returns a random value which will determine which player gets to start the game.
int CoinFlip(Referee& official)
{
    int flip = rand() % 2;

    if(flip == 1)
    {
        official.PrintMessage("Player L will start!");
        return 1;
    }
    else
    {
        official.PrintMessage("Player N will start!");
        return 0;
    }
}

///PrintMessage - prints referee dialogue.
void Referee::PrintMessage(string str)
{
    cout << endl << endl << "Ref: " << str << endl;
}