#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class knightTour
{
private:
    const int row = 8;
    const int col = 8;
    int moves[8][2] = {{-2, -1}, {-2, 1}, {2, -1}, {2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}};
    vector<vector<int>> board;

public:
    knightTour() : board(row, vector<int>(col, 0)) {}

    void printBoard()
    {
        cout << "========RESULT========" << endl;
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                if (board[i][j] < 10)
                    std::cout << ' ';
                std::cout << board[i][j] << ' ';
            }
            cout << endl;
        }
        cout << "=====================" << endl;
    }

    int countAccessibleMoves(int i, int j, int totalMove)
    {
        int count = 0;
        for (int k = 0; k < 8; ++k)
        {
            int ni = i + moves[k][0];
            int nj = j + moves[k][1];
            if (ni >= 0 && ni < row && nj >= 0 && nj < col)
            {
                if (board[ni][nj] == 0){
                    count++;
                }
                // Checks if 64 can move back to 1
                else if (totalMove == 64 && board[ni][nj] == 1){
                    return -1;
                }
                
            }

        }
        return count;
    }

    int searchEveryPossibleState(int i, int j, int totalMove)
    {
        if (totalMove == col * row)
        {
            int isClosed = countAccessibleMoves(i, j, totalMove);
            if (isClosed == -1)
            {
                printf ("++++ NEXT BOARD IS A CLOSED LOOP ++++\n");
            }
            printBoard();
            cin.get();
            return 1;
        }

        vector<pair<pair<int, int>, int>> state;
        for (int k = 0; k < 8; ++k)
        {
            int ni = i + moves[k][0];
            int nj = j + moves[k][1];
            if (ni >= 0 && ni < row && nj >= 0 && nj < col && board[ni][nj] == 0)
            {
                int accessMoves = countAccessibleMoves(ni, nj, totalMove);
                state.push_back(make_pair(make_pair(ni, nj), accessMoves));
            }
        }

        sort(state.begin(), state.end(), [](const auto &a, const auto &b)
             { return a.second < b.second; });

        for (auto &s : state)
        {
            // printf("MOVES : %d\n", totalMove);
            int ni = s.first.first;
            int nj = s.first.second;
            board[ni][nj] = totalMove + 1;
            int isSolutionFound = searchEveryPossibleState(ni, nj, totalMove + 1);

            board[ni][nj] = 0;
            if (isSolutionFound) 
            {
                return 1;

            }
            // Allows retry different move without causing infinite loops
            if (state.size() <= 1){
                return 0;
            }
        }
        return 0;
    }

    void runEveryPossibleState()
    {
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                printf("%d %d\n", i, j);
                board[i][j] = 1;
                printf("RETURN : %d\n", searchEveryPossibleState(i, j, 1));
                board[i][j] = 0;
            }
        }
    }
};

int main()
{
    knightTour KT;
    KT.runEveryPossibleState();
    return 0;
}
