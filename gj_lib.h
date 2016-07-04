
// gj lib, The Giantjelly library?

// Dont really want to have to include all these
#if 1
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include <memory.h>
#include <string.h>
#endif

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int uint;
typedef unsigned long long u64;
typedef char s8;
typedef short s16;
typedef long long s64;

#define bool int

#define assert(expression) {if (!(expression)) { int *np = 0; *(np) = 0; }}
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

void gjMemcpy (void *dest, void *source, size_t size) {
	void *result = memcpy(dest, source, size);
	int x = 0;
}

void gjClearMem (void *mem, size_t size) {
	memset(mem, 0, size);
}

int gjStrlen (const char *str) {
	int result = strlen(str);
	return result;
}

void gjStrcpy (char *dest, char *source) {
	strcpy(dest, source);
}

int gjStrcmp (const char *str1, const char *str2) {
	return strcmp(str1, str2);
}

bool gjEqual (const char *str1, const char *str2) {
	bool result = false;
	if (gjStrcmp(str1, str2) == 0) {
		result = true;
	}
	return result;
}

struct gjData {
	char *mem;
	size_t size;
};

struct gjMemStack {
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

void gjClearMemStack (gjMemStack *memStack) {
	memStack->used = 0;
}

char *gjPushMemStack (gjMemStack *memStack, size_t size, bool clear = false) {
	if (memStack->used + size <= memStack->size) {
		char *result = memStack->mem + memStack->used;
		memStack->used += size;
		if (clear) {
			gjClearMem(result, size);
		}
		return result;
	} else {
		printf("Ran out of memory %lu/%lu \n", memStack->used + size, memStack->size);
		assert(false);
	}

	return null;
}

void gjPopMemStack (gjMemStack *memStack, size_t size) {
	if (size <= memStack->used) {
		memStack->used -= size;
	} else {
		assert(false);
	}
}

// Testing C++ syntax, this namespacing stuff is not bad
namespace Net {

	static int server = 0;

	static void connect (int serv) {
		server = serv;
	}

	static void disconnect () {

	}

};

namespace gj {

	void *readFile (const char *file) {
		return 0;
	}

};

void testStuff () {
	Net::connect(3);
	int netServer = Net::server;
	void *fileData = gj::readFile("test.file");
}
