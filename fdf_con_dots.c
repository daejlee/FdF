#include "./fdf.h"
#include "./mlx/mlx.h"
#include <math.h>

typedef struct s_fdf_con_dot
{
	double			x_offset;
	double			y_offset;
	double			crit_offset;
	double			grad_color;
	double			grad;
}	t_fdf_con_dot;

void	init_d(t_fdf_con_dot *d, int *from, int *to, int *color_arr)
{
	d->x_offset = to[0] - from[0];
	d->y_offset = to[1] - from[1];
	if (!d->x_offset || !d->y_offset)
		d->grad = 0;
	else
		d->grad = d->y_offset / d->x_offset;
	if (fabs(d->y_offset) > fabs(d->x_offset))
	{
		d->crit_offset = d->y_offset;
		d->grad_color = (color_arr[1] - color_arr[0]) / d->y_offset;
		if (d->grad)
			d->grad = 1 / d->grad;
	}
	else
	{
		d->crit_offset = d->x_offset;
		d->grad_color = (color_arr[1] - color_arr[0]) / d->x_offset;
	}
}

void	dot_link(t_fdf_info *p, int *from, int *to, int *color_arr)
{
	t_fdf_con_dot	d;
	int				color;
	int				i;

	i = 0;
	init_d(&d, from, to, color_arr);
	while (i != d.crit_offset)
	{
		color = d.grad_color * i + color_arr[0];
		if (fabs(d.y_offset) > fabs(d.x_offset))
			mlx_pixel_put(p->mp, p->wp, d.grad * (from[1] + i)
				- d.grad * to[1] + to[0], from[1] + i, color);
		else
			mlx_pixel_put(p->mp, p->wp, from[0] + i, d.grad
				* (from[0] + i) - d.grad * to[0] + to[1], color);
		if (d.crit_offset < 0)
			i--;
		else
			i++;
	}
}

void	con_dots(t_fdf_info *p, unsigned int x, unsigned int y)
{
	int	color_arr[2];

	color_arr[0] = p->map_color[x][y];
	color_arr[1] = p->map_color[x + 1][y];
	if (x == p->x - 1 && y == p->y - 1) // 우하단
		return ;
	else if (y == p->y - 1) // 하단
	{
		dot_link(p, p->map_proj[x][y], p->map_proj[x + 1][y],
			color_arr);
	}
	else if (x == p->x - 1) // 우단
	{
		color_arr[1] = p->map_color[x][y +1];
		dot_link(p, p->map_proj[x][y], p->map_proj[x][y + 1],
			color_arr);
	}
	else
	{
		dot_link(p, p->map_proj[x][y], p->map_proj[x + 1][y],
			color_arr);
		color_arr[1] = p->map_color[x][y + 1];
		dot_link(p, p->map_proj[x][y], p->map_proj[x][y + 1],
			color_arr);
	}
}
