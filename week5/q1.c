#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>

#define MAX_SOURCE_SIZE (0x100000)

int main(void) {
    // Create the two input vectors
	int i, size, num;
	printf("Enter size: ");
	scanf("%d", &size);
	//const int LIST_SIZE = 1024;
    int *decimal = (int*)malloc(sizeof(int)*size);
    int *octal = (int*)malloc(sizeof(int)*size);
    printf("Enter %d values: ", size);
    for(i = 0; i < size; i++) {
    	scanf("%d", &num);
        decimal[i] = num;
    }

    // Load the kernel source code into the array source_str
    FILE *fp;
    char *source_str;
    size_t source_size;

    fp = fopen("dec2octal.cl", "r");
    if (!fp) {
        fprintf(stderr, "Failed to load kernel.\n");
        exit(1);
    }
    source_str = (char*)malloc(MAX_SOURCE_SIZE);
    source_size = fread( source_str, 1, MAX_SOURCE_SIZE, fp);
    fclose( fp );

    // Get platform and device information
    cl_platform_id platform_id = NULL;
    cl_device_id device_id = NULL;
    cl_uint ret_num_devices;
    cl_uint ret_num_platforms;
    cl_int ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
    ret = clGetDeviceIDs( platform_id, CL_DEVICE_TYPE_DEFAULT, 1,
            &device_id, &ret_num_devices);

    // Create an OpenCL context
    cl_context context = clCreateContext( NULL, 1, &device_id, NULL, NULL, &ret);

    // Create a command queue
    cl_command_queue command_queue = clCreateCommandQueue(context, device_id, 0, &ret);

    // Create memory buffers on the device for each vector
    cl_mem decimal_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY,
            size * sizeof(int), NULL, &ret);
    cl_mem octal_mem_obj = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
            size * sizeof(int), NULL, &ret);

    // Copy the list to its respective memory buffers
    ret = clEnqueueWriteBuffer(command_queue, decimal_mem_obj, CL_TRUE, 0,
            size * sizeof(int), decimal, 0, NULL, NULL);


    // Create a program from the kernel source
    cl_program program = clCreateProgramWithSource(context, 1,
            (const char **)&source_str, (const size_t *)&source_size, &ret);

    // Build the program
    ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);
    if (ret == CL_BUILD_PROGRAM_FAILURE) {
        // Determine the size of the log
        size_t log_size;
        clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);

        // Allocate memory for the log
        char *log = (char *) malloc(log_size);

        // Get the log
        clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_LOG, log_size, log, NULL);

        // Print the log
        printf("%s\n", log);
    }
    // Create the OpenCL kernel
    cl_kernel kernel = clCreateKernel(program, "decimal2octal", &ret);

    // Set the arguments of the kernel
    ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&decimal_mem_obj);
    ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&octal_mem_obj);

    // Execute the OpenCL kernel on the list
    size_t global_item_size = size; // Process the entire lists
    size_t local_item_size = 1; // Divide work items into groups of 64
    ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL,
            &global_item_size, &local_item_size, 0, NULL, NULL);

    // Read the memory buffer C on the device to the local variable C
    ret = clEnqueueReadBuffer(command_queue, octal_mem_obj, CL_TRUE, 0,
            size * sizeof(int), octal, 0, NULL, NULL);

    // Display the result to the screen
    for(i = 0; i < size; i++)
        printf("%d in octal = %d\n", decimal[i], octal[i]);

    // Clean up
    ret = clFlush(command_queue);
    ret = clFinish(command_queue);
    ret = clReleaseKernel(kernel);
    ret = clReleaseProgram(program);
    ret = clReleaseMemObject(decimal_mem_obj);
    ret = clReleaseMemObject(octal_mem_obj);
    ret = clReleaseCommandQueue(command_queue);
    ret = clReleaseContext(context);
    free(decimal);
    free(octal);
    return 0;
}
