#ifndef TINY_STL_VECTOR_H_
#define TINY_STL_VECTOR_H_

#include "tiny_stl_config.h"
#include "allocator.h"
#include "uninitialized.h"
#include <initializer_list>
#include "util.h"
TINY_STL_BEGIN

template <class T, class Alloc = allocator<T>>
class vector
{
public:
	typedef T value_type;
	typedef T* pointer;
	typedef const T* const_pointer;
	typedef T* iterator;
	typedef const T* const_iterator;
	typedef T& reference;
	typedef const T& const_reference;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;

protected:
	typedef Alloc data_allocator;
	iterator start;
	iterator finish;
	iterator end_of_storage;
	void insert_aux(iterator position, const T& x);
	void deallocate() 
	{
		if (start) data_allocator::deallocate(start, end_of_storage - start);
	}
	void fill_initialize(size_type n, const T& value)
	{
		start = allocate_and_fill(n, value);
		finish = start + n;
		end_of_storage = finish;
	}
public:
	iterator begin() { return start; }
	const_iterator begin() const { return start; }
	iterator end() { return finish; }
	const_iterator end() const { return finish; }
	size_type size() const { return size_type(end() - begin()); }
	size_type max_size() const { return size_type(-1) / sizeof(T); }
	size_type capacity() const { return size_type(end_of_storage - begin()); }
	bool empty() const { return begin() == end(); }
	Alloc get_allocator() { return data_allocator(); }
	reference at(size_type pos)
	{
		return *(start + pos);
	}
	reference back() { return *(finish - 1); }
	const_reference back() const { return *(finish - 1); }
	reference operator[](size_type n) { return *(begin() + n); }
	const_reference operator[](size_type n) const { return *(begin() + n); }
	vector<T, Alloc>& operator=(const vector<T, Alloc>& x);
	vector<T, Alloc>& operator=(vector<T, Alloc>&& x); //tbd
	vector<T, Alloc>& operator=(std::initializer_list<T>& list); //tbd
	

	vector() : start(0), finish(0), end_of_storage(0) {}
	vector(size_type n, const T& value) { fill_initialize(n, value); }
	vector(int n, const T& value) { fill_initialize(n, value); }
	vector(long n, const T& value) { fill_initialize(n, value); }
	explicit vector(size_type n) { fill_initialize(n, T()); }
	vector(const vector<T,Alloc>& vec)
	{
		start = allocate_and_copy(vec.end() - vec.begin(), vec.begin(), vec.end());
		finish = start + (vec.end() - vec.begin());
		end_of_storage = finish;
	}
	vector(std::initializer_list<T> list)
	{
		start = allocate_and_copy(list.size(),list.begin(), list.end());
		finish = start + list.size();
		end_of_storage = finish;
	}


protected:
	iterator allocate_and_fill(size_type n, const T& x)
	{
		iterator result = data_allocator::allocate(n);
		uninitialized_fill_n(result, n, x);
		return result;
	}

	iterator allocate_and_copy(size_type n, const_iterator first,const_iterator last)
	{
		iterator result = data_allocator::allocate(n);
		uninitialized_copy(first, last, result);
		return result;
	}

};



template <class T, class Alloc>
void vector<T, Alloc>::insert_aux(iterator position, const T& x)
{
	if (finish != end_of_storage)
	{
		construct(finish,*(finish-1));
		++finish;
		T x_copy = x;
		copy_backward(position, finish - 2, finish - 1);
		*position = x_copy;
	}
	else
	{
		size_type old_size = size();
		const size_type new_size = old_size != 0 ? (2 * old_size) : 1;
		iterator iter_new_start = data_allocator::allocate(new_size);
		iterator iter_new_finish = iter_new_start;
		iter_new_finish = uninitialized_copy(start, position, iter_new_start);
		construct(iter_new_finish, x);
		++iter_new_finish;
		iter_new_finish = uninitialized_copy(position, finish, iter_new_finish);
		destroy(begin(), end());
		deallocate();
		start = iter_new_start;
		finish = iter_new_finish;
		end_of_storage = iter_new_start + new_size;
	}
}

template <class T, class Alloc>
vector<T, Alloc>& vector<T, Alloc>::operator=(const vector<T, Alloc>& x)
{
	if (this != &x)
	{
		if (x.size() > capacity())
		{
			iterator new_start = allocate_and_copy(x.size(), x.begin(), x.end());
			destroy(begin(), end());
			deallocate();
			start = new_start;
			end_of_storage = start + (x.end() - x.begin());
		}
		else if (x.size() <= size())
		{
			iterator temp = copy(x.begin(), x.end(), begin());
			tiny_stl::destroy(temp, end());
		}
		else
		{
			copy(x.begin(), x.begin()+size(), start);
			uninitialized_copy(x.begin() + size(),x.end(),finish);
		}
		finish = start + x.size();
	}
	return *this;
}




TINY_STL_END

#endif
