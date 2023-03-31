#include <iostream>  
#include "../vector/vectorex.h"
#include <random>
#include <cstdlib>
#include<windows.h>
#include<ctime>
using namespace std;



class Complex {
  
public:
    double real; // ʵ��
    double imag; // �鲿
    double model;
    Complex(double r = rand()%10, double i = rand()%10) {
        real = r;
        imag = i;
        model = real * real + imag * imag;
    }

    void display() {
        cout << "(" << real << "," << imag << "i) ";
    }

    double getreal() { return real; }//����ʵ��
    double getimag() { return imag; }//�����鲿
    double getmodel() {
        model = sqrt(model);
        return model;
    }

    void givereal(double i) { real = i; }
    void giveimag(double i) { imag = i; }

    //�����Ƚ���
    bool operator>(Complex& c)const
    {
        if (real > c.real)
            return true;
        else if (real == c.real)
        {
            if (imag > c.imag)
            {
                return true;
            }
            else
                return false;
        }
        else
            return false;
    }
    bool operator<(Complex& c)const
    {
        if (real < c.real)
        {
            return true;
        }
        else if (real == c.real)
        {
            if (imag < c.imag)
                return true;
            else
                return false;
        }
        else
            return false;
    }
    bool operator>=(Complex& c)const
    {
        if (*this < c)
            return false;
        else
            return true;
    }
    bool operator<=(Complex& c)const
    {
        if (*this > c)
            return false;
        else
            return true;
    }
    bool operator==(Complex& c)const
    {
        if ((*this > c) || (*this < c))
            return false;
        else
            return true;
    }
    bool operator!=(Complex& c)
    {
        if (*this == c)
            return false;
        else
            return true;
    }
};

void Randomize(Vector<Complex>& v) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 100);
    for (unsigned i = 0; i < v.size(); i++) {
        double real = double(dis(gen)) / 10.0;
        double imag = double(dis(gen)) / 10.0;
        Complex c(real, imag);
        v[i] = c;
    }
}



