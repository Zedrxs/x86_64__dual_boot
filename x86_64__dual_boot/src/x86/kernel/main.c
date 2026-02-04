typedef unsigned long uint64_t;
typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;

#define VGA_ADDR (uint16_t*)0xB8000
#define VGA_COLS 80
#define VGA_ROWS 25

static uint8_t cursor_x = 0;
static uint8_t cursor_y = 0;

static const char keymap[] = {
    0,0,'1','2','3','4','5','6','7','8','9','0',0,0,0,0,
    'q','w','e','r','t','y','u','i','o','p',0,0,0,0,
    'a','s','d','f','g','h','j','k','l',0,0,0,
    0,0,'z','x','c','v','b','n','m',0,0,0,0,
    [28]='\n',[57]=' '
};

void outb(uint16_t port, uint8_t val) {
    __asm__ volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

uint8_t inb(uint16_t port) {
    uint8_t ret;
    __asm__ volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

void clear_screen(void) {
    uint16_t* vga = VGA_ADDR;
    for(int i = 0; i < VGA_COLS * VGA_ROWS; i++) {
        vga[i] = (0x07 << 8) | ' ';
    }
    cursor_x = 0;
    cursor_y = 0;
}

void putchar(char c) {
    uint16_t* vga = VGA_ADDR;
    if(c == '\n') {
        cursor_x = 0;
        cursor_y++;
        return;
    }
    vga[cursor_y * VGA_COLS + cursor_x] = (0x0F << 8) | c;
    cursor_x++;
    if(cursor_x >= VGA_COLS) {
        cursor_x = 0;
        cursor_y++;
    }
}

void print(const char* str) {
    while(*str) putchar(*str++);
}

char getchar(void) {
   