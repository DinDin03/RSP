#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

bool containsDuplicate(const vector<int>& nums) {
    unordered_set<int> seen; // Create an unordered set to store seen numbers

    for (int num : nums) { // Iterate through the array
        if (seen.find(num) != seen.end()) { // Check if num is already in the set
            return true; // Duplicate found
        }
        seen.insert(num); // Add num to the set
    }

    return false; // No duplicates found
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
