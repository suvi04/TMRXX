#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/ioctl.h>


struct winsize ws;
#define cls "\x1b[2J"
#define cs "\x1b[H"

void init();
void timer();
void centerTXT(int len);
void splashSCR();






void init()
{
    ioctl(STDIN_FILENO,TIOCGWINSZ,&ws);
    //printf("%d:%d",ws.ws_row,ws.ws_col);
}

void timer(int hours, int minutes)
{
    minutes--;
    for(int i=59;i>=0;i--)
    {
        sleep(0.1);
        if(minutes==0 && i==0 && hours ==0) break;
        if(minutes==0 && i==0 &&hours!=0)
		{
			hours--;
			minutes=59;
		}
		if(i==0)
		{
			minutes--;
			i=59;
		}
        printf(cls);
        printf(cs);
        centerTXT(17); // length of below string

        if(minutes<10 && hours<10 && i<10)
        {printf("-- 0%d:0%d:0%d --\n",hours,minutes,i);continue;}
        if(minutes<10 && hours<10) 
        {printf("-- 0%d:0%d:%d --\n",hours,minutes,i);continue;}

        if(minutes<10 && i<10 ) 
        {printf("-- %d:0%d:0%d --\n",hours,minutes,i);continue;}

        if(hours<10 && i<10) 
        {printf("-- 0%d:%d:0%d --\n",hours,minutes,i);continue;}

		if(minutes<10) 
        {printf("-- %d:0%d:%d --\n",hours,minutes,i);continue;}

        if(i<10) 
        {printf("-- %d:%d:0%d --\n",hours,minutes,i);continue;}

        if(hours<10) 
        {printf("-- 0%d:%d:%d --\n",hours,minutes,i);continue;}

        printf("-- %d:%d:%d --\n",hours,minutes,i);
        

    }
    printf(cls);
    printf(cs);
    centerTXT(14);
    sleep(1);
    printf("~ Time Over ~\a\n");

    return;
}


void centerTXT(int len)
{
    for(int k=0;k<ws.ws_row/2; k++) printf("\n");
	for(int k=0;k<(ws.ws_col-len)/2;k++) printf(" ");
}


void splashSCR()
{
    printf(cls);
    printf(cs);
    centerTXT(20);
    printf("-- TMRXX v.0xff --\n");
    sleep(1);
}


void main(int argc, char*argv[])
{
    init();

    int flag=1;
    int hours,minutes;
    char conf;

    if(argv[1]!=NULL)
    {
        hours = atoi(argv[1]);
        minutes=atoi(argv[2]);
        if(minutes>=60 || minutes<=0)
        {
            printf("Minute dimension error! \n");
            return;
        }
        splashSCR();
        timer(hours,minutes);
        return;
    }

    while(flag)
    {
        
        splashSCR();
        printf(cls);
        printf(cs);
        printf("\nEnter Timer duration (HH:MM) : ");
        scanf("%d:%d",&hours,&minutes);
        if(minutes>=60 || minutes<=0)
        {
            printf("Minute dimension error! \n");
            return;
        }
        printf("Set timer for %d:%d ?\nPress (n) to reset or RET to start ", hours,minutes);
        getchar();
        conf=getchar();
        if(conf == 'n') continue;
        else timer(hours,minutes);
        printf("Do you wish to continue ? (0) to quit : ");
        scanf("%d", &flag);
    }
}