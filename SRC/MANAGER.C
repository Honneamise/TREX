/* HEADERS */
#include <stdlib.h>
#include <stdio.h>

#include "DIXIE/BASE.H"

static Array data;

void ManagerInit(char *file)
{
	FILE *fp = NULL;
	char str[32] = {0};
	byte *buf = NULL;

	ArrayInit(&data);

	fp = fopen(file,"r");	

	while(fgets(str, 32, fp) != NULL )
	{
		if(str[0]=='#'){ continue; }
		
		str[strlen(str)-1] = 0;

		BufferLoad(str, &buf, NULL);

		ArrayAdd(&data, buf);

	}

	fclose(fp);
}

void ManagerClose()
{
	ArrayClose(&data, free);
}

int ManagerSize()
{
	return data.elems_count;
}

byte *ManagerGet(int index)
{
	return ArrayGet(&data,index);
}