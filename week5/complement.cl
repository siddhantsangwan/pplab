__kernel void complement(__global const int *A, __global int *B) {
 
    // Get the index of the current element to be processed
    int i = get_global_id(0);
 	int tmp = A[i];

 	B[i] = !tmp;
}