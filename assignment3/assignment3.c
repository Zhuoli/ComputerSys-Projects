# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# define END 255


char *algorithm;
int page_num;
int capacity;
int memory[1024];
int *freelist[512];
int *busylist[512];
char flag;
char *file;
char buffer_capacity[1024];
char *buffer = buffer_capacity;
FILE *fp = NULL;
int index_free=0;
int index_busy=0;

void init(int,char **);
int fifo_insert_this_page(int,int);
int lru_insert_this_page(int, int);
int fifo_evict_algrothim(int capacity);
int has_this_page(int,int);
int has_free_page(void);
void use_a_free_page(int);
int main(int argc, char ** argv)
{
	int i=0;
        int evict;         // represents the page_num to be evicted
        int  page_list[1024];
        init(argc,argv);
	while(1)
	{ 
         if(!fgets(buffer,1024,fp)){
	  perror("Fgets:");	
	  break;}
	 page_num=atoi(buffer);
         page_list[i]=page_num;
	 i++;
    	};
        getchar();
         page_list[i]=END;
         i=0;
      while(page_list[i]!=END)
      {
        page_num=page_list[i];
        i++;
         if(has_this_page(page_num,flag))
	   { printf("Hit %d\n",page_num);}
	 else
	   {
	      evict = insert_this_page(page_num,capacity);
 	    if (evict == 255) 
	      { printf("Miss %d evicting None\n",page_num);}
	    else
	       printf("Miss %d evicting %d\n",page_num,evict);
           }
	}
}

int insert_this_page(int page_num,int capacity)
{
   int temp=255;
   if (has_free_page())
     { use_a_free_page(page_num);}
   else
     temp = evict_algrothim(page_num);
   return temp; 
}
int evict_algrothim(int capacity)
{

 int i=0;
 int *p = busylist[0];
 int evict_num=*busylist[0];
 for (i=0;i<capacity;i++)
 { 
   busylist[i]=busylist[i+1];
   if(busylist[i]==NULL)
     break;
 }
 
 busylist[i]=p;
 *busylist[i]=page_num;
 return evict_num;
 
}
void use_a_free_page(page_num)
{
  busylist[index_busy]=freelist[index_free-1];
  *busylist[index_busy]=page_num;
  index_busy++;
  index_free--;

}
int has_free_page(void)
{
  if (index_free>0)
     {return 1;}
  else
      return 0;
}

int has_this_page(int page_num,int flag)
{
 int i = 0;
 int *p_page;
 if(flag == 1)
  {
   while(busylist[i]!=NULL)
    if(*busylist[i] == page_num)
     { return 1; }
    else i++;
   return 0;
  }
 else
  {
   while(busylist[i]!=NULL)
    if(*busylist[i]==page_num)
     { 
      p_page=busylist[i];
      for (i ;i<capacity;i++)
      { busylist[i]=busylist[i+1];
        if(busylist[i]==NULL)
          break; }
      busylist[i]=p_page;
      return 1;
     }
    else i++;
   return 0;
  }
}
 

void init(int argc, char ** argv)
{
   int i = 0;
	if (argc<4) 
	{ 
	  printf("Please input correct arguments\n");
	  exit(0);}
	file = argv[3];
	if((fp = fopen(file,"r"))==NULL)
	{
	  perror("Open:");
	  exit(-1);}
	algorithm = argv[1];
	if (0 == strcmp("lru",algorithm))
	  { flag=0;}
	else if (0 == strcmp("fifo",algorithm))
	  { flag=1;}
	else
	  { puts("Please input correct replacement algorithm\n"); 
	    exit(0);}
	capacity = atoi(argv[2]);

  index_free=capacity;
   for(i=0;i<index_free;i++)
  {
    freelist[i]=&memory[i];
  }
   for(i=0;i<512;i++)
  {
   busylist[i]= NULL;
  }  
}
	
