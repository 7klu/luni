#include "./luni_dev.h"

/*
 - write ! x86, x86_64, arm, aarch64
 - read  ! x86, x86_64, arm, aarch64
*/

ssize_t linux_x86_write(int fd, const void *buff, size_t count) {
    ssize_t ret;
    __asm__ volatile (
        "movl $4, %%eax;"
        "movl %1, %%ebx;"
        "movl %2, %%ecx;"
        "movl %3, %%edx;"
        "int $0x80;"
        "movl %%eax, %0;"
        : "=r" (ret)
        : "r" (fd), "r" (buff), "r" (count)
        : "%eax", "%ebx", "%ecx", "%edx"
    );
    return ret;
}

ssize_t linux_x86_64_write(int fd, const void *buff, size_t count) {
    ssize_t ret;
    __asm__ volatile (
        "movq $1, %%rax;"
        "movq %1, %%rdi;"
        "movq %2, %%rsi;"
        "movq %3, %%rdx;"
        "syscall;"
        "movq %%rax, %0;"
        : "=r" (ret)
        : "r" (fd), "r" (buff), "r" (count)
        : "%rax", "%rdi", "%rsi", "%rdx"
    );
    return ret;
}

ssize_t linux_arm_write(int fd, const void *buff, size_t count) {
    ssize_t ret;
    __asm__ volatile (
        "mov r7, #4;"
        "mov r0, %1;"
        "mov r1, %2;"
        "mov r2, %3;"
        "swi #0;"
        "mov %0, r0;"
        : "=r" (ret)
        : "r" (fd), "r" (buff), "r" (count)
        : "r7", "r0", "r1", "r2"
    );
    return ret;
}

ssize_t linux_aarch64_write(int fd, const void *buff, size_t count) {
    ssize_t ret;
    __asm__ volatile (
        "mov x8, #64;"
        "mov x0, %1;"
        "mov x1, %2;"
        "mov x2, %3;"
        "svc #0;"
        "mov %0, x0;"
        : "=r" (ret)
        : "r" (fd), "r" (buff), "r" (count)
        : "x8", "x0", "x1", "x2"
    );
    return ret;
}

ssize_t linux_x86_read(int fd, void *buff, size_t count) {
    ssize_t ret;
    __asm__ volatile (
        "movl $3, %%eax;"
        "movl %1, %%ebx;"
        "movl %2, %%ecx;"
        "movl %3, %%edx;"
        "int $0x80;"
        "movl %%eax, %0;"
        : "=r" (ret)
        : "r" (fd), "r" (buff), "r" (count)
        : "%eax", "%ebx", "%ecx", "%edx"
    );
    return ret;
}

ssize_t linux_x86_64_read(int fd, void *buff, size_t count) {
    ssize_t ret;
    __asm__ volatile (
        "movq $0, %%rax;"
        "movq %1, %%rdi;"
        "movq %2, %%rsi;"
        "movq %3, %%rdx;"
        "syscall;"
        "movq %%rax, %0;"
        : "=r" (ret)
        : "r" (fd), "r" (buff), "r" (count)
        : "%rax", "%rdi", "%rsi", "%rdx"
    );
    return ret;
}

ssize_t linux_arm_read(int fd, void *buff, size_t count) {
    ssize_t ret;
    __asm__ volatile (
        "mov r7, #3;"
        "mov r0, %1;"
        "mov r1, %2;"
        "mov r2, %3;"
        "swi #0;"
        "mov %0, r0;"
        : "=r" (ret)
        : "r" (fd), "r" (buff), "r" (count)
        : "r7", "r0", "r1", "r2"
    );
    return ret;
}

ssize_t linux_aarch64_read(int fd, void *buff, size_t count) {
    ssize_t ret;
    __asm__ volatile (
        "mov x8, #63;"
        "mov x0, %1;"
        "mov x1, %2;"
        "mov x2, %3;"
        "svc #0;"
        "mov %0, x0;"
        : "=r" (ret)
        : "r" (fd), "r" (buff), "r" (count)
        : "x8", "x0", "x1", "x2"
    );
    return ret;
}

/*
 full function
 - linux
*/

/* write */
ssize_t linux_full_write(ssize_t (*func_t)(int, const void*, size_t), int fd, const void *buff, size_t count) {
    const char *p = (const char*)buff;
    size_t ttwrite = 0;
    while (ttwrite < count) {
        ssize_t w = func_t(fd, p + ttwrite, count - ttwrite);
        if (w <= 0) return (w < 0) ? -1 : ttwrite;
        ttwrite += w;
    }
    return ttwrite;
}

/* read */
ssize_t linux_full_read(ssize_t (*func_t)(int, void*, size_t), int fd, void *buff, size_t count) {
    char *p = (char*)buff;
    size_t ttread = 0;
    while (ttread < count) {
        ssize_t r = func_t(fd, p + ttread, count - ttread);
        if (r <= 0) return (r < 0) ? -1 : ttread;
        ttread += r;
    }
    return ttread;
}
