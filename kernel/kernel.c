#include <drivers/screen.h>
#include <drivers/keyboard.h>
#include <cpu/isr.h>
#include <cpu/timer.h>
#include <string.h>
#include <memory.h>

void main()
{
    isr_install();
    irq_install();

    clear_screen();
    kprint_at("TinyOS kernel loaded...\n> ", 0, 0);
}

void user_input(char *input)
{
    int nextCmd;
    int len = strlen(input);
    if ((nextCmd = strstarts(input, "END")) &&
        (input[nextCmd] == ' ' || len == nextCmd))
    {
        kprint("Stopping the CPU. Bye!\n");
        __asm__ __volatile__("hlt");
    }
    else if ((nextCmd = strstarts(input, "ECHO")) &&
        input[nextCmd] == ' ' && len > nextCmd)
    {
        char* text = &input[nextCmd + 1];
        kprint(text);
    }
    else if ((nextCmd = strstarts(input, "PAGE")) &&
        (input[nextCmd] == ' ' || len == nextCmd))
    {
        u32 phys_addr;
        u32 page = (u32)kmalloc(1000, 1, &phys_addr);
        char page_str[16] = "";
        hex_to_ascii(page, page_str);
        char phys_str[16] = "";
        hex_to_ascii(phys_addr, phys_str);
        kprint("Page: ");
        kprint(page_str);
        kprint(", physical address: ");
        kprint(phys_str);
    }
    else
    {
        kprint("Unknown command: ");
        kprint(input);
    }
    
    kprint("\n> ");
}
