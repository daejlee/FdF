#include "./fdf.h"
#include "./libft_garage/ft_printf/ft_printf.h"
#include <stdio.h>
#include <stdlib.h>

int	err(void)
{
	perror("fdf error :");
	return (1);
}

int	terminate(fdf_t_info *p)
{
	unsigned int	i;

	i = 0;
	if (p->map_cord)
	{
		while (i < p->x)
			free (p->map_cord[i++]);
		free (p->map_cord);
	}
	i = 0;
	if (p->map_color)
	{
		while (i < p->x)
			free (p->map_color[i++]);
		free (p->map_color);
	}
	return (0);
}

void	print_int_arr(fdf_t_info p)
{
	unsigned int	i;
	unsigned int	k;

	i = 0;
	while (i < p.y)
	{
		k = 0;
		while (k < p.x)
			ft_printf("%i ", p.map_cord[k++][i]);
		ft_printf("\n");
		i++;
	}
	ft_printf("---------------------------------------------------------------\n");
	i = 0;
	while (i < p.y)
	{
		k = 0;
		while (k < p.x)
			ft_printf("%i ", p.map_color[k++][i]);
		ft_printf("\n");
		i++;
	}
	ft_printf("---------------------------------------------------------------\n");
}

int	free_arr(char **arr)
{
	unsigned int	i;

	i = 0;
	while (arr[i])
		free (arr[i++]);
	free (arr);
	return (0);
}
