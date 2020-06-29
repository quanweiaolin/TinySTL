#ifndef TINY_STL_UNINITIALIZED_H_
#define TINY_STL_UNINITIALIZED_H_

#include "tiny_stl_config.h"
#include "construct.h"
#include "type_traits.h"
#include "iterator.h"
#include <cstring>

TINY_STL_BEGIN

template <class InputIter, class ForwardIter>
ForwardIter uninitialized_copy_aux(InputIter first, InputIter last, ForwardIter result, __true_type)
{
	while (first != last) {
		*result++ = *first++;
	}
	return result;
}

template <class InputIter, class ForwardIter>
ForwardIter uninitialized_copy_aux(InputIter first, InputIter last, ForwardIter result, __false_type)
{
	ForwardIter cur = result;
	for (; first != last; ++cur, ++first)
	{
		tiny_stl::construct(&*cur,*first);
	}
	return cur;
}

template <class InputIter, class ForwardIter, class T>
ForwardIter __uninitialized_copy(InputIter first, InputIter last, ForwardIter result, T*)
{
	typedef typename __type_traits<T>::is_POD_type is_POD;
	return uninitialized_copy_aux(first, last, result, is_POD());
}

template <class InputIter, class ForwardIter>
ForwardIter uninitialized_copy(InputIter first, InputIter last, ForwardIter result)
{
	return __uninitialized_copy(first,last, result, value_type(result));
}

template <class ForwardIter, class T>
inline void uninitialized_fill_aux(ForwardIter first, ForwardIter last, const T& x, __true_type)
{
	while (first != last)
	{
		*first = x;
		++first;
	}
}

template <class ForwardIter, class T>
inline void uninitialized_fill_aux(ForwardIter first, ForwardIter last, const T& x, __false_type)
{
	for (; first != last; ++first)
	{
		construct(&*first, x);
	}
}

template <class ForwardIter, class T1, class T2>
inline void __uninitialized_fill(ForwardIter first, ForwardIter last, const T1& x, T2*)
{
	typedef typename __type_traits<T2>::is_POD_type is_POD;
	uninitialized_fill_aux(first,last,x, is_POD());
}

template <class ForwardIter, class T>
inline void uninitialized_fill(ForwardIter first, ForwardIter last, const T& x)
{
	__uninitialized_fill(first, last, x,value_type(first));
}


template <class ForwardIter, class Size, class T>
inline ForwardIter __uninitialized_fill_n_aux(ForwardIter first, Size n, const T& x, __true_type)
{
	for (Size i = 0; i != n;  ++i)
	{
		*first= x;
		++first;
	}
	return first;
}

template <class ForwardIter, class Size, class T>
inline ForwardIter __uninitialized_fill_n_aux(ForwardIter first, Size n, const T& x, __false_type)
{
	ForwardIter cur = first;
	for (; n > 0; --n, ++cur)
		construct(&*cur, x);
	return cur;
}

template <class ForwardIter, class Size, class T, class T1>
inline ForwardIter __uninitialized_fill_n(ForwardIter first, Size n,
	const T& x, T1*) {
	typedef typename __type_traits<T1>::is_POD_type is_POD;
	return __uninitialized_fill_n_aux(first, n, x, is_POD());

}

template <class ForwardIter, class Size, class T>
inline ForwardIter uninitialized_fill_n(ForwardIter first, Size n, const T& x) 
{
	return __uninitialized_fill_n(first, n, x, value_type(first));
}

TINY_STL_END

#endif
