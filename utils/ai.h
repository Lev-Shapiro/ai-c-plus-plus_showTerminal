int counter = 0;

class Ai
{
private:
    int reward(Board board)
    {
        int reward = board.findEmptyPlaces().size();

        return 0.001 + reward;
    }

    int recursive(Board board, int depth)
    {
        int globalRecursiveReward = 0;
        counter++;
        
        if (depth == 0)
            return reward(board);

        //* edi - emulate direction index
        for (int edi = 0; edi < 4; edi++)
        {
            Board boardCopy = board;
            Direction direction = directions[edi];

            boardCopy.agentAction(direction);

            vector<vector<int>> emptyPlaces = boardCopy.findEmptyPlaces();

            if (!emptyPlaces.size())
                continue;

            for (int emptyPlacesIndex = 0; emptyPlacesIndex < emptyPlaces.size(); emptyPlacesIndex++)
            {
                Board boardCopy2 = boardCopy;
                boardCopy2.setTile(emptyPlaces[emptyPlacesIndex][0], emptyPlaces[emptyPlacesIndex][1], 2);

                Board boardCopy3 = boardCopy;
                boardCopy3.setTile(emptyPlaces[emptyPlacesIndex][0], emptyPlaces[emptyPlacesIndex][1], 4);

                int rewardA = recursive(boardCopy2, depth - 1);
                int rewardB = recursive(boardCopy3, depth - 1);

                globalRecursiveReward += (rewardA + rewardB) / 2;
            }
        }

        return globalRecursiveReward;
    }

public:
    bool losed = false;

    Direction suggest(Board board)
    {
        counter = 0;

        vector<Direction> availableDirections = board.findAvailableDirections();

        if (!availableDirections.size())
        {
            losed = true;
            return DOWN;
        }

        Direction bestMove = availableDirections[0]; // availableDirections[0] default
        int bestValue = -1;

        for (int i = 0; i < availableDirections.size(); i++)
        {
            Direction direction = availableDirections[i];

            Board boardCopy = board;

            boardCopy.agentAction(direction);

            int a = 2;
            
            if(boardCopy.findEmptyPlaces().size() < 3) {
                a = 3;
            }

            int currValue = recursive(boardCopy, a);

            if(bestValue < currValue) {
                bestMove = direction;
                bestValue = currValue;
            }
        }

        cout << "counted times: " << counter << endl;
        return bestMove;
    }
};