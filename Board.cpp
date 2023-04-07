///Board.cpp
#include "Board.h"

///Constructor
Board::Board()
    : sacredLineValues({' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}),
      boardValues({' ', ' ', ' ', ' ', ' ',' ', ' ', ' ', ' ', ' '})
{

}

///Destructor
Board::~Board()
{

}

///GetBoardValue - returns the value at a specific position on the board.
char Board::GetBoardValue(int index)
{
    return boardValues[index];
}

///GetSacredLineValue - returns the value at a specific position on the sacred line.
char Board::GetSacredLineValue(int index)
{
    return sacredLineValues[index];
}

///GetBoardValuePos - returns the position value of a specific character.
///The additional conditionals are in case the characters is on the sacred line.
int Board::GetBoardValuePos(char ch)
{
    int value = -1;

    for(int i = 0; i < 10; i++)
    {
        if(GetBoardValue(i) == ch)
        {
            value = i;
            break;
        }
    }

    if(value == -1)
    {
        for(int i = 0; i < 8; i++)
        {
            if(GetSacredLineValue(i) == ch && GetSacredLineValuePos(ch) < 4 && GetSacredLineValuePos(ch) >= 0)
            {
                value = 7;
                break;
            }
            else if(GetSacredLineValue(i) == ch && GetSacredLineValuePos(ch) >=4 && GetSacredLineValue(ch) < 8)
            {
                value = 2;
                break;
            }
        }

    }

    return value;
}

///GetSacredLineValuePos - returns the position of a specific character on the sacred line.
int Board::GetSacredLineValuePos(char ch)
{
    for(int i = 0; i < 8; i++)
    {
        if(GetSacredLineValue(i) == ch)
        {
            return i;
        }
    }

    return -1;

}

///SetBoardValue - sets the value of a character at a specific position on the board.
void Board::SetBoardValue(int index, char ch)
{
    boardValues[index] = ch;
}

///SetSacredLineValue - sets the value of a character at a specific position on the sacred line.
void Board::SetSacredLineValue(int index, char ch)
{
    sacredLineValues[index] = ch;
}

///FillSacredLine - Adds a character value to the next available spot in the sacred line.
void Board::FillSacredLine(char ch, int start, int stop)
{
    int pos = GetBoardValuePos(ch);

    for(int i = start; i < stop; i++)
    {
        if(GetSacredLineValue(i) == ' ')
        {
            SetSacredLineValue(i, ch);
            break;
        }
    }

    SetBoardValue(pos, ' ');
}

///ClearSacredLine - clears the sacred line of a specific character.
void Board::ClearSacredLine(char ch)
{
    for(int i = 0; i < 8; i++)
    {
        if(GetSacredLineValue(i) == ch)
        {
            SetSacredLineValue(i, ' ');
        }
    }
}

///DrawBoard - draws the game board to the screen with corresponding values of each location.
void Board::DrawBoard()
{
    cout << "     ---" << endl
         << "     |" << GetSacredLineValue(3) << "|" << endl
         << "     ---" << endl
         << "     |" << GetSacredLineValue(2) << "|" << endl
         << "     ---" << endl
         << "     |" << GetSacredLineValue(1) << "|" << endl
         << "     ---" << endl
         << "     |" << GetSacredLineValue(0) << "|" << endl;

    cout << "   -------" << endl
         << "   |" << GetBoardValue(8) << "|" << GetBoardValue(7) << "|" << GetBoardValue(6) << "|" << endl;

    cout << "-------------" << endl
         << "|" << GetBoardValue(9) << "|       |" << GetBoardValue(5) << "|" << endl;
    cout << "-------------" << endl
         << "|" << GetBoardValue(0) << "|       |" << GetBoardValue(4) << "|" << endl;

    cout << "   -------" << endl
         << "   |" << GetBoardValue(1) << "|" << GetBoardValue(2) << "|" << GetBoardValue(3) << "|" << endl;

    cout << "     ---" << endl
         << "     |" << GetSacredLineValue(4) << "|" << endl
         << "     ---" << endl
         << "     |" << GetSacredLineValue(5) << "|" << endl
         << "     ---" << endl
         << "     |" << GetSacredLineValue(6) << "|" << endl
         << "     ---" << endl
         << "     |" << GetSacredLineValue(7) << "|" << endl;

}


