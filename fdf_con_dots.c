#include "./fdf.h"
// #include "./minilibx-linux/mlx.h"
#include "./mlx/mlx.h"
#include <math.h>

/*
. . .	우하단으로 선을 이어서 진행할거임.
. . .
. . .		아니 우단이랑 하단만 처리하면 되자나..
*/
/*
void	no_x_offset(fdf_t_info *p, int x, int from_y, int to_y)
{
	int	i;
	int	y_offset;

	i = 0;
	y_offset = to_y - from_y;
	while (from_y != to_y)
	{
		get_grad_color(x, )
		mlx_pixel_put(p->mp, p->wp1, x, from_y, )
	}
}

void	x_crit_offset(fdf_t_info *p, int grad, double x_offset, int from_color, int to_color, int *from, int *to)
{
	int				color;
	int				i;
	double			grad_color;

	i = 0;
	grad_color = (to_color - from_color) / x_offset;
	while (i != x_offset)
	{
		color = grad_color * i - grad_color * i + from_color;
		mlx_pixel_put(p->mp, p->wp1,
		from[0] + i,
		grad * (from[0] + i) - grad * to[0] + to[1],
		color);
		if (x_offset < 0)
			i--;
		else
			i++;
	}
}

void	y_crit_offset(fdf_t_info *p, int grad, double y_offset, int from_color, int to_color, int *from, int *to)
{
	int				color;
	int				i;
	double			grad_color;

	i = 0;
	grad_color = (to_color - from_color) / y_offset;
	while (i != y_offset)
	{
		color = grad_color * i - grad_color * i + from_color;
		mlx_pixel_put(p->mp, p->wp1,
		grad * (from[1] + i) - grad * to[1] + to[0],
		from[1] + i,
		color);
		if (y_offset < 0)
			i--;
		else
			i++;
	}
}

void	dot_link(fdf_t_info *p, int *from, int *to, int from_color, int to_color)
{
	double			x_offset;
	double			y_offset;

	x_offset = to[0] - from[0];
	y_offset = to[1] - from[1];
	if (!x_offset || !y_offset)
		return ;
	//if (fabs(x_offset) > fabs(y_offset))
		x_crit_offset(p, y_offset / x_offset, x_offset, from_color, to_color, from, to);
	//else
		//y_crit_offset(p, x_offset / y_offset, y_offset, from_color, to_color, from, to);
}
*/

void	dot_link(fdf_t_info *p, int *from, int *to, int from_color, int to_color)
{
	double			x_offset;
	double			y_offset;
	int				color;
	double			grad;
	int				i;
	double			grad_color;

	x_offset = to[0] - from[0];
	y_offset = to[1] - from[1];
	if (!x_offset)
		return ;
	grad = y_offset / x_offset;
	i = 0;
	grad_color = (to_color - from_color) / x_offset;
	while (i != x_offset)
	{
		color = grad_color * i - grad_color * i + from_color;
		mlx_pixel_put(p->mp, p->wp1,
		from[0] + i,
		grad * (from[0] + i) - grad * to[0] + to[1],
		color);
		if (x_offset < 0)
			i--;
		else
			i++;
	}
}

void	con_dots(fdf_t_info *p, unsigned int x, unsigned int y)
{
	if (x == p->x - 1 && y == p->y - 1) // 우하단
		return ;
	else if (y == p->y - 1) // 하단
		dot_link(p, p->map_proj[x][y], p->map_proj[x + 1][y],
				p->map_color[x][y], p->map_color[x + 1][y]);
	else if (x == p->x - 1) // 우단
		dot_link(p, p->map_proj[x][y], p->map_proj[x][y + 1],
				p->map_color[x][y], p->map_color[x][y + 1]); 
	else
	{
		dot_link(p, p->map_proj[x][y], p->map_proj[x + 1][y],
				p->map_color[x][y], p->map_color[x + 1][y]);
		dot_link(p, p->map_proj[x][y], p->map_proj[x][y + 1],
				p->map_color[x][y], p->map_color[x][y + 1]);
	}
}
