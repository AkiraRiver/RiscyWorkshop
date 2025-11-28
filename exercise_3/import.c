#include <stdint.h>

static __attribute((noinline)) uint64_t resolve_import(const char* module, const char* function)
{
    register uint64_t a0 asm("a0") = (uint64_t)module;
    register uint64_t a1 asm("a1") = (uint64_t)function;
    register uint64_t a7 asm("a7") = 10105;
    asm volatile("ecall" : "+r"(a0) : "r"(a1), "r"(a7) : "memory");
    return a0;
}

static __attribute((noinline)) uint64_t host_call(uint64_t fn, uint64_t args[13])
{
    register uint64_t a0 asm("a0") = fn;
    register uint64_t a1 asm("a1") = (uint64_t)args;
    register uint64_t a7 asm("a7") = 20000;
    asm volatile("ecall" : "+r"(a0) : "r"(a1), "r"(a7) : "memory");
    return a0;
}

static __attribute((noinline)) uint64_t exit(int exit_code)
{
    register uint64_t a0 asm("a0") = exit_code;
    register uint64_t a1 asm("a1") = 0; // unused
    register uint64_t a7 asm("a7") = 10000;
    asm volatile("ecall" : "+r"(a0) : "r"(a1), "r"(a7) : "memory");
    return a0;
}

void _start() __attribute__((section(".text.start")));

void _start()
{
    // TODO: call resolve_import and host_call here
    resolve_import("kernel32.dll", "GetCurrentThreadId");
    uint64_t args[13] = {0};
    host_call(0x12345678, args);
    exit(0);
    asm volatile("ebreak");
}
