#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include"../../../vector/stack.h"
using namespace std;
// ����������ݽṹ
class Queue {
private:
    vector<int> data;
    int p_start;
public:
    Queue() { p_start = 0; }
    bool empty() { return p_start >= data.size(); }
    int front() { return data[p_start]; }
    void push(int val) { data.push_back(val); }
    void pop() { p_start++; }
};
// ��������������ĺ���
int largestRectangleArea(vector<int>& heights) {
    int n = heights.size();
    if (n == 0) return 0;
    if (n == 1) return heights[0];
    // ��������ָ���������
    int left, right, area = 0;
    // ���嵥������ջ
    stack<int> s;
    // ����ÿ������
    for (int i = 0; i < n; i++) {
        while (!s.empty() && heights[s.top()] > heights[i]) {
            // ���ջ��Ԫ�ش��ڵ�ǰԪ�أ��򵯳�ջ��Ԫ�ز��������
            int h = heights[s.top()];
            s.pop();
            left = s.empty() ? -1 : s.top();
            right = i;
            area = max(area, h * (right - left - 1));
        }
        s.push(i);
    }
    // ����ջ��ʣ��Ԫ��
    while (!s.empty()) {
        int h = heights[s.top()];
        s.pop();
        left = s.empty() ? -1 : s.top();
        right = n;
        area = max(area, h * (right - left - 1));
    }
    return area;
}

// ������ɸ߶�����
vector<int> generateHeights(int n) {
    vector<int> heights(n);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 105);
    for (int i = 0; i < n; i++) {
        heights[i] = dis(gen);
    }
    return heights;
}

int main() {
    // �������10�����ݽ��в���
    for (int i = 0; i < 10; i++) {
        vector<int> heights = generateHeights(rand() % 10 + 1);
        cout << "������Ŀ " << i + 1 << ": " << endl;
        for (int j = 0; j < heights.size(); j++) {
            cout << heights[j] << " ";
        }
        cout << endl;
        int area = largestRectangleArea(heights);
        cout << "���������: " << area << endl;
        cout << endl;

    }
    return 0;
}