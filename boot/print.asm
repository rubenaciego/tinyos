; receiving data in bx

print:
    pusha
    mov ah, 0x0e

    ; while (string[i] != 0) { print string[i], i++ }

start:
    mov al, [bx]
    cmp al, 0
    je done

    int 0x10

    add bx, 1
    jmp start

done:
    popa
    ret


print_nl:
    pusha
    
    mov ah, 0x0e
    mov al, 0x0a ; newline char
    int 0x10
    mov al, 0x0d ; carriage return
    int 0x10
    
    popa
    ret
