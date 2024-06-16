.global flush_gdt
flush_gdt:
        movl 4(%esp), %eax
        lgdt (%eax)
        # 0x8 is the code segment selector
        jmp $0x8, $.flush
.flush:
        mov $0x10, %ax 
        mov %ax, %ds
        mov %ax, %es
        mov %ax, %fs
        mov %ax, %gs
        mov %ax, %ss
        ret