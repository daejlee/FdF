#include "./fdf.h"
// #include "./minilibx-linux/mlx.h"
#include "./mlx/mlx.h"
#include <math.h>

/*
. . .	우하단으로 선을 이어서 진행할거임.
. . .
. . .		아니 우단이랑 하단만 처리하면 되자나..
*/

void	dot_link(fdf_t_info *p, int *from, int *to, int from_color, int to_color)
{
	double			x_offset;
	double			y_offset;
	double			crit_offset;
	int				color;
	int				i;
	double			grad_color;
	double			grad;

	x_offset = to[0] - from[0];
	y_offset = to[1] - from[1];
	if (!x_offset || !y_offset)
		return ;
	i = 0;
	grad = y_offset / x_offset;
	if (fabs(y_offset) > fabs(x_offset))
	{
		crit_offset = y_offset;
		grad_color = (to_color - from_color) / y_offset;
		grad = 1 / grad;
	}
	else
	{
		crit_offset = x_offset;
		grad_color = (to_color - from_color) / x_offset;
	}
	while (i != crit_offset)
	{
		color = grad_color * i + from_color;
		//color = 16777215;
		if (fabs(y_offset) > fabs(x_offset))
			mlx_pixel_put(p->mp, p->wp1, grad * (from[1] + i) - grad * to[1] + to[0], from[1] + i, color);
		else
			mlx_pixel_put(p->mp, p->wp1, from[0] + i, grad * (from[0] + i) - grad * to[0] + to[1], color);
		if (crit_offset < 0)
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
