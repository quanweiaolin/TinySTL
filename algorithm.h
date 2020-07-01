#ifndef TINY_STL_ALGORITHM_H_
#define TINY_STL_ALGORITHM_H_

#include "tiny_stl_config.h"

TINY_STL_BEGIN

template <class BidirectionalIterator1, class BidirectionalIterator2>
BidirectionalIterator2 copy_backward(BidirectionalIterator1 first, BidirectionalIterator1 last, BidirectionalIterator2 result)
{
	while (first != last)
	{
		*(result) = *(last--);
	}
	return result;
}



TINY_STL_END

#endif