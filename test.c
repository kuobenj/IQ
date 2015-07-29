#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/mman.h>
#include <fcntl.h>

#define TLMM_GPIO_CFG(n) 		(0x01000000+0x1000*n)
// #define TLMM_GPIO_OUT(n) 		0x01000004+0x1000*n

int main(int argc, char const *argv[])
{
	int fd = -1;
	// printf("HELLO0\n");

	if (argc == 0)
	{
		printf("NO ARGS\n");
		return -1;
	}

	if ((fd = open("/dev/mem", O_RDWR|O_SYNC)) < 0 ) {
	    printf("Error opening file. \n");
	    close(fd);
	    return (-1);
	}

	int* addr = (int *) mmap(NULL , 0x012000FF, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_SHARED, fd, 0x0);
	if (addr == MAP_FAILED)
	{
		printf("ERROR MAPPING\n");
        // handle_error("mmap");
        return(-1);
    }
    int i;
    for (i = 0x012000FF-atoi(argv[0]); i > 0; i--)
    {
    	// sleep(1);
    	printf("%X", i);
    	printf("%X\n", *(addr+i));
    }

	printf("%X\n", addr);

	printf("HELLO1\n");
	int* gpio36cfg = TLMM_GPIO_CFG(36)+addr;
	// int* gpio36out = TLMM_GPIO_IN_OUT(36);
	printf("HELLO2\n");
	int* gpio36out = 0x01200004+addr;

	printf("HELLO3\n");
	// *gpio36cfg = 0;//set to no pull

	printf("HELLO4\n");
	// *gpio36cfg += (0x7 << 6);//increase driving current

	printf("HELLO5\n");
	while(1)
	{
		printf("ON\n");
		*gpio36out |= (0x1 << 5);

		sleep(1);
		printf("OFF\n");
		*gpio36out &= ~(0x1 << 5);
		sleep(2);
	}

	return 0;
}