#pragma once
#include<iostream>
#define true 1
#define false 0
#include "vectordes.h"
template<typename T>//������������A[lo, hi)
void Vector<T>::copyFrom(T const* A, Rank lo, Rank hi) {
    _elem = new T[_capacity = 2 * (hi - lo)];
    _size = 0;
    while (lo < hi)
        _elem[_size++] = A[lo++];
}

template<typename T>//�ռ䲻��ʱ����
void Vector<T>::expand() {
    if (_size < _capacity) return;
    if (_capacity < DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY;
    T* oldElem = _elem;
    _elem = new T[_capacity <<= 1];
    for (int i = 0; i < _size; i++)
        _elem[i] = oldElem[i];
}

template<typename T>//װ�����ӹ�Сʱѹ��
void Vector<T>::shrink() {
    if (_capacity < DEFAULT_CAPACITY << 1) return;
    if (_size << 2 > _capacity) return;
    T* oldElem = _elem;
    _elem = new T[_capacity >>= 1];
    for (int i = 0; i < _size; i++) _elem[i] = oldElem[i];
    delete[] oldElem;
}

template<typename T>
bool Vector<T>::bubble(Rank lo, Rank hi) {//ɨ�轻��
    bool sorted = true;
    while (++lo < hi)
        if (_elem[lo - 1] > _elem[lo]) {
            sorted = false;
            swap(_elem[lo - 1], _elem[lo]);
        }
    return sorted;
}

template<typename T>//��������
void Vector<T>::bubbleSort(Rank lo, Rank hi)
{
    while (!bubble(lo, hi--));
}

template<typename T>//�鲢����
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



template < typename T> //����������������[lo, hi)�ڣ�ȷ��������e�����һ���ڵ����
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

template <typename T> T Vector<T>::remove(Rank r) { //ɾ����������Ϊr��Ԫ�أ�0 <= r < size
    T e = _elem[r]; //���ݱ�ɾ��Ԫ��
    remove(r, r + 1); //��������ɾ���㷨����Ч�ڶ�����[r, r + 1)��ɾ��
    return e; //���ر�ɾ��Ԫ��

}

template <typename T> Rank Vector<T>::remove(Rank lo, Rank hi) { //0 <= lo <= hi <= n
    if (lo == hi) return 0; //����Ч�ʿ��ǣ����������˻����
    while (hi < _size) _elem[lo++] = _elem[hi++]; //��׺[hi, _size)˳��ǰ��hi-loλ
    _size = lo; shrink(); //���¹�ģ��lo=_size֮��������������㣻���Ҫ��������
    //���б�Ҫ��������
    return hi - lo; //���ر�ɾ��Ԫ�ص���Ŀ

}

template < typename T> //��e������[r]
Rank Vector<T>::insert(Rank r, T const& e) { //0 <= r <= size
    expand(); //���Ҫ��������
    for (Rank i = _size; r < i; i--) //�Ժ���ǰ�����Ԫ��
        _elem[i] = _elem[i - 1]; //˳�κ���һ����Ԫ
    _elem[r] = e; _size++; //������Ԫ�ز���������
    return r; //������

}

template <typename T> void Vector<T>::unsort(Rank lo, Rank hi) { //�����������[lo, hi)
    T* V = _elem + lo; //��������_elem[lo, hi)������һ����V[0, hi - lo)
    for (Rank i = hi - lo; 1 < i; --i) //�Ժ���ǰ
        swap(V[i - 1], V[rand() % i]); //��V[i - 1]��V[0, i)��ĳһԪ���������

}




template <typename T> Rank Vector<T>::uniquify() { //���������ظ�Ԫ���޳��㷨����Ч�棩
    Rank i = 0, j = 0; //���Ի��조���ڡ�Ԫ�ص���
    while (++j < _size) //��һɨ�裬ֱ��ĩԪ��
        if (_elem[i] != _elem[j]) //������ͬ��
            _elem[++i] = _elem[j]; //���ֲ�ͬԪ��ʱ����ǰ����������ǰ���Ҳ�
    _size = ++i; shrink(); //ֱ�ӽس�β������Ԫ��
    return j - i; //������ģ�仯��������ɾ��Ԫ������

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
    return oldSize - _size; //��ɾ��Ԫ������
}

template <typename T> void Vector<T>::traverse(void (*visit)(T&)) //���ú���ָ����Ƶı���
{
    for (int i = 0; i < _size; i++) visit(_elem[i]);
}

template <typename T> template < typename VST> //Ԫ�����͡�������
void Vector<T>::traverse(VST& visit) //���������������
{
    for (Rank i = 0; i < _size; i++) visit(_elem[i]);
}

