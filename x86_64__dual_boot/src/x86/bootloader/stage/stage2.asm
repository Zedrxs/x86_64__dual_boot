bits 16
org 0x7E00

start:
	cli
	in al, 0x92
	or al, 2
	out 0x92, al
	
	lgdt [gdtr32]
	
	mov eax, cr0
	or al, 1
	mov cr0, eax
	jmp 0x08:pmode

bits 32
pmode:
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	mov esp, 0x90000
	
	mov edi, 0x1000
	mov cr3, edi
	xor eax, eax
	mov ecx, 4096
	rep stosd
	mov edi, 0x1000
	
	mov dword [edi], 0x2003
	add edi, 0x1000
	mov dword [edi], 0x3003
	add edi, 0x1000
	mov dword [edi], 0x4003
	add edi, 0x1000
	
	mov ebx, 0x00000003
	mov ecx, 512
.set_entry:
	mov dword [edi], ebx
	add ebx, 0x1000
	add edi, 8
	loop .set_entry
	
	mov eax, cr4
	or eax, 1 << 5
	mov cr4, eax
	
	mov ecx, 0xC0000080
	rdmsr
	or eax, 1 << 8
	wrmsr
	
	mov eax, cr0
	or eax, 1 << 31
	mov cr0, eax
	
	lgdt [gdtr64]
	jmp 0x08:lm

bits 64
lm:
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	mov rsp, 0x200000
	
	mov rax, 0x200000
	call rax
	
	cli
	hlt
	jmp $

align 8
gdt32:
	dq 0
	dw 0xFFFF, 0, 0x9A00, 0x00CF
	dw 0xFFFF, 0, 0x9200, 0x00CF
gdtr32:
	dw $ - gdt32 - 1
	dd gdt32

align 8
gdt64:
	dq 0
	dw 0xFFFF, 0, 0x9A00, 0x00AF
	dw 0xFFFF, 0, 0x9200, 0x00AF
gdtr64:
	dw $ - gdt64 - 1
	dd gdt64