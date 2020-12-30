#ifndef array_2d_h
#define array_2d_h

#include <stddef.h> // size_t

template<typename T>
class Array2D{
	
	private:
		T* data = nullptr;
		size_t lin;
		size_t col;
	
	public:
		Array2D(size_t pLin,size_t pCol);
		Array2D(const Array2D& other);
		~Array2D();
		
		Array2D operator=(const Array2D& other);
		
		size_t lines() const;
		size_t columns() const;
		size_t size() const;
		
		T at(size_t x,size_t y);
		T operator()(size_t x,size_t y);
		
		const T at(size_t x,size_t y) const;
		const T operator()(size_t x,size_t y) const;
		
		T at(size_t i);
		T operator[](size_t i);
		T operator()(size_t i);
		
		const T at(size_t i) const;
		const T operator[](size_t i) const;
		const T operator()(size_t i) const;
};

#include "Array2D.hpp"

#endif // array_2d_h
