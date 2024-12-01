#include <iostream>
#include <string>
#include <vector>

using namespace std;

void get_input(vector <int>& nums)
{
    int n, number;
    cin >> n;
    for(int i = 0; i < n; i++)
    {
        cin >> number;
        nums.push_back(number);
    }
}

void array_navigate(const vector <int>& nums, int index = 0, int stage = 1, int prev_stage = 0)
{
    int forward_count = 0;
    
    if (index > nums.size())
    { 
        cout << endl;
        return;
    }
    cout << nums[index] << " ";
    if (stage % 2 == 0) 
        forward_count = min(nums[index], prev_stage);
    else
        forward_count = max(nums[index], prev_stage);

    if(nums[index] == 0 && prev_stage == 0)
    {
        cout << endl;
        return;
    }

    array_navigate(nums, index + forward_count, stage + 1, nums[index]);
}

int main()
{
    vector <int> numbers;
    get_input(numbers);
    array_navigate(numbers);
    return 0;
}