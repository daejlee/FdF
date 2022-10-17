/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_keyhook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daejlee <daejlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 18:34:08 by daejlee           #+#    #+#             */
/*   Updated: 2022/10/13 18:34:09 by daejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "./mlx/mlx.h"
#include "./fdf.h"

enum
{
	ONE = 18,
	TWO = 19,
	THREE = 20,
	FOUR = 21,
	FIVE = 23,
	SIX = 22,
	UP = 125,
	DOWN = 126,
	LEFT = 123,
	RIGHT = 124,
	A = 0,
	D = 2,
	W = 13,
	S = 1,
	ESC = 53,
	N = 46,
	M = 45,
	PLUS = 24,
	MINUS = 27
};

# ifndef LINUX
#  define LINUX
#  define KEY_A	0
#  define KEY_S	1
#  define KEY_D 2
#  define KEY_Q	12
#  define KEY_W	13
#  define KEY_E	14
#  define KEY_UP	126
#  define KEY_DOWN	125
#  define KEY_LEFT	123
#  define KEY_RIGHT 124
#  define KEY_ESC	53
# else
#  define KEY_UP	65362
#  define KEY_DOWN	65364
#  define KEY_LEFT	65361
#  define KEY_RIGHT	65363
#  define KEY_ESC	65307
# endif

void	kh_turn_view(int keycode, t_fdf_info *p)
{
	int	prev_h;
	int	prev_v;

	prev_h = p->h_angle;
	prev_v = p->v_angle;
	free_tri_arr(p);
	if (keycode == ONE)
		proj(p, 55, -45);
	else if (keycode == TWO)
		proj(p, 0, 0);
	else if (keycode == THREE)
		proj(p, 90, 0);
	else if (keycode == FOUR)
		proj(p, 90, 180);
	else if (keycode == FIVE)
		proj(p, 90, 90);
	else if (keycode == SIX)
		proj(p, 90, -90);
}

void	kh_get_offset(int keycode, int *x_offset, int *y_offset)
{
	if (keycode == UP)
		*y_offset = 100;
	else if (keycode == DOWN)
		*y_offset = -100;
	else if (keycode == LEFT)
		*x_offset = -100;
	else if (keycode == RIGHT)
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
	if (keycode == A)
		proj(p, prev_v, prev_h + 5);
	else if (keycode == D)
		proj(p, prev_v, prev_h - 5);
	else if (keycode == W)
		proj(p, prev_v + 5, prev_h);
	else if (keycode == S)
		proj(p, prev_v - 5, prev_h);
}

int	key_hook(int keycode, t_fdf_info *p)
{
	if (keycode == ESC)
		terminate(p);
	else if (keycode >= ONE && keycode <= FIVE)
		kh_turn_view(keycode, p);
	else if (keycode <= DOWN && keycode >= LEFT)
		kh_move_view(keycode, p);
	else if (keycode == A || keycode == D || keycode == W || keycode == S)
		kh_rot_view(keycode, p);
	else if (keycode == N || keycode == M || keycode == PLUS
		|| keycode == MINUS)
	{
		if (keycode == N)
			p->z_scale *= 2;
		else if (keycode == M)
			p->z_scale *= 0.5;
		else if (keycode == PLUS)
			p->scale *= 2;
		else
			p->scale *= 0.5;
		free_tri_arr(p);
		proj(p, p->v_angle, p->h_angle);
	}
	return (0);
}
