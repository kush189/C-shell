# include "echo.h"

void checkEcho(char **input)
{
	int i=1;
	while(input[i]!=NULL)
	{
		printf("%s ",input[i]);
		i++;
	}
	printf("\n");
}
