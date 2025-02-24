#include "./luni_dev.h"

/*
 - write ! x86, x86_64, arm, aarch64, riscv64, powerpc64, mips, sparc64
 - read  ! x86, x86_64, arm, aarch64, riscv64, powerpc64, mips, sparc64
*/

ssize_t linux_x86_write(int fd, const void *buff, size_t count)
{
    ssize_t ret;
    __asm__ volatile(
        "movl $4, %%eax;" // load syscall write (4) into eax
        "movl %1, %%ebx;" // move fd into ebx
        "movl %2, %%ecx;" // move buff into ecx
        "movl %3, %%edx;" // move count into edx
        "int $0x80;"      // invoke syscall
        "movl %%eax, %0;" // store syscall ret value (eax) into ret
        : "=r"(ret)
        : "r"(fd), "r"(buff), "r"(count)
        : "%eax", "%ebx", "%ecx", "%edx");
    return ret;
}

ssize_t linux_x86_64_write(int fd, const void *buff, size_t count)
{
    ssize_t ret;
    __asm__ volatile(
        "movq $1, %%rax;" // load syscall write (1) into rax
        "movq %1, %%rdi;" // move fd into rdi
        "movq %2, %%rsi;" // move buff into rsi
        "movq %3, %%rdx;" // move count into rdx
        "syscall;"        // invoke syscall
        "movq %%rax, %0;" // store syscall ret value (rax) into ret
        : "=r"(ret)
        : "r"(fd), "r"(buff), "r"(count)
        : "%rax", "%rdi", "%rsi", "%rdx");
    return ret;
}

ssize_t linux_arm_write(int fd, const void *buff, size_t count)
{
    ssize_t ret;
    __asm__ volatile(
        "mov r7, #4;" // laod syscall write (4) into r7
        "mov r0, %1;" // move fd into r0
        "mov r1, %2;" // move buff into r1
        "mov r2, %3;" // move count into r2
        "swi #0;"     // invoke syscall
        "mov %0, r0;" // store syscall ret value (r0) into ret
        : "=r"(ret)
        : "r"(fd), "r"(buff), "r"(count)
        : "r7", "r0", "r1", "r2");
    return ret;
}

ssize_t linux_aarch64_write(int fd, const void *buff, size_t count)
{
    ssize_t ret;
    __asm__ volatile(
        "mov x8, #64;" // laod syscall write (64) into x0
        "mov x0, %1;"  // move fd into x0
        "mov x1, %2;"  // move buff into x1
        "mov x2, %3;"  // move count into x2
        "svc #0;"      // invoke syscall
        "mov %0, x0;"  // store syscall ret value (x0) into ret
        : "=r"(ret)
        : "r"(fd), "r"(buff), "r"(count)
        : "x8", "x0", "x1", "x2");
    return ret;
}

ssize_t linux_riscv64_write(int fd, const void *buff, size_t count)
{
    ssize_t ret;
    __asm__ volatile(
        "li a7, 64;" // laod syscall write (64) into a7
        "mv a0, %1;" // move fd into a0
        "mv a1, %2;" // move buff into a1
        "mv a2, %3;" // move count into a2
        "ecall;"     // invoke syscall
        "mv %0, a0;" // store syscall ret value (a0) into ret
        : "=r"(ret)
        : "r"(fd), "r"(buff), "r"(count)
        : "a7", "a0", "a1", "a2");
    return ret;
}

ssize_t linux_powerpc64_write(int fd, const void *buff, size_t count)
{
    ssize_t ret;
    __asm__ volatile(
        "li r0, 4;"  // load syscall write (4) into r0
        "mr r3, %1;" // move fd into r3
        "mr r4, %2;" // move buff into r4
        "mr r5, %3;" // move count into r5
        "sc;"        // invoke syscall
        "mr %0, r3;" // store syscall ret value (r3) into ret
        : "=r"(ret)
        : "r"(fd), "r"(buff), "r"(count)
        : "r0", "r3", "r4", "r5");
    return ret;
}

ssize_t linux_mips_write(int fd, const void *buff, size_t count)
{
    ssize_t ret;
    __asm__ volatile(
        "li $v0, 4004;" // load syscall write (4004) into $v0
        "move $a0, %1;" // move fd into $a0
        "move $a1, %2;" // move buff into $a1
        "move $a2, %3;" // move count into $a2
        "syscall;"      // invoke syscall
        "move %0, $v0;" // store syscall ret value ($v0) into ret
        : "=r"(ret)
        : "r"(fd), "r"(buff), "r"(count)
        : "$v0", "$a0", "$a1", "$a2");
    return ret;
}

