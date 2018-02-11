#include "global.h"
#include "cd.h"
#include "pwd.h"
#include "ls.h"
#include "echo.h"
#include "pinfo.h"

char home[5000];


void Ctoken(char* string, char** output, char* omitter)
{
	char* token;
	token=strtok(string,omitter);
	int lp=0;
	while((token)!=NULL)
	{
		output[lp]=token;
		token=strtok(NULL,omitter);
		lp=lp+1;
	}
}

int main(void)
{
	struct utsname buffer;
	register struct passwd *pw;
	register uid_t uid;
	
	getcwd(home,sizeof(home));
	int len_home = strlen(home);
	while(1)
	{
		int background =0;
		int temp;
		char p[1032];
		char command[500];
		char* storeColon[100]={NULL};
		
		if (uname(&buffer) != 0) 
		{
			perror("uname");
			exit(EXIT_FAILURE);
		}
		//char *args[]= {"./initial","1" , "2",NULL};
		int pid;

		uid = geteuid();
		pw = getpwuid(uid);
		if(pw)
		{
			printf("<%s@%s:",pw->pw_name,buffer.nodename);
			getcwd(p,sizeof(p));
			if(!strcmp(p,home))
			{
				printf("~>");
			}
			else
			{
				if(strstr(p,home)!=NULL)
				{
					printf("~%s>",len_home+p);
				}
				else
				{
					printf("%s>",p);
				}
			}

			int counter=0;

			fgets(command,500,stdin);
			Ctoken(command,storeColon,";");
			
			//int command_len=strlen(storeColon);
			//printf("%d\n",command_len);

			while(storeColon[counter]!=NULL)
			{
				//printf("%s\n",storeColon);
				char array[500];

				strcpy(array,storeColon[counter]);
				//printf("%s\n",array);
				if(array[strlen(array)-1]=='\n')
				{    
					//printf("pro\n");
					array[strlen(array)-1]='\0';
				}
				char* new_str[100]={NULL};
				Ctoken(array,new_str," \t\n");
				int sts,t=0;
				while(new_str[t]){
					t++;
				}
		//		printf("%d\n",t );
				if (new_str[t-1]){
				if(new_str[0]!='\0' && (!strcmp(new_str[t-1] ,"&")))
				{
					new_str[t-1] = NULL ; 			
					printf("bitch\n");
					background =1;
			
				}}

				if (background){
					pid = fork();
					if(pid != 0 )
					{
						printf("Waiting on child (%d).\n", pid);
   		         			waitpid	(-1,&sts,WNOHANG);
					}
					else if (pid <0)
						exit (1);
				
					else
					{	
						execvp(*new_str , new_str);
						exit(1);
					}
			}
				else if(new_str[0]!='\0')
				{
					if (!strcmp(new_str[0], "exit")) exit(0);

					else if(!strcmp(new_str[0],"cd"))
					{
						checkCd(new_str,home);
					} 
					else if(!strcmp(new_str[0],"pwd"))
					{
						checkPwd();
					}
					else if(!strcmp(new_str[0],"ls"))
					{
						checkLs(new_str);					
					}
					else if(!strcmp(new_str[0],"echo"))
					{
						checkEcho(new_str);					
					}
					else if(!strcmp(new_str[0],"pinfo"))
					{
						CheckPinfo(new_str,home);					
					}
					else
					{
						temp = fork(); 
						int status;
						if(temp == 0)
						{ 
							if(execvp(*new_str, new_str) < 0) 
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
				counter++;
				//printf("%d\n",counter);
			}
		}	
	}
	return 0;
}
