#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>
#include <stdlib.h> /* srand, rand */
#include <cstring>

using namespace std;

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
     * @setTiles          : loop setTile
     * @setRow            : replace row in board ( vertical or horizontal line )
     * @getRow            : get row from board ( vertical or horizontal line )
     * @newRandomTile     : 80% returns 2 and 20% returns BOARD_SIZE
     *------------------------------------------------------------------------**/

    void setTile(int y, int x, int value)
    {
        board[y][x] = value;
    }

    void setRow(Axis direction, int line, vector<int> row)
    {
        for (int i = 0; i < BOARD_SIZE; i++)
        {
            direction == VERTICAL
                ? (board[i][line] = row[i])
                : (board[line][i] = row[i]);
        }
    }

    vector<int> getRow(Axis direction, int line)
    {
        vector<int> row(BOARD_SIZE);

        for (int i = 0; i < BOARD_SIZE; i++)
        {
            row.push_back(
                direction == VERTICAL
                    ? board[i][line]
                    : board[line][i]);
        }

        return row;
    }

    int newRandomTile()
    {
        return ((float)rand() / RAND_MAX < 0.8) ? 2 : BOARD_SIZE;
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
     * @opponentAction : add number 2 or BOARD_SIZE to one of empty tiles
     *------------------------------------------------------------------------**/

    void agentAction(Direction direction)
    {
        Axis axis = (direction == DOWN || direction == UP) ? VERTICAL : HORIZONTAL;

        for (int x = 0; x < BOARD_SIZE; x++)
        {
            vector<int> arr = getRow(axis, x);

            // remove all 0 from array
            arr.erase(remove(arr.begin(), arr.end(), 0), arr.end());

            arr.shrink_to_fit();

            if (direction == DOWN || direction == RIGHT)
            {
                reverse(arr.begin(), arr.end());
            }

            vector<int> arrCopy;

            while (arr.size() != 0)
            {
                if (arr.size() != 1 && arr[1] == arr[0])
                {
                    arrCopy.push_back(arr[1] * 2);
                    arr.erase(arr.begin());
                }
                else
                {
                    arrCopy.push_back(arr[0]);
                }

                arr.erase(arr.begin());

                arr.shrink_to_fit();
            }

            arrCopy.shrink_to_fit();
            for (int z = arrCopy.size(); z < BOARD_SIZE; z++)
            {
                arrCopy.push_back(0);
            }

            arrCopy.shrink_to_fit();

            if (direction == DOWN || direction == RIGHT)
            {
                reverse(arrCopy.begin(), arrCopy.end());
            }

            setRow(axis, x, arrCopy);
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