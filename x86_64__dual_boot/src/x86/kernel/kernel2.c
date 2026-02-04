typedef unsigned long uint64_t;
typedef unsigned short uint16_t;

void kernel2(void) {
    uint16_t* vga = (uint16_t*)0xB8000;
    for(int i = 0; i < 2000; i++) {
        vga[i] = (0x0B << 8) | ' ';
    }
    
    const char* msg = "KERNEL 2";
    for(int i = 0; msg[i]; i++) {
        vga[80 + i] = (0x0B << 8) | msg[i];
    }
    
    while(1) {
        __asm__ volatile ("hlt");
    }
}