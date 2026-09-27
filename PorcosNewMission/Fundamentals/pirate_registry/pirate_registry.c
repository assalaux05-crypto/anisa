#define _GNU_SOURCE
#include <string.h>
#include "pirate_registry.h"
#include <stdio.h>
#include <err.h>


/*

   struct Pirate
   {
   char name[64];
   char plane[64];
   int danger_level;
   };

*/

int write_pirates_file(const char *filename, const struct Pirate *pirates, size_t n)
{


	if (filename==NULL  || pirates ==NULL) 
	{
		printf("Error : Invalid Parameter\n");
		return 1;

	}
	FILE* file=fopen(filename,"w");
	if (file==NULL)
	{
		return 1;

	}

	for (size_t i=0; i<n;i++)
	{

		if(fprintf(file, "%s,%s,%d\n",pirates[i].name,pirates[i].plane,pirates[i].danger_level)<0)
		{
			fclose(file);
			return 1;

		}
		
	}
		fclose(file);
		return 0;
	}


int parse_line(char *line, struct Pirate *p) {

	if (line ==NULL || p==NULL)return 1;
	size_t len=strlen(line);
	if(len ==0 || line[len-1]!='\n')return 1;

	char* token=strtok(line,",");
	if(token ==NULL || token[0]=='\0')return 1;
	if(strlen(token)>=sizeof(p->name))
	{
		return 1;
	}
	strcpy(p->name,token);
	token =strtok(NULL,",");
	if(token ==NULL || token[0]=='\0')return 1;
	strcpy(p->plane,token);
	token=strtok(NULL,",");
	p->danger_level=atoi(token);
	return 0;
		

}
/*

int main(void)
{
char line[] = "Captain Bruno,Curtiss-Wright Pusher,5\n";
struct Pirate p;

int status = parse_line(line, &p);
printf("int:%i\n",p.danger_level);
printf("int:%s\n",p.plane);
return status;
}
*/


int read_pirates_file(const char *filename, struct Pirate *pirates, size_t n)
{
	if(!filename || !pirates || n==0)
	{
		printf("Error : Invalid Parameter\n");
		return 1;
	}
	FILE* f=fopen(filename,"r");
	if(!f)
	{
		printf("Error: Could not open file\n");
		return 1;
	}
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	for(size_t i=0;i<n;i++)
	{
		read = getline(&line, &len, f);
		if (read==-1)
		{
			printf("Error : Not enough lines\n");
			fclose(f);
			free(line);
			return 1;
		}
		/*int status= parse_line(line,&pirates[i]);*/
			if (parse_line(line,&pirates[i])!=0)
			{
				fclose(f);
				free(line);
				printf("Error : Incorrect syntax\n");
				return 1;
			}
	}
	free(line);
	fclose(f);
	return 0;
	
}
/*
int main(void)
{

const char *filename = "pirates.csv";
struct Pirate pirates[10];
size_t n = 10; // We suppose that our CSV contains at least 10 lines in this example

int status = read_pirates_file(filename, pirates, n);
printf("%s\n",pirates[0].name);
return status ;
}
*/
