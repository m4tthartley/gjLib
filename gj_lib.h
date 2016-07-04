
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

// Undo the near/far bullshit that windows.h does
#undef near // FUCK YOU WINDOWS!!!
#undef far

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

float gjSqrt (float num) {
	float result = sqrt(num);
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

void gjMemcpy (void *dest, void *source, size_t size) {
	memcpy(dest, source, size);
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

// #ifndef GJ_EXCLUDE_VECTOR_MATH
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
// #endif

float gjLength (Vec3 v) {
	float result = gjSqrt(v.x*v.x + v.y*v.y + v.z*v.z);
	return result;
}

Vec3 gjNormalize (Vec3 v) {
	Vec3 result;
	if (gjLength(v)) {
		result = {v.x/gjLength(v), v.y/gjLength(v), v.z/gjLength(v)};
	} else {
		result = {0.0f, 0.0f, 0.0f};
	}
	return result;
}

Vec3 gjCross (Vec3 a, Vec3 b) {
	Vec3 result;
	result.x = a.y*b.z - a.z*b.y;
	result.y = a.z*b.x - a.x*b.z;
	result.z = a.x*b.y - a.y*b.x;
	return gjNormalize(result);
}

Vec3 gjCross2d (Vec3 a, Vec3 b) {
	Vec3 result;
	result.x = a.y - b.y;
	result.y = b.x - a.x;
	result.z = 0.0f;
	result = gjNormalize(result);
	return result;
}

union Mat4 {
	float m[16];
};

Mat4 operator* (Mat4 mat1, Mat4 mat2) {
	Mat4 result = {
		mat1.m[0]*mat2.m[0] + mat1.m[1]*mat2.m[4] + mat1.m[2]*mat2.m[8] + mat1.m[3]*mat2.m[12],
		mat1.m[0]*mat2.m[1] + mat1.m[1]*mat2.m[5] + mat1.m[2]*mat2.m[9] + mat1.m[3]*mat2.m[13],
		mat1.m[0]*mat2.m[2] + mat1.m[1]*mat2.m[6] + mat1.m[2]*mat2.m[10] + mat1.m[3]*mat2.m[14],
		mat1.m[0]*mat2.m[3] + mat1.m[1]*mat2.m[7] + mat1.m[2]*mat2.m[11] + mat1.m[3]*mat2.m[15],

		mat1.m[4]*mat2.m[0] + mat1.m[5]*mat2.m[4] + mat1.m[6]*mat2.m[8] + mat1.m[7]*mat2.m[12],
		mat1.m[4]*mat2.m[1] + mat1.m[5]*mat2.m[5] + mat1.m[6]*mat2.m[9] + mat1.m[7]*mat2.m[13],
		mat1.m[4]*mat2.m[2] + mat1.m[5]*mat2.m[6] + mat1.m[6]*mat2.m[10] + mat1.m[7]*mat2.m[14],
		mat1.m[4]*mat2.m[3] + mat1.m[5]*mat2.m[7] + mat1.m[6]*mat2.m[11] + mat1.m[7]*mat2.m[15],

		mat1.m[8]*mat2.m[0] + mat1.m[9]*mat2.m[4] + mat1.m[10]*mat2.m[8] + mat1.m[11]*mat2.m[12],
		mat1.m[8]*mat2.m[1] + mat1.m[9]*mat2.m[5] + mat1.m[10]*mat2.m[9] + mat1.m[11]*mat2.m[13],
		mat1.m[8]*mat2.m[2] + mat1.m[9]*mat2.m[6] + mat1.m[10]*mat2.m[10] + mat1.m[11]*mat2.m[14],
		mat1.m[8]*mat2.m[3] + mat1.m[9]*mat2.m[7] + mat1.m[10]*mat2.m[11] + mat1.m[11]*mat2.m[15],

		mat1.m[12]*mat2.m[0] + mat1.m[13]*mat2.m[4] + mat1.m[14]*mat2.m[8] + mat1.m[15]*mat2.m[12],
		mat1.m[12]*mat2.m[1] + mat1.m[13]*mat2.m[5] + mat1.m[14]*mat2.m[9] + mat1.m[15]*mat2.m[13],
		mat1.m[12]*mat2.m[2] + mat1.m[13]*mat2.m[6] + mat1.m[14]*mat2.m[10] + mat1.m[15]*mat2.m[14],
		mat1.m[12]*mat2.m[3] + mat1.m[13]*mat2.m[7] + mat1.m[14]*mat2.m[11] + mat1.m[15]*mat2.m[15],
	};
	return result;
}

Mat4 gjmInvert (Mat4 mat) {
	Mat4 result = {};
	float m[4][4];
	gjMemcpy(m, mat.m, sizeof(Mat4));

	float det = m[0][0]*m[1][1]*m[2][2]*m[3][3] + m[0][0]*m[1][2]*m[2][3]*m[3][1] + m[0][0]*m[1][3]*m[2][1]*m[3][2];

	return result;
}

Mat4 gjmIdentity () {
	Mat4 result = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1,
	};
	return result;
}

Mat4 gjmRotateX (float rads) {
	Mat4 result = {
		1,  0,             0,             0,
		0,  gj_cos(rads), -gj_sin(rads),  0,
		0,  gj_sin(rads),  gj_cos(rads),  0,
		0,  0,             0,             1,
	};
	return result;
}

Mat4 gjmRotateY (float rads) {
	Mat4 result = {
		 gj_cos(rads),  0,  gj_sin(rads),  0,
		 0,             1,  0,             0,
		-gj_sin(rads),  0,  gj_cos(rads),  0,
		 0,             0,  0,             1,
	};
	return result;
}

Mat4 gjmRotateZ (float rads) {
	Mat4 result = {
		gj_cos(rads),  -gj_sin(rads),  0,  0,
		gj_sin(rads),   gj_cos(rads),  0,  0,
		0,             0,              1,  0,
		0,             0,              0,  1,
	};
	return result;
}

Mat4 gjmTranslate (float x, float y, float z) {
	Mat4 result = {
		1, 0, 0, x,
		0, 1, 0, y,
		0, 0, 1, z,
		0, 0, 0, 1,
	};
	return result;
}

Mat4 gjmTranslate (Vec3 pos) {
	Mat4 result = gjmTranslate(pos.x, pos.y, pos.z);
	return result;
}

Mat4 gjmScale (float scale) {
	Mat4 result = {
		scale, 0,     0,     0,
		0,     scale, 0,     0,
		0,     0,     scale, 0,
		0,     0,     0,     1,
	};
	return result;
}

/*
	OpenGL perspective matrix

	f = cotangent(fovy / 2)

	f / aspect, 0, 0                              ,	0                                  ,
	0         ,	f, 0                              ,	0                                  ,
	0         ,	0, (zFar + zNear) / (zNear - zFar), (2 × zFar × zNear) / (zNear - zFar),
	0         ,	0, -1                             ,	0                                  ,
*/
	// createPerspectiveMatrix
Mat4 gjmPerspective (float fov, float aspect, float near, float far) {
	float f = 1.0f / tanf(rads(fov) / 2.0f);
	Mat4 matrix = {
		f / aspect, 0, 0, 0,
		0, f, 0, 0,
		0, 0, (far + near) / (near - far), -1,
		0, 0, (2.0f * far * near) / (near - far), 0,
	};

	return matrix;
}

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
