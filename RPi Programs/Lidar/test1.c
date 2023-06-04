#include "lidarLite.h"
#include <time.h>

int main(int argc,char *argv[])
{
	int fd, res;
  	unsigned char st, ver;
	fd = lidar_init(false);
   
    	if (fd == -1)
	{
        	printf("initialization error\n");
        }
    
	else 
	{
        	while (1)
		{
            		res = lidar_read(fd);
            		printf("%3.0d cm \n", res);           
            		delay(1000);
            	}
        }
}
