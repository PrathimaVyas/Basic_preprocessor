#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define SUCCESS 1
#define FAILURE 0


int create_file(char **argv,FILE *fptr);
int header_file_inclusion(char *line,FILE *fptr,FILE *fptr1);
int single_line_comment(char *line,FILE *fptr1);
void multi_line_comment(char *line,FILE *fptr);
int macro_replacement(char *line,FILE *fptr,FILE *fptr1);
int copy_contents_to_file(FILE *pre_file,FILE *src_file);

int main(int argc,char **argv)
{
    if(argc == 1)
    {
	printf("INFO : INVALID NUMBER OF COMMAND LINE ARGUMENTS\n");
	return 0;
    }
    else if(argc > 2)
    {
	printf("INFO : Arguments in cla should be only one file\n");
	return 0;
    }
    else
    {
	if(strstr(argv[1],".c") != NULL)
	{
	    FILE *fptr = fopen(argv[1],"r+");
	    if(fptr == NULL)
	    {
		printf("%s is not present \n",argv[1]);
		return FAILURE;
	    }

	    if(create_file(argv,fptr)==1)
	    {
		return SUCCESS;
	    }
	    else
	    {
		printf("INFO : Failure to create .i file\n");
		return FAILURE;
	    }
	}
	else
	{
	    printf("%s should have .c extension\n",argv[1]);
	    return FAILURE;
	}
    }
}



int create_file(char **argv,FILE *fptr)
{
    //to create file extension with .i
    int i,j=0;
    char *duplicate = argv[1];
    char *filename=malloc(sizeof(argv[i]));
    for(i=0;duplicate[i] != '\0' && duplicate[i] != '.' ;i++)
    {
	filename[i]  = duplicate[i];
    }
    filename[i] = '.';
    filename[i+1] = 'i';

    FILE *pre_file = fopen(filename,"w+");

    if(pre_file == 0)
    {
	printf("INFO : FAILURE TO CREATE .i FILE\n");
	return FAILURE;
    }

    if(copy_contents_to_file(pre_file,fptr) == SUCCESS)
    {
    }
    else
    {
	printf("INFO : Content copying is failure\n");
    }

    //TO REPLACE THE MACRO 

    int k=1;
    fseek(pre_file,0,SEEK_SET); 

    char line[450];
    while(fgets(line,448,pre_file)!=NULL)
    {
	// MACRO SUBSTITUTION
	if(strstr(line,"#define"))
	{
	    if(macro_replacement(line,fptr,pre_file) == SUCCESS)
	    {
		//continue;
	    }
	}
	else
	    continue;
    }

    return SUCCESS;


}

int copy_contents_to_file(FILE *pre_file,FILE *src_file)
{
    //to open .i file

    fseek(src_file,0,SEEK_SET);
    char line[1000];
    while(fgets(line,400,src_file)!=NULL)
    {
	// HEADER FILE INCLUSION
	if(strstr(line,"#include"))
	{
	    if(header_file_inclusion(line,src_file,pre_file) == SUCCESS)
	    {
		continue;
	    }
	}
	// SINGLE LINE COMMENT REMOVAL
	if(single_line_comment(line,pre_file) == SUCCESS)
	{
	    fputs(line,pre_file);
	    fprintf(pre_file,"\n");
	    continue;
	}
	// MULTILINE COMMENT REMOVAL
	multi_line_comment(line,src_file);
	fputs(line,pre_file);

    }
    fseek(src_file,0,SEEK_SET);
    return SUCCESS;
}

int header_file_inclusion(char *line,FILE *fptr,FILE *fptr1)
{
    char *headerline;
    int i=0;
    char *headerfile;
    if(headerfile=strstr(line,"\""))   //header file name
    {
	// TO REMOVE "MAIN.h"  "" WE NEED THESE 3 STEPS
	headerfile++;
	for(i=0;headerfile[i]!='"';i++);
	headerfile[i] = '\0';


	//	printf("header file --> %s\n",headerfile);

	FILE *hfptr = fopen(headerfile,"r");
	if(hfptr == NULL)
	{
	    printf("%s is not present\n",headerfile);
	    exit(0);
	}

	char line[100];
	while(fgets(line,10,hfptr) != NULL)
	{
	    fputs(line,fptr1);
	}
	fread(line,sizeof(char),9,fptr1);  //skip the header file name after replacing the header file content
	return SUCCESS;
    }
}

int macro_replacement(char *line,FILE *src_file,FILE *pre_file)
{
    line = strstr(line," ")+1; // it will ignore #define and contain the remaining

    //TO FIND AND STORE THE MACRO NAME
    char macro_name[25];
    int i=0;
    while(line[i] != ' ')
    {
	macro_name[i] = line[i];
	i++;
    }
    macro_name[i] = '\0';         
    printf("macro name  -> %s\n",macro_name);

    //TO FIND AND STORE THE MACRO VALUE
    char *macro_value;
    macro_value = strstr(line," ")+1;
    i=0;
    while(macro_value[i] != '\0')
	i++;
    macro_value[i-1] = ';';
    macro_value[i] = '\0';
    printf("macro_value --> %s\n",macro_value);  

    // MOVE THE FILE POINTER TILL THE MAIN FUNCTION BECAUSE IF WE CHECK FOR THE MACRO IT WILL SHOW THE DEFINED MACRO OUTSIDE SO CHECK INSIDE THE FUNCTION
    char str[450];
    while(fgets(str,448,pre_file) != NULL)
    {
	if(strstr(str,"int main()") != NULL)
	    break;
    }

    char *address;
    printf("\t AFTER int main()\n");
    while(fgets(str,448,pre_file) != NULL)
    {
    i=0;

	printf("string --> %s, %d\n",str,str[0]);
	if(strstr(str,macro_name))
	{
	    if(address = strstr(str," ")+1) // to get the space before the macro if it is return success
	    {
		printf("Address ->%s\n",address);
		int len = strlen(address);
		int j=0;
		//	printf("len --> %d\n",len);
		while(address[j] != 'S')
		{
		    j++;
		}
		i=j; 	       

		//TO REPLACE THE MACRO before that macro value should be stored in address and remaining indexes should be null
		int k=0;
		while(i < len-1)
		{
		    if(macro_value[k] != '\0')
			address[i] = macro_value[k++];
		    else
			address[i] = ' ';
		    printf("address[%d] = %d\n",i,address[i]);
		    i++;
		}
		printf("\nAddress after modifying --> %s\n",address);

		fseek(pre_file,-(len),SEEK_CUR);  //bring the cursor back to its position after checking for the macro

		//	printf("\nString in if --> %s, %ld\n",str,ftell(pre_file));
		fprintf(pre_file,"%s",address);
		fprintf(stdout,"hi:%s",address);
		fprintf(stdout,"str:%s",str);
	    }

	}
	//fseek
    }	
    return SUCCESS;
}

int single_line_comment(char *line,FILE *fptr1)
{
    char *ptr = strstr(line,"//");
    if(ptr != NULL)
    {
	*ptr = '\0';
	return SUCCESS;
    }
    return FAILURE;
}

void multi_line_comment(char *line,FILE *fptr)
{
    char *ptr1 = strstr(line,"/*");
    if(ptr1 != NULL)
    {
	*ptr1 = '\0';
	char ch[3];
	while(fread(ch,sizeof(char),3,fptr) != 0 && (strstr(ch,"*/") == NULL));
	//skip the entire comment
    }

}




