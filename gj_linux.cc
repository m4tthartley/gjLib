
// Linux versions of the gjLib functions

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <glob.h>

typedef int gjFile;

// Alloc memory and init mem stack
gjMemStack gjInitMemStack (size_t size) {
	gjMemStack memStack = {};
	// todo: use mmap instead of malloc
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

void gjWriteFile (const char *file, void *data, size_t size) {
	int fd = open(file, O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH); // 0644
	if (fd == -1) {
		printf("%s open failed \n", __FUNCTION__);
		assert(false);
	}

	int bytesWritten = write(fd, data, size);
	if (bytesWritten != size) {
		printf("%s write failed \n", __FUNCTION__);
		assert(false);
	}

	close(fd);
}

gjFile gjCreateFile (const char *file) {
	int fd = open(file, O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH); // 0644
	if (fd == -1) {
		printf("%s open failed \n", __FUNCTION__);
		assert(false);
	}

	return fd;
}

void gjWrite (gjFile file, void *data, size_t size) {
	int bytesWritten = write(file, data, size);
	if (bytesWritten != size) {
		printf("%s write failed \n", __FUNCTION__);
		assert(false);
	}
}

void gjCloseFile (gjFile file) {
	close(file);
}

bool gjFileExists (const char *file) {
	struct stat fileInfo;
	int statResult = stat(file, &fileInfo);
	if (statResult == -1) {
		return false;
	} else {
		return true;
	}
}

/*struct gjFileList {
	char **files;
	int fileCount;
};*/

int gjFindFiles (const char *wildCard, gjMemStack *memStack, char **fileOutput, int fileMax) {
	// todo: glob might not be the best since it doesn't give you control of the memory

	glob_t globState = {};
	glob(wildCard, 0, NULL, &globState);
	int x = 0;

	if (globState.gl_pathc < fileMax) {
		fileMax = globState.gl_pathc;
	}

	fiz (fileMax) {
		fileOutput[i] = gjPushMemStack(memStack, gjStrlen(globState.gl_pathv[i]) + 1, true);
		gjStrcpy(fileOutput[i], globState.gl_pathv[i]);
	}

	return fileMax;
}