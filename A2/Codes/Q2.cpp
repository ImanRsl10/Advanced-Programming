#include <iostream>

using namespace std;

void path_counter(const int& n, int& num_of_valid_path, int i = 0, int j = 0)
{
    if (i < n)
    {
        path_counter(n, num_of_valid_path, i + 1, j);
    }
    if (j < i)
    {
        path_counter(n, num_of_valid_path, i, j + 1);
    }
    if (i == n && j == n)
    {
        num_of_valid_path++;
        return;
    }
}

int main()
{
    int matrix_size, path_num = 0;

    cin >> matrix_size;

    path_counter(matrix_size, path_num);
    
    cout << path_num << endl;
    return 0;
}