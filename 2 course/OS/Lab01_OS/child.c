#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    const int max_size_string = 80;
    char input_line[max_size_string];
    while (fgets(input_line, sizeof(input_line), stdin) != NULL)
    {
        char *one_number_line = strtok(input_line, " \n");
        float result = atof(one_number_line);
        while ((one_number_line = strtok(NULL, " \n")) != NULL)
        {
            float number = atof(one_number_line);
            if (number == 0.0)
            {
                exit(-1);
            }
            result /= number;
        }
        printf("%f\n", result);
    }

    return 0;
}
