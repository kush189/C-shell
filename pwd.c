#include "pwd.h"
void checkPwd()
{
	//printf("yo\n");
	char p[1000];
	getcwd(p,sizeof(p));
	printf("%s\n",p);
}