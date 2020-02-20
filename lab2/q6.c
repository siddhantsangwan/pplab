#include<mpi.h>
#include<stdio.h>
#include<string.h>
#define MAX 200

int main(int argc, char *argv[])
{
	int rank,size;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	int val;
	char str[MAX];
	MPI_Status status;
	if(rank==0)
	{
		FILE *fd = fopen("name.txt","r");
		int cnt = 1;
		while(fgets(str,MAX,fd)!=NULL)
		{
			char *ch1,*ch2;
			if((ch1=strstr(str,"<TEXT>"))&&(ch2=strstr(str,"</TEXT>")))
			{
				ch1+=6;

				int k=0;
				char temp[MAX];
				while(ch1!=ch2)
				{
					temp[k++]=ch1[0];
					ch1++;
				}
				temp[k]='\0';
				strcpy(str,temp);
				MPI_Send(&str,(strlen(str)+1),MPI_CHAR,cnt++,1,MPI_COMM_WORLD);
				MPI_Recv(&k,1,MPI_INT,cnt-1,1,MPI_COMM_WORLD,&status);
				printf("Length Recieved by Process 0 from %d: %d\n",k,cnt-1);
			}
		}
		fclose(fd);
	}
	else
	{
		MPI_Recv(&str,MAX,MPI_CHAR,0,1,MPI_COMM_WORLD,&status);
		val = strlen(str);
		printf("String Recieved by Process %d %s | %d\n",rank,str,val);
		MPI_Send(&val,1,MPI_INT,0,1,MPI_COMM_WORLD);
	}
	MPI_Finalize();
	return 0;
}
