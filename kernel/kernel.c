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
    else
    {
        kprint("Unknown command: ");
        kprint(input);
    }
    
    kprint("\n> ");
}
