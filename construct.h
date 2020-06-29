#ifndef TINY_STL_CONSTRUCT_H_
#define TINY_STL_CONSTRUCT_H_

#include "tiny_stl_config.h"
#include "type_traits.h"
#include <new>
#include "iterator.h"

TINY_STL_BEGIN

template <class Ty1, class Ty2>
inline void construct(Ty1* ptr, const Ty2& val)
{
	::new ((void*)ptr) Ty1(val);
}

template <class Ty>
inline void destroy(Ty * pointer)
{
	pointer->~Ty();
}

template <class Iter>
inline void destroy_aux(Iter first, Iter last, __true_type){}

template <class Iter>
inline void destroy_aux(Iter first, Iter last, __false_type)
{
	for (; first < last; ++first)
		destroy(&*first);
}

template <class Iter, class T>
inline void __destroy(Iter first, Iter last, T*)
{
	typedef typename __type_traits<T>::has_trivial_destructor trivial_destructor;
	destroy_aux(first, last, trivial_destructor());
}

template <class Iter>
inline void destroy(Iter first, Iter last)
{
	__destroy(first, last, value_type(last));
}


inline void destroy(char*, char*) {}
inline void destroy(wchar_t*, wchar_t*) {}



TINY_STL_END


#endif
