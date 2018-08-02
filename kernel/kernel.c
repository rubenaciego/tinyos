#include "../drivers/screen.h"
#include "../cpu/isr.h"

void entryPoint() {}

void main()
{
    clear_screen();
    kprint_at("TinyOS kernel loaded...\n", 0, 0);

    isr_install();
}
