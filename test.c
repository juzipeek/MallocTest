#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#define DEBUG( fmt, arg... ) \
	printf("%03d:%8s:"fmt"\n", __LINE__, __FUNCTION__, ##arg )

#define RADIX  (1024)
#define M_SIZE (1024*1024)

int main()
{
	double m_size ;
	long alloc_count = 0L;
	void *ptr = NULL;
	
	while(1)
	{
		ptr = malloc( 8*M_SIZE );
		if( NULL==ptr )
		{
			DEBUG("malloc failed!");
			break;
		}

#ifdef MEMSET
    memset( ptr, 0x00, 8*M_SIZE );/* memset对测试有影响 */
#endif

		alloc_count++;
		m_size = alloc_count*8.0;
		DEBUG("malloced [%.2f]M [%.2f]G [%.2f]T"
			, m_size
			, m_size/RADIX
			, m_size/RADIX/RADIX );
	}		
	DEBUG("has malloced [%.2f]M [%.2f]G [%.2f]T"
		, m_size
		, m_size/RADIX
		, m_size/RADIX/RADIX );
	usleep(30);
}
