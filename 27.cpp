#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

int removeElement(vector<int>& nums, int val) {
  vector<int> result;
  int count = 0;
  for (int i = 0; i < nums.size(); i++) {
    if (nums[i] != val) {
      result.push_back(nums[i]);
      count++;
    }
  }
  nums = result;
  return count;
}

int main() {
  vector<int> nums = {3, 2, 2, 3};
  int val = 3;
  int count = removeElement(nums, val);
  cout << count << endl;
  return 0;
}