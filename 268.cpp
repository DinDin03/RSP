#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;

int missingNumber(vector<int>& nums) {
  sort(nums.begin(), nums.end());
  for (int i = 0; i < nums.size(); i++) {
    if (nums.front() == 0 && nums.back() == nums.size() - 1) {
      return nums.size();
    }
    if (nums[i] != i) {
      return i;
    }
  }
  return -1;
}

int missingNumber2(vector<int>& nums) {
    int sum = 0;
    int expectedSum = nums.size() * (nums.size()+1)/2;
    cout << "Expected sum is " << expectedSum << endl;;

    for(int i = 0; i < nums.size(); i++){
        sum = sum + nums[i];
    }
    if(sum != expectedSum){
        return expectedSum - sum;
    }
    return 0;
}

int main() {
  vector<int> nums = {1,2,3,4};
  cout << missingNumber(nums) << endl;
  cout << missingNumber2(nums) << endl;
  return 0;
}