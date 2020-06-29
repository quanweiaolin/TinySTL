#ifndef TINY_STL_UTIL_H_
#define TINY_STL_UTIL_H_
#include "tiny_stl_config.h"
TINY_STL_BEGIN

template<class InputIt, class OutputIt> 
OutputIt copy(InputIt first, InputIt last, OutputIt d_first)
{
    while (first != last) {
        *d_first++ = *first++;
    }
    return d_first;
}





TINY_STL_END

#endif
