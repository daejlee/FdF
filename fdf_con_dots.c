#include "./fdf.h"
#include "./minilibx-linux/mlx.h"
#include "./minilibx-linux/mlx_int.h"

/*
. . .	우하단으로 선을 이어서 진행할거임.
. . .
. . .		아니 우단이랑 하단만 처리하면 되자나..
*/

void	dot_link(fdf_t_info *p, int *from, int *to, int from_color, int to_color)
{
	double			x_offset;
	double			y_offset;
	int				color_offset;
	double			grad;
	int				temp;
	unsigned int	i;

	x_offset = to[0] - from[0];
	y_offset = to[1] - from[1];
	if (x_offset)
		grad = y_offset / x_offset;
	else
		grad = 0;
	i = 0;
	color_offset = to_color - from_color;
	while (i)
	{
		temp = to[0] + i;
		mlx_pixel_put(p->mp, p->wp1, temp, grad * (temp) + from[1], from_color);
		if (color_offset)
		{

		}
		i++;
	}
}

void	con_dots(fdf_t_info *p, unsigned int x, unsigned int y)
{
	if (y == p->y - 1) // 하단
		dot_link(p, p->map_proj[x][y], p->map_proj[x + 1][y], p->map_color[x][y], p->map_color[x + 1][y]);
	else if (x == p->x - 1) // 우단
		dot_link(p, p->map_proj[x][y], p->map_proj[x][y + 1], p->map_color[x][y], p->map_color[x][y + 1]);
	else if (x == p->x - 1 && y == p->y - 1) // 우하단
		return ;
	else
	{
		dot_link(p->map_proj[x][y], p->map_proj[x + 1][y], p->map_color[x][y], p->map_color[x + 1][y]);
		dot_link(p->map_proj[x][y], p->map_proj[x][y + 1], p->map_color[x][y], p->map_color[x][y + 1]);
	}
}