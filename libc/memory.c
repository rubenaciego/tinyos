#include <memory.h>

void memcpy(byte* source, byte* dest, int nbytes)
{
    for (int i = 0; i < nbytes; i++)
        *(dest + i) = *(source + i);
}

void memset(byte* dest, byte val, int len)
{
    for (; len != 0; len--) *dest++ = val;
}

u32 current_mem = 0x10000;

void* kmalloc(u32 size)
{
    current_mem += size;
    return (void*)(current_mem - size);
}
