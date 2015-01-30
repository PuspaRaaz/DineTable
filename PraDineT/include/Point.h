#ifndef __POINT__
#define __POINT__

#include <stdint.h>
#include "Color.h"

struct Point
{
	int32_t x;
	int32_t y;
	int64_t d;
	Color color;
};

#endif