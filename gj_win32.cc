
// Win32 versions of the gjLib functions

#include <intrin.h>
#include <windows.h>

gjMemStack gjInitMemStack (size_t size) {
	gjMemStack memStack = {};

	memStack.mem = (char*)VirtualAlloc(0, size, MEM_RESERVE|MEM_COMMIT, PAGE_READWRITE);
	if (memStack.mem) {
		memStack.size = size;
	} else {
		assert(false);
	}

	return memStack;
}

void GetWin32ErrorString (char *str, int size) {
	DWORD error = GetLastError();
	FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM, NULL, error,
				   MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), str, size, NULL);
}

gjData gjReadFile (char *file, gjMemStack *memStack) {
	gjData data = {};

	HANDLE handle = CreateFileA(file, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);

	if (handle != INVALID_HANDLE_VALUE) {
		LARGE_INTEGER size64;
		if (GetFileSizeEx(handle, &size64)) {
			unsigned int size = (unsigned int)size64.QuadPart;
			data.mem = gjPushMemStack(memStack, size);

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

bool gjWriteFile (char *file, void *data, size_t size) {
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