#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <math.h>

const int MAX_ELEMENT_ARRAY=100000000;

struct Thread_Args
{
    int *array;
    int start;
    int end;
};

void max_available_threads(int* threads_count){
    int max_threads=(int) sysconf(_SC_NPROCESSORS_ONLN);
    printf("max_available_threads : %d\n",max_threads);
    if (*threads_count>max_threads){
        *threads_count=max_threads;
    }
}

int augment_array_to_power_two(int input_size_array){
    printf("%d %d",(int)pow(2,log2(input_size_array)),input_size_array);
    if ((int)pow(2,log2(input_size_array))==input_size_array){
        printf("EEEE");
    }
    return 0;
}

void Bitonic_merge(int *array, int start, int size, int direction)
{
    if (size > 1)
    {
        int middle = size / 2;
        for (int index = start; index < start + middle; ++index)
        {
            if ((array[index] > array[index + middle]) == direction)
            {
                int temp = array[index];
                array[index] = array[index + middle];
                array[index + middle] = temp;
            }
        }
        Bitonic_merge(array, start, middle, direction);
        Bitonic_merge(array, start + middle, middle, direction);
    }
}

void Bitonic_sort(int *array, int start, int size, int direction)
{
    if (size > 1)
    {
        int middle = size / 2;
        Bitonic_sort(array, start, middle, 1);
        Bitonic_sort(array, start + middle, middle, 0);
        Bitonic_merge(array, start, size, direction);
    }
}

void *thread_function(void *arg)
{
    struct Thread_Args *args = (struct Thread_Args *)arg;
    Bitonic_sort(args->array, args->start, args->end - args->start + 1, 1);
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    int array_size;//262144
    int threads_count;

    if (argc != 3)
    {
        perror("invalid argument console");
        exit(-1);
    }

    if (atoi(argv[1]) < 1)
    {
        perror("the number of threads is a negative number");
        exit(-1);
    }
    threads_count = atoi(argv[1]);
    max_available_threads(&threads_count);
    int input_size_array=atoi(argv[2]);
    array_size=augment_array_to_power_two(input_size_array);
    int Array_sort[array_size];
    // for (int index = 0; index < array_size; ++index) {
    //     Array_sort[index] = rand() % 100;            //random generate array
    // }
    for (int index = 0; index < array_size; ++index)
    {
        Array_sort[index] = array_size - index;
    }

    struct timeval start, end;
    gettimeofday(&start, NULL);
    pthread_t threads[threads_count];
    struct Thread_Args thread_args[threads_count];

    int part_array_size = array_size / threads_count;
    int remainder = array_size % threads_count;

    int start_index = 0;
    int end_index = part_array_size - 1;

    for (int index_of_element = 0; index_of_element < threads_count; ++index_of_element)
    {
        if (remainder > 0)
        {
            end_index++;
            remainder--;
        }

        thread_args[index_of_element].array = Array_sort;
        thread_args[index_of_element].start = start_index;
        thread_args[index_of_element].end = end_index;

        pthread_create(&threads[index_of_element], NULL, thread_function, (void *)&thread_args[index_of_element]);

        start_index = end_index + 1;
        end_index = start_index + part_array_size - 1;
    }

    for (int index = 0; index < threads_count; ++index)
    {
        pthread_join(threads[index], NULL);
    }

    Bitonic_sort(Array_sort, 0, array_size, 1);

    gettimeofday(&end, NULL);
    double work_time = (end.tv_sec - start.tv_sec) * 1000.0;
    work_time += (end.tv_usec - start.tv_usec) / 1000.0;

    printf("work time: %.20f ms\n", work_time);

    FILE *output_file = fopen("output.txt", "w");
    if (output_file == NULL)
    {
        printf("Error opening output.txt for writing\n");
        return 1;
    }

    printf("Writing sorted array to output.txt...\n");
    for (int index_of_element = 0; index_of_element < array_size; ++index_of_element)
    {
        fprintf(output_file, "%d, ", Array_sort[index_of_element]);
    }
    printf("Sorted array written to output.txt\n");

    fclose(output_file);

    return 0;
}
