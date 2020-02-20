__kernel void swap(__global int *A) {
 
    // Get the index of the current element to be processed
    int i = get_global_id(0);
 	if(i%2 == 0){
 		int tmp = A[i];
 		A[i] = A[i+1];
 		A[i+1] = tmp;
 	}
}