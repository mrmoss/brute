#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char* argv[])
{
	char* map="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 ";
	int map_len=strlen(map);
	int pass_len=5;
	int ii=0;
	int* spots=NULL;
	char* pass=NULL;

	if(argc>1)
		pass_len=(int)strtol(argv[1],NULL,10);

	if(pass_len>0)
	{
		spots=(int*)malloc(pass_len*sizeof(int));
		pass=(char*)malloc(pass_len);

		if(spots==NULL||pass==NULL)
			return 2;

		for(ii=0;ii<pass_len;++ii)
			spots[ii]=-1;

		memset(pass,0,pass_len);

		if(argc>2)
			snprintf(pass,pass_len+1,"%s",argv[2]);

		while(1)
		{
			++spots[0];

			for(ii=0;ii<pass_len;++ii)
			{
				if(spots[ii]>=map_len)
				{
					if(ii+1>=pass_len)
						return 1;

					spots[ii]=0;
					++spots[ii+1];
				}

				if(spots[ii]>=0)
					pass[ii]=map[spots[ii]];
			}

			printf("%s\n",pass);
		}
	}

	free(spots);
	free(pass);

	return 0;
}