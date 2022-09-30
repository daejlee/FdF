#include <stdlib.h>

int	free_arr(char **arr)
{
	unsigned int	i;

	i = 0;
	while (arr[i])
		free (arr[i++]);
	free (arr);
	return (0);
}
