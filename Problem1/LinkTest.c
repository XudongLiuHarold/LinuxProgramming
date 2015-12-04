#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>

int main ()

{

	int fd;
	char buffer[5];
	struct stat st;
	
	if((fd=open("temp",O_RDWR|O_CREAT))<0)
			perror("Create file error!\n");

	stat("temp",&st);
	printf("The temp file's link = %d\n",st.st_nlink);

	if(unlink("temp") < 0 )
		perror("unlink temp error!\n");

	stat("temp",&st);
	printf("---------\nUnlink the temp file,and now the temp file's link = %d\n",st.st_nlink);

	if(fork()==0)
	{
		if(write(fd,"@@@@@@@",5)<0)
			perror("write file error!\n");

		printf("write successed\n");

		lseek(fd,0,SEEK_SET);
		if(read(fd,buffer,5)<0)
		  perror("read file error\n");

		printf("%s\n",buffer);
  }
  else
	{
	// wait writing to the file 
		sleep(5);
		if(link("temp","temp2")<0)
			perror("can't link to temp\n");
		
		fstat(fd,&st);
		printf("---------\nLink to the temp file again,now temp file's link = %d\n",st.st_nlink);
		printf("----------------------\n");
  }
	
	return 0;
}