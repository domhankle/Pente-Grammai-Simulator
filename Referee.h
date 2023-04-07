///Referee.h

#ifndef REFEREE_H
#define REFEREE_H

///Header files
#include "Board.h"

class Referee
{
    public:

        ///Constructors and Destructor
        Referee();
        Referee(int& startingPlayer);
        virtual ~Referee();

        ///Utility Functions
        bool LegalPosition(int currentPosition, int amountToMove, Board& board);
        bool TurnChange(int score, Board& board, char moveToCheck);
        void Introduction(int& startingPlayer);
        void PrintMessage(string str);


};

#endif // REFEREE_H
