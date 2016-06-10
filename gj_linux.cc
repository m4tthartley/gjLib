
// Linux versions of the gjLib functions

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

// Alloc memory and init mem stack
gjMemStack gjInitMemStack (size_t size) {
	gjMemStack memStack = {};
	memStack.mem = (char*)malloc(size);
	memStack.size = size;
	return memStack;
}

// Read entire file and close it again
gjData gjReadFile (const char *file, gjMemStack *memStack) {
	gjData data = {};
	
	int fd = open(file, O_RDONLY);
	if (fd == -1) {
		assert(false);
	}

	struct stat fileInfo;
	int statResult = fstat(fd, &fileInfo);
	if (statResult == -1) {
		assert(false);
	}

	size_t fileSize = fileInfo.st_size;
	void *fileMemory = gjPushMemStack(memStack, fileSize);
	size_t bytesRead = read(fd, fileMemory, fileSize);
	if (bytesRead != fileSize) {
		assert(false);
	}

	close(fd);

	data.mem = (char*)fileMemory;
	data.size = fileSize;
	return data;
}
