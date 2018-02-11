#include "pinfo.h"

void CheckPinfo(char **input, char home[])
{
	char Path[1000];
	const char *PROC = "/proc/";
	snprintf(Path, sizeof(Path), "%s", PROC);

	if(input[1]==NULL)
		strncat(Path,"self" , 4);
	else
	{
		strcat(Path,input[1]);
		if(!opendir(Path))
		{
			snprintf(Path, sizeof(Path), "%s", PROC);
			strncat(Path,"self" , 4);
		}

	}

	char final[1000],exec[10000];
	snprintf(final, sizeof(final), "%s", Path);

	strncat(final,"/statm" , 6);
	int size;
	FILE *mem=fopen(final,"r");
	fscanf(mem,"%d",&size);
	printf("Memory: %d\n",size);
	fclose(mem);
	
	snprintf(final, sizeof(final), "%s", Path);
	strcat(final,"/stat");
	int pid;
	char sts,name[50];
	FILE *stat=fopen(final,"r");
	fscanf(stat,"%d %s %c",&pid,name,&sts);
	printf(" pid: %d\n Process Status: %c\n",pid,sts);
	fclose(stat);
	snprintf(final, sizeof(final), "%s", Path);

	strncat(final,"/exe" , 4);
	readlink(final , exec , 10000);
	if(strstr(exec,home)!=NULL)
		printf("Excecutable Path : ~%s\n",exec+strlen(home));
	else
		printf("Excecutable Path : %s\n",exec);
}
