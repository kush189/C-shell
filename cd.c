#include "cd.h"

void checkCd(char **input,char home[])
{
	char buf[500];
	char  *gdir;
	char  *dir;
	char  *to;
	//printf("ok\n");
	gdir = getcwd(buf, sizeof(buf));
	//printf("%s\n",gdir);
	dir = strcat(gdir, "/");
	if(input[1]==NULL)
	{
		if(chdir(home)<0)
		{
			printf("No such directory.\n");
		}
		else
		{
			chdir(home);
		}
	}
	else if(input[1][0]=='/')
	{
		if(chdir(input[1])<0)
		{
			printf("No such directory.\n");
		}
		else
		{
			chdir(input[1]);
		}	
	}
	else if(input[1][0]=='~')
	{
		int j;
		char temp[1000];
		int l = strlen(input[1]);
		strcpy(temp,home);
		int len_temp = strlen(temp);
		for(j=1;j<l;j++)
		{
			temp[len_temp+j-1]= input[1][j];
		}
		if(chdir(temp)<0)
		{
			printf("No such directory.\n");
		}
		else
		{
			chdir(temp);
		}
	}
	else
	{	
		to = strcat(dir, input[1]);
		if(chdir(to)<0)
		{
			printf("No such directory.\n");
		}
		else
		{
			chdir(to);
		}
	}
	//printf("%s\n",to);
}