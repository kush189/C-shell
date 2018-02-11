#include "ls.h"

void checkLs(char **input)
{
	//printf("%s\n",input[1]);
    DIR *mydir;
    struct dirent *myfile;
    struct stat mystat;
	struct passwd *user; 
    struct group *group;
    char buf[512];
    //int inp_len = strlen(*input);
    int f1=0,f2=0,f3=0,f4=0;
    int i=1,index=0;
    int storeDir[500]={0};

    while(input[i]!=NULL)
    {
    	int j;    	
    	if(input[i][0]=='-')
    	{
    		f1=1;
    	}
    	else
    	{
    		storeDir[index]=i;
    		//printf("%d\n",i);
    		index++;
    	}
    	if(f1)
    	{
    		for(j=1;j<strlen(input[i]);j++)
    		{
    			if(input[i][j]=='l')
    			{
    				f2=1;
    			}
    			else if(input[i][j]=='a')
    			{
    				f3=1;
    			}
    		}
    	}
    	i++;
    }
    //printf("%d %d %d %d\n",f1,f2,f3,f4);
    //for()
    if(!f1)
    {
    	char cur[500];
    	getcwd(cur, sizeof(cur));
    	//printf("%s\n",cur);
    	if(index==0)
    	{
    		//printf("ok\n");
    		storeDir[index]=0;
    		strcpy(input[0],cur);
    		//printf("%s\n",input[1]);
    		index++;
    	}
    	int a=0;
    	//printf("%d\n",index);
    	for(a=0;a<index;a++)
    	{
    		if(index>1)
    		{
    			printf("%s:\n",input[storeDir[a]]);
    		}
    		mydir = opendir(input[storeDir[a]]);
    		if(mydir==NULL)
	    	{
	    		printf("file/directory doesn't exist\n");
	    		continue;
	    	}
    		while((myfile = readdir(mydir)) != NULL)
    		{
    		   sprintf(buf, "%s/%s",".", myfile->d_name);
    		   stat(buf, &mystat);

    		   //printf("%zu",mystat.st_size);
    		   if(myfile->d_name[0]!='.')
                {
                    int f=0;
                    switch (mystat.st_mode & S_IFMT)
                    { 
                        case S_IFDIR:
                        f=1;
                        break;
                    }
                    if(f)
                    {
                        printf(KBLU "%s " RESET,myfile->d_name); 

                    }
                    else
                    {
                        printf("%s ", myfile->d_name);
                    }
                }
    		}
    		closedir(mydir);
    		printf("\n");
    	}
    }
    else if(f1 && !f2 && f3 && !f4)
    {
    	char cur[500];
    	getcwd(cur, sizeof(cur));
    	//printf("%s\n",cur);
    	if(index==0)
    	{
    		storeDir[index]=0;
    		strcpy(input[0],cur);
    		index++;
    	}
    	int a=0;
    	for(a=0;a<index;a++)
    	{
    		if(index>1)
    		{
    			printf("%s:\n",input[storeDir[a]]);
    		}
    		mydir = opendir(input[storeDir[a]]);
    		if(mydir==NULL)
	    	{
	    		printf("file/directory doesn't exist\n");
	    		continue;
	    	}
    		while((myfile = readdir(mydir)) != NULL)
    		{
    		   sprintf(buf, "%s/%s",".", myfile->d_name);
    		   stat(buf, &mystat);
               int f=0;
                switch (mystat.st_mode & S_IFMT)
                { 
                    case S_IFDIR:
                    f=1;
                    break;
                }
                if(f)
                {
                    printf(KBLU "%s " RESET,myfile->d_name); 
                }
                else
                {
                    printf("%s ", myfile->d_name);
                }
    		}
    		closedir(mydir);
    		printf("\n");
    	}
    }
    else if(f1 && f2 && !f4)
    {
    	char cur[500];
    	getcwd(cur, sizeof(cur));
    	//printf("%s\n",cur);
    	if(index==0)
    	{
    		storeDir[index]=1;
    		strcpy(input[1],cur);
    		index++;
    	}
    	int a=0;
    	for(a=0;a<index;a++)
    	{
    		if(index>1)
    		{
    			printf("%s:\n",input[storeDir[a]]);
    		}
    		mydir = opendir(input[storeDir[a]]);
	    	int total_s=0;
	    	if(mydir==NULL)
	    	{
	    		printf("file/directory doesn't exist\n");
	    		continue;
	    	}
	    	while((myfile = readdir(mydir)) != NULL)
	    	{
	    		sprintf(buf, "%s/%s",".", myfile->d_name);
	    		time_t rawtime;
	   			struct tm *info;
	   			char buffer[80];
	   			time( &rawtime );
	   			info = localtime( &rawtime );
	   			stat(buf, &mystat);
	   			if(!f3)
	   			{
	   				if(myfile->d_name[0]=='.')
	   					continue;
	   			}
                int f=0;
	   			switch (mystat.st_mode & S_IFMT)
   		        {
   	   		      	case S_IFBLK:  printf("b"); break;
	            	case S_IFCHR:  printf("c"); break; 
    	        	case S_IFDIR:  printf("d"); f=1;break; //It's a (sub)directory 
    	        	case S_IFIFO:  printf("p"); break; //fifo
    	        	case S_IFLNK:  printf("l"); break; //Sym link
    	        	case S_IFSOCK: printf("s"); break;
    	        	//Filetype isn't identified
    	        	default:       printf("-"); break;
    	        }

		        printf((mystat.st_mode & S_IRUSR) ? "r" : "-");
    		    printf((mystat.st_mode & S_IWUSR) ? "w" : "-");
    	    	printf((mystat.st_mode & S_IXUSR) ? "x" : "-");
    	    	printf((mystat.st_mode & S_IRGRP) ? "r" : "-");
		        printf((mystat.st_mode & S_IWGRP) ? "w" : "-");
    		    printf((mystat.st_mode & S_IXGRP) ? "x" : "-");
    		    printf((mystat.st_mode & S_IROTH) ? "r" : "-");
    	    	printf((mystat.st_mode & S_IWOTH) ? "w" : "-");
    	    	printf((mystat.st_mode & S_IXOTH) ? "x" : "-");

				printf(" | %lu |", mystat.st_nlink);
				user= getpwuid(mystat.st_uid);
    	    	printf(" %s |", user->pw_name);

    		    group=getgrgid(mystat.st_gid);
		        printf(" %s |", group->gr_name);


   				strftime(buffer,80,"%b %d %H:%M", info);
   				sprintf(buf, "%s/%s |",".", myfile->d_name);
    		   	
    		   	printf(" %zu |",mystat.st_size);
    		   	printf(" %s |", buffer );
                if(!f)
    		   	    printf(" %s\n", myfile->d_name);
                else
                    printf(KBLU "%s\n" RESET,myfile->d_name); 
    		   	//printf(" %s", (ctime(&mystat.st_mtime)));
    		   	total_s+=mystat.st_blocks;
    		}
    		printf("total %d\n",total_s/2);
    		closedir(mydir);
    	}
    }
    else
    {
    	int temp;
		temp = fork(); 
		int status;
		if(temp == 0)
		{ 
			if(execvp(*input, input) < 0) 
			{
				printf("Input error: Command not found!\n");		
			}
		}
		else 
		{  
			waitpid(temp,&status,WUNTRACED);
		}
	}
}
