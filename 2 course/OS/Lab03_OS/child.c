#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>
#include <stdio.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/stat.h>

const char* MEMORY_NAME = "lab4_shared_memory";
const size_t SHARED_MEMORY_OBJECT_SIZE = 2048;
#define BUFFER_SIZE 256
// const size_t BUFFER_SIZE = 256;

typedef struct buffer_struct {
    float buffer[BUFFER_SIZE];
    size_t size;
} buffer_struct;

void divide_and_print_answer(FILE *input, buffer_struct *address_buffer) {
    char line[BUFFER_SIZE];
    address_buffer->size = 0;

    while (fgets(line, BUFFER_SIZE, input) != NULL) {
        int num_count = 0;
        float result = 0.0;
        char *token = strtok(line, " \n");

        while (token != NULL) {
            float number = atof(token);
            if (num_count == 0) {
                result = number;
            } else {
                if (number == 0) {
                    fprintf(stderr, "Error: Division by zero\n");
                    return;
                }
                result /= number;
            }
            num_count++;
            token = strtok(NULL, " \n");
        }

        if (num_count > 0) {
            address_buffer->buffer[address_buffer->size++] = result;
        }
    }
}

int main(int argc, const char *argv[]) {
    int file_descriptor = shm_open(MEMORY_NAME, O_EXCL | O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if (file_descriptor == -1) {
        char message[] = "Can't open shared memory file\n";
        fprintf(stderr, "%s", message);
        shm_unlink(MEMORY_NAME);
        close(file_descriptor);
        return 1;
    }
    if (ftruncate(file_descriptor, SHARED_MEMORY_OBJECT_SIZE) == -1) {
        char message[] = "Can't extend shared memory file\n";
        fprintf(stderr, "%s", message);
        shm_unlink(MEMORY_NAME);
        close(file_descriptor);
        return 1;
    }

    buffer_struct *address_buffer = mmap(NULL, SHARED_MEMORY_OBJECT_SIZE, PROT_WRITE, MAP_SHARED, file_descriptor, 0);
    if (address_buffer == (void *) -1) {
        char message[] = "Mmap error\n";
        fprintf(stderr, "%s", message);
        munmap(address_buffer, SHARED_MEMORY_OBJECT_SIZE);
        shm_unlink(MEMORY_NAME);
        close(file_descriptor);
        return 1;
    }
    FILE *input = NULL;
    if (argc == 2) {
        input = fopen(argv[1], "r");
    }
    if (input == NULL) {
        char message[] = "Can't open file\n";
        fprintf(stderr, "%s", message);
        munmap(address_buffer, SHARED_MEMORY_OBJECT_SIZE);
        shm_unlink(MEMORY_NAME);
        close(file_descriptor);
        return 1;
    }
    divide_and_print_answer(input, address_buffer);
    fclose(input);

    if (address_buffer->size == 0) {
        exit(1); 
    }

    munmap(address_buffer, SHARED_MEMORY_OBJECT_SIZE);
    close(file_descriptor);
    return 0;
}
