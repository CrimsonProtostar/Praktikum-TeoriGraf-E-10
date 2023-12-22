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

    int countAccessibleMoves(int i, int j)
    {
        int count = 0;
        for (int k = 0; k < 8; ++k)
        {
            int ni = i + moves[k][0];
            int nj = j + moves[k][1];
            if (ni >= 0 && ni < row && nj >= 0 && nj < col && board[ni][nj] == 0)
            {
                count++;
            }
        }
        return count;
    }

    void searchEveryPossibleState(int i, int j, int totalMove)
    {
        if (totalMove == col * row)
        {
            printBoard();
            cin.get();
            return;
        }

        vector<pair<pair<int, int>, int>> state;
        for (int k = 0; k < 8; ++k)
        {
            int ni = i + moves[k][0];
            int nj = j + moves[k][1];
            if (ni >= 0 && ni < row && nj >= 0 && nj < col && board[ni][nj] == 0)
            {
                int accessMoves = countAccessibleMoves(ni, nj);
                state.push_back(make_pair(make_pair(ni, nj), accessMoves));
            }
        }

        sort(state.begin(), state.end(), [](const auto &a, const auto &b)
             { return a.second < b.second; });

        for (auto &s : state)
        {
            int ni = s.first.first;
            int nj = s.first.second;
            board[ni][nj] = totalMove + 1;
            searchEveryPossibleState(ni, nj, totalMove + 1);

            board[ni][nj] = 0;
            return;
        }
        
    }

    void runEveryPossibleState()
    {
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                printf("%d %d\n", i, j);
                board[i][j] = 1;
                searchEveryPossibleState(i, j, 1);
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
