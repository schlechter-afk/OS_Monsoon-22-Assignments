#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
typedef long long int ll;
struct stat files;

// Algorithm to check if two files are reverse of each other : Maintain 4 pointers , 2 pointers for each file and check if content
// between the two pointers are reverse of each other and if so continue till the entire file is read.

int main(int argc, char *argv[])
{
    struct stat old_file, new_file, directory_check;
    int input_file_descriptor = open(argv[1], O_RDONLY);
    char *old_input = argv[2];
    char *new_input = argv[1];
    char *directory = argv[3];
    fstat(input_file_descriptor, &files);
    ll file_size = files.st_size;
    if (input_file_descriptor == -1)
    {
        perror("Error in extracting input_file_descriptor !!");
    }

    char *progress_bar = (char *)malloc(sizeof(char *) * (file_size + 2));
    char *input_arr = (char *)malloc(sizeof(char *) * (file_size + 2));
    char *reverse_arr = (char *)malloc(sizeof(char *) * (file_size + 2));
    int reverse_file_descriptor = open(argv[2], O_RDONLY);

    if (reverse_file_descriptor == -1)
    {
        perror("Error in extracting reverse_file_descriptor !!");
    }

    ll curr_ptr = file_size - 2000;
    ll end_ptr = file_size;
    ll curr_ptr_reverse = file_size - curr_ptr;
    ll end_ptr_reverse = file_size - end_ptr;

    int check = 0;
    int checkreverse = 1;
    int countiterations = 0;

    while (1)
    {
        if (curr_ptr <= 0)
        {
            curr_ptr_reverse += curr_ptr;
            curr_ptr = 0;
            check = 1;
        }
        // printf("%lld %lld %lld %lld\n", curr_ptr, end_ptr, curr_ptr_reverse, end_ptr_reverse);

        lseek(input_file_descriptor, curr_ptr, SEEK_SET);
        lseek(reverse_file_descriptor, end_ptr_reverse, SEEK_SET);

        int count = read(input_file_descriptor, input_arr, end_ptr - curr_ptr);
        int countreverse = read(reverse_file_descriptor, reverse_arr, curr_ptr_reverse - end_ptr_reverse);

        if (count == -1)
        {
            perror("Cant read anymore here!");
        }

        for (int i = 0; i < count; i++)
        {
            // printf("%c %c\n", input_arr[i], reverse_arr[count - i - 1]);
            if (input_arr[i] != reverse_arr[count - i - 1])
            {
                checkreverse = 0;
            }
        }

        end_ptr = curr_ptr;
        curr_ptr -= 2000;
        end_ptr_reverse = file_size - end_ptr;
        curr_ptr_reverse = file_size - curr_ptr;
        if (checkreverse)
        {
            break;
        }
        if (check)
        {
            break;
        }
    }

    stat(new_input, &new_file);
    stat(old_input, &old_file);
    stat(directory, &directory_check);

    if (stat(directory, &directory_check) == 0 && (S_IFDIR & directory_check.st_mode))
    {
        char toprint[200];
        int len = sprintf(toprint, "Directory is created: Yes\n");
        write(1, toprint, len);
    }
    else
    {
        char toprint[200];
        int len = sprintf(toprint, "Directory is created: No\n");
        write(1, toprint, len);
    }

    if (checkreverse)
    {
        char toprint[200];
        int len = sprintf(toprint, "Whether file contents are reversed in newfile: Yes\n");
        write(1, toprint, len);
    }
    else
    {
        char toprint[200];
        int len = sprintf(toprint, "Whether file contents are reversed in newfile: No\n");
        write(1, toprint, len);
    }

    /*  FOR NEW FILE */
    /*****************************************************************************************/
    // USER READ PERMISSIONS

    if (new_file.st_mode & S_IRUSR)
    {
        char toprint[200];
        int len = sprintf(toprint, "User has read permission on newfile: Yes\n");
        write(1, toprint, len);
    }
    else
    {
        char toprint[200];
        int len = sprintf(toprint, "User has read permission on newfile: No\n");
        write(1, toprint, len);
    }

    /****************************************************************************************/

    /*****************************************************************************************/
    // USER WRITE PERMISSIONS

    if (new_file.st_mode & S_IWUSR)
    {
        char toprint[200];
        int len = sprintf(toprint, "User has write permission on newfile: Yes\n");
        write(1, toprint, len);
    }
    else
    {
        char toprint[200];
        int len = sprintf(toprint, "User has write permission on newfile: No\n");
        write(1, toprint, len);
    }

    /****************************************************************************************/

    /*****************************************************************************************/
    // USER EXECUTE PERMISSIONS

    if (new_file.st_mode & S_IXUSR)
    {
        char toprint[200];
        int len = sprintf(toprint, "User has execute permission on newfile: Yes\n");
        write(1, toprint, len);
    }
    else
    {
        char toprint[200];
        int len = sprintf(toprint, "User has execute permission on newfile: No\n");
        write(1, toprint, len);
    }

    /****************************************************************************************/

    /*****************************************************************************************/
    // GROUP READ PERMISSIONS

    if (new_file.st_mode & S_IRGRP)
    {
        char toprint[200];
        int len = sprintf(toprint, "Group has read permission on newfile: Yes\n");
        write(1, toprint, len);
    }
    else
    {
        char toprint[200];
        int len = sprintf(toprint, "Group has read permission on newfile: No\n");
        write(1, toprint, len);
    }

    /****************************************************************************************/

    /*****************************************************************************************/
    // GROUP WRITE PERMISSIONS

    if (new_file.st_mode & S_IWGRP)
    {
        char toprint[200];
        int len = sprintf(toprint, "Group has write permission on newfile: Yes\n");
        write(1, toprint, len);
    }
    else
    {
        char toprint[200];
        int len = sprintf(toprint, "Group has write permission on newfile: No\n");
        write(1, toprint, len);
    }

    /****************************************************************************************/

    /*****************************************************************************************/
    // GROUP EXECUTE PERMISSIONS

    if (new_file.st_mode & S_IXGRP)
    {
        char toprint[200];
        int len = sprintf(toprint, "Group has execute permission on newfile: Yes\n");
        write(1, toprint, len);
    }
    else
    {
        char toprint[200];
        int len = sprintf(toprint, "Group has execute permission on newfile: No\n");
        write(1, toprint, len);
    }

    /****************************************************************************************/

    /*****************************************************************************************/
    // OTHERS READ PERMISSIONS

    if (new_file.st_mode & S_IROTH)
    {
        char toprint[200];
        int len = sprintf(toprint, "Others has read permission on newfile: Yes\n");
        write(1, toprint, len);
    }
    else
    {
        char toprint[200];
        int len = sprintf(toprint, "Others has read permission on newfile: No\n");
        write(1, toprint, len);
    }

    /****************************************************************************************/

    /*****************************************************************************************/
    // OTHERS WRITE PERMISSIONS

    if (new_file.st_mode & S_IWOTH)
    {
        char toprint[200];
        int len = sprintf(toprint, "Others has write permission on newfile: Yes\n");
        write(1, toprint, len);
    }
    else
    {
        char toprint[200];
        int len = sprintf(toprint, "Others has write permission on newfile: No\n");
        write(1, toprint, len);
    }

    /****************************************************************************************/

    /*****************************************************************************************/
    // OTHERS EXECUTE PERMISSIONS

    if (new_file.st_mode & S_IXOTH)
    {
        char toprint[200];
        int len = sprintf(toprint, "Others has execute permission on newfile: Yes\n");
        write(1, toprint, len);
    }
    else
    {
        char toprint[200];
        int len = sprintf(toprint, "Others has execute permission on newfile: No\n");
        write(1, toprint, len);
    }

    /****************************************************************************************/
    /* END OF NEW FILE */

    /*  FOR OLD FILE */
    /*****************************************************************************************/
    // USER READ PERMISSIONS

    if (old_file.st_mode & S_IRUSR)
    {
        char toprint[200];
        int len = sprintf(toprint, "User has read permission on oldfile: Yes\n");
        write(1, toprint, len);
    }
    else
    {
        char toprint[200];
        int len = sprintf(toprint, "User has read permission on oldfile: No\n");
        write(1, toprint, len);
    }

    /****************************************************************************************/

    /*****************************************************************************************/
    // USER WRITE PERMISSIONS

    if (old_file.st_mode & S_IWUSR)
    {
        char toprint[200];
        int len = sprintf(toprint, "User has write permission on oldfile: Yes\n");
        write(1, toprint, len);
    }
    else
    {
        char toprint[200];
        int len = sprintf(toprint, "User has write permission on oldfile: No\n");
        write(1, toprint, len);
    }

    /****************************************************************************************/

    /*****************************************************************************************/
    // USER EXECUTE PERMISSIONS

    if (old_file.st_mode & S_IXUSR)
    {
        char toprint[200];
        int len = sprintf(toprint, "User has execute permission on oldfile: Yes\n");
        write(1, toprint, len);
    }
    else
    {
        char toprint[200];
        int len = sprintf(toprint, "User has execute permission on oldfile: No\n");
        write(1, toprint, len);
    }

    /****************************************************************************************/

    /*****************************************************************************************/
    // GROUP READ PERMISSIONS

    if (old_file.st_mode & S_IRGRP)
    {
        char toprint[200];
        int len = sprintf(toprint, "Group has read permission on oldfile: Yes\n");
        write(1, toprint, len);
    }
    else
    {
        char toprint[200];
        int len = sprintf(toprint, "Group has read permission on oldfile: No\n");
        write(1, toprint, len);
    }

    /****************************************************************************************/

    /*****************************************************************************************/
    // GROUP WRITE PERMISSIONS

    if (old_file.st_mode & S_IWGRP)
    {
        char toprint[200];
        int len = sprintf(toprint, "Group has write permission on oldfile: Yes\n");
        write(1, toprint, len);
    }
    else
    {
        char toprint[200];
        int len = sprintf(toprint, "Group has write permission on oldfile: No\n");
        write(1, toprint, len);
    }

    /****************************************************************************************/

    /*****************************************************************************************/
    // GROUP EXECUTE PERMISSIONS

    if (old_file.st_mode & S_IXGRP)
    {
        char toprint[200];
        int len = sprintf(toprint, "Group has execute permission on oldfile: Yes\n");
        write(1, toprint, len);
    }
    else
    {
        char toprint[200];
        int len = sprintf(toprint, "Group has execute permission on oldfile: No\n");
        write(1, toprint, len);
    }

    /****************************************************************************************/

    /*****************************************************************************************/
    // OTHERS READ PERMISSIONS

    if (old_file.st_mode & S_IROTH)
    {
        char toprint[200];
        int len = sprintf(toprint, "Others has read permission on oldfile: Yes\n");
        write(1, toprint, len);
    }
    else
    {
        char toprint[200];
        int len = sprintf(toprint, "Others has read permission on oldfile: No\n");
        write(1, toprint, len);
    }

    /****************************************************************************************/

    /*****************************************************************************************/
    // OTHERS WRITE PERMISSIONS

    if (old_file.st_mode & S_IWOTH)
    {
        char toprint[200];
        int len = sprintf(toprint, "Others has write permission on oldfile: Yes\n");
        write(1, toprint, len);
    }
    else
    {
        char toprint[200];
        int len = sprintf(toprint, "Others has write permission on oldfile: No\n");
        write(1, toprint, len);
    }

    /****************************************************************************************/

    /*****************************************************************************************/
    // OTHERS EXECUTE PERMISSIONS

    if (old_file.st_mode & S_IXOTH)
    {
        char toprint[200];
        int len = sprintf(toprint, "Others has execute permission on oldfile: Yes\n");
        write(1, toprint, len);
    }
    else
    {
        char toprint[200];
        int len = sprintf(toprint, "Others has execute permission on oldfile: No\n");
        write(1, toprint, len);
    }

    /****************************************************************************************/
    /* END OF OLD FILE */

    /*  FOR DIRECTORY */
    /*****************************************************************************************/
    // USER READ PERMISSIONS

    if (directory_check.st_mode & S_IRUSR)
    {
        char toprint[200];
        int len = sprintf(toprint, "User has read permission on directory: Yes\n");
        write(1, toprint, len);
    }
    else
    {
        char toprint[200];
        int len = sprintf(toprint, "User has read permission on directory: No\n");
        write(1, toprint, len);
    }

    /****************************************************************************************/

    /*****************************************************************************************/
    // USER WRITE PERMISSIONS

    if (directory_check.st_mode & S_IWUSR)
    {
        char toprint[200];
        int len = sprintf(toprint, "User has write permission on directory: Yes\n");
        write(1, toprint, len);
    }
    else
    {
        char toprint[200];
        int len = sprintf(toprint, "User has write permission on directory: No\n");
        write(1, toprint, len);
    }

    /****************************************************************************************/

    /*****************************************************************************************/
    // USER EXECUTE PERMISSIONS

    if (directory_check.st_mode & S_IXUSR)
    {
        char toprint[200];
        int len = sprintf(toprint, "User has execute permission on directory: Yes\n");
        write(1, toprint, len);
    }
    else
    {
        char toprint[200];
        int len = sprintf(toprint, "User has execute permission on directory: No\n");
        write(1, toprint, len);
    }

    /****************************************************************************************/

    /*****************************************************************************************/
    // GROUP READ PERMISSIONS

    if (directory_check.st_mode & S_IRGRP)
    {
        char toprint[200];
        int len = sprintf(toprint, "Group has read permission on directory: Yes\n");
        write(1, toprint, len);
    }
    else
    {
        char toprint[200];
        int len = sprintf(toprint, "Group has read permission on directory: No\n");
        write(1, toprint, len);
    }

    /****************************************************************************************/

    /*****************************************************************************************/
    // GROUP WRITE PERMISSIONS

    if (directory_check.st_mode & S_IWGRP)
    {
        char toprint[200];
        int len = sprintf(toprint, "Group has write permission on directory: Yes\n");
        write(1, toprint, len);
    }
    else
    {
        char toprint[200];
        int len = sprintf(toprint, "Group has write permission on directory: No\n");
        write(1, toprint, len);
    }

    /****************************************************************************************/

    /*****************************************************************************************/
    // GROUP EXECUTE PERMISSIONS

    if (directory_check.st_mode & S_IXGRP)
    {
        char toprint[200];
        int len = sprintf(toprint, "Group has execute permission on directory: Yes\n");
        write(1, toprint, len);
    }
    else
    {
        char toprint[200];
        int len = sprintf(toprint, "Group has execute permission on directory: No\n");
        write(1, toprint, len);
    }

    /****************************************************************************************/

    /*****************************************************************************************/
    // OTHERS READ PERMISSIONS

    if (directory_check.st_mode & S_IROTH)
    {
        char toprint[200];
        int len = sprintf(toprint, "Others has read permission on directory: Yes\n");
        write(1, toprint, len);
    }
    else
    {
        char toprint[200];
        int len = sprintf(toprint, "Others has read permission on directory: No\n");
        write(1, toprint, len);
    }

    /****************************************************************************************/

    /*****************************************************************************************/
    // OTHERS WRITE PERMISSIONS

    if (directory_check.st_mode & S_IWOTH)
    {
        char toprint[200];
        int len = sprintf(toprint, "Others has write permission on directory: Yes\n");
        write(1, toprint, len);
    }
    else
    {
        char toprint[200];
        int len = sprintf(toprint, "Others has write permission on directory: No\n");
        write(1, toprint, len);
    }

    /****************************************************************************************/

    /*****************************************************************************************/
    // OTHERS EXECUTE PERMISSIONS

    if (directory_check.st_mode & S_IXOTH)
    {
        char toprint[200];
        int len = sprintf(toprint, "Others has execute permission on directory: Yes\n");
        write(1, toprint, len);
    }
    else
    {
        char toprint[200];
        int len = sprintf(toprint, "Others has execute permission on directory: No\n");
        write(1, toprint, len);
    }

    /****************************************************************************************/
    /* END OF DIRECTORY */

    return 0;
}
