///Player.h

#ifndef PLAYER_H
#define PLAYER_H

///Header files
#include <string>
#include "Referee.h"

class Player
{
    public:
        ///Constructors and Destructor
        Player();
        Player(string aName, char* markers);
        virtual ~Player();

        ///Getters
        string GetName();
        int GetScore();
        char GetMarker(int index);

        ///Setters
        void SetName(string aName);
        void SetScore(int num);
        void SetMarker(int index, char ch);

        ///Utility Functions
        void MoveMarker(char marker, int amountToMove, Board& board);
        void UpdateScore(Board& board);
        bool MarkerExists(char marker);
        bool LegalMoveExists(Board& board, Referee& official, int amountToMove);

        ///Operator overloads
        void operator=(Player& rhsPlayer);
        bool operator==(Player& rhsPlayer);

    private:

        ///Member variables
        int score;
        char marker[5];
        string name;

};

#endif // PLAYER_H