ssize_t linux_sparc64_write(int fd, const void *buff, size_t count)
{
    ssize_t ret;
    __asm__ volatile(
        "mov 64, %%g1;" // load syscall write (64) into g1
        "mov %1, %%o0;" // move fd into o0
        "mov %2, %%o1;" // move buff into o1
        "mov %3, %%o2;" // move count into o2
        "ta 0;"         // invoke syscall
        "mov %%o0, %0;" // store syscall ret value (o0) into ret
        : "=r"(ret)
        : "r"(fd), "r"(buff), "r"(count)
        : "%g1", "%o0", "%o1", "%o2");
    return ret;
}

ssize_t linux_x86_read(int fd, void *buff, size_t count)
{
    ssize_t ret;
    __asm__ volatile(
        "movl $3, %%eax;"
        "movl %1, %%ebx;"
        "movl %2, %%ecx;"
        "movl %3, %%edx;"
        "int $0x80;"
        "movl %%eax, %0;"
        : "=r"(ret)
        : "r"(fd), "r"(buff), "r"(count)
        : "%eax", "%ebx", "%ecx", "%edx");
    return ret;
}

ssize_t linux_x86_64_read(int fd, void *buff, size_t count)
{
    ssize_t ret;
    __asm__ volatile(
        "movq $0, %%rax;"
        "movq %1, %%rdi;"
        "movq %2, %%rsi;"
        "movq %3, %%rdx;"
        "syscall;"
        "movq %%rax, %0;"
        : "=r"(ret)
        : "r"(fd), "r"(buff), "r"(count)
        : "%rax", "%rdi", "%rsi", "%rdx");
    return ret;
}

ssize_t linux_arm_read(int fd, void *buff, size_t count)
{
    ssize_t ret;
    __asm__ volatile(
        "mov r7, #3;"
        "mov r0, %1;"
        "mov r1, %2;"
        "mov r2, %3;"
        "swi #0;"
        "mov %0, r0;"
        : "=r"(ret)
        : "r"(fd), "r"(buff), "r"(count)
        : "r7", "r0", "r1", "r2");
    return ret;
}

ssize_t linux_aarch64_read(int fd, void *buff, size_t count)
{
    ssize_t ret;
    __asm__ volatile(
        "mov x8, #63;"
        "mov x0, %1;"
        "mov x1, %2;"
        "mov x2, %3;"
        "svc #0;"
        "mov %0, x0;"
        : "=r"(ret)
        : "r"(fd), "r"(buff), "r"(count)
        : "x8", "x0", "x1", "x2");
    return ret;
}

ssize_t linux_riscv64_read(int fd, void *buff, size_t count)
{
    ssize_t ret;
    __asm__ volatile(
        "li a7, 63;"
        "mv a0, %1;"
        "mv a1, %2;"
        "mv a2, %3;"
        "ecall;"
        "mv %0, a0;"
        : "=r"(ret)
        : "r"(fd), "r"(buff), "r"(count)
        : "a7", "a0", "a1", "a2");
    return ret;
}

ssize_t linux_powerpc64_read(int fd, void *buff, size_t count)
{
    ssize_t ret;
    __asm__ volatile(
        "li r0, 3;"  // load syscall read (3) into r0
        "mr r3, %1;" // move fd into r3
        "mr r4, %2;" // move buff into r4
        "mr r5, %3;" // move count into r5
        "sc;"        // invoke syscall
        "mr %0, r3;" // store syscall ret value (r3) into ret
        : "=r"(ret)
        : "r"(fd), "r"(buff), "r"(count)
        : "r0", "r3", "r4", "r5");
    return ret;
}

ssize_t linux_mips_read(int fd, void *buff, size_t count)
{
    ssize_t ret;
    __asm__ volatile(
        "li $v0, 4003;" // load syscall read (4003) into $v0
        "move $a0, %1;" // move fd into $a0
        "move $a1, %2;" // move buff into $a1
        "move $a2, %3;" // move count into $a2
        "syscall;"      // invoke syscall
        "move %0, $v0;" // store syscall ret value ($v0) into ret
        : "=r"(ret)
        : "r"(fd), "r"(buff), "r"(count)
        : "$v0", "$a0", "$a1", "$a2");
    return ret;
}

ssize_t linux_sparc64_read(int fd, void *buff, size_t count)
{
    ssize_t ret;
    __asm__ volatile(
        "mov 63, %%g1;" // load syscall read (63) into g1
        "mov %1, %%o0;" // move fd into o0
        "mov %2, %%o1;" // move buff into o1
        "mov %3, %%o2;" // move count into o2
        "ta 0;"         // invoke syscall
        "mov %%o0, %0;" // store syscall ret value (o0) into ret
        : "=r"(ret)
        : "r"(fd), "r"(buff), "r"(count)
        : "%g1", "%o0", "%o1", "%o2");
    return ret;
}