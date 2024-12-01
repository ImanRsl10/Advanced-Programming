#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int ROW_COUNT = 7;
const int COL_COUNT = 7;
const int POSSIBLE_MOVES = 4;
const int MIDDLE = 3;

void print_board(vector <string> board)
{
    for (int i = 0; i < ROW_COUNT; i++) 
        cout << board[i] << endl;
    cin.get();
}

void get_board(vector <string>& board)
{
    string line;
    for(int row = 0; row < ROW_COUNT; row++)
    {
        getline(cin, line);
        board.push_back(line);
    }
}

int cacl_num_of_N (const vector <string>& board)
{
    int num_of_N = 0;
    for(int row = 0; row < ROW_COUNT; row++)
        for(int col = 0; col < COL_COUNT; col++)
            if(board[row][col] == 'N')
                num_of_N++;
    return num_of_N;
}

bool find_path(vector <string>& board, vector <string>& win_path)
{
    const string moves[POSSIBLE_MOVES] = {"DOWN", "UP", "RIGHT", "LEFT"};
    const string row_lable[ROW_COUNT] = {"A", "B", "C", "D", "E", "F", "G"};
    const int row_delta[POSSIBLE_MOVES] = {2, -2, 0, 0}; // RIGHT --> {2,0} LEFT --> {-2,0}
    const int col_delta[POSSIBLE_MOVES] = {0, 0, 2, -2}; //UP --> {0,2} DOWN --> {0,-2}
    const int row_jump[POSSIBLE_MOVES] = {1, -1, 0, 0};
    const int col_jump[POSSIBLE_MOVES] = {0, 0, 1, -1};

    int num_of_N = cacl_num_of_N(board);
    string valid_move;

    for(int row = 0; row < ROW_COUNT; row++)
    {
        for(int col = 0; col < COL_COUNT; col++)
        {
            if(board[row][col] == 'N')
            {
                //print_board(board);

                if(num_of_N == 1 && board[MIDDLE][MIDDLE] == 'N')
                    return true;

                for (int move = 0; move < POSSIBLE_MOVES; move++)
                {
                    int new_row = row + row_delta[move];
                    int new_col = col + col_delta[move];

                    int row_jump_from = row + row_jump[move];
                    int col_jump_from = col + col_jump[move];

                    if (new_row < 0 || new_row >= ROW_COUNT || new_col < 0 || new_col >= COL_COUNT)
                        continue;

                    if (board[row_jump_from][col_jump_from] != 'N')
                        continue;

                    if (board[new_row][new_col] != 'O')
                        continue;
                    
                    board[row][col] = 'O';
                    board[row_jump_from][col_jump_from] = 'O';
                    board[new_row][new_col] = 'N';
                    num_of_N--;

                    if(find_path(board, win_path))
                    {
                        valid_move = row_lable[row] + to_string(col + 1) + " " + moves[move];
                        win_path.push_back(valid_move);
                        return true;
                    }

                    board[row][col] = 'N';
                    board[row_jump_from][col_jump_from] = 'N';
                    board[new_row][new_col] = 'O';
                    num_of_N++;
                }
            }
        }
    }
    return false;
}

void print_moves(const vector <string>& win_path)
{
    for(int path = win_path.size() - 1; path >= 0; path--)
    {
        cout << win_path[path] << endl;
    }
}

void solve(vector <string>& board)
{
    vector <string> win_path;

    get_board(board);

    if (find_path(board, win_path))
        print_moves(win_path);
    else
        cout << "Loser\n";
}

int main()
{
    vector <string> board;
    solve(board);
    return 0;
}