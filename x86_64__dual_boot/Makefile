SRCDIR = src
OBJDIR = obj
BINDIR = bin

AS = nasm
CC = gcc
LD = ld

CFLAGS = -m64 -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti -nostdlib -nostdinc -mno-red-zone -mno-mmx -mno-sse -mno-sse2 -fno-pie

BOOT_SRC = $(SRCDIR)/x86/bootloader/stage/boot.asm
STAGE2_SRC = $(SRCDIR)/x86/bootloader/stage/stage2.asm
C_SRCS = $(wildcard $(SRCDIR)/x86/kernel/*.c)

BOOT_BIN = $(BINDIR)/boot.bin
STAGE2_BIN = $(BINDIR)/stage2.bin
C_OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(C_SRCS))
KERNEL_ELF = $(BINDIR)/kernel.elf
KERNEL_BIN = $(BINDIR)/kernel.bin
TARGET = $(BINDIR)/os.bin

all: directories $(TARGET)

directories:
	@mkdir -p $(BINDIR)
	@mkdir -p $(OBJDIR)/x86/bootloader/stage
	@mkdir -p $(OBJDIR)/x86/kernel

$(BOOT_BIN): $(BOOT_SRC) | directories
	$(AS) -f bin $< -o $@

$(STAGE2_BIN): $(STAGE2_SRC) | directories
	$(AS) -f bin $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c | directories
	$(CC) $(CFLAGS) -c $< -o $@

$(KERNEL_BIN): $(C_OBJS) linker.ld | directories
	$(LD) -m elf_x86_64 -nostdlib -T linker.ld -o $(KERNEL_ELF) $(C_OBJS)
	objcopy -O binary $(KERNEL_ELF) $@

$(TARGET): $(BOOT_BIN) $(STAGE2_BIN) $(KERNEL_BIN)
	cat $(BOOT_BIN) $(STAGE2_BIN) $(KERNEL_BIN) > $@
	truncate -s 128K $@

clean:
	rm -rf $(OBJDIR) $(BINDIR)

run: $(TARGET)
	qemu-system-x86_64 -fda $(TARGET) -boot a

.PHONY: all clean run directories