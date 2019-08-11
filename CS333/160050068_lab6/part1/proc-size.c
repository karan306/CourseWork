#include "types.h"
#include "stat.h"
#include "user.h"
char b[1024];

#define kb 0x80000000 
#define pstop 0x7FFFFFFF
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
int getpksz()
{
	uint x=0;
	uint pa; int flags,space=0;
	while(x<=pstop)
	{
		if(get_va_to_pa(x+kb, &pa, &flags))
		{
			space+=0x1000;
		}
		x+=0x1000;
	}
	return space;
	/* todo */
}

int
main(int argc, char *argv[])
{
	char *buf;

	printf(1, "\ngetpsz: %d bytes \n", getpsz());
	printf(1,"getpusz: %d bytes \n",getpusz());
	printf(1,"getpksz: %d bytes\n",getpksz());


	buf=sbrk(4096);
	buf[0]='\0';
	printf(1, "\ngetpsz: %d bytes \n", getpsz());
	printf(1,"getpusz: %d bytes \n",getpusz());
	printf(1,"getpksz: %d bytes\n",getpksz());

	
	buf=sbrk(4096*7);
	printf(1, "\ngetpsz: %d bytes \n", getpsz());
	printf(1,"getpusz: %d bytes \n",getpusz());
	printf(1,"getpksz: %d bytes\n",getpksz());

	buf=sbrk(1);
	printf(1, "\ngetpsz: %d bytes \n", getpsz());
	printf(1,"getpusz: %d bytes \n",getpusz());
	printf(1,"getpksz: %d bytes\n",getpksz());

	buf=sbrk(2);
	printf(1, "\ngetpsz: %d bytes \n", getpsz());
	printf(1,"getpusz: %d bytes \n",getpusz());
	printf(1,"getpksz: %d bytes\n",getpksz());


	exit();
}