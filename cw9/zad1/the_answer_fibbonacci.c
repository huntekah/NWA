//#include <math.h>
#include <stdbool.h> 
bool isPerfectSquare(int);
bool isFibonacci(int n) 
{
       	return isPerfectSquare(5*n*n + 4) || isPerfectSquare(5*n*n - 4); 
} 
   
bool isPerfectSquare(int x) 
{ 
	for(int i=1;i*i<=x;i++){
		if(i*i==x){
			return i*i==x;
		}
	}
	return 1==0;
}

#define BUF 4096
#define CORRECT 0
#define CORRUPTED 1
#define FBI_DETECTED 3
uint32_t entrypoint(void)
{
    unsigned char buffer[BUF];

    int32_t size = seek(0, SEEK_END);
    if (size == -1)
	return CORRUPTED;
    if (size < BUF)
	return CORRUPTED;
    if (seek(-size, SEEK_END) == -1)
	return CORRUPTED;
    if (read(buffer, size) != size)
	return CORRUPTED;

    int fib1=0;
    int fib2=0;
    int n_fibs=0;
    int cur_byte=0;
    for (unsigned i=0;i<sizeof(buffer);i++) {
	cur_byte=(int)(buffer[i]);
	if ( isFibonacci(cur_byte)){
		if(fib1 == 0){
			fib1 = cur_byte;
		}
		else if( fib2 == 0){
			fib2 = cur_byte;
		}
		else if(cur_byte == fib1+fib2) {
			fib2=fib1;
			fib2=cur_byte;
			if(n_fibs == 0){
				n_fibs=3;
			}
			else {
				n_fibs+=1;
			}
		}
		else {
			fib1=cur_byte;
			fib2=0;
			n_fibs=0;
		}
	}
	else {
		fib1=0;
		fib2=0;
		n_fibs=0;
	}
	if(n_fibs>=5){
		return FBI_DETECTED;
	}
    }
    return CORRECT;
}

