#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

bool containsDuplicate(const vector<int>& nums) {
    unordered_set<int> seen; 
    for (int num : nums) {
        if (seen.find(num) != seen.end()) { 
            return true; 
        }
        seen.insert(num); 
    }
    return false;
}

int main() {
    // Example usage
    vector<int> nums1 = {1, 2, 3, 1};
    vector<int> nums2 = {1, 2, 3, 4};

    cout << boolalpha;
    cout << "nums1 has duplicates: " << containsDuplicate(nums1) << endl;
    cout << "nums2 has duplicates: " << containsDuplicate(nums2) << endl;

    return 0;
}
