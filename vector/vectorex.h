#pragma once
#include<iostream>
#define true 1
#define false 0
#include "vectordes.h"
template<typename T>//复制数组区间A[lo, hi)
void Vector<T>::copyFrom(T const* A, Rank lo, Rank hi) {
    _elem = new T[_capacity = 2 * (hi - lo)];
    _size = 0;
    while (lo < hi)
        _elem[_size++] = A[lo++];
}

template<typename T>//空间不足时扩容
void Vector<T>::expand() {
    if (_size < _capacity) return;
    if (_capacity < DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY;
    T* oldElem = _elem;
    _elem = new T[_capacity <<= 1];
    for (int i = 0; i < _size; i++)
        _elem[i] = oldElem[i];
}

template<typename T>//装填因子过小时压缩
void Vector<T>::shrink() {
    if (_capacity < DEFAULT_CAPACITY << 1) return;
    if (_size << 2 > _capacity) return;
    T* oldElem = _elem;
    _elem = new T[_capacity >>= 1];
    for (int i = 0; i < _size; i++) _elem[i] = oldElem[i];
    delete[] oldElem;
}

template<typename T>
bool Vector<T>::bubble(Rank lo, Rank hi) {//扫描交换
    bool sorted = true;
    while (++lo < hi)
        if (_elem[lo - 1] > _elem[lo]) {
            sorted = false;
            swap(_elem[lo - 1], _elem[lo]);
        }
    return sorted;
}

template<typename T>//起泡排序
void Vector<T>::bubbleSort(Rank lo, Rank hi)
{
    while (!bubble(lo, hi--));
}

template<typename T>//归并排序
void Vector<T>::merge(Rank lo, Rank mi, Rank hi) {
    T* A = _elem + lo;
    int lb = mi - lo;
    T* B = new T[lb];
    for (Rank i = 0; i < lb; B[i] = A[i++]);
    int lc = hi - mi;
    T* C = _elem + mi;
    for (Rank i = 0, j = 0, k = 0; (j < lb) || (k < lc);) {
        if ((j < lb) && (k >= lc || (B[j] <= C[k]))) A[i++] = B[j++];
        if ((k < lc) && (j >= lb || (C[k] < B[j]))) A[i++] = C[k++];
    }
    delete[] B;
}

template<typename T>
void Vector<T>::mergeSort(Rank lo, Rank hi) {
    if (hi - lo < 2) return;
    int mi = (lo + hi) / 2;
    mergeSort(lo, mi);
    mergeSort(mi, hi);
    merge(lo, mi, hi);
}



template < typename T> //在有序向量的区间[lo, hi)内，确定不大于e的最后一个节点的秩
Rank Vector<T>::search(T const& e, Rank lo, Rank hi) const { // 0 <= lo < hi <= _size
    return (rand() % 2) ?
        binSearch(_elem, e, lo, hi) : fibSearch(_elem, e, lo, hi);
}

template<typename T>
Vector<T>& Vector<T>::operator=(Vector<T> const& V) {
    delete[] _elem;
    copyFrom(V._elem, 0, V.size());
    return *this;
}

template<typename T>
T& Vector<T>::operator[](Rank r) { return _elem[r]; }

template <typename T> T Vector<T>::remove(Rank r) { //删除向量中秩为r的元素，0 <= r < size
    T e = _elem[r]; //备份被删除元素
    remove(r, r + 1); //调用区间删除算法，等效于对区间[r, r + 1)的删除
    return e; //返回被删除元素

}

template <typename T> Rank Vector<T>::remove(Rank lo, Rank hi) { //0 <= lo <= hi <= n
    if (lo == hi) return 0; //出于效率考虑，单独处理退化情况
    while (hi < _size) _elem[lo++] = _elem[hi++]; //后缀[hi, _size)顺次前移hi-lo位
    _size = lo; shrink(); //更新规模，lo=_size之后的内容无需清零；如必要，则缩容
    //若有必要，则缩容
    return hi - lo; //返回被删除元素的数目

}

template < typename T> //将e插入至[r]
Rank Vector<T>::insert(Rank r, T const& e) { //0 <= r <= size
    expand(); //如必要，先扩容
    for (Rank i = _size; r < i; i--) //自后向前，后继元素
        _elem[i] = _elem[i - 1]; //顺次后移一个单元
    _elem[r] = e; _size++; //置入新元素并更新容量
    return r; //返回秩

}

template <typename T> void Vector<T>::unsort(Rank lo, Rank hi) { //随机置乱区间[lo, hi)
    T* V = _elem + lo; //将子向量_elem[lo, hi)视作另一向量V[0, hi - lo)
    for (Rank i = hi - lo; 1 < i; --i) //自后向前
        swap(V[i - 1], V[rand() % i]); //将V[i - 1]与V[0, i)中某一元素随机交换

}




template <typename T> Rank Vector<T>::uniquify() { //有序向量重复元素剔除算法（高效版）
    Rank i = 0, j = 0; //各对互异“相邻”元素的秩
    while (++j < _size) //逐一扫描，直至末元素
        if (_elem[i] != _elem[j]) //跳过雷同者
            _elem[++i] = _elem[j]; //发现不同元素时，向前移至紧邻于前者右侧
    _size = ++i; shrink(); //直接截除尾部多余元素
    return j - i; //向量规模变化量，即被删除元素总数

}

template<typename T>
Rank Vector<T>::deduplicate() {
    int oldSize = _size;
    Rank i = 0;
    while (i < _size - 1) {
        Rank j;
        j = i + 1;
        while (j < _size) {
            if ((_elem[i].getreal() == _elem[j].getreal()) && (_elem[i].getimag() == _elem[j].getimag())) {
                remove(j, j + 1);
            }
            else {
                j++;
            }
        }
        i++;
    }
    return oldSize - _size; //被删除元素总数
}

template <typename T> void Vector<T>::traverse(void (*visit)(T&)) //利用函数指针机制的遍历
{
    for (int i = 0; i < _size; i++) visit(_elem[i]);
}

template <typename T> template < typename VST> //元素类型、操作器
void Vector<T>::traverse(VST& visit) //借助函数对象机制
{
    for (Rank i = 0; i < _size; i++) visit(_elem[i]);
}

