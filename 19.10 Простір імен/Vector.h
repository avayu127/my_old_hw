#pragma once
#include <iostream>
using namespace std;

//клас що містить масив
template <typename T>
class Vector
{
private:
	//вектор
	T* vect;
	int size;
public:
	//КОНСТРУКТОРИ 
	Vector();
	explicit Vector(int size);  //конструктор, що дозволяє задавати розмір вектора, але котрий не є конструктором перетворення
	Vector(T* ptr, int size);   //конструктор, що дозволяє проініціалізувати вектор за допомогою існуючого масиву
	Vector(const Vector<T>& v); //копі конструктор
	Vector(Vector<T>&& v);      //конструктор переміщення
	~Vector(); //деструктор

	//ГЕТТЕРИ ТА СЕТТЕРИ
	int GetSize()const { return size; }; //функція повертає розмір вектора 
	T* GetVect()const; //функція повертає вектор

	//ПЕРЕВАНТАЖЕННЯ
	Vector<T>& operator = (Vector<T>& v); //перевантажений оператор = copy БЕЗ перетвореня типів

	//перевантажений оператор = copy З перетвореням типів
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

	Vector<T>& operator= (Vector<T>&& v); //перевантажений оператор =move
	T& operator [] (int index)const; //перевантажений оператор індексації

	//ІНШІ МЕТОДИ
	void Print() const; //метод виводу у консоль
	void Inicialization(const T* ptr, int size);

	//ФРЕНД ФУНКЦІЯ ПЕРЕВАНТАЖЕННЯ ОПЕРАТОРА ВИВОДУ 
	template <typename T> friend istream& operator>> <T>(istream& cin, Vector<T>& v); //ввод вектора з клавіатури
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
