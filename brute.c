#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	char map[95]="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 ~!@#$%^&*()_+`-={}|[]\\;':\",./<>?";
	int map_len=strlen(map);
	int pass_len=2;
	int ii=0;
	int* spots=(int*)malloc(pass_len*sizeof(int));
	char* pass=(char*)malloc(pass_len);

	if(spots==NULL||pass==NULL)
		return 2;

	if(pass_len>0)
	{
		for(ii=0;ii<pass_len;++ii)
			spots[ii]=-1;

		memset(pass,0,pass_len);

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