typedef unsigned long uint64_t;
typedef unsigned short uint16_t;

void kernel1(void) {
    uint16_t* vga = (uint16_t*)0xB8000;
    for(int i = 0; i < 2000; i++) {
        vga[i] = (0x0E << 8) | ' ';
    }
    
    const char* msg = "KERNEL 1";
    for(int i = 0; msg[i]; i++) {
        vga[i] = (0x0E << 8) | msg[i];
    }
    
    while(1) {
        __asm__ volatile ("hlt");
    }
}