#include<sys/types.h>
#include<sys/dir.h>
#include<sys/param.h>
#include<sys/stat.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pwd.h>
#include<grp.h>

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

void get_mode(int mode)
{
  if(S_ISDIR(mode))
		  printf("d");
  else if(S_ISDIR(mode))
		  printf("c");
  else if(S_ISDIR(mode))
		  printf("b");
	else 
			printf("-");

	if (mode & S_IRUSR)
		printf("r");
	else 
		printf("-");

	if (mode & S_IWUSR)
		printf("w");
	else 
		printf("-");
	if (mode & S_IXUSR)
		printf("x");
	else 
		printf("-");


	if (mode & S_IRGRP)
		printf("r");
	else 
		printf("-");
	if (mode & S_IWGRP)
		printf("w");
	else 
		printf("-");
	if (mode & S_IXGRP)
		printf("x");
	else 
		printf("-");

	if (mode & S_IROTH)
		printf("r");
	else 
		printf("-");

	if (mode & S_IWOTH)
		printf("w");
	else 
		printf("-");

	if (mode & S_IXOTH)
		printf("x");
  else
		printf("-");
	printf("\t");
}

int main(void)
{

  	int count, i;
	struct direct **files;
	struct group* g;
	struct passwd* p;
	if(!getcwd(pathname,sizeof(pathname)))
 			die("Error Getting Pathname\n");

	printf("Current Working Directory = %s\n",pathname);
	count = scandir(pathname, &files,file_select,alphasort);

	if(count<=0)
		die("No Files in this Directory\n");

 	printf("Files Numbers:%d\n",count);
		printf("--------------------------\n");
		for( i =1;i<count+1;++i)
			{
			struct stat st;
			stat(files[i-1]->d_name, &st);
			get_mode(st.st_mode);
		  p = getpwuid(st.st_uid);
			g = getgrgid(st.st_gid);
	
 			
			printf("%s\t",p->pw_name);
			printf("%s\t",g->gr_name);
			printf("%d\t",st.st_size);

			printf("%d\t",localtime(&st.st_mtime));
			printf("%s\n",files[i-1]->d_name);
			}
		printf("-------------------------\n");
}
