 #include "../include/cub3d.h"

void	free_array(char **arr)
{
	size_t	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	free_array_n(char **arr, int n)
{
	int	k;

	k = 0;
	while (k < n)
	{
		free(arr[k]);
		k++;
	}
	free(arr);
}
