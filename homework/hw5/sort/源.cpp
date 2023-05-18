#include <iostream>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include<vector>
#include <algorithm>
#include <numeric>   
using namespace std;

void bubble_sort(vector<int>& nums) {
    int n = nums.size();
    for (int i = 0; i < n - 1; ++i) {
        bool flag = false;
        for (int j = 0; j < n - 1 - i; ++j) {
            if (nums[j] > nums[j + 1]) {
                swap(nums[j], nums[j + 1]);
                flag = true;
            }
        }
        if (!flag) break;
    }
}

void insertion_sort(vector<int>& nums) {
    int n = nums.size();
    for (int i = 1; i < n; ++i) {
        int curr = nums[i];
        int j;
        for (j = i - 1; j >= 0 && nums[j] > curr; --j) {
            nums[j + 1] = nums[j];
        }
        nums[j + 1] = curr;
    }
}

void selection_sort(vector<int>& nums) {
    int n = nums.size();
    for (int i = 0; i < n - 1; ++i) {
        int min_idx = i;
        for (int j = i + 1; j < n; ++j) {
            if (nums[j] < nums[min_idx]) {
                min_idx = j;
            }
        }
        swap(nums[i], nums[min_idx]);
    }
}

void merge(vector<int>& nums, vector<int>& tmp, int left, int mid, int right) {
    int i = left, j = mid + 1, k = left;
    while (i <= mid && j <= right) {
        if (nums[i] < nums[j]) {
            tmp[k++] = nums[i++];
        }
        else {
            tmp[k++] = nums[j++];
        }
    }
    while (i <= mid) {
        tmp[k++] = nums[i++];
    }
    while (j <= right) {
        tmp[k++] = nums[j++];
    }
    for (int x = left; x <= right; ++x) {
        nums[x] = tmp[x];
    }
}

void merge_sort_helper(vector<int>& nums, vector<int>& tmp, int left, int right) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    merge_sort_helper(nums, tmp, left, mid);
    merge_sort_helper(nums, tmp, mid + 1, right);
    merge(nums, tmp, left, mid, right);
}

void merge_sort(vector<int>& nums) {
    int n = nums.size();
    vector<int> tmp(n);
    merge_sort_helper(nums, tmp, 0, n - 1);
}


int partition(vector<int>& nums, int left, int right) {
    int pivot = nums[right];
    int i = left - 1;
    for (int j = left; j < right; ++j) {
        if (nums[j] <= pivot) {
            ++i;
            swap(nums[i], nums[j]);
        }
    }
    swap(nums[i + 1], nums[right]);
    return i + 1;
}


void quick_sort_helper(vector<int>& nums, int left, int right) {
    if (left >= right) return;
    int pivot_idx = partition(nums, left, right);
    quick_sort_helper(nums, left, pivot_idx - 1);
    quick_sort_helper(nums, pivot_idx + 1, right);
}

void quick_sort(vector<int>& nums) {
    int n = nums.size();
    quick_sort_helper(nums, 0, n - 1);
}

void print(vector<int>& nums) {
    for (int num : nums) {
        cout << num << " ";
    }
    cout << endl;
}

void test_sorting_algorithm(const string& name, void (*sorting_algorithm)(vector<int>&), vector<int>& nums) {
    auto start = chrono::steady_clock::now();
    sorting_algorithm(nums);
    auto end = chrono::steady_clock::now(); chrono::duration<double, milli> elapsed_time = end - start;
    cout << name << ":" << endl;
    cout << "运行时间: " << elapsed_time.count()*1000 << "微秒" << endl;
}

int main() {
    srand(time(nullptr));

    // Test on ordered sequence
    vector<int> nums1(10000);
    cout << "第一组数据测试时间：" << endl;
    iota(nums1.begin(), nums1.end(), 1); 
    test_sorting_algorithm("冒泡排序", bubble_sort, nums1);
    test_sorting_algorithm("插入排序", insertion_sort, nums1);
    test_sorting_algorithm("选择排序", selection_sort, nums1);
    test_sorting_algorithm("归并排序", merge_sort, nums1);
    test_sorting_algorithm("快速排序", quick_sort, nums1);
    cout << endl;

    // Test on reversed sequence
    vector<int> nums2(10000);
    cout << "第二组数据测试时间：" << endl;
    iota(nums2.rbegin(), nums2.rend(), 1); 
    test_sorting_algorithm("冒泡排序", bubble_sort, nums2);
    test_sorting_algorithm("插入排序", insertion_sort, nums2);
    test_sorting_algorithm("选择排序", selection_sort, nums2);
    test_sorting_algorithm("归并排序", merge_sort, nums2);
    test_sorting_algorithm("快速排序", quick_sort, nums2);
    cout << endl;

    // Test on random sequence
    vector<int> nums3(10000);
    cout << "第三组数据测试时间：" << endl;
    generate(nums3.begin(), nums3.end(), [] { return rand(); });
    test_sorting_algorithm("冒泡排序", bubble_sort, nums3);
    test_sorting_algorithm("插入排序", insertion_sort, nums3);
    test_sorting_algorithm("选择排序", selection_sort, nums3);
    test_sorting_algorithm("归并排序", merge_sort, nums3);
    test_sorting_algorithm("快速排序", quick_sort, nums3);
    cout << endl;

    return 0;
}



