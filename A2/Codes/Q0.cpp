#include <iostream>
#include <string>

using namespace std;

string to_upper(const string& str_low, int str_index = 0)
{
    if (str_index >= str_low.size())
        return "";
    return (char)toupper(str_low[str_index]) + to_upper(str_low, str_index + 1);
}

int main()
{
    string line;    
    while (getline(cin, line))
    {
        cout << to_upper(line) << endl;
    }
    return 0;
}