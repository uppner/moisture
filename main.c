#include <stdio.h>
#include <fcntl.h>
#include <time.h>
#include <sys/ioctl.h>
#include <unistd.h>

#define IOCTL_TRIG 7000
#define IOCTL_READ 7001 

int get_value(int);
void print_temp(int);
void print_moist(int);

int main(int argc, char **argv)
{
	int fd = open("/dev/rht03", 0); 

	int value = get_value(fd);
	time_t timestamp = time(NULL);
	printf("%d: ", timestamp);
	print_temp(value);
	printf(", ");
	print_moist(value);
	printf("\n");
	return 0;
}

int get_value(int fd)
{
	ioctl(fd, IOCTL_TRIG); 
	usleep(5000);
	int value= ioctl(fd, IOCTL_READ); 
	return value;
}
void print_temp(int value)
{
	int masked = value & 0xFFFF;
	int upper = masked / 10;
	int decimal = masked % 10;
	printf("%d.%d C", upper, decimal);
}
void print_moist(int value)
{
	int masked = (value & 0xFFFF0000) >> 16;
	int upper = masked / 10;
	int decimal = masked % 10;
	printf("%d.%d RH%%", upper, decimal);

}

