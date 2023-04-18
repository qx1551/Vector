#pragma once
#include"list.h"

template <typename T>
class Queue : public List<T>
{       // ����ģ���ࣨ�̳�Listԭ�нӿڣ�
public: // size()��empty()�Լ��������Žӿھ���ֱ������
    void enqueue(T const& e)
    {
        List<T>::insertAsLast(e);
    }
    T dequeue() { return List<T>::remove(List<T>::first()); }
    T& front() { return List<T>::first()->data; }
};
