#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "head.h"
#include <sys/mman.h>

void	test() {
	write(1, "Hello World !\n", 14);
}

void	print_mem(void *addr, int size) {
	unsigned char *ptr = (unsigned char*) addr;
	ft_printf("0x%x : ", (long)ptr);
	for (int i = 0; i < size && i < 16; i++) {
		ft_printf("%02hhx ", ptr[i]);
	}
	ft_printf("\n");
	if (size > 16)
		print_mem(ptr + 16, size - 16);
}

int	main() {
	char fct_asm[] = {0x00, 0x48, 0x2d, 0xe9, 0x04, 0xb0, 0x8d, 0xe2, 0x0e, 0x20, 0xa0, 0xe3, 0x0c, 0x10, 0x9f, 0xe5, 
0x01, 0x00, 0xa0, 0xe3, 0xb6, 0xff, 0xff, 0xeb, 0x00, 0x00, 0xa0, 0xe1, 0x00, 0x88, 0xbd, 0xe8, 
0x98, 0x6e, 0x01, 0x00};
	size_t fct_size = 36;

	//void *map = mmap(0, fct_size, PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	//ft_memcpy(map, fct_asm, fct_size);
	print_mem(fct_asm, fct_size);
	//int res = mprotect(map, fct_size, PROT_EXEC);
	//ft_printf("Res = %d\n", res);
	//char *shifted = ((char*)(&map)) + 0x1c4;
	//void (*fct)() = (void (*)())(&map);
	//(*fct)();
	//((void*)fct_asm)();
	//test();
	//unsigned char tab[] = {1, 10, 16, 255};
	//size_t test_size = ((size_t)(&print_mem)) - ((size_t)(&test));
	//ft_printf("Test size = %d\n", (int)test_size);
	//print_mem(&test, test_size);
	//munmap(map, fct_size);
	return 0;
}
