#include <stdexcept> // std::out_of_range

template<typename T>
Array2D<T>::Array2D(size_t pLin,size_t pCol) : lin(pLin), col(pCol){
	size_t s = size();
	if(s != 0){
		data = new T[s];
	}
}

template<typename T>
Array2D<T>::~Array2D(){
	if(data != nullptr){
		delete[] data;
		data = nullptr;
	}
}

template<typename T>
Array2D<T> Array2D<T>::operator=(Array2D<T>& other){
	if(data != nullptr){
		delete[] data;
		data = nullptr;
	}
	lin = other.lin;
	col = other.col;
	size_t oS = other.size();
	if(oS != 0){
		data = new T[oS];
		for(size_t i = 0;i < oS;i++){
			data[i] = other.data[i];
		}
	}
	return *this;
}

template<typename T>
size_t Array2D<T>::lines() const{
	return lin;
}

template<typename T>
size_t Array2D<T>::columns() const{
	return col;
}

template<typename T>
size_t Array2D<T>::size() const{
	return lin*col;
}

template<typename T>
T Array2D<T>::at(size_t x,size_t y){
	if(x > col){
		throw new std::out_of_range("x parameter out of range");
	}
	if(y > lin){
		throw new std::out_of_range("y parameter out of range");
	}
	return data[x+y*col];
}

template<typename T>
T Array2D<T>::operator()(size_t x,size_t y){
	return at(x,y);
}

template<typename T>
const T Array2D<T>::at(size_t x,size_t y) const{
	if(x > col){
		throw new std::out_of_range("x parameter out of range");
	}
	if(y > lin){
		throw new std::out_of_range("y parameter out of range");
	}
	return data[x+y*col];
}

template<typename T>
const T Array2D<T>::operator()(size_t x,size_t y) const{
	return at(x,y);
}

template<typename T>
T Array2D<T>::at(size_t i){
	if(i > size()){
		throw new std::out_of_range("i parameter out of range");
	}
	return data[i];
}

template<typename T>
T Array2D<T>::operator[](size_t i){
	return at(i);
}

template<typename T>
T Array2D<T>::operator()(size_t i){
	return at(i);
}

template<typename T>
const T Array2D<T>::at(size_t i) const{
	if(i > size()){
		throw new std::out_of_range("i parameter out of range");
	}
	return data[i];
}

template<typename T>
const T Array2D<T>::operator[](size_t i) const{
	return at(i);
}

template<typename T>
const T Array2D<T>::operator()(size_t i) const{
	return at(i);
}
