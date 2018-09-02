#include <types.h>

void memcp(byte* source, byte* dest, int nbytes);
void memset(byte* dest, byte val, int len);
void* kmalloc(u32 size, int align, u32 *phys_addr);
