#include <stddef.h>    // size_t
#include <stdint.h>    // uint8_t, uint32_t
#include <stdio.h>     // printf
#include <string.h>    // memcpy
#include <sys/mman.h>  // mmap, mprotect, munmap, MAP_FAILURE
#include <unistd.h>

void	hello() {
	write(1, "Hello World !\n", 14);
}

uint32_t	new(uint32_t *size)
{
	return(*size * 2);
}

int main(int argc, char **argv) {
    // Allocate a new page of memory, setting its protections to read+write
	size_t fct_size = (size_t)&main - (size_t)&new;
//	fct_size = sizeof(machine_code);

    void *mem = mmap(NULL, fct_size, PROT_READ | PROT_WRITE,
        MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    if (mem == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    // Write the machine code into the newly allocated page
    memcpy(mem, &new, fct_size);

    // Change the page protections to read+execute
    if (mprotect(mem, fct_size, PROT_READ | PROT_EXEC) == -1) {
        perror("mprotect");
        return 2;
    }
    // Point a function pointer at the newly allocated page, then call it
    uint32_t(*fn)(uint32_t*) = (uint32_t(*)(uint32_t*)) mem;
    uint32_t tes = 21;
    uint32_t result = fn(&tes);
    printf("result = %d\n", result);

    // Free the memory
    if (munmap(mem, fct_size) == -1) {
        perror("munmap");
        return 3;
    }

    return 0;
}
