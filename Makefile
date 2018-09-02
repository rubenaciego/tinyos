C_SOURCES = $(wildcard kernel/*.c drivers/*.c cpu/*.c libc/*.c include/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h cpu/*.h libc/*.h include/*.h)
# Nice syntax for file extension replacement
OBJ = ${C_SOURCES:.c=.o cpu/interrupt.o}

CC = i386-elf-gcc
GDB = i386-elf-gdb

CFLAGS = -g -Iinclude -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs

# First rule is run by default
build/os-image.bin: boot/bootsect.bin build/kernel.bin
	cat $^ > build/os-image.bin

# '--oformat binary' deletes all symbols as a collateral, so we don't need
# to 'strip' them manually on this case
build/kernel.bin: boot/kernel_entry.o ${OBJ}
	i386-elf-ld -o $@ -Ttext 0x1000 $^ --oformat binary

# Used for debugging purposes
debug/kernel.elf: boot/kernel_entry.o ${OBJ}
	i386-elf-ld -o $@ -Ttext 0x1000 $^

run: build/os-image.bin
	qemu-system-i386 -drive file=build/os-image.bin,format=raw,if=floppy

# Open the connection to qemu and load our kernel-object file with symbols
debug: build/os-image.bin debug/kernel.elf
	qemu-system-i386 -drive file=build/os-image.bin,format=raw,if=floppy &
	${GDB} -ex "target remote localhost:1234" -ex "symbol-file debug/kernel.elf"

%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -ffreestanding -S -c $< -o $(@:.o=.asm)
	i386-elf-as $(@:.o=.asm) -o $@
	rm $(@:.o=.asm)

%.o: %.asm
	nasm $< -f elf -o $@

%.bin: %.asm
	nasm $< -f bin -o $@

clean:
	rm -rf *.bin *.dis *.o os-image.bin *.elf
	rm -rf kernel/*.o cpu/*.o boot/*.bin drivers/*.o boot/*.o build/* debug/* libc/*.o
