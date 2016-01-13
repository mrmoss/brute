#include <stdio.h>
#include <stdlib.h>
#include <string.h>

inline void print(char* pass,int show)
{
	printf("%s\n",pass);

	if(show!=0)
		fprintf(stderr,"\r  Current:      %s",pass);
}

inline void help()
{
	printf("Usage:  ./brute [--help] [--map STR] [--len INT] [--maxlen INT] [--show]\n");
	printf("  --help        Show this menu.\n");
	printf("  --map STR     String of characters to use for password generation (default is all printable characters).\n");
	printf("  --maxlen INT  Length of passwords.\n");
	printf("  --len INT     Length of passwords (includes passwords of size less than as well).\n");
	printf("  --show        Shows the passwords in stderr (nice for viewing current password when redirecting passwords to a file).\n");
	exit(0);
}

int main(int argc,char* argv[])
{
	char* default_map="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 ~`!@#$%^&*()_+-={}[]|\\:;\"'<,>.?/";

	char* map=(char*)malloc(strlen(default_map)+1);

	if(map==NULL)
	{
		printf("Could not allocate memory for map.\n");
		exit(1);
	}

	int map_len=strlen(default_map);
	int pass_len=-1;
	int ii=0;
	int* spots=NULL;
	char* pass=NULL;
	int show=0;
	int abs_len=1;

	memset(map,0,strlen(default_map)+1);
	strncpy(map,default_map,strlen(default_map));

	for(ii=1;ii<argc;++ii)
	{
		if(strlen(argv[ii])==6&&strncmp(argv[ii],"--help",6)==0)
		{
			help();
		}
		else if(strlen(argv[ii])==5&&strncmp(argv[ii],"--map",5)==0)
		{
			if(ii+1>=argc||strlen(argv[ii+1])<=0)
			{
				fprintf(stderr,"Expected argument after \"--map\".\n");
				exit(1);
			}

			++ii;
			free(map);
			map=NULL;
			map=(char*)malloc(strlen(argv[ii])+1);

			if(map==NULL)
			{
				printf("Could not allocate memory for map.\n");
				exit(1);
			}

			memset(map,0,strlen(argv[ii])+1);
			strncpy(map,argv[ii],strlen(argv[ii]));
			map_len=strlen(argv[ii]);
		}
		else if(strlen(argv[ii])==5&&strncmp(argv[ii],"--len",5)==0)
		{
			if(ii+1>=argc)
			{
				fprintf(stderr,"Expected argument after \"--len\".\n");
				exit(1);
			}

			++ii;
			pass_len=(int)strtol(argv[ii],NULL,10);
			abs_len=1;
		}
		else if(strlen(argv[ii])==8&&strncmp(argv[ii],"--maxlen",8)==0)
		{
			if(ii+1>=argc)
			{
				fprintf(stderr,"Expected argument after \"--maxlen\".\n");
				exit(1);
			}

			++ii;
			pass_len=(int)strtol(argv[ii],NULL,10);
			abs_len=0;
		}
		else if(strlen(argv[ii])==6&&strncmp(argv[ii],"--show",6)==0)
		{
			show=1;
		}
		else
		{
			fprintf(stderr,"Unknown argument \"%s\".\n",argv[ii]);
			exit(1);
		}
	}

	if(pass_len<0)
		help();

	fprintf(stderr,"Generating Passwords\n");

	if(abs_len==1)
		fprintf(stderr,"  Length:       %d\n",pass_len);
	else
		fprintf(stderr,"  Max Length:   %d\n",pass_len);

	fprintf(stderr,"  Map:              %s\n",map);

	if(abs_len==0||pass_len==0)
		print("",show);

	if(pass_len>0)
	{
		spots=(int*)malloc(pass_len*sizeof(int));
		pass=(char*)malloc(pass_len+1);

		if(spots==NULL||pass==NULL)
			return 1;

		for(ii=0;ii<pass_len;++ii)
			spots[ii]=-1;

		memset(pass,0,pass_len+1);

		if(abs_len!=0)
			memset(pass,map[0],pass_len);

		while(1)
		{
			++spots[0];

			for(ii=0;ii<pass_len;++ii)
			{
				if(spots[ii]>=map_len)
				{
					if(ii+1>=pass_len)
						goto done; //goto==SHAME!

					spots[ii]=0;
					++spots[ii+1];
				}

				if(spots[ii]>=0)
					pass[ii]=map[spots[ii]];
			}

			print(pass,show);
		}
	}

	done:
		if(show!=0)
			fprintf(stderr,"\n  Done.\n");

		free(map);
		free(spots);
		free(pass);

		return 0;
}
