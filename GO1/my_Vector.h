#pragma once
using namespace std;
template <class T>

class my_Vector
{
public:
	//typedef T* iterator;

	my_Vector() {
		this->my_size = 0;
		this->buffer = new T[this->my_size];
	}
	unsigned int size() { return my_size; }
	bool empty() { return my_size == 0; }
	void clear() {
		this->my_size = 0;
		this->buffer = new T[this->my_size];
	}
	T& operator[](unsigned int index) {
		if (index >= 0 && index < my_size)
			return buffer[index];
	}

	const my_Vector<T>& operator=(my_Vector<T>& v)
	{
		if (this != &v)
		{
			delete[] buffer;
			buffer = new T[my_size = v.my_size];
			for (int i = 0; i < my_size; ++i)
				buffer[i] = v[i];
		}
		return *this;
	}

	void push_back(T data) {
		T* _result = new T[++this->my_size];
		for (int index = 0; index < this->my_size; index++) {
			if (index != this->my_size - 1) {
				_result[index] = this->buffer[index];
			}
			else {
				_result[index] = data;
				break;
			}
		}
		delete[] this->buffer;
		this->buffer = _result;
	}


private:
	T* buffer;
	unsigned int my_size;
};

