#pragma once
#include <iostream>
using namespace std;

//���� �� ������ �����
template <typename T>
class Vector
{
private:
	//������
	T* vect;
	int size;
public:
	//������������ 
	Vector();
	explicit Vector(int size);  //�����������, �� �������� �������� ����� �������, ��� ������ �� � ������������� ������������
	Vector(T* ptr, int size);   //�����������, �� �������� �������������� ������ �� ��������� ��������� ������
	Vector(const Vector<T>& v); //��� �����������
	Vector(Vector<T>&& v);      //����������� ����������
	~Vector(); //����������

	//������� �� �������
	int GetSize()const { return size; }; //������� ������� ����� ������� 
	T* GetVect()const; //������� ������� ������

	//��������������
	Vector<T>& operator = (Vector<T>& v); //�������������� �������� = copy ��� ����������� ����

	//�������������� �������� = copy � ������������ ����
	template< typename T1>
	Vector<T>& operator= (const Vector<T1>& v)
	{
		if (v.GetVect() == nullptr)
		{
			return *this;
		}
		if (vect != nullptr)
		{
			delete[]vect;
		}
		size = v.GetSize();
		vect = new T[size];
		for (int i = 0; i < size; i++)
		{
			vect[i] = (T)v.GetVect()[i];
		}
		return *this;
	}

	Vector<T>& operator= (Vector<T>&& v); //�������������� �������� =move
	T& operator [] (int index)const; //�������������� �������� ����������

	//��ز ������
	void Print() const; //����� ������ � �������
	void Inicialization(const T* ptr, int size);

	//����� ����ֲ� �������������� ��������� ������ 
	template <typename T> friend istream& operator>> <T>(istream& cin, Vector<T>& v); //���� ������� � ���������
};



template <typename T>
Vector<T>::Vector()
{
	size = 0;
	vect = nullptr;
}

//DZ-----------------------------------------------------------------
template <typename T>
Vector<T>::Vector(int size)
{
	try {
		if (size < 0) throw "ERROR - size can't be a negative number";
		else
		{
			this->size = size;
			vect = new T[size];
			//*(vect + size) = '\0';
		}
	}
	catch (const char* warning) {
		cout << "\n\n" << warning << "\n\n";
	}
}

template <typename T>
Vector<T>::Vector(T* ptr, int size)
{
	vect = ptr;
	this->size = size;
}

template <typename T>
Vector<T>::Vector(const Vector<T>& v)
{
	vect = new T[v.size];
	vect = v.vector;
	size = v.size;
}

template <typename T>
Vector<T>::Vector(Vector<T>&& v)
{
	vect = v.vect;
	size = v.size;
	v.vect = nullptr;
	v.size = 0;
}

template <typename T>
Vector<T>::~Vector()
{
	delete[] vect;
}

template<class T>
T* Vector<T>::GetVect() const {
	return vect;
}

template <typename T>
Vector<T>& Vector<T>::operator= (Vector<T>& v)
{
	if (this == &v) {
		return *this;
	}
	if (vect != nullptr) {
		delete[] vect;
	}
	vect = new T[v.size];
	vect = v.vect;
	size = v.size;
	return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator= (Vector<T>&& v)
{
	if (vect != nullptr) {
		delete[] vect;
	}
	vect = v.vect;
	v.vect = nullptr;
	size = v.size;
	v.size = 0;
	return *this;
}

template <typename T>
T& Vector<T>::operator[] (int index)const
{
	try {
		if (index >= 0 && index < strlen(vect))
		{
			return vect[index];
		}
		else
		{
			throw "ERROR - wrong index";
		}
	}

	catch (const char* warning)
	{
		cout << "\n\n" << warning << "\n\n";
	}
}


template <typename T>
void Vector<T>::Print() const
{
	for (int i = 0; i < size; i++)
	{
		cout << vect[i] << "\t";
	}
}

template <typename T>
void Vector<T>::Inicialization(const T* ptr, int size)
{
	vect = ptr;
	this->size = size;
}

template <typename T>
std::istream& operator>>(std::istream& cin, Vector<T>& v)
{
	cin >> v.vect;
	cin >> v.size;

	return cin;
}
