#include <iostream>
#include <vector>
using namespace std;

int removeDuplicates(vector<int>& nums) {
  vector<int> result;
  int unique;
  int uniqueCount = 0;
  for (int i = 0; i < nums.size(); i++) {
    if (nums[i] != unique) {
      result.push_back(nums[i]);
      unique = nums[i];
      uniqueCount++;
    }
  }
  nums = result;
  return uniqueCount;
}