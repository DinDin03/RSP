#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;

vector<int> findDisappearedNumbers(vector<int>& nums) {
  vector<int> list;
  sort(nums.begin(), nums.end());
  for (int i = 0; i < nums.size() - 1; i++) {
    if (nums[i] == nums[i + 1]) {
      i++;
    }
    if (nums[i + 1] - nums[i] != 1) {
      list.push_back(nums[i] + 1);
      nums.push_back(nums[i] + 1);
      sort(nums.begin(), nums.end());
    }
  }
  return list;
}

vector<int> findDisappearedNumbers3(vector<int>& nums) {
  for(int i = 0; i < nums.size(); i++){
    int index = abs(nums[i]) - 1;
    if(nums[index] > 0){
      nums[index] = -nums[index];
    }
  }
  vector<int> results;
  for(int i = 0; i < nums.size(); i++){
    if(nums[i] > 0){
      results.push_back(i + 1); // Because 1-based [1,n]
    }
  }
}

vector<int> findDisappearedNumbers2(vector<int>& nums) {
  unordered_set<int> set(nums.begin(), nums.end());
  vector<int> notInList;
  for (int i = 1; i <= nums.size(); i++) {
    if(set.count(i) == false){
      notInList.push_back(i);
    }
  }
  return notInList;
}

int main() {
  vector<int> nums = {4, 3, 2, 7, 8, 2, 3, 1};
  vector<int> result = findDisappearedNumbers3(nums);
  for (int i = 0; i < result.size(); i++) {
    cout << result[i] << " ";
  }
  return 0;
}