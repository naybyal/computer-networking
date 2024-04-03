#include <stdio.h>
int min(int x,int y)
{
	if(x<y)
	{
		return x;
	}
	return y;
}
void main()
{
	int drop=0,mini,msec,cap,count=0;
	int i,inp[25],process;
	printf("enter the bucket size\n");
	scanf("%d",&cap);
	printf("enter the output rate");
	scanf("%d",&process);
	printf("enter the no of sec to stimulate\n");
	scanf("%d",&msec);
	for(i=0;i<msec;i++)
	{
		printf("enter the size of the packet entering at %d sec",i+1);
		scanf("%d",&inp[i]);
	}
	printf("Time |packet recieved|packet send from buc|packet left in buc|packet drop\n");
	for(i=0;i<msec;i++)
	{
		count+=inp[i];
		if(count>cap)
		{
			drop=count-cap;
			count=cap;
		}
		else if(count<=cap)
		{
			printf("%d",i+1);
			printf("\t%d",inp[i]);
			mini=min(count,process);
			printf("\t\t%d",mini);
			count=count-mini;
			printf(" \t\t%d",count);
			printf(" \t\t%d\n",drop);
			drop=0;
		}
	}
	for(;count!=0;i++) {
		if(count>cap)
		{
			drop=count-cap;
			count=cap;
		}
		printf("%d",i+1);
		printf("\t0");
		mini=min(count,process);
		printf("\t\t%d",mini);
		count=count-mini;
		printf(" \t\t%d",count);
		printf(" \t\t%d\n",drop);
	
	}
}

