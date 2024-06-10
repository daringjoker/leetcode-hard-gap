#include <algorithm>
#include <cmath>
#include <cstdio>
#include <ctime>
#include <vector>

using namespace std;

class Solution {
public:
  double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2) {
    int p1 = 0;
    int p2 = 0;
    vector<int> nums;
    while (p1 < nums1.size() && p2 < nums2.size()) {
      if (nums1[p1] < nums2[p2]) {
        nums.push_back(nums1[p1++]);
      } else {
        nums.push_back(nums2[p2++]);
      }
    }
    while (p1 < nums1.size()) {
      nums.push_back(nums1[p1++]);
    }
    while (p2 < nums2.size()) {
      nums.push_back(nums2[p2++]);
    }
    double median = (nums.size() + 1) / 2.0;
    double m1 = ceil(median);
    double m2 = floor(median);
    return (nums[m1 - 1] + nums[m2 - 1]) / 2.0;
  }
};

typedef struct {
  vector<int> nums1;
  vector<int> nums2;
  double expected;
} TestCase;

TestCase randomTestGenerator(int sizeMin = 50, int sizeMax = 10000,
                             int numMagnitude = 1000) {
  int size = rand() % (sizeMax - sizeMin) + sizeMin;
  vector<int> nums1;
  vector<int> nums2;
  vector<int> nums;
  for (int i = 0; i < size; i++) {
    int current = rand() % numMagnitude;
    nums.push_back(current);
    if (rand() % 2 == 0) {
      nums1.push_back(current);
    } else {
      nums2.push_back(current);
    }
  }
  sort(nums.begin(), nums.end());
  double median = (nums.size() + 1) / 2.0;
  double m1 = ceil(median);
  double m2 = floor(median);
  double expected = (nums[m1 - 1] + nums[m2 - 1]) / 2.0;
  sort(nums1.begin(), nums1.end());
  sort(nums2.begin(), nums2.end());
  return {
      std::move(nums1),
      std::move(nums2),
      expected,
  };
}

int test(int maxTotal = 10000, int sizeMin = 50, int sizeMax = 10000,
         int numMagnitude = 1000) {
  srand(time(0));
  int total = rand() % maxTotal;
  printf("Running tests with %d tests, with array size range:(%d,%d) and "
         "elements<=%d\n",
         total, sizeMin, sizeMax, numMagnitude);
  int passed = 0;
  double totalDuration = 0;
  double sqSum = 0;
  double minTime = 1000000;
  double maxTime = 0;
  for (int i = 0; i < total; i++) {
    TestCase t = randomTestGenerator(sizeMin, sizeMax, numMagnitude);
    Solution s;
    double startTime = clock();
    double result = s.findMedianSortedArrays(t.nums1, t.nums2);
    double endTime = clock();
    double duration = ((endTime - startTime) / (double)CLOCKS_PER_SEC) * 1000.0;
    totalDuration += duration;
    sqSum += duration * duration;
    minTime = min(minTime, duration);
    maxTime = max(maxTime, duration);
    if (result != t.expected) {
      printf("\rTest #%d failed", i + 1);
      printf("\rExpected: %f Got: %lf", t.expected, result);
    } else {
      passed++;
      printf("\rTest #%d passed. Took %f ms for n=%ld ,m=%ld Average= %lf ms , "
             "stdDev= %lf ms, min=%f ms, max=%f ms",
             i + 1, duration, t.nums1.size(), t.nums2.size(),
             totalDuration / (i + 1),
             sqrt(sqSum / total - pow(totalDuration / total, 2)), minTime,
             maxTime);
    }
  }
  printf("\r\nPassed %d of %d\n", passed, total);
  if (passed == total) {
    printf("All tests passed :-)\n");
  } else {
    printf("%d tests failed :-(\n", total - passed);
  }
  printf("Average time: %lf ms\n", totalDuration / total);
  printf("Max time: %lf ms\n", maxTime);
  printf("Min time: %f ms\n", minTime);
  printf("stddev time: %lf ms\n",
         sqrt(sqSum / total - pow(totalDuration / total, 2)));
  return passed;
}

typedef struct TestType {
  int numTests;
  int minSize;
  int maxSize;
  int magnitude;
} TestType;

int main() {
  vector<TestType> testTypes = {
      {10000, 50, 10000, 1000},
      {1000, 500, 100000, 1000000},
      {100, 5000, 1000000, 100000000},
  };
  for (TestType t : testTypes) {
    printf("##############################################\n\n");
    test(t.numTests, t.minSize, t.maxSize, t.magnitude);
    printf("\n\n");
  }
  return 0;
}
