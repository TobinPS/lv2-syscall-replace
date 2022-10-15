ppu-gcc src/*.c src/*.S -nodefaultlibs -nostdlib -fPIC -fPIE -T src/lv2.ld -o lv2.elf
ppu-objcopy -O binary lv2.elf lv2.bin