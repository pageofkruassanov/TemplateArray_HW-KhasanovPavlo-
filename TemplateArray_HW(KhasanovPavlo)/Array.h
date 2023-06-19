#pragma once
#include <iostream>
using namespace std;

template<typename T>
class Array {
private:
	T* arr;
	int sizeArray;
	int grow;
	int tempGrow;
	bool isEmpty;
public:
	Array() : Array(5, 5) {};
	Array(int size, int grow);
	Array(int size, int grow, T* arr);
	int getSize();
	void setSize(int size, int grow);
	T& GetUpperBound();
	bool IsEmpty();
	void FreeExtra();
	void RemoveAll();
	T& GetAt(int index);
	T& operator[](int index);
	void SetAt(int index, T el);
	void Add(T el);
	void Append(Array<T>& obj);
	T* GetData();
	void InsertAt(int index, T el);
	void RemoveAt(int index);

	template <typename T>
	friend ostream& operator<<(ostream& out, Array<T>& obj);
	~Array();
};

template<typename T>
inline Array<T>::Array(int size, int grow)
{
	this->arr = nullptr;
	this->sizeArray = size;
	this->grow = grow;
	isEmpty = true;
}

template<typename T>
inline Array<T>::Array(int size, int grow, T* arr)
{
	this->arr = new T[size + grow];
	for (int i = 0; i < size; i++) {
		this->arr[i] = arr[i];
	}
	this->grow = grow;
	this->sizeArray = size;
	isEmpty = false;
}

template<typename T>
inline int Array<T>::getSize()
{
	return sizeArray + grow;
}

template<typename T>
inline void Array<T>::setSize(int size, int grow)
{
	if (size > this->sizeArray) {
		T* tempArr = new T[this->sizeArray + grow];
		for (int i = 0; i < this->sizeArray; i++) {
			tempArr[i] = this->arr[i];
		}
		this->grow = grow;
		delete[] this->arr;
		this->arr = tempArr;
	}
	else {
		T* tempArr = new T[size + grow];
		for (int i = 0; i < size; i++) {
			tempArr[i] = this->arr[i];
		}
		this->sizeArray = size;
		this->grow = grow;
		delete[] this->arr;
		this->arr = tempArr;
	}
}

template<typename T>
inline T& Array<T>::GetUpperBound()
{
	return this->arr[sizeArray - 1];
}

template<typename T>
inline bool Array<T>::IsEmpty()
{
	return this->isEmpty;
}

template<typename T>
inline void Array<T>::FreeExtra()
{
	T* tempArr = new T[sizeArray];
	for (int i = 0; i < sizeArray; i++) {
		tempArr[i] = arr[i];
	}
	this->grow = 0;
	delete[] this->arr;
	this->arr = tempArr;
}

template<typename T>
inline void Array<T>::RemoveAll()
{
	T* tempArr = new T[this->sizeArray + this->grow];
	delete[] this->arr;
	this->arr = tempArr;
	this->sizeArray = 0;
	this->isEmpty = true;
}

template<typename T>
inline T& Array<T>::GetAt(int index)
{
	if (!this->isEmpty && index >= 0 && index < sizeArray)
		return arr[index];
}

template<typename T>
inline T& Array<T>::operator[](int index)
{
	if (!this->isEmpty && index >= 0 && index < sizeArray)
		return arr[index];

}

template<typename T>
inline void Array<T>::SetAt(int index, T el)
{
	if (!this->isEmpty && index >= 0 && index < sizeArray)
		arr[index] = el;
}

template<typename T>
inline void Array<T>::Add(T el)
{
	tempGrow = grow;
	if (tempGrow > 0) {
		tempGrow--;
		arr[sizeArray] = el;
		sizeArray++;
	}
	else{
		tempGrow = grow;
		T* tempArr = new T[sizeArray + grow];
		for (int i = 0; i < sizeArray; i++) {
			tempArr[i] = arr[i];
		}
		tempArr[sizeArray] = el;
		sizeArray++;
		tempGrow--;
		delete[] arr;
		arr = tempArr;
	}
}

template<typename T>
inline void Array<T>::Append(Array<T>& obj)
{
	if (obj.isEmpty || this->isEmpty)
		return;
	if (this->tempGrow >= obj.sizeArray) {
		for (int i = 0, j = this->sizeArray; i < obj.sizeArray; i++, j++) {
			arr[j] = obj.arr[i];
			tempGrow--;
		}
		sizeArray += obj.sizeArray;
		if (tempGrow == 0) {
			tempGrow = grow;
			T* tempArr = new T[sizeArray + grow];
			for (int i = 0; i < sizeArray; i++) {
				tempArr[i] = arr[i];
			}
			delete[] arr;
			arr = tempArr;
		}
	}
	else {
		T* tempArr = new T[sizeArray + obj.sizeArray + grow];
		tempGrow = grow;
		for (int i = 0; i < sizeArray; i++) {
			tempArr[i] = arr[i];
		}
		for (int i = sizeArray; i < sizeArray + obj.sizeArray; i++) {
			tempArr[i] = obj.arr[i - sizeArray];
		}
		sizeArray += obj.sizeArray;
		delete[] arr;
		arr = tempArr;
	}
}

template<typename T>
inline T* Array<T>::GetData()
{
	return arr;
}

template<typename T>
inline void Array<T>::InsertAt(int index, T el)
{
	if (index >= 0 && index < sizeArray && !isEmpty && tempGrow > 0) {
		for (int i = sizeArray; i > index; i--) {
			arr[i] = arr[i - 1];
		}
		arr[index] = el;
		sizeArray++;
		tempGrow--;
	}
}

template<typename T>
inline void Array<T>::RemoveAt(int index)
{
	if (index >= 0 && index < sizeArray && !isEmpty && tempGrow > 0) {
		for (int i = 0; i < sizeArray - 1; i++) {
			if(index <= i)
				arr[i] = arr[i + 1];
		}
		sizeArray--;
		tempGrow++;
	}
}

template<typename T>
inline Array<T>::~Array()
{
	if (this->arr != nullptr)
		delete[] this->arr;
}

template<typename T>
inline ostream& operator<<(ostream& out, Array<T>& obj)
{
	for (int i = 0; i < obj.sizeArray; i++) {
		out << obj[i] << " ";
	}
	return out;
}
