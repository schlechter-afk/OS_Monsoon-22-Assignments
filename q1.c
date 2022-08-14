#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
typedef long long int ll;
struct stat files;

// Algorithm to solve the question : Maintain two pointers ptr1 which is at file_size-2000 bytes and ptr2 which is at file_size.
// Read the content between the two pointers and reverse them and write the text in the output file , decrease ptr1,ptr2 both by 2000 bytes 
// 2000 bytes is the chunk size.

int main(int argc, char *argv[])
{
    int input_file_descriptor = open(argv[1], O_RDONLY);
    fstat(input_file_descriptor, &files);
    ll file_size = files.st_size;
    if (input_file_descriptor == -1)
    {
        perror("Error in extracting input_file_descriptor !!");
    }

    char outputfile[100000] = "Assignment/";
    int dir = mkdir("Assignment", 0777);

    char *stringpref = (char *)malloc(sizeof(char *) * 1000);
    stringpref = "1_";
    char *toappend = (char *)malloc(sizeof(char *) * 100000);
    strcpy(toappend, stringpref);
    char *given = (char *)malloc(sizeof(char *) * 10000);
    char *filename = (char *)malloc(sizeof(char *) * 10000);
    char *tempname = (char *)malloc(sizeof(char *) * 10000);

    // filename = argv[1];
    // chmod("Assignment",700);

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

    // printf("%s\n", tempname);
    for (int i = strlen(tempname) - 1; i >= 0; i--)
    {
        filename[strlen(tempname) - 1 - i] = tempname[i];
    }

    strcat(toappend, filename);
    strcat(outputfile, toappend);
    // printf("%s\n", outputfile);

    char *progress_bar = (char *)malloc(sizeof(char *) * (file_size + 2));
    char *input_arr = (char *)malloc(sizeof(char *) * (file_size + 2));
    int output_file_descriptor = open(outputfile, O_WRONLY | O_CREAT, 0644);

    ll curr_ptr = file_size - 2000;
    ll end_ptr = file_size;

    int check = 0;
    int countiterations = 0;

    while (1)
    {
        if (curr_ptr <= 0)
        {
            curr_ptr = 0;
            check = 1;
        }
        // lseek(input_file_descriptor, curr_ptr - end_ptr, SEEK_END);
        lseek(input_file_descriptor, curr_ptr, SEEK_SET);

        int count = read(input_file_descriptor, input_arr, end_ptr - curr_ptr);

        // printf("%d\n", count);
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

        double progress = ((file_size - curr_ptr) * 100) / file_size;
        sprintf(progress_bar, "\rProgress till now is: %6.2f %%", progress);
        write(1, progress_bar, strlen(progress_bar));

        end_ptr = curr_ptr;
        curr_ptr -= 2000;

        if (check)
        {
            // printf("Breaking at %d\n", countiterations);
            break;
        }
        // countiterations++;
    }
    return 0;
}