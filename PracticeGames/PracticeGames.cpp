#include <iostream>
#include "Games.h"

using namespace std;
using namespace Games;

int main()
{
    int game;
    cout << "Lets play a game!\nChoose one:\n1) Quiz\n2) Tic-Tac-Toe\n";
    cin >> game;
    if (game == 1)
        Quiz();
    else
        TicTacToe();
}
