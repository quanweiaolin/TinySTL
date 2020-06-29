#ifndef TINY_STL_ALLOCATOR_H_
#define TINY_STL_ALLOCATOR_H_

#include "tiny_stl_config.h"
#include <stdlib.h>
#include <limits>
#include <cstddef>

TINY_STL_BEGIN

template <class T>
struct allocator
{
	typedef T value_type;
	typedef T* pointer;
	typedef const T* const_pointer;
	typedef T& reference;
	typedef const T& const_reference;
	typedef T& reference;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;

	allocator() {};
	~allocator() {};
	static T * allocate(size_t n);
	static void deallocate(pointer ptr, size_t n);
	static T* reallocate(pointer ptr, size_t, size_t new_sz);
	static size_t max_size();
	static void construct(pointer ptr, const_reference val);
	static void destroy(pointer ptr);
	static void destroy(pointer first, pointer last);

	//bool operator==(allocator);
};

template <class T>
T * allocator<T>::allocate(size_t n)
{
	T * result =static_cast<T*>(malloc(sizeof(T)*n));
	return result;
}

template <class T>
void allocator<T>::deallocate(pointer ptr, size_t n)
{
	free(ptr);
}

template <class T>
T* allocator<T>::reallocate(pointer ptr, size_t, size_t new_sz)
{
	return static_cast<T*>(realloc(ptr, new_sz));
}

template <class T>
size_t allocator<T>::max_size()
{
	return std::numeric_limits<value_type>::max() / sizeof(value_type);
}

template <class T>
void allocator<T>::construct(pointer ptr, const_reference val)
{
	tiny_stl::construct(ptr, val);
}

template <class T>
void allocator<T>::destroy(pointer ptr)
{
	tiny_stl::destroy(ptr);
}

template <class T>
void allocator<T>::destroy(pointer first, pointer last)
{
	tiny_stl::destroy(first, last);
}

TINY_STL_END

#endif

