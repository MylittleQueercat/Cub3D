#include "../include/cub3d.h"

// 用于free是null-terminated的数组
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

// 用于free后面的指针可能是未初始化垃圾值的数组
void	free_array_n(char **arr, int n)
{
    for (int k = 0; k < n; k++)
        free(arr[k]);
    free(arr);
}