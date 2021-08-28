#pragma once
#include <Windows.h>

extern void Patch(BYTE* dst, BYTE* src, unsigned int size);
extern bool Hook(char* src, char* dst, int len);
extern char* TrampHook(char* src, char* dst, unsigned int len);