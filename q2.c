#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
typedef long long int ll;
struct stat files;

// Algorithm to solve the question : Reverse the content of file from 0 to start_input and write it to output file , then write the
// content directly from start_input to end_input and lastly reverse the content of the file from end_input to end of file. <3 iterations>

int main(int argc, char *argv[])
{
    int input_file_descriptor = open(argv[1], O_RDONLY);
    fstat(input_file_descriptor, &files);
    ll file_size = files.st_size;
    int start_inp = atoi(argv[2]);
    int end_inp = atoi(argv[3]);

    if (input_file_descriptor == -1)
    {
        perror("Error in extracting input_file_descriptor !!");
    }

    int sizetoreverse = file_size - (end_inp - start_inp);

    char outputfile[10000] = "Assignment/";
    int dir = mkdir("Assignment", 0777);

    char *stringpref = (char *)malloc(sizeof(char *) * 100);
    stringpref = "2_";

    char *toappend = (char *)malloc(sizeof(char *) * 10000);
    strcpy(toappend, stringpref);

    char *given = (char *)malloc(sizeof(char *) * 10000);
    char *filename = (char *)malloc(sizeof(char *) * 10000);
    char *tempname = (char *)malloc(sizeof(char *) * 10000);

    given = argv[1];
    int len = strlen(argv[1]);
    for (int i = len - 1; i >= 0; i--)
    {
        if (given[i] == '/')
        {
            break;
        }
        tempname[len - 1 - i] = given[i];
    }

    for (int i = strlen(tempname) - 1; i >= 0; i--)
    {
        filename[strlen(tempname) - 1 - i] = tempname[i];
    }

    strcat(toappend, filename);
    strcat(outputfile, toappend);

    char *progress_bar = (char *)malloc(sizeof(char *) * (file_size + 2));
    char *input_arr = (char *)malloc(sizeof(char *) * (file_size + 2));

    int output_file_descriptor = open(outputfile, O_WRONLY | O_CREAT, 0644);

    ll curr_ptr = file_size - 2000;
    ll end_ptr = file_size;
    int check = 0;

    check = 0;
    end_ptr = start_inp - 1;
    curr_ptr = end_ptr - 2000;

    if (end_ptr == 0)
    {
        int count = read(input_file_descriptor, input_arr, 1);
        write(output_file_descriptor, input_arr, count);
        goto try;
    }

    if (end_ptr < 0)
    {
        goto try;
    }

    while (1)
    {
        if (curr_ptr <= 0)
        {
            curr_ptr = 0;
            check = 1;
        }
        // printf("%lld %lld\n", curr_ptr, end_ptr);
        lseek(input_file_descriptor, curr_ptr, SEEK_SET);

        int count = read(input_file_descriptor, input_arr, end_ptr - curr_ptr + 1);
        if (count == -1)
        {
            perror("Cant read anymore here!");
        }

        int start_idx = 0;
        for (; start_idx <= (count - 1) / 2; start_idx++)
        {
            char temp = input_arr[start_idx];
            input_arr[start_idx] = input_arr[count - 1 - start_idx];
            input_arr[count - 1 - start_idx] = temp;
        }

        write(output_file_descriptor, input_arr, count);

        double progress = ((sizetoreverse - curr_ptr) * 100) / sizetoreverse;
        sprintf(progress_bar, "\rProgress: %6.2f %%", progress);
        write(1, progress_bar, strlen(progress_bar));

        end_ptr = curr_ptr;
        curr_ptr -= 2000;

        if (check)
        {
            break;
        }
    }
    try : lseek(output_file_descriptor, 0, SEEK_END)
        ;
    ll ptr1 = end_inp;
    ll ptr2 = start_inp;

    lseek(input_file_descriptor, ptr2, SEEK_SET);

    int count = read(input_file_descriptor, input_arr, ptr1 - ptr2 + 1);
    if (count == -1)
    {
        perror("Cant read anymore here!");
    }

    write(output_file_descriptor, input_arr, count);

    check = 0;
    end_ptr = file_size;
    curr_ptr = end_ptr - 2000;

    while (1)
    {
        if (curr_ptr <= end_inp)
        {
            curr_ptr = end_inp + 1;
            check = 1;
        }

        lseek(input_file_descriptor, curr_ptr, SEEK_SET);
        int count = read(input_file_descriptor, input_arr, end_ptr - curr_ptr);
        if (count == -1)
        {
            perror("Cant read anymore here!");
        }

        int start_idx = 0;
        for (; start_idx <= (count - 1) / 2; start_idx++)
        {
            char temp = input_arr[start_idx];
            input_arr[start_idx] = input_arr[count - 1 - start_idx];
            input_arr[count - 1 - start_idx] = temp;
        }

        write(output_file_descriptor, input_arr, count);
        double progress = ((sizetoreverse - curr_ptr + 1) * 100) / sizetoreverse;
        sprintf(progress_bar, "\rProgress: %6.2f %%", progress);
        write(1, progress_bar, strlen(progress_bar));

        end_ptr = curr_ptr;
        curr_ptr -= 2000;

        if (check)
        {
            double progress = 100;
            sprintf(progress_bar, "\rProgress: %6.2f %%", progress);
            write(1, progress_bar, strlen(progress_bar));
            break;
        }
    }
    return 0;
}