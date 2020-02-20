__kernel void swap(__global int *A)
{
	int i=get_global_id(0);\
	int temp;
	if(i%2==0)
	{
		temp=A[i+1];
		A[i+1]=A[i];
		A[i]=temp;
	}
}