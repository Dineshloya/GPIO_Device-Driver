#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int8_t read_buf[4];
int8_t write_buf[4];

int main()
{
        int fd,i,t;
        char option,str[4];
        printf("*********************************\n");
        printf("***simple GPIO device driver***\n");

        fd = open("/dev/multi_gpio", O_RDWR);
        if(fd < 0) {
                printf("Cannot open device file...\n");
                return 0;
        }

        while(1) {
		system("clear");
                printf("****Please Enter the Option******\n");
                printf("        1. Turn all LEDs ON\n");
                printf("        2. Turn all LEDs OFF\n");
                printf("        3. Read LED states\n");
                printf("        4. Blink leds\n");
                printf("        5. User input\n");
		printf("	6. Exit\n");
                printf("*********************************\n");
                scanf(" %c", &option);
             

                switch(option) {
                        case '1':
                                write(fd,"1111",4);
                                break;
                        case '2':
                                write(fd,"0000",4);
                                break;
                        case '3':
                                if(read(fd, read_buf,4)<0)
					printf("Failed to read LED state\n");
				else
				{
                                	printf("LEDs state:\n");
					for(int i=1;i<=4;i++)
					{
					printf("LED %d state:",i);	
					if(read_buf[i-1]==1)
						printf("ON\n");
					else
						printf("OFF\n");
					}
				}
				sleep(3);
                                break;
			case '4':
				printf("Enter no of times to blink:");
				scanf("%d",&i);
				printf("Enter delay between each blink in miliseconds:");
				scanf("%d",&t);
				printf("Led blibking....\n");
				for(int j=0;j<i;j++)
				{
                                write(fd,"1111",4);
				usleep(t*1000);	
                                write(fd,"0000",4);
				usleep(t*1000);
				}
				break;
			case '5':
				printf("Enter your own input as 1 for ON and 0 for OFF\n");
				scanf(" %s",str);
				write(fd, str, sizeof(str));
				break;
				
                        case '6':
                                close(fd);
				system("clear");
                                exit(1);
                                break;
                        default:
                                printf("Enter Valid option = %c\n",option);
                                break;
                }
        }
        close(fd);
}
