<!-- file is written in markdown format -->

```
Assignment-1

Name : Swayam Agrawal
Roll : 2021101068
Branch : CSE
Course : Operating Systems and Networking , Monsoon'22

OS:Linux
```

# ***Part 1 :***


```
$ gcc q1.c
$ ./a.out <path_to_input_file/input.txt>
$ cd Assignment

Access the 1_input.txt

* Newline is considered to be another normal byte.
```


# ***Part 2:***

``` 
$ gcc q2.c
$ ./a.out <path_to_input_file/input.txt> <starting_index> <end_index>
$ cd Assignment

Access the 2_input.txt

* Newline is considered to be another normal byte.

* For large file_size , if the start_index is 0 and the end_index is
  file_size then there is no content to reverse , hence the progress 
  would not be gradually increased and would automatically be 100%
  as the progress would be when content is being
  reversed. *

```

# ***Part 3:***

``` 
$ gcc q3.c
$ ./a.out <path_to_input_file1> <path_to_file2> <path_to_directory>

Everything printed on the terminal

* Newline is considered to be another normal byte.

* Path has to be given to both files and the directory.
  Example of test input : assume that one file exists in folder1 in
  home directory and the other file exists in the assignment
  directory which again exists in the home directory and the
  directory we want to check upon is checkdirectory and it exists in
  the videos directory of home.

The input should ideally be:

$ ./a.out /home/folder1/file1.txt /home/assignment/file2.txt /home/videos/checkdirectory

The permission would be printed on the terminal.

```

