// This is a real implementation of ocalls
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <filesystem>
#include <string.h>
#include <string>

namespace fs = std::filesystem;

#define WORK_DIR "/tmp/OCallWorkDir/"

#define NEW_PATH(path) ((std::string(WORK_DIR) + path).c_str())

extern "C" {
int ocall_lstat(const char *path, struct stat* buf){
    //printf("Entering %s\n", __func__);
    return lstat(NEW_PATH(path), buf);
}

int ocall_stat(const char *path, struct stat* buf){
    //printf("Entering %s\n", __func__);
    return stat(NEW_PATH(path), buf);
}

int ocall_fstat(int fd, struct stat* buf){
    //printf("Entering %s\n", __func__);
    return fstat(fd, buf);
}

int ocall_ftruncate(int fd, off_t length){
    //printf("Entering %s\n", __func__);
    return ftruncate(fd, length);
}

char* ocall_getcwd(char *buf, size_t size){
    auto oldPath = fs::current_path();
    auto newPath = fs::path(WORK_DIR) / oldPath;
    fs::current_path(newPath);
    //printf("Entering %s\n", __func__);
    auto ret = getcwd(buf, size);
    fs::current_path(oldPath);
    return ret;
}

int ocall_getpid(void){
    //printf("Entering %s\n", __func__);
    return getpid();
}

int ocall_open64(const char *filename, int flags, mode_t mode){
    //printf("Entering %s\n", __func__);
    return open(NEW_PATH(filename), flags, mode); // redirect it to open() instead of open64()
}

off_t ocall_lseek64(int fd, off_t offset, int whence){
    //printf("Entering %s\n", __func__);
    return lseek(fd, offset, whence); // redirect it to lseek() instead of lseek64()
}

int ocall_read(int fd, void *buf, size_t count){
    //printf("Entering %s\n", __func__);
    return read(fd, buf, count);
}

int ocall_write(int fd, const void *buf, size_t count){
    //printf("Entering %s\n", __func__);
    return write(fd, buf, count);
}

int ocall_fcntl(int fd, int cmd, void* arg, size_t size){
    //printf("Entering %s\n", __func__);
    return fcntl(fd, cmd, arg);
}

int ocall_close(int fd){
    //printf("Entering %s\n", __func__);
    return close(fd);
}

int ocall_unlink(const char *pathname){
    //printf("Entering %s\n", __func__);
    return unlink(NEW_PATH(pathname));
}

int ocall_getuid(void){
    //printf("Entering %s\n", __func__);
    return getuid();
}

char* ocall_getenv(const char *name){
    //printf("Entering %s\n", __func__);
    return getenv(name);
}

int ocall_fsync(int fd){
    //printf("Entering %s\n", __func__);
    return fsync(fd);
}
}