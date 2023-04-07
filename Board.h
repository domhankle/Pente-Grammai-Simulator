///Board.h

#ifndef BOARD_H
#define BOARD_H

///Header files
#include <iostream>
#include <string>


using namespace std;

class Board
{
    public:

        ///Utility Functions
        void DrawBoard();
        void FillSacredLine(char ch, int start, int stop);
        void ClearSacredLine(char ch);
        bool PieceOnBoard(char ch);

        ///Getters
        char GetBoardValue(int index);
        char GetSacredLineValue(int index);
        int GetBoardValuePos(char ch);
        int GetSacredLineValuePos(char ch);

        ///Setters
        void SetBoardValue(int index, char ch);
        void SetSacredLineValue(int index, char ch);

        ///Constructor and Destructor
        Board();
        virtual ~Board();



    private:

        ///Member variables
        char boardValues[10];
        char sacredLineValues[8];

};

#endif // BOARD_H
