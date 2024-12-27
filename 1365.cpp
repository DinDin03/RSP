#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

vector<int> smallerNumbersThanCurrent(vector<int>& nums) {
  vector<int> mins(nums.size(), 0);
  for (int i = 0; i < nums.size(); i++) {
    int min = nums[i];
    for (int j = 0; j < nums.size(); j++) {
      if (nums[j] < nums[i]) {
        mins[i]++;
      }
    }
  }
  return mins;
}

vector<int> smallerNumbersThanCurrent2(vector<int>& nums) {
    unordered_map<int,int> map;
    vector<int> result;
    vector<int> sortedNums = nums;
    sort(nums.begin(), nums.end());

    for(int i = 0; i < sortedNums.size(); i++){
        if(map.find(sortedNums[i]) == map.end()){
            map[sortedNums[i]] = i;
        }
    }
    for(int i = 0; i < nums.size(); i++){
        result.push_back(map[nums[i]]);
    }
    return result;
}


int main() {
  vector<int> nums = {6, 5, 4, 8};
  vector<int> result = smallerNumbersThanCurrent2(nums);
  cout << "[";
  for (int i = 0; i < result.size(); i++) {
    cout << result[i];
    cout << " ";
  }
  cout << "]" << endl;
  return 0;
}