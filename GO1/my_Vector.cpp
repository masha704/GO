//#include "my_Vector.h"
//template<class T>
//my_Vector<T>::my_Vector()
//{
//	this->my_size = 0;
//	this->buffer = new T[this->my_size];
//}
//
//template<class T>
//unsigned int my_Vector<T>::size()
//{
//	return my_size;
//}
//
//template<class T>
//bool my_Vector<T>::empty()
//{
//	return my_size==0;
//}
//
//template<class T>
//void my_Vector<T>::clear()
//{
//	this->my_size = 0;
//	this->buffer = new T[this->my_size];
//}
//
//template<class T>
//T& my_Vector<T>::operator[](unsigned int index)
//{
//	if (index >= 0 && index < my_size)
//		return buffer[index];
//}
//
////template<class T>
////my_Vector<T>& my_Vector<T>::operator=(const my_Vector<T>& v)
////{
////	if (this != &v)
////	{
////		delete[] buffer;
////		buffer = new int[my_size = v.my_size];
////		for (int i = 0; i < my_size; ++i)
////			buffer[i] = v[i];
////	}
////	return *this;
////}
//
//template<class T>
//void my_Vector<T>::push_back(T data)
//{
//	T* _result = new T[++this->my_size];
//	for (int index = 0; index < this->my_size; index++) {
//		if (index != this->my_size - 1) {
//			_result[index] = this->buffer[index];
//		}
//		else {
//			_result[index] = data;
//			break;
//		}
//	}
//	delete[] this->buffer;
//	this->buffer = _result;
//}
//
//
