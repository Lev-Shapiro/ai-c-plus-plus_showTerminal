#include <iostream>
#include <chrono>
#include "utils/entities.h"
#include "utils/board.h"
#include "utils/ai.h"
#include "utils/color.h"
using namespace std;
using namespace chrono;

void stringifyBoard(Board board)
{
    cout << string(64, '-') << endl;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            color("yellow", to_string(board.board[i][j]), false);
            cout << "\t";
        }

        cout << "\n";
    }

    cout << string(64, '-') << endl;
}

int main()
{
    srand(time(NULL)); // initialize the random seed

    Board board;
    Ai ai;

    color("blue", "game: 2048", true);
    color("blue", "board: 4 x 4", true);
    color("blue", "==============", true);

    board.opponentAction();
    board.opponentAction();

    // board.setTile(1, 1, 4);
    // board.setTile(1, 2, 4);

    // stringifyBoard(board);

    // board.agentAction(LEFT);

    stringifyBoard(board);

    while (!ai.losed)
    {
        auto t1 = high_resolution_clock::now();
        Direction direction = ai.suggest(board);
        auto t2 = high_resolution_clock::now();

        duration<double> time_span = duration_cast<duration<double>>(t2 - t1);

        std::cout << "AI suggests: " << time_span.count() << " seconds." << endl;


        board.agentAction(direction);
        board.opponentAction();

        stringifyBoard(board);
    }

    color("red", "game ended", true);
    cout << "exiting! Go fuck yourself nor giving me stupid tasks!" << endl;

    return 0;
}