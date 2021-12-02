#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>

#define MAX_BUF 1024

int main()
{
    int fd,c=0;
    char *fifo1="fifo1";
    char *fifo2="fifo2";
    int fd1;
    int words=1,lines=1,chars=0,space=0;
    char data[MAX_BUF];
    
    // creating a fifo pipeline
    mkfifo(fifo1,0666);
    
    // opening the pipeline
    fd=open(fifo1,O_RDWR);
    
    // taking the input
    char str;
    printf("\nEnter the String & to end buffer enter '#': " );

    while ((str=getchar())!= '#' ) 
    {
	    data[c++]=str;
	}
    data[c]='\0';
	    
	// writing to the pipeline
    write(fd,data,sizeof(data));
    
    // close the buffer and unlink the pipe
    close(fd);
    unlink(fifo1);
    
    // creating a new fifo pipeline to display in read write mode.
    fd1=open(fifo2,O_RDWR);
    
    // reading data from bur
    read(fd1,data,sizeof(data));
    printf("\nThe contents of file are : \n %s\n",data);
    int i=0;
	while(data[i]!='\0') 
    {
		if(data[i] == ' ')
        {
			space += 1;
            words += 1;
		}
		else 
        {
		 	chars += 1;
		}
		if(data[i]=='\n') 
        {
			lines += 1;
            words += 1;
		}
		i += 1;
	}

    // Printing the summary
	printf("\n No of Words: %d",words);
	printf("\n No of Characters: %d",chars);
	printf("\n No of Space Characters: %d",space);
	printf("\n No of Lines: %d",lines);
	printf("\n");
	close(fd1);
    return 0;
}

/*
 Output

varadmash@varadmash-G3-3590:~/OS_Lab/Assignment7A$ gcc fifo.c 
varadmash@varadmash-G3-3590:~/OS_Lab/Assignment7A$ ./a.out 

Enter the String & to end buffer enter '#': Hello World
This is a new line
This is another line#

The contents of file are : 
 Hello World
This is a new line
This is another line

 No of Words: 11
 No of Characters: 43
 No of Space Characters: 8
 No of Lines: 3

 */
