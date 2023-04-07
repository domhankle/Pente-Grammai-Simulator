///Player.cpp

#include "Player.h"

///Constructor
Player::Player()
    : name(""), score(0), marker({' ', ' ', ' ', ' ', ' '})
{

}

///Custom Constructor - sets the values of name and the markers.
Player::Player(string aName, char* markers)
    : name(aName), score(0), marker({markers[0], markers[1], markers[2], markers[3], markers[4]})
{

}

///Destructor
Player::~Player()
{

}

///GetMarker - returns the value of a marker at a specific index
char Player::GetMarker(int index)
{
    return marker[index];
}

///GetScore - returns the value of score on this object.
int Player::GetScore()
{
    return score;
}

///GetName - returns the value of name on this object.
string Player::GetName()
{
    return name;
}

///SetMarker - sets the value of a marker at a specific index
void Player::SetMarker(int index, char ch)
{
    marker[index] = ch;
}

///SetScore - sets the value of score on this object.
void Player::SetScore(int num)
{
    score = num;
}

///SetName - sets the value of name on this object.
void Player::SetName(string aName)
{
    name = aName;
}

///UpdateScore - changes the score value of this object based on the state of a board passed to this function.
void Player::UpdateScore(Board& board)
{
    SetScore(0);

    if(GetName() == "N")
    {
        switch(board.GetBoardValue(7))
        {
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
                SetScore(GetScore() + 1);
                break;
        }

        for(int i = 0; i < 4; i++)
        {
            switch(board.GetSacredLineValue(i))
            {
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                    SetScore(GetScore() + 1);
                    break;
            }
        }
    }
    else if(GetName() == "L")
    {
        switch(board.GetBoardValue(2))
        {
            case 'A':
            case 'B':
            case 'C':
            case 'D':
            case 'E':
                SetScore(GetScore() + 1);
                break;
        }

        for(int i = 4; i < 8; i++)
        {
            switch(board.GetSacredLineValue(i))
            {
                case 'A':
                case 'B':
                case 'C':
                case 'D':
                case 'E':
                    SetScore(GetScore() + 1);
                    break;

            }
        }
    }
}

///MarkerExists - checks to see if this object has a specific type of marker.
bool Player::MarkerExists(char marker)
{
    for(int i = 0; i < 5; i++)
    {
        if(marker == GetMarker(i))
        {
            return true;
        }
    }

    //cerr << "Marker does not exist!" << endl;
    return false;
}

///LegalMoveExists - checks to see if a marker has a possible legal movement based on it's position and the dice roll.
bool Player::LegalMoveExists(Board& board, Referee& official, int amountToMove)
{
    int positionOfPiece;
    for(int i = 0; i < 5; i++)
    {
        //cerr << "Checking: " <<  GetMarker(i) << endl;
        positionOfPiece = board.GetBoardValuePos(GetMarker(i));

        if(official.LegalPosition(positionOfPiece, amountToMove, board))
        {
            //cerr << "Legal move found for " << GetMarker(i) << endl;

            official.PrintMessage("There is a possible move to make, keep looking!");
            return true;
        }
        //cerr << "No legal move found for " << GetMarker(i) << endl;
    }
    return false;
}

///MoveMarker - moves a specific marker/piece on the board to another legal location on the board.
void Player::MoveMarker(char marker, int amountToMove, Board& board)
{
    int positionOnBoard = board.GetBoardValuePos(marker);

    //cerr << endl << endl << "POSITION ON BOARD: " << positionOnBoard;

    //cerr << endl <<"Legal Position to Move To: " << official.LegalPosition(positionOnBoard, amountToMove, board) << endl;

    int positionRequested = positionOnBoard + amountToMove;

    if(positionRequested >= 10)
    {
        positionRequested -= 10;
    }

    //cerr << endl << endl << "POSITION REQUESTED: " << positionRequested;

    //cerr << (int)' ' << endl;
    //cerr << (int)board.GetBoardValue(positionRequested) << endl;

    if(positionRequested == 7 && board.GetBoardValue(positionRequested) != ' ')
    {
        //cerr << "Statement 1" << endl;
        board.ClearSacredLine(marker);
        board.FillSacredLine(marker, 0, 4);
    }
    else if(positionRequested == 2 && board.GetBoardValue(positionRequested) != ' ')
    {
        //cerr << "Statement 2" << endl;
        board.ClearSacredLine(marker);
        board.FillSacredLine(marker, 4, 8);
    }
    else if(positionOnBoard == 7 && board.GetBoardValue(positionOnBoard) != marker)
    {
        //cerr << "Statement 3" << endl;
        board.ClearSacredLine(marker);
        board.SetBoardValue(positionRequested, marker);
    }
    else if(positionOnBoard == 2 && board.GetBoardValue(positionOnBoard) != marker)
    {
        //cerr << "Statement 4" << endl;
        board.ClearSacredLine(marker);
        board.SetBoardValue(positionRequested, marker);
    }
    else
    {
        //cerr << "Statement 5" << endl;
        board.SetBoardValue(positionRequested, marker);
        board.SetBoardValue(positionOnBoard, ' ');
    }

}

///Operator Overload of '=' - Player objects can now have their attributes copied over to another.
void Player::operator=(Player& rhsPlayer)
{
    for(int i = 0; i < 5; i++)
    {
        SetMarker(i, rhsPlayer.GetMarker(i));
    }

    SetScore(rhsPlayer.GetScore());
    SetName(rhsPlayer.GetName());
}

///Operator Overload of '==' - Player objects can be compared using == to see if their marker attributes are the same.
bool Player::operator==(Player& rhsPlayer)
{
    for(int i = 0; i < 5; i++)
    {
        if(GetMarker(i) == rhsPlayer.GetMarker(i))
        {
            continue;
        }
        else
        {
            return false;
        }
    }

    return true;
}