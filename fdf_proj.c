#include "./fdf.h"
#include "./minilibx-linux/mlx.h"
#include "./minilibx-linux/mlx_int.h"
#include <stdlib.h>
#include <math.h>

/*
z ---------------------------------------------------------> x
| 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
| 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
| 0  0 10 10  0  0 10 10  0  0  0 10 10 10 10 10  0  0  0
| 0  0 10 10  0  0 10 10  0  0  0  0  0  0  0 10 10  0  0
| 0  0 10 10  0  0 10 10  0  0  0  0  0  0  0 10 10  0  0
| 0  0 10 10 10 10 10 10  0  0  0  0 10 10 10 10  0  0  0
| 0  0  0 10 10 10 10 10  0  0  0 10 10  0  0  0  0  0  0
| 0  0  0  0  0  0 10 10  0  0  0 10 10  0  0  0  0  0  0
| 0  0  0  0  0  0 10 10  0  0  0 10 10 10 10 10 10  0  0
| 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
| 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
y
*/

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
				return (free_tri_arr(p));
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
	double			a;
	double			b;

	i = 0;
	scale = 900 / p->map_size;
	a = 0.615472907;
	b = 0.785398;
	while (i < p->x)
	{
		k = 0;
		while (k < p->y)
		{
			z = p->map_cord[i][k];
			p->map_proj[i][k][0] = cos(b) * (i * scale) - sin(b) * (z * scale);
			if (p->map_proj[i][k][0] > p->x_max)
				p->x_max = p->map_proj[i][k][0];
			if (p->map_proj[i][k][0] < p->x_min)
				p->x_min = p->map_proj[i][k][0];
			p->map_proj[i][k][1] = ((2 * (k * scale) * cos(a)) - ((i * scale) * cos(a + b))
					+ (i * scale) * cos(a - b) + (z * scale) * sin(a + b) + (z * scale) * sin(a - b)) / 2;
			if (p->map_proj[i][k][1] > p->y_max)
				p->y_max = p->map_proj[i][k][1];
			if (p->map_proj[i][k][1] < p->y_min)
				p->y_min = p->map_proj[i][k][1];
			k++;
		}
		i++;
	}
}

void	move_proj(fdf_t_info *p)
{
	unsigned int	i;
	unsigned int	k;

	i = 0;
	while (i < p->x)
	{
		k = 0;
		while (k < p->y)
		{
			if (p->x_min < 0)
				p->map_proj[i][k][0] -= p->x_min;
			if (p->y_min < 0)
				p->map_proj[i][k][1] -= p->y_min;
			k++;
		}
		i++;
	}
}

void	print_proj(fdf_t_info *p)
{
	unsigned int	i;
	unsigned int	k;

	if (p->x_min < 0 || p->y_min < 0)
		move_proj(p);
	i = 0;
	while (i < p->x)
	{
		k = 0;
		while (k < p->y)
		{
			mlx_pixel_put(p->mp, p->wp1, p->map_proj[i][k][0], p->map_proj[i][k][1], p->map_color[i][k]);
			k++;
		}
		i++;
	}
}

int	proj(fdf_t_info *p)
{
	p->map_proj =  get_proj_slots(p);
	if (!p->map_proj)
		return (0);
	shoot_proj(p);
	print_proj(p);
	return (1);
}
