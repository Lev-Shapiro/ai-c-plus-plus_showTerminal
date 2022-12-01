#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>
#include <stdlib.h> /* srand, rand */
#include <cstring>

using namespace std;

void reverse(int arr[], int n)
{
    reverse(arr, arr + n);
}
class Board
{
public:
    int BOARD_SIZE = 4;
    int board[4][4];

    Board()
    {
        memset(board, 0, sizeof(board[0][0]) * BOARD_SIZE * BOARD_SIZE);
    }

    bool sameBoard(int b1[4][4], int b2[4][4])
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (b1[i][j] != b2[i][j])
                    return false;
            }
        }

        return true;
    }

    /**------------------------------------------------------------------------
     * ?                          BOARD CONTROLLER
     * @setTile           : add {value} at board[i][j]
     * @newRandomTile     : 80% returns 2 and 20% returns BOARD_SIZE
     *------------------------------------------------------------------------**/

    void setTile(int y, int x, int value)
    {
        board[y][x] = value;
    }

    int newRandomTile()
    {
        return ((float)rand() / RAND_MAX < 0.8) ? 2 : 4;
    }
    
    /**------------------------------------------------------------------------
     * ?                       HELPER FUNCTIONS
     * @findEmptyPlaces             : returns coords of all empty places
     * @findScore                   : returns sum of all tiles
     * @findHighestTile             : returns highest tile
     * @findMergesCount             : returns number from 0 to 8
     * @findAvailableDirections     : returns array of available directions
     * @isLosed                     : returns true or false
     *------------------------------------------------------------------------**/

    vector<vector<int>> findEmptyPlaces()
    {
        //* [number, number][]
        vector<vector<int>> result(0, vector<int>(2));

        for (int i = 0; i < BOARD_SIZE; i++)
        {
            for (int j = 0; j < BOARD_SIZE; j++)
            {
                if (board[i][j] == 0)
                {
                    result.push_back({i, j});
                }
            }
        }

        result.shrink_to_fit();

        return result;
    }

    int findScore()
    {
        int score = 0;

        for (int i = 0; i < BOARD_SIZE; i++)
        {
            for (int j = 0; j < BOARD_SIZE; j++)
            {
                score += board[i][j];
            }
        }

        return score;
    }

    int findHighestTile()
    {
        int highestTile = 0;

        for (int i = 0; i < BOARD_SIZE; i++)
        {
            for (int j = 0; j < BOARD_SIZE; j++)
            {
                if (highestTile < board[i][j])
                {
                    highestTile = board[i][j];
                }
            }
        }

        return highestTile;
    }

    int findMergesCount(Direction direction)
    {
        Board boardCopy(*this);

        int emptyPlaces1 = boardCopy.findEmptyPlaces().size();
        boardCopy.agentAction(direction);
        int emptyPlaces2 = boardCopy.findEmptyPlaces().size();

        return emptyPlaces2 - emptyPlaces1;
    }

    vector<Direction> findAvailableDirections()
    {
        vector<Direction> availableDirections;

        for (int i = 0; i < BOARD_SIZE; i++)
        {
            Direction direction = directions[i];

            Board boardCopy(*this);

            boardCopy.agentAction(direction);

            if (sameBoard(board, boardCopy.board))
                continue;

            availableDirections.push_back(direction);
        }

        availableDirections.shrink_to_fit();

        return availableDirections;
    }

    bool isLosed()
    {
        return !findAvailableDirections().size();
    }

    /**------------------------------------------------------------------------
     * ?                             PLAYERS
     * @player1      : agent, AI bot
     * @player2      : computer
     *------------------------------------------------------------------------**/

    /**------------------------------------------------------------------------
     * ?                         PLAYERS ACTIONS
     * @agentAction    : move left/right/down/up
     * @opponentAction : add number 2 or 4 to one of empty tiles
     *------------------------------------------------------------------------**/

    void agentAction(Direction direction)
    {
        Axis axis = (direction == DOWN || direction == UP) ? VERTICAL : HORIZONTAL;

        for (int i = 0; i < BOARD_SIZE; i++)
        {
            int prevValue = 0, prevIndex = -1;

            for (int _ = 0; _ < BOARD_SIZE; _++)
            {
                int j = (direction == UP || direction == LEFT) ? BOARD_SIZE - 1 - _ : _;
                int a = j, b = i;

                if (axis == HORIZONTAL)
                {
                    a = i;
                    b = j;
                }

                int currValue = board[a][b];

                if (currValue == prevValue)
                {
                    currValue *= 2;
                    prevValue = 0;
                }

                if (prevValue != 0 && currValue == 0)
                {
                    currValue = prevValue;
                    prevValue = 0;
                }

                //* update data
                board[a][b] = currValue;

                if (prevIndex >= 0)
                    (axis == HORIZONTAL)
                        ? board[a][prevIndex] = prevValue
                        : board[prevIndex][b] = prevValue;

                if (currValue)
                {
                    prevValue = currValue;
                    prevIndex = j;
                }
            }
        }
    }

    PlayStatus opponentAction()
    {
        vector<vector<int>> emptyPlaces = findEmptyPlaces();

        if (emptyPlaces.size() == 0)
        {
            return LOSS;
        }

        int index = rand() % emptyPlaces.size();

        setTile(
            emptyPlaces[index][0],
            emptyPlaces[index][1],
            newRandomTile());

        return PLAYING;
    }
};
