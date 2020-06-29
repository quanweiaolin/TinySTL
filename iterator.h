#ifndef TINY_STL_ITERATOR_H_
#define TINY_STL_ITERATOR_H_

#include "tiny_stl_config.h"
#include <cstddef>
TINY_STL_BEGIN


struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag :			public input_iterator_tag {};
struct bidirectional_iterator_tag :		public forward_iterator_tag {};
struct random_access_iterator_tag :		public bidirectional_iterator_tag {};

template <class T, class Distance>
struct input_iterator
{
	typedef input_iterator_tag				iterator_catagory;
	typedef T								value_type;
	typedef Distance						difference_type;
	typedef T*								pointer;
	typedef T&								reference;
};

template <class T, class Distance>
struct output_iterator
{
	typedef output_iterator_tag				iterator_catagory;
	typedef void							value_type;
	typedef void							difference_type;
	typedef void							pointer;
	typedef void							reference;
};

template <class T, class Distance>
struct forward_iterator
{
	typedef forward_iterator_tag			iterator_catagory;
	typedef T								value_type;
	typedef Distance						difference_type;
	typedef T*								pointer;
	typedef T&								reference;
};

template <class T, class Distance>
struct bidirectional_iterator
{
	typedef bidirectional_iterator_tag		iterator_catagory;
	typedef T								value_type;
	typedef Distance						difference_type;
	typedef T*								pointer;
	typedef T&								reference;
};

template <class T, class Distance>
struct random_access_iterator
{
	typedef random_access_iterator_tag		iterator_catagory;
	typedef T								value_type;
	typedef Distance						difference_type;
	typedef T* pointer;
	typedef T& reference;
};

template <class Category, class T, class Distance = ptrdiff_t, 
	class Pointer = T*, class Reference = T&>
struct iterator
{
	typedef Category						iterator_catagory;
	typedef T								value_type;
	typedef Distance						difference_type;
	typedef Pointer							pointer;
	typedef Reference						reference;
};

template <class I>
struct iterator_traits
{
	typedef typename I::iterator_catagory	iterator_catagory;
	typedef typename I::value_type			value_type;
	typedef typename I::difference_type		difference_type;
	typedef typename I::pointer				pointer;
	typedef typename I::reference			reference;
};

template <class T>
struct iterator_traits<T*>
{
	typedef random_access_iterator_tag		iterator_catagory;
	typedef T								value_type;
	typedef ptrdiff_t						difference_type;
	typedef T&								reference;
	typedef T*								pointer;
};

template <class T>
struct iterator_traits<const T*>
{
	typedef random_access_iterator_tag		iterator_catagory;
	typedef T								value_type;
	typedef ptrdiff_t						difference_type;
	typedef const T*						pointer;
	typedef const T&						reference;	
};

template <class Iter>
inline typename iterator_traits<Iter>::iterator_catagory catagory(const Iter&)
{
	typedef typename iterator_traits<Iter>::iterator_catagory catagory;
	return catagory();
}

template <class Iter>
inline typename iterator_traits<Iter>::difference_type* distance_type(const Iter&)
{
	return static_cast<typename iterator_traits<Iter>::difference_type*>(0);
}

template <class Iter>
inline typename iterator_traits<Iter>::value_type* value_type(const Iter&)
{
	return static_cast<typename iterator_traits<Iter>::value_type*>(0);
}

template <class Iter>
inline typename iterator_traits<Iter>::difference_type __distance(Iter first, Iter last, input_iterator_tag)
{
	typename iterator_traits<Iter>::difference_type n = 0;
	while (first != last)
	{
		++first;
		++n;
	}
	return n;
}

template <class Iter>
inline typename iterator_traits<Iter>::difference_type __distance(Iter first, Iter last, random_access_iterator_tag)
{
	return static_cast<typename iterator_traits<Iter>::difference_type> (last - first);
}

template <class Iter>
inline typename iterator_traits<Iter>::difference_type distance(Iter first, Iter last)
{
	typedef typename iterator_traits<Iter>::iterator_catagory catagory;
	return __distance(first,last, catagory());
}



template <class Iter, class Distance = ptrdiff_t>
inline void __advance(Iter& iter, Distance n, input_iterator_tag)
{
	while (n--)
	{
		++iter;
	}
}

template <class Iter, class Distance = ptrdiff_t>
inline void __advance(Iter& iter, Distance n, bidirectional_iterator_tag)
{
	if (n >= 0)
	{
		while (n--) ++iter;
	}
	else
	{
		while (n++) --iter;
	}
}

template <class Iter, class Distance = ptrdiff_t>
inline void __advance(Iter& iter, Distance n, random_access_iterator_tag)
{
	iter += n;
}

template <class Iter, class Distance = ptrdiff_t>
inline void advance(Iter& iter, Distance n)
{
	typedef typename iterator_traits<Iter>::iterator_catagory catagory;
	__advance(iter,n, catagory());
}


template <class T, class Distance>
inline T* value_type(const input_iterator<T, Distance>&) { return (T*)(0); };

template <class T, class Distance>
inline T* value_type(const forward_iterator<T, Distance>&) { return (T*)(0); };

template <class T, class Distance>
inline T* value_type(const bidirectional_iterator<T, Distance>&) { return (T*)(0); };

template <class T, class Distance>
inline T* value_type(const random_access_iterator<T, Distance>&) { return (T*)(0); };

template <class T> inline T* value_type(const T*) { return (T*)(0); };





TINY_STL_END
#endif