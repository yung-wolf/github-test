#include "main.h"

#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
	int file_from, file_to, n_close_file_from, n_close_file_to;
	size_t n_read, n_wrote;
	char buffer[BUFFER_SIZE];

	/*passed wrong num of args*/
	if (argc != 3)
	{
		dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
		exit (97);
	}

	/*open file_to in write only mode*/
	file_to = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (file_to == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't write to %s\n", argv[2]);
		exit (99);
	}

	/*open file from in read only mode*/
	file_from = open(argv[1], O_RDONLY);
	if (file_from == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", argv[1]);
		exit (98);
	}

	/*writes to file_to from file_from*/	
	while ((n_read = read(file_from, buffer, BUFFER_SIZE)) > 0)
	{
		n_wrote = write(file_to, buffer, n_read);
		if (n_wrote != n_read)
		{
			dprintf(STDERR_FILENO, "Error: Can't write to %s\n", argv[2]);
			exit (99); 
		}
	}

	/*failed to read file_from*/
	if ((int)n_read == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", argv[1]);
		exit (98);
	}

	/*Closes the opened files. Handle error cases.*/
	n_close_file_from = close(file_from);
	if (n_close_file_from == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", n_close_file_from);
		exit (100);
	}

	n_close_file_to = close(file_to);
	if (n_close_file_to == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", n_close_file_to);
		exit (100);
	}
	return (0);
}
