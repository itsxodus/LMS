#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int createStatus () {

	// knowledge of <unistd.h> header and access function: https://linux.die.net/man/2/access

	if (access("checker.txt", F_OK) == 0) { // If status.txt file exists
		return 0;
	} else {                               // If status.txt file does not exist
		FILE *statusfile;
		statusfile = fopen("checker.txt", "a");
		fprintf(statusfile, "Please do not delete this file.");
		fclose(statusfile);
		return 1;
	}
}

int encrypt(char fname[100])
{
	char ch;
	FILE *fpts, *fptt;
	
	fpts=fopen(fname, "r");
	if(fpts==NULL)
	{
		printf("\nError encrypting: File does not exists or error in opening..!! (1)");

	}
	fptt=fopen("temp.txt", "w");
	if(fptt==NULL)
	{
		printf("\nError encrypting: Error in creation of file temp.txt ..!! (2)");
		fclose(fpts);

	}
	while(1)
	{
		ch=fgetc(fpts);
		if(ch==EOF)
		{
			break;
		}
		else
		{
			ch=ch+100;
			fputc(ch, fptt);
		}
	}
	fclose(fpts);
	fclose(fptt);

	fpts=fopen(fname, "w");
	if(fpts==NULL)
	{
		printf("\nError encrypting: File does not exists or error in opening..!! (3)");
		fclose(fpts);

	}
	fptt=fopen("temp.txt", "r");
	if(fptt==NULL)
	{
		printf("\nError Encrypting: File does not exists or error in opening..!! (4)");
		fclose(fpts);

	}
	while(1)
	{
		ch=fgetc(fptt);
		if(ch==EOF)
		{
			break;
		}
		else
		{
			fputc(ch, fpts);
		}
	}
	//printf("\nFile %s successfully encrypted ..!!\n\n", fname);
	fclose(fpts);
	fclose(fptt);
	return 0;
}

int decrypt(char fname[100])
{
	char ch;
	FILE *fpts, *fptt;
	
	fpts=fopen(fname, "w");
	if(fpts==NULL)
	{
		printf("\nError decrypting: File does not exists or error in opening..!! (5)");
		fclose(fpts);

	}
	fptt=fopen("temp.txt", "r");
	if(fptt==NULL)
	{
		printf("\nError decrypting: File does not exists or error in opening..!! (6)");
		fclose(fpts);

	}
	while(1)
	{
		ch=fgetc(fptt);
		if(ch==EOF)
		{
			break;
		}
		else
		{
			ch=ch-100;
			fputc(ch, fpts);
		}
	}
	//printf("\nThe file %s decrypted successfully..!!\n\n",fname);
	fclose(fpts);
	fclose(fptt);
	return 0;
}