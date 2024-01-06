#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

int create_process_and_check_error()
{
    pid_t process_id = fork();
    if (-1 == process_id)
    {
        perror("error create process");
        exit(2);
    }
    return process_id;
}

int try_open_file(char* name_file)
{
    int file_descriptor;
    if ((file_descriptor = open(name_file, O_RDONLY)) < 0)
    {
        perror("file did not open");
        exit(3);
    }
    return file_descriptor;
}

int main()
{
    const int max_size_string = 80;
    char file_name[max_size_string];
    printf("Enter the file name:\n");
    scanf("%s", file_name);

    int pipe_[2];
    if (pipe(pipe_) < 0)
    {
        perror("create pipe");
        exit(1);
    }
    pid_t process_id = create_process_and_check_error();

    if (process_id == 0)
    {

        close(pipe_[0]);

        int file_descriptor = try_open_file(file_name);
        dup2(file_descriptor, STDIN_FILENO);
        close(file_descriptor);

        dup2(pipe_[1], STDOUT_FILENO);
        close(pipe_[1]);

        execl("./child", "./child", NULL);
        perror("error starting child(execl)");
        exit(4);
    }
    close(pipe_[1]);

    char result_child[max_size_string];
    int bytes_read;
    while ((bytes_read = read(pipe_[0], result_child, sizeof(result_child))) > 0)
    {
        write(STDOUT_FILENO, result_child, bytes_read);
    }

    int status;
    wait(&status);

    if (WIFEXITED(status))
    {
        int child_program_status = WEXITSTATUS(status);
        if (child_program_status != 0)
        {
            fprintf(stderr, "division by zero!\n");
        }
    }
    else
    {
        fprintf(stderr, "child program failed with an error \n");
    }

    return 0;
}
