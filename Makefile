udev-testing: main.c
	gcc -ggdb -o udev-testing.elf main.c -ludev

clean:
	rm *.elf
