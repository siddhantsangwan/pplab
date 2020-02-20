__kernel void decimal2octal(__global const int *A, __global int *B) {
 
    // Get the index of the current element to be processed
    int i = get_global_id(0);
 	int tmp = A[i];
 	int oct = 0;
	int multiplier = 1;
 	while(tmp){
 		oct += (tmp%8)*multiplier;
 		tmp /= 8;
 		multiplier *= 10;
 	}
 	B[i] = oct;
}