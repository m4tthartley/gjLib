
// gj lib, The Giantjelly library?

// Dont really want to have to include all these
#if 1
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include <intrin.h>
#include <memory.h>
#include <string.h>
#include <windows.h>
#endif

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int uint;
typedef unsigned long long u64;
typedef char s8;
typedef short s16;
typedef long long s64;

#define bool int

#define assert(expression) {if (!(expression)) { *((int*)0) = 0; }}
#define null 0
#define PI 3.14159265359f
#define PI2 (3.14159265359f*2.0f)

float rads (float degs) {
	float result = (degs / 180.0f) * PI;
	return result;
}

float degs (float rads) {
	float result = (rads / PI) * 180.0f;
	return result;
}

#define kilobytes(num) (num*1024)
#define megabytes(num) (kilobytes(num)*1024)
#define gigabytes(num) (megabytes(num)*1024)

#define arraySize(array) (sizeof(array)/sizeof(array[0]))
#define fiz(count) for (int i = 0; i < count; ++i)
#define fjz(count) for (int j = 0; j < count; ++j)
#define fkz(count) for (int k = 0; k < count; ++k)

// todo: replace these crt functions, maybe not sin/cos
inline float gj_sin (float num) {
	float result = sinf(num);
	return result;
}

inline float gj_cos (float num) {
	float result = cosf(num);
	return result;
}

void gj_clearMem (void *mem, size_t size) {
	memset(mem, 0, size);
}

int gj_strlen (char *str) {
	int result = strlen(str);
	return result;
}

void gjStrcpy (char *dest, char *source) {
	strcpy(dest, source);
}

struct gj_Data {
	char *mem;
	size_t size;
};

struct gj_Mem_Stack {
	char *mem;
	size_t size;
	size_t used;
};

#ifndef GJ_EXCLUDE_VECTOR_MATH
struct Vec3 {
	union {
		struct {
			float x;
			float y;
			float z;
		};
		struct {
			float r;
			float g;
			float b;
		};
	};
};
#endif

gj_Mem_Stack gj_initMemStack (size_t size) {
	gj_Mem_Stack memStack = {};

	memStack.mem = (char*)VirtualAlloc(0, size, MEM_RESERVE|MEM_COMMIT, PAGE_READWRITE);
	if (memStack.mem) {
		memStack.size = size;
	} else {
		assert(false);
	}

	return memStack;
}

void gj_clearMemStack (gj_Mem_Stack *memStack) {
	memStack->used = 0;
}

char *gj_pushMemStack (gj_Mem_Stack *memStack, size_t size, bool clear = false) {
	if (memStack->used + size <= memStack->size) {
		char *result = memStack->mem + memStack->used;
		memStack->used += size;
		if (clear) {
			gj_clearMem(result, size);
		}
		return result;
	} else {
		// printf("Ran out of memory %i/%i \n", memStack->used + size, memStack->size);
		assert(false);
	}

	return null;
}

void gj_popMemStack (gj_Mem_Stack *memStack, size_t size) {
	if (size <= memStack->used) {
		memStack->used -= size;
	} else {
		assert(false);
	}
}

void testFunction () {

	gj_Mem_Stack memStack = {};

	char *mem = gj_pushMemStack(&memStack, 1024);

	// fuck

}

void GetWin32ErrorString (char *str, int size) {
	DWORD error = GetLastError();
	FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM, NULL, error,
				   MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), str, size, NULL);
}

gj_Data gj_readFile (char *file, gj_Mem_Stack *memStack) {
	gj_Data data = {};

	HANDLE handle = CreateFileA(file, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);

	if (handle != INVALID_HANDLE_VALUE) {
		LARGE_INTEGER size64;
		if (GetFileSizeEx(handle, &size64)) {
			unsigned int size = (unsigned int)size64.QuadPart;
			data.mem = gj_pushMemStack(memStack, size);

			if (data.mem) {
				DWORD bytesRead;
				if (ReadFile(handle, data.mem, size, &bytesRead, 0)
					&& size == bytesRead) {
					data.size = size;
				} else {
					VirtualFree(data.mem, 0, MEM_RELEASE);
					data.mem = 0;
				}
			}
		}

		CloseHandle(handle);
	} else {
		// DWORD error = GetLastError();
		char str[256];
		GetWin32ErrorString(str, 256);
		assert(false);
	}

	return data;
}

bool gj_writeFile (char *file, void *data, size_t size) {
	bool result = false;
	HANDLE handle = CreateFileA(file, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, 0, 0);
	if (handle != INVALID_HANDLE_VALUE) {
		DWORD bytesWritten;
		if (WriteFile(handle, data, size, &bytesWritten, 0)) {
			if (bytesWritten == size) {
				result = true;
			} else {
				// todo: write file error
			}
		}
	} else {
		// todo: open file error
	}

	return result;
}