int main() {
    int tp1, tp2;
    cout << "���ɵ�����:" << endl;//����qx����
    Vector<Complex> qx1(10, 10);//���������˳����
    Vector<Complex> qx2(10, 10);//�鲢�����˳����
    Vector<Complex> qx3(10, 10);//����������
    Vector<Complex> qx4(10, 10);//�鲢������
    Vector<Complex> qx5(10, 10);//������
    Randomize(qx1);
    int i;
    

    for (i = 0; i < 10; i++) {
        qx1[i].display();
    }//�����������
    cout << endl;

 
    cout << "���Һ������:" << endl;
    qx1.unsort(0, 10);
    for (i = 0; i < 10; i++) {
        qx1[i].display();
    }//����
    cout << endl;

    cout << endl << "����ʵ���鲿��ͬ�ĸ���:" << endl;
    qx1.findcomplex(0, 10);//����ʵ�����鲿��ͬ�ĸ��������
    cout << endl;

    cout << endl << "����ĸ�����" << endl;
    Complex insert;//����һ��׼������ĸ���
    insert.display();//չʾ׼������ĸ���
    cout << endl << "�����ĸ�����" << endl;
    qx1.insert(5, insert);//�������м䴦����
    for (i = 0; i < 11; i++) {
        qx1[i].display();
    }//��������ĸ�������
    cout << endl;

    cout << endl << "����ɾ����ĸ���������" << endl;
    qx1.remove( 5 ,9 );//ɾ����������[5��8]�ĸ���
    for (i = 0; i < 9; i++) {
        qx1[i].display();
    }//���ɾ�������ĸ�������
    cout << endl;

    int j = qx1.deduplicate();
    cout << endl << "ɾ���ظ�Ԫ�أ�" << j << "��" << endl << "Ψһ����ĸ�������:" << endl;
    for (i = 0; i < 9 - j; i++) {
        qx1[i].display();
    }//���ɾ���ظ�Ԫ�غ�ĸ�������
    cout << endl;

    for (i = 0; i < 10; i++) {
        qx2[i] = qx1[i];
    }

    cout << endl;//��������
    clock_t start1, end1;
    double timeused1;
    start1 = clock();
    qx1.bubbleSort(0, 9);
    cout << "���������ĸ���:" << endl;
    for (i = 0; i < 9 - j; i++) {
        qx1[i].display();
    }
    cout << endl;
    end1 = clock();
    timeused1 = ((double)(end1 - start1)) / CLOCKS_PER_SEC;
    cout << "����ð������ʱ�䣺" << timeused1 << "��" << endl;


    cout << endl;//�鲢����
    clock_t start2, end2;
    double timeused2;
    start2 = clock();
    qx2.mergeSort(0, 9);
    cout << "�鲢�����ĸ���:" << endl;
    for (i = 0; i < 9 - j; i++) {
        qx2[i].display();
    }
    cout << endl;
    end2 = clock();
    timeused2 = ((double)(end2 - start2)) / CLOCKS_PER_SEC;
    cout << "����鲢����ʱ�䣺" << timeused1 << "��" << endl;


    cout << endl;
    clock_t start3, end3;
    double timeused3;
    start3 = clock();
    qx1.bubbleSort(0, 9);
    cout << "���������ĸ���:" << endl;
    for (i = 0; i < 9 - j; i++) {
        qx1[i].display();
    }
    cout << endl;
    end3 = clock();
    timeused3 = ((double)(end3 - start3)) / CLOCKS_PER_SEC;
    cout << "˳��ð������ʱ�䣺" << timeused1 << "��" << endl;


    cout << endl;
    clock_t start4, end4;
    double timeused4;
    start4 = clock();
    qx2.mergeSort(0, 9);
    cout << "�鲢�����ĸ���:" << endl;
    for (i = 0; i < 9 - j; i++) {
        qx2[i].display();
    }
    cout << endl;
    end4 = clock();
    timeused4 = ((double)(end4 - start4)) / CLOCKS_PER_SEC;
    cout << "˳��鲢����ʱ�䣺" << timeused1 << "��" << endl;

    //������õĽ������
    for (i = 0; i < 10; i++) {
        qx3[i] = qx1[9-i];
    }
    for (i = 0; i < 10; i++) {
        qx4[i] = qx2[9 - i];
    }

    cout << endl;
    cout <<  "������������" << endl;
    for (i = 1; i < 10 - j; i++) {
        qx3[i].display();  
    }
    cout << endl;
    for (i = 1; i < 10 - j; i++) {    
        qx4[i].display();
    }
    cout << endl;


    cout << endl;
    clock_t start5, end5;
    double timeused5;
    start5 = clock();
    qx3.bubbleSort(1, 10);
    cout << "���������ĸ���:" << endl;
    for (i = 1; i < 10 - j; i++) {
        qx3[i].display();
    }
    cout << endl;
    end5 = clock();
    timeused5 = ((double)(end5 - start5)) / CLOCKS_PER_SEC;
    cout << "����ð������ʱ�䣺" << timeused1 << "��" << endl;


    cout << endl;
    clock_t start6, end6;
    double timeused6;
    start6 = clock();
    qx4.mergeSort(1, 10);
    cout << "�鲢�����ĸ���:" << endl;
    for (i = 1; i < 10 - j; i++) {
        qx4[i].display();
    }
    cout << endl;
    end6 = clock();
    timeused6 = ((double)(end6 - start6)) / CLOCKS_PER_SEC;
    cout << "����鲢����ʱ�䣺" << timeused1 << "��" << endl;

    //����ģ������[2,7)�ڵĸ���
    cout << endl;
    int m1 = 2;
    int m2 = 7;
    int sum = 0;
    double num;
    for (i = 0; i < 10; i++) {
        num = qx1[i].getmodel();
        if (num >= m1 && num < m2) {//����[m1,m2)���䣬�������������ֵ
            qx5[sum].givereal(qx1[i].getreal());
            qx5[sum].giveimag(qx1[i].getimag());
            sum++;
        }
        else if (num >= m2) {//���Ѵ���m2�����˳���ֵ
            break;
        }
    }
    cout << "����ģ������[2,7)�ڵĸ�������:" << endl;
    for (i = 0; i < sum; i++) {
        qx5[i].display();
    }//�������������
    return 0;


























}


