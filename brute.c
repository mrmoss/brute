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
	printf("Usage:  ./brute [--help] [--alpha STR] [--len INT] [--maxlen INT] [--start STR] [--show]\n");
	printf("  --help        Show this menu.\n");
	printf("  --alpha STR   String of characters to use for password generation (default is all printable characters).\n");
	printf("  --len INT     Length of passwords (default is 8).\n");
	printf("  --maxlen INT  Length of passwords (includes passwords of size less than as well).\n");
	printf("  --start STR   Password to start at.\n");
	printf("  --show        Shows the passwords in stderr (nice for viewing current password when redirecting passwords to a file).\n");
	exit(0);
}

int main(int argc,char* argv[])
{
	char* default_alpha="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 ~`!@#$%^&*()_+-={}[]|\\:;\"'<,>.?/";

	char* alpha=(char*)malloc(strlen(default_alpha)+1);

	if(alpha==NULL)
	{
		printf("Could not allocate memory for alphabet.\n");
		exit(1);
	}

	int alpha_len=strlen(default_alpha);
	int pass_len=8;
	int ii=0;
	int jj=0;
	int spot_test=-1;
	int* spots=NULL;
	char* pass=NULL;
	int show=0;
	int abs_len=1;
	char* start_pass=NULL;

	memset(alpha,0,strlen(default_alpha)+1);
	strncpy(alpha,default_alpha,strlen(default_alpha));

	for(ii=1;ii<argc;++ii)
	{
		if(strlen(argv[ii])==6&&strncmp(argv[ii],"--help",6)==0)
		{
			help();
		}
		else if(strlen(argv[ii])==7&&strncmp(argv[ii],"--alpha",7)==0)
		{
			if(ii+1>=argc||strlen(argv[ii+1])<=0)
			{
				fprintf(stderr,"Expected argument after \"--alpha\".\n");
				exit(1);
			}

			++ii;
			free(alpha);
			alpha=(char*)malloc(strlen(argv[ii])+1);

			if(alpha==NULL)
			{
				printf("Could not allocate memory for alphabet.\n");
				exit(1);
			}

			memset(alpha,0,strlen(argv[ii])+1);
			strncpy(alpha,argv[ii],strlen(argv[ii]));
			alpha_len=strlen(argv[ii]);
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
		else if(strlen(argv[ii])==7&&strncmp(argv[ii],"--start",7)==0)
		{
			if(ii+1>=argc||strlen(argv[ii+1])<=0)
			{
				fprintf(stderr,"Expected argument after \"--start\".\n");
				exit(1);
			}

			++ii;

			free(start_pass);
			start_pass=(char*)malloc(strlen(argv[ii])+1);

			if(start_pass==NULL)
			{
				printf("Could not allocate memory for starting password.\n");
				exit(1);
			}

			memset(start_pass,0,strlen(argv[ii])+1);
			memcpy(start_pass,argv[ii],pass_len);
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

	if(abs_len!=0)
		fprintf(stderr,"  Length:       %d\n",pass_len);
	else
		fprintf(stderr,"  Max Length:   %d\n",pass_len);

	if(start_pass!=NULL)
		fprintf(stderr,"  Start:        %s\n",start_pass);

	fprintf(stderr,"  Alphabet:     %s\n",alpha);

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
			memset(pass,alpha[0],pass_len);

		if(start_pass!=NULL)
		{
			for(ii=0;ii<strlen(start_pass);++ii)
			{
				spot_test=-1;

				for(jj=0;jj<alpha_len;++jj)
				{
					if(start_pass[ii]==alpha[jj])
					{
						spots[ii]=spot_test=jj;
						break;
					}
				}

				if(spot_test==-1)
				{
					fprintf(stderr,"Starting password contains characters not in the alphabet.\n");
					exit(1);
				}
			}
		}

		while(1)
		{
			++spots[0];

			for(ii=0;ii<pass_len;++ii)
			{
				if(spots[ii]>=alpha_len)
				{
					if(ii+1>=pass_len)
						goto done; //goto==SHAME!

					spots[ii]=0;
					++spots[ii+1];
				}

				if(spots[ii]>=0)
					pass[ii]=alpha[spots[ii]];
			}

			print(pass,show);
		}
	}

	done:
		if(show!=0)
			fprintf(stderr,"\n  Done.\n");

		free(alpha);
		free(spots);
		free(pass);

		return 0;
}
