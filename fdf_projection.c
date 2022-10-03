#include "./fdf.h"
#include "./minilibx-linux/mlx.h"
#include "./minilibx-linux/mlx_int.h"
#include <stdlib.h>
#include <math.h>

void	*free_tri_arr(fdf_t_info *p, int ***arr)
{
	unsigned int	i;
	unsigned int	k;

	i = 0;
	while (i < p->x)
	{
		i++;
		while (k < p->y)
		{
			k = 0;
			free (arr[i][k++]);
		}
		free (arr[i]);
	}
	free (arr);
	return (0);
}

int	***get_proj_slots(fdf_t_info *p)
{
	int				***ret;
	unsigned int	i;
	unsigned int	k;

	ret = (int ***)malloc(sizeof (int *) * (p->x));
	if (!ret)
		return (NULL);
	i = 0;
	while (i < p->x)
	{
		ret[i] = (int **)malloc(sizeof (int *) * p->y);
		if (!ret[i])
		{
			free_arr((char **)ret);
			return (NULL);
		}
		k = 0;
		while (k < p->y)
		{
			ret[i][k] = (int *)malloc(sizeof (int) * 2);
			if (!ret[i][k++])
				return (free_tri_arr(p, ret));
		}
		i++;
	}
	return (ret);
}

void	shoot_proj(fdf_t_info *p)
{
	unsigned int	i;
	unsigned int	k;
	unsigned int	scale;
	int				z;

	i = 0;
	scale = 900 / p->map_size;
	while (i < p->x)
	{
		k = 0;
		while (k < p->y)
		{
			z = p->map_cord[i][k];
			p->map_proj[i][k][0] = (sqrt(2) * (i * scale) - sqrt(2) * (z * scale)) / 2;
			p->map_proj[i][k][1] = (sqrt(6) * (i * scale) + 2 * sqrt(6) * (k * scale) + sqrt(6) * (z * scale)) / 6;
			k++;
		}
		i++;
	}
}

int	get_projection(fdf_t_info *p)
{
	p->map_proj =  get_proj_slots(p);
	if (!p->map_proj)
		return (0);
	shoot_proj(p);
	//print_proj(p);
	return (1);
}
