#include "types.h"
#include "stat.h"
#include "user.h"

#define ARRAY_SIZE 2048
int buf[ARRAY_SIZE];

#define EXTRA_SPACE 8182

#define kb 0x80000000 
#define pstop 0xE000000
int getpusz()
{
	int space=0;
	uint pa; int flags;
	for(uint x=0;x<kb;x=x+0x1000)
	{
		if(get_va_to_pa(x, &pa, &flags))
		{
			space+=0x1000;
		}
	}
	return space;
	/* todo */
}
void print_status()
{
	int vp;
	int pp;
	int sz;

	sz = getpsz();
	vp = sz / 4096;
	if((sz % 4096) != 0)
		vp += 1;
	pp = getpusz() / 4096;

	printf(1, "sz: %d, vp: %d, pp: %d\n", sz, vp, pp);
}


int
main(int argc, char *argv[])
{	
	buf[ARRAY_SIZE-1] = 1234;

	print_status();

	int * ptr = (int *)&buf[ARRAY_SIZE-1];
	printf(1, "addr: %d, value: %d\n", ((int)ptr), *ptr);

	sbrk(EXTRA_SPACE);

	print_status();
	
	ptr = (int *)20484;
	printf(1, "addr: %d, value: %d\n", ((int)ptr), *ptr);

	print_status();
	
	ptr = (int *)28658;
	printf(1, "addr: %d, value: %d\n", ((int)ptr), *ptr);

	print_status();

	ptr = (int *)28676;
	printf(1, "addr: %d\n", ((int)ptr));
	printf(1, "value: %d\n", *ptr);

	print_status();
		
	exit();
}