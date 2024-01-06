#include <sys/mman.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stddef.h>

const char *MEMORY_NAME = "lab4_shared_memory";
const size_t SHARED_MEMORY_OBJECT_SIZE = 2048;
#define BUFFER_SIZE 256
// const size_t BUFFER_SIZE = 256;

typedef struct buffer_struct
{
    float buffer[BUFFER_SIZE];
    size_t size;
} buffer_struct;

int main(int argc, const char *argv[])
{
    pid_t process_id;
    int status;

    switch (process_id = fork())
    {
    case -1:
        char message[] = "fork error\n";
        fprintf(stderr, "%s", message);
        return 2;

    case 0:
        execl("child", "child",  argv[1] , NULL);
        perror("Can't execute child\n");
        exit(1);

    default:
        if (waitpid(process_id, &status, 0) == -1)
        {
            char message[] = "Waitpid error\n";
            fprintf(stderr, "%s", message);
            return 1;
        }
        int file_descriptor = shm_open(MEMORY_NAME, O_RDONLY, S_IRUSR | S_IWUSR);	
        if (file_descriptor == -1)
        {
            char message[] = "Can't open shared memory file\n";
            fprintf(stderr, "%s", message);
            shm_unlink(MEMORY_NAME);
            close(file_descriptor);
            return 1;
        }

        buffer_struct *address_buffer = mmap(NULL, SHARED_MEMORY_OBJECT_SIZE, PROT_READ, MAP_SHARED, file_descriptor, 0);
        if (address_buffer == (void *)-1)
        {
            char message[] = "Mmap error\n";
            fprintf(stderr, "%s", message);
            munmap(address_buffer, SHARED_MEMORY_OBJECT_SIZE);
            shm_unlink(MEMORY_NAME);
            close(file_descriptor);
            return 1;
        }

        for (int i = 0; i < address_buffer->size; i++)
        {
            printf("%.6f\n", address_buffer->buffer[i]);
        }

        munmap(address_buffer, SHARED_MEMORY_OBJECT_SIZE);
        shm_unlink(MEMORY_NAME);
        close(file_descriptor);
    }

    return 0;
}
