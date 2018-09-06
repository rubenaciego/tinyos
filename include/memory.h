#include <types.h>

void meminit();
void memcpy(byte* source, byte* dest, int nbytes);
void memset(byte* dest, byte val, int len);
void* kmalloc(u32 size);
void kfree(u32* addr);
