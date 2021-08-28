#pragma once

#include <iostream>

#if !NDEBUG
#define log(f_, ...) printf((f_), __VA_ARGS__);
#else
#define log(f_, ...)
#endif