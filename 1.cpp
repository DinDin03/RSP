#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

vector<int> twoSum(vector<int>& nums, int target) {
  vector<int> result;
  for (int i = 0; i < nums.size(); i++) {
    int sum = 0;
    for (int j = i + 1; j < nums.size(); j++) {
      sum = nums[i] + nums[j];
      if (sum == target) {
        result.push_back(i);
        result.push_back(j);
        return result;
      }
    }
  }
  return result;
}

vector<int> twoSum2(vector<int>& nums, int target) {
    unordered_map<int, int> map;
    vector<int> result;

    for(int i = 0; i < nums.size(); i++){
        int complement = target - nums[i];
        if(map.find(complement) != map.end()){
            result.push_back(map[complement]);
            result.push_back(i);
            return result;
        }
        map[nums[i]] = i;
    }
    return result;
}

int main() {
  vector<int> nums = {3, 2, 4};
  int target = 6;
  vector<int> result = twoSum2(nums, target);
  for (int n : result) {
    cout << n << " ";
  }
  return 0;
}