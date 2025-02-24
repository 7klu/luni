/*
path: luni/lunilib
*/

#ifndef LUNI_DEV_H
#define LUNI_DEV_H

#if defined(_WIN32) || defined(_WIN64) // windows
    #ifdef _WIN64
        #define __c_write win_x86_64_write
        #define __c_read win_x86_64_read
    #else
        #define __c_write win_x86_write
        #define __c_read win_x86_read
    #endif
#elif defined(__linux__) // all linux distro
    #ifdef __x86_64__
        #define __c_write linux_x86_64_write
        #define __c_read linux_x86_64_read
    #elif defined(__i386__)
        #define __c_write linux_x86_write
        #define __c_read linux_x86_read
    #elif defined(__arm__)
        #define __c_write linux_arm_write
        #define __c_read linux_arm_read
    #elif defined(__aarch64__)
        #define __c_write linux_aarch64_write
        #define __c_read linux_aarch64_read
    #else
        #error "Unsupported architecture on Linux"
    #endif
#elif defined(__APPLE__) // all apple
    #include <TargetConditionals.h>
    #if TARGET_OS_OSX
        #ifdef __x86_64__
            #define __c_write apple_x86_64_write
            #define __c_read apple_x86_64_read
        #elif defined(__i386__)
            #define __c_write apple_x86_write
            #define __c_read apple_x86_read
        #elif defined(__arm__)
            #define __c_write apple_arm_write
            #define __c_read apple_arm_read
        #elif defined(__aarch64__)
            #define __c_write apple_aarch64_write
            #define __c_read apple_aarch64_read
        #else
            #error "Unsupported architecture on Apple"
        #endif
    #else
        #error "Unsupported Apple platform"
    #endif
#else
    #error "Unsupported OS"
#endif

#define STDIN_FD  0
#define STDOUT_FD 1
#define STDERR_FD 2


typedef char* string_t;

#if defined(__GNUC__) || defined(__clang__)
    typedef _Float16 __f16_t;
#endif

/* int */
typedef signed char __i8_t;
typedef signed short __i16_t;
typedef signed int __i32_t;
typedef signed long long __i64_t;

/* unsig int */
typedef unsigned char __u8_t;
typedef unsigned short __u16_t;
typedef unsigned int __u32_t;
typedef unsigned long long __u64_t;

/* float */
typedef float __f32_t;
typedef double __f64_t;
typedef long double __f128_t;

/* ptr */
typedef void* __ptr_t;

/* size */
typedef unsigned long size_t;
typedef long ssize_t;

/* linux part
@
*/

/* all linux write */
ssize_t linux_x86_write(int fd, const void *buff, size_t count);
ssize_t linux_x86_64_write(int fd, const void *buff, size_t count);
ssize_t linux_arm_write(int fd, const void *buff, size_t count);
ssize_t linux_aarch64_write(int fd, const void *buff, size_t count);

/* all linux read */
ssize_t linux_x86_read(int fd, void *buff, size_t count);
ssize_t linux_x86_64_read(int fd, void *buff, size_t count);
ssize_t linux_arm_read(int fd, void *buff, size_t count);
ssize_t linux_aarch64_read(int fd, void *buff, size_t count);

/* all windows write */
//ssize_t win_x86_write(int fd, const void *buff, size_t count);
//ssize_t win_x86_64_write(int fd, const void *buff, size_t count);

/* all windows read */
//ssize_t win_x86_read(int fd, void *buff, size_t count);
//ssize_t win_x86_64_read(int fd, void *buff, size_t count);

/* all apple write */
//ssize_t apple_x86_write(int fd, const void *buff, size_t count);
//ssize_t apple_x86_64_write(int fd, const void *buff, size_t count);
//ssize_t apple_arm_write(int fd, const void *buff, size_t count);
//ssize_t apple_aarch64_write(int fd, const void *buff, size_t count);

/* all apple read */
//ssize_t apple_x86_read(int fd, void *buff, size_t count);
//ssize_t apple_x86_64_read(int fd, void *buff, size_t count);
//ssize_t apple_arm_read(int fd, void *buff, size_t count);
//ssize_t apple_aarch64_read(int fd, void *buff, size_t count);

/* full write function */
ssize_t write(int fd, const void *buff, size_t count) {
    const char *p = (const char*)buff;
    size_t ttwrite = 0;
    while (ttwrite < count) {
        ssize_t w = __c_write(fd, p + ttwrite, count - ttwrite);
        if (w <= 0) return (w < 0) ? -1 : ttwrite;
        ttwrite += w;
    }
    return ttwrite;
}

/* full read function */
ssize_t read(int fd, void *buff, size_t count) {
    char *p = (char*)buff;
    size_t ttread = 0;
    while (ttread < count) {
        ssize_t r = __c_read(fd, p + ttread, count - ttread);
        if (r <= 0) return (r < 0) ? -1 : ttread;
        ttread += r;
    }
    return ttread;
}

#endif
