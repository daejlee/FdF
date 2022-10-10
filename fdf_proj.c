#include "./fdf.h"
// #include "./minilibx-linux/mlx.h"
#include "./mlx/mlx.h"
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265359
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
	int				z;
	double			a;
	double			b;
	double			scale;

	i = 0;
	scale = p->scale;
	a = p->v_angle * (PI / 180); //vertical rot
	b = p->h_angle * (PI / 180); //horizental rot
	p->x_max = 0;
	p->x_min = 0;
	p->y_max = 0;
	p->y_min = 0;
	while (i < p->x)
	{
		k = 0;
		while (k < p->y)
		{
			z = p->map_cord[i][k];
			p->map_proj[i][k][0] = (cos(b) * i - sin(b) * k) * scale;
			if (p->map_proj[i][k][0] > p->x_max)
				p->x_max = p->map_proj[i][k][0];
			if (p->map_proj[i][k][0] < p->x_min)
				p->x_min = p->map_proj[i][k][0];
			p->map_proj[i][k][1] = scale * (k * cos(a + b) + k * cos(a - b) - 2 * z * sin(a) + i * sin(a + b) - i * sin(a - b)) / 2;
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
	unsigned int	x_offset;
	unsigned int	y_offset;

	i = 0;
	if (p->x_min < 0)
		p->x_max -= p->x_min;
	if (p->y_min < 0)
		p->y_max -= p->y_min;
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
	//moving proj to the center of the screen.
	x_offset = (1600 - p->x_max) / 2;
	y_offset = (800 - p->y_max) / 2;
	i = 0;
	while (i < p->x)
	{
		k = 0;
		while (k < p->y)
		{
			p->map_proj[i][k][0] += x_offset;
			p->map_proj[i][k][1] += y_offset;
			k++;
		}
		i++;
	}
}

void	print_proj(fdf_t_info *p)
{
	unsigned int	i;
	unsigned int	k;


	i = 0;
	while (i < p->x)
	{
		k = 0;
		while (k < p->y)
		{
			mlx_pixel_put(p->mp, p->wp, p->map_proj[i][k][0], p->map_proj[i][k][1], p->map_color[i][k]);
			con_dots(p, i, k);
			k++;
		}
		i++;
	}
}

int	proj(fdf_t_info *p, int v_rot, int h_rot)
{
	p->map_proj =  get_proj_slots(p);
	if (!p->map_proj)
		return (0);
	p->v_angle = v_rot;
	p->h_angle = h_rot;
	shoot_proj(p);
	if (p->x_min < 0 || p->y_min < 0)
		move_proj(p);
	mlx_clear_window(p->mp, p->wp);
	print_proj(p);
	return (1);
}
