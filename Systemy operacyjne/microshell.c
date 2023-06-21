#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <limits.h>
#include <pwd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define BLU "\e[0;36m"
#define GRN "\e[0;32m"
#define WHT "\e[0;37m"
#define MAG "\e[1;95m"
#define ORG "\e[0;33m"
#define YEL "\e[0;93m"
#define RED "\e[0;91m"
#define cRESET "\e[0m"



void Path()
{
    char cwd[128];
    char *login="";

    uid_t id = geteuid();
    struct passwd *log = getpwuid(id);
    if (log)
    {  
    login=log->pw_name;
    }
    
    if (getcwd(cwd, sizeof(cwd)) != NULL) 
    {
       printf("["BLU"%s"cRESET":"GRN"%s"cRESET"]\n",login, cwd);
       printf(WHT"$"cRESET);
       
    } 
    else
    {
       perror(RED"getcwd() error"cRESET);
    }
}

void Cd(char* pth,char *prev)
{
    if(strcmp(pth,"-")==0 || pth[0]=='~')
    {
        if(strcmp(pth,"-")==0)
        {
            
            if(strcmp(prev,"")!=0)
            {
                
                chdir(prev);
                
            }
            else
            {
                printf(RED"Command error: No previous directory\n"cRESET);
            }
            
        }
        if(pth[0]=='~')
        {
            if(strcmp(pth,"~")==0)
            {
                char* home=getenv("HOME");
                chdir(home);
            }
            if(pth[1]=='/')
            {
                char tmp[100];
                strcpy(tmp,pth);
                char* npth=strtok(tmp,"~/");
                char* home=getenv("HOME");
                chdir(home);
                if(chdir(npth)!=-1)
                chdir(npth);
                else
                printf(RED"There is no such file or directory like: %s in %s\nYou were moved to: %s\n"cRESET,npth,home,home);
            }
            if(strcmp(pth,"~")!=0 && pth[1]!='/')
            {
               printf(RED"Command error: No such file or directory\n"cRESET); 
            }
            
        }
    }
    else
    {	
        if(chdir(pth)!=-1)
		chdir(pth);
        else
        printf(RED"Command error: No such file or directory\n"cRESET);
    }

}

void Help()
{
   printf(MAG"\n*** PROJEKT MICROSHELL ***\n"YEL "Autor: Adam Cherek\n");
   printf(ORG"\nKomendy:\nhelp		:wyswietla notatke pomocnicza\ncd		:zmienia katalog roboczy\nexit		:konczy dzialanie programu powloki\nexit -c		:konczy dzialanie programu powloki i czysci ekran\n\n"cRESET);
}

int main()
{  
    char prev[128]="";
    
    
    while(1)
    {
    int pid=getpid();
    Path();
    
    
    char znak;
    scanf("%c",&znak);
    
        char komenda[128]={};
        komenda[0]=znak;
        int i=1;
        while(znak!='\n')
        {
            scanf("%c",&znak);
            komenda[i]=znak;
            i++;
        }
        
        int count=0;
        char* schowek;
        schowek = strtok(komenda, " \n");
        char* arg[2]={};
        arg[count]=schowek;
        schowek = strtok(NULL, "\n");
        if(schowek != NULL)
        {
            
            count++;
            arg[count]=schowek;
        }

            
        if(arg[0]==NULL || strcmp(arg[0],"exit")==0  || strcmp(arg[0],"cd")==0 || strcmp(arg[0],"help")==0)
        {
            if(arg[0]!=NULL)
            {
                if(strcmp(arg[0],"exit")==0)
                {
                    if(arg[1]==NULL)
                    {
                    printf("\n\nThanks for using and have a nice day :D\n\n\n");
                    exit(0);
                    }
                    if(strcmp(arg[1],"-c")==0)
                    {
                    printf("\e[1;1H\e[2J");
                    printf("\n\nThanks for using and have a nice day :D\n\n\n");
                    exit(0);
                    }
                    if(strcmp(arg[1],"-c")!=0)
                    {
                    printf(RED"There is no command like: %s %s\n"cRESET,arg[0],arg[1]);
                    }
                    
                }
                if(strcmp(arg[0],"cd")==0)
                {   
                    char tmp[128];
                    getcwd(tmp, sizeof(tmp));
					if(count!=0)
					{
                    	Cd(arg[1],prev);
					}
					else
					{
						char* home=getenv("HOME");
            			chdir(home);
					}
					
                    strcpy(prev,tmp);
                }
                if(strcmp(arg[0],"help")==0)
                {
                    Help();
                }
            }
        }
        else
        {
            if(count==0)
            {   
                fork();
                if(getpid()!=pid)
                {
                execlp(arg[0],arg[0],NULL);
                fprintf(stderr,RED"Command error (%d): %s\n"cRESET,errno,strerror(errno));
                exit(EXIT_FAILURE);
                }
                else
                wait(NULL);
            }
            if(count==1)
            {   
                fork();
                if(getpid()!=pid)
                {
                execlp(arg[0],arg[0],arg[1],NULL);
                fprintf(stderr,RED"Command error (%d): %s\n"cRESET,errno,strerror(errno));
                exit(EXIT_FAILURE);
                }
                else
                wait(NULL);
            }
        }

    
    
    
    
    }
    
}
