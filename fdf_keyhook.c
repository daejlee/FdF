#include "./mlx/mlx.h"
#include "./fdf.h"
#include "./libft_garage/ft_printf/ft_printf.h"

void	kh_turn_perspective(int keycode, fdf_t_info *p)
{
	int	prev_h;
	int	prev_v;

	prev_h = p->h_angle;
	prev_v = p->v_angle;
	free_tri_arr(p);
	if (keycode == 18) //X
		proj(p, 55, -45);
	else if (keycode == 19) //Z
		proj(p, 0, 0);
	else if (keycode == 20) //W
		proj(p, prev_v + 90, prev_h);
	else if (keycode == 21) //S
		proj(p, prev_v - 90, prev_h);
	else if (keycode == 23) //A
		proj(p, prev_v, prev_h - 90);
	else if (keycode == 22) //D
		proj(p, prev_v, prev_h + 90);
}

void	kh_move_perspective(int keycode, fdf_t_info *p)
{
	int				prev_h;
	int				prev_v;
	unsigned int	i;
	unsigned int	k;
	int				x_offset;
	int				y_offset;

	prev_h = p->h_angle;
	prev_v = p->v_angle;
	x_offset = 0;
	y_offset = 0;
	if (keycode == 126) //Up
		y_offset = 100;
	else if (keycode == 125) //Down
		y_offset = -100;
	else if (keycode == 123) //Left
		x_offset = -100;
	else if (keycode == 124) //Right
		x_offset = 100;
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
	mlx_clear_window(p->mp, p->wp);
	print_proj(p);
}

int	key_hook(int keycode, fdf_t_info *p)
{
	int	prev_h;
	int	prev_v;

	prev_h = p->h_angle;
	prev_v = p->v_angle;
	ft_printf("keycode is %i.\n", keycode);
	if (keycode == 53) //ESC
		mlx_destroy_window(p->mp, p->wp);
	else if (keycode == 7 || keycode == 6 || keycode == 13
			|| keycode == 1 || keycode == 0 || keycode == 2)
		kh_turn_perspective(keycode, p);
	else if (keycode <= 126 && keycode >= 123)
		kh_move_perspective(keycode, p);
//	else if (ROTATE)
//		kh_rotate_perspective(keycode, p);
	return (0);
}
