#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


/*
 *  gcc void_ptr_add.c 
 */

#define DEBUG( fmt, arg... ) \
	printf("%03d:%8s:"fmt"\n", __LINE__, __FUNCTION__, ##arg )

int main()
{

	void *void_ptr = NULL;
	int array[20] = {1,2,3,4,5};
	
	void_ptr = (void *) array;
	
	DEBUG(" void_ptr addr[%p] value[%d]", void_ptr ,* (char *) void_ptr);
	void_ptr+=sizeof(int);
	DEBUG(" void_ptr addr[%p] value[%d]", void_ptr ,* (char *) void_ptr);

}
