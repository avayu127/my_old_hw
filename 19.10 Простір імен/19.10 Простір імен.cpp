#include<iostream>
#include"Vector.h"
using namespace std;

int main() {
	const int size = 5;
	int* ptrA = new int[size];
	for (int i = 0; i < size; i++) {
		ptrA[i] = i + 2;
	}
	Vector<int> obj1(ptrA, size);
	obj1.Print();
	cout << endl;

	double* ptrB = new double[size];
	for (int i = 0; i < size; i++) {
		ptrB[i] = (double)i + 0.1;
	}
	Vector<double> obj2(ptrB, size);
	obj2.Print();
	cout << endl;

	obj2 = obj1;
	obj2.Print();
}