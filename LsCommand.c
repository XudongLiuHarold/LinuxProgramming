#include<sys/types.h>
#include<sys/dir.h>
#include<sys/param.h>
#include<sys/stat.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


#define FALSE 0
#define TRUE !FALSE

extern int alphasort();

char pathname[MAXPATHLEN];

void die(char *msg)
{
  perror(msg);
  return;
}

int file_select(struct direct *entry)
{
 if((strcmp(entry->d_name,".")==0)||(strcmp(entry->d_name,"..")==0))
	return FALSE;
 else
	return TRUE;
}


int main(void)
{

  int count, i;
	struct direct **files;
	struct group* g;
	struct passwd* p;
	if(!getcwd(pathname,sizeof(pathname)))
 			die("Error Getting Pathname\n");

	printf("\nCurrent Working Directory = %s\n",pathname);
	count = scandir(pathname, &files,file_select,alphasort);

	if(count<=0)
		die("No Files in this Directory\n");
 
 printf("Files Numbers:%d\n",count);
 printf("------------------------------------\n");
     for(i=1; i< count+1;++i)
       printf("%s\t",files[i-1] ->d_name);
 printf("\n----------------------------------\n");
}
