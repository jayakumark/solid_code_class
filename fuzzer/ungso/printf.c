//Implements printf by C.M. 4/8/2014
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

char *itoa(long, char *);
int printf(const char *format, ...);
int xprintf(const char *fmt, va_list argp);
void *Calloc(size_t nmemb, size_t size);
static void unix_error(char *msg); /* unix-style error */

int main(){
}



int printf(const char *fmt, ...){
	int ret;
	va_list ap;
	va_start(ap, fmt);
	ret = xprintf(fmt, ap);
	va_end(ap);
	return ret;
}


int xprintf(const char *fmt, va_list argp){
int i;
char *s;
char fmtbuf[256];
const char *p;

 for(p = fmt; *p != '\0'; p++)
   {
     if(*p != '%')
       {
	 putchar(*p);
	 continue;
       }

     switch(*++p)
       {
       case 'c':
	 i = va_arg(argp, int);
	 putchar(i);
	 break;

       case 'd':
	 i = va_arg(argp, int);
	 s = itoa((long)i, fmtbuf);
	 fputs(s, stdout);
	 break;

       case 's':
	 s = va_arg(argp, char *);
	 fputs(s, stdout);
	 break;

       case 'x':
	 i = va_arg(argp, int);
	 s = itoa((long)i, fmtbuf);
	 fputs(s, stdout);
	 break;

       case '%':
	 putchar('%');
	 break;
       }
   }

}


//convert int in to string
char *itoa(long in, char *out){

  int num = count(in);  
  out = (char*) Calloc(sizeof(char), num+1); // +1 for null
  snprintf(out, num, "%ld", in);
  return out;

}


int count(int in){

  int c = 0;

  while (in != 0){
    in /= 10;
    c++;
  }
  return c;
}



void *Calloc(size_t nmemb, size_t size) 
{
    void *p;

    if ((p = calloc(nmemb, size)) == NULL)
	unix_error("Calloc error");
    return p;
}


static void unix_error(char *msg) /* unix-style error */
{
    printf("%s\n", msg);
    exit(255);
}
