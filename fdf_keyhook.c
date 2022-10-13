#include "./mlx/mlx.h"
#include "./fdf.h"
#include "./libft_garage/ft_printf/ft_printf.h"

void	kh_turn_view(int keycode, t_fdf_info *p)
{
	int	prev_h;
	int	prev_v;

	prev_h = p->h_angle;
	prev_v = p->v_angle;
	free_tri_arr(p);
	if (keycode == 18) //1
		proj(p, 55, -45);
	else if (keycode == 19) //2 Above
		proj(p, 0, 0);
	else if (keycode == 20) //3 S
		proj(p, 90, 0);
	else if (keycode == 21) //4 N
		proj(p, 90, 180);
	else if (keycode == 23) //5 E
		proj(p, 90, 90);
	else if (keycode == 22) //6 W
		proj(p, 90, -90);
}

void	kh_get_offset(int keycode, int *x_offset, int *y_offset)
{
	if (keycode == 125) //Up cursor
		*y_offset = 100;
	else if (keycode == 126) //Down cursor
		*y_offset = -100;
	else if (keycode == 123) //Left cursor
		*x_offset = -100;
	else if (keycode == 124) //Right cursor
		*x_offset = 100;
}

void	kh_move_view(int keycode, t_fdf_info *p)
{
	unsigned int	i;
	unsigned int	k;
	int				x_offset;
	int				y_offset;

	x_offset = 0;
	y_offset = 0;
	kh_get_offset(keycode, &x_offset, &y_offset);
	i = 0;
	while (i < p->x)
	{
		k = 0;
		while (k < p->y)
		{
			p->map_proj[i][k][0] += x_offset;
			p->map_proj[i][k++][1] += y_offset;
		}
		i++;
	}
	p->x_offset += x_offset;
	p->y_offset += y_offset;
	print_proj(p);
}

void	kh_rot_view(int keycode, t_fdf_info *p)
{
	int	prev_h;
	int	prev_v;

	prev_h = p->h_angle;
	prev_v = p->v_angle;
	free_tri_arr(p);
	if (keycode == 0) //A
		proj(p, prev_v, prev_h + 5);
	else if (keycode == 2) //D
		proj(p, prev_v, prev_h - 5);
	else if (keycode == 13) //W
		proj(p, prev_v + 5, prev_h);
	else if (keycode == 1) //S
		proj(p, prev_v - 5, prev_h);
}

int	key_hook(int keycode, t_fdf_info *p)
{
	ft_printf("keycode is %i.\n", keycode);
	if (keycode == 53) //ESC
		mlx_destroy_window(p->mp, p->wp);
	else if (keycode >= 18 && keycode <= 23)
		kh_turn_view(keycode, p);
	else if (keycode <= 126 && keycode >= 123)
		kh_move_view(keycode, p);
	else if (keycode == 0 || keycode == 2 || keycode == 13 || keycode == 1)
		kh_rot_view(keycode, p);
	else if (keycode == 45 || keycode == 46 || keycode == 24 || keycode == 27)// N, M, +, -
	{
		if (keycode == 46) //N
			p->z_scale *= 2;
		else if (keycode == 45) //M
			p->z_scale *= 0.5;
		else if (keycode == 24) //+
			p->scale *= 2;
		else //-
			p->scale *= 0.5;
		proj(p, p->v_angle, p->h_angle);
	}
	return (0);
}
