#include <iostream>  
#include "../vector/vectorex.h"
#include <random>
#include <cstdlib>
#include<windows.h>
#include<ctime>
using namespace std;



class Complex {
  
public:
    double real; // 实部
    double imag; // 虚部
    double model;
    Complex(double r = rand()%10, double i = rand()%10) {
        real = r;
        imag = i;
        model = real * real + imag * imag;
    }

    void display() {
        cout << "(" << real << "," << imag << "i) ";
    }

    double getreal() { return real; }//返回实部
    double getimag() { return imag; }//返回虚部
    double getmodel() {
        model = sqrt(model);
        return model;
    }

    void givereal(double i) { real = i; }
    void giveimag(double i) { imag = i; }

    //复数比较用
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
    cout << "生成的向量:" << endl;//生成qx向量
    Vector<Complex> qx1(10, 10);//起泡乱序后顺序用
    Vector<Complex> qx2(10, 10);//归并乱序后顺序用
    Vector<Complex> qx3(10, 10);//起泡逆序用
    Vector<Complex> qx4(10, 10);//归并逆序用
    Vector<Complex> qx5(10, 10);//查找用
    Randomize(qx1);
    int i;
    

    for (i = 0; i < 10; i++) {
        qx1[i].display();
    }//输出复数向量
    cout << endl;

 
    cout << "置乱后的数组:" << endl;
    qx1.unsort(0, 10);
    for (i = 0; i < 10; i++) {
        qx1[i].display();
    }//置乱
    cout << endl;

    cout << endl << "查找实部虚部相同的复数:" << endl;
    qx1.findcomplex(0, 10);//查找实部和虚部相同的复数并输出
    cout << endl;

    cout << endl << "插入的复数：" << endl;
    Complex insert;//生成一个准备插入的复数
    insert.display();//展示准备插入的复数
    cout << endl << "插入后的复数：" << endl;
    qx1.insert(5, insert);//在向量中间处插入
    for (i = 0; i < 11; i++) {
        qx1[i].display();
    }//输出插入后的复数向量
    cout << endl;

    cout << endl << "区间删除后的复数向量：" << endl;
    qx1.remove( 5 ,9 );//删除向量区间[5，8]的复数
    for (i = 0; i < 9; i++) {
        qx1[i].display();
    }//输出删除区间后的复数向量
    cout << endl;

    int j = qx1.deduplicate();
    cout << endl << "删除重复元素：" << j << "个" << endl << "唯一化后的复数向量:" << endl;
    for (i = 0; i < 9 - j; i++) {
        qx1[i].display();
    }//输出删除重复元素后的复数向量
    cout << endl;

    for (i = 0; i < 10; i++) {
        qx2[i] = qx1[i];
    }

    cout << endl;//起泡排序
    clock_t start1, end1;
    double timeused1;
    start1 = clock();
    qx1.bubbleSort(0, 9);
    cout << "起泡排序后的复数:" << endl;
    for (i = 0; i < 9 - j; i++) {
        qx1[i].display();
    }
    cout << endl;
    end1 = clock();
    timeused1 = ((double)(end1 - start1)) / CLOCKS_PER_SEC;
    cout << "乱序冒泡排序时间：" << timeused1 << "秒" << endl;


    cout << endl;//归并排序
    clock_t start2, end2;
    double timeused2;
    start2 = clock();
    qx2.mergeSort(0, 9);
    cout << "归并排序后的复数:" << endl;
    for (i = 0; i < 9 - j; i++) {
        qx2[i].display();
    }
    cout << endl;
    end2 = clock();
    timeused2 = ((double)(end2 - start2)) / CLOCKS_PER_SEC;
    cout << "乱序归并排序时间：" << timeused1 << "秒" << endl;


    cout << endl;
    clock_t start3, end3;
    double timeused3;
    start3 = clock();
    qx1.bubbleSort(0, 9);
    cout << "起泡排序后的复数:" << endl;
    for (i = 0; i < 9 - j; i++) {
        qx1[i].display();
    }
    cout << endl;
    end3 = clock();
    timeused3 = ((double)(end3 - start3)) / CLOCKS_PER_SEC;
    cout << "顺序冒泡排序时间：" << timeused1 << "秒" << endl;


    cout << endl;
    clock_t start4, end4;
    double timeused4;
    start4 = clock();
    qx2.mergeSort(0, 9);
    cout << "归并排序后的复数:" << endl;
    for (i = 0; i < 9 - j; i++) {
        qx2[i].display();
    }
    cout << endl;
    end4 = clock();
    timeused4 = ((double)(end4 - start4)) / CLOCKS_PER_SEC;
    cout << "顺序归并排序时间：" << timeused1 << "秒" << endl;

    //将排序好的结果逆序化
    for (i = 0; i < 10; i++) {
        qx3[i] = qx1[9-i];
    }
    for (i = 0; i < 10; i++) {
        qx4[i] = qx2[9 - i];
    }

    cout << endl;
    cout <<  "逆序后的向量：" << endl;
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
    cout << "起泡排序后的复数:" << endl;
    for (i = 1; i < 10 - j; i++) {
        qx3[i].display();
    }
    cout << endl;
    end5 = clock();
    timeused5 = ((double)(end5 - start5)) / CLOCKS_PER_SEC;
    cout << "逆序冒泡排序时间：" << timeused1 << "秒" << endl;


    cout << endl;
    clock_t start6, end6;
    double timeused6;
    start6 = clock();
    qx4.mergeSort(1, 10);
    cout << "归并排序后的复数:" << endl;
    for (i = 1; i < 10 - j; i++) {
        qx4[i].display();
    }
    cout << endl;
    end6 = clock();
    timeused6 = ((double)(end6 - start6)) / CLOCKS_PER_SEC;
    cout << "逆序归并排序时间：" << timeused1 << "秒" << endl;

    //查找模在区间[2,7)内的复数
    cout << endl;
    int m1 = 2;
    int m2 = 7;
    int sum = 0;
    double num;
    for (i = 0; i < 10; i++) {
        num = qx1[i].getmodel();
        if (num >= m1 && num < m2) {//若在[m1,m2)区间，则给子向量按序赋值
            qx5[sum].givereal(qx1[i].getreal());
            qx5[sum].giveimag(qx1[i].getimag());
            sum++;
        }
        else if (num >= m2) {//若已大于m2，则退出赋值
            break;
        }
    }
    cout << "查找模在区间[2,7)内的复数向量:" << endl;
    for (i = 0; i < sum; i++) {
        qx5[i].display();
    }//按序输出子向量
    return 0;


























}


