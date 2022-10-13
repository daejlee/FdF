/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_proj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daejlee <daejlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 18:34:23 by daejlee           #+#    #+#             */
/*   Updated: 2022/10/13 18:34:24 by daejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "./fdf.h"
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

static void	shoot_proj(t_fdf_info *p)
{
	unsigned int	i;
	unsigned int	k;
	int				z;

	i = 0;
	init_range(p);
	while (i < p->x)
	{
		k = 0;
		while (k < p->y)
		{
			z = p->map_cord[i][k] * p->z_scale;
			p->map_proj[i][k][0] = (cos(p->h_rad) * i
					- sin(p->h_rad) * k) * p->scale;
			p->map_proj[i][k][1] = p->scale
				* (k * cos(p->v_rad + p->h_rad) + k
					* cos(p->v_rad - p->h_rad) - 2 * z * sin(p->v_rad) + i
					* sin(p->v_rad + p->h_rad) - i
					* sin(p->v_rad - p->h_rad)) / 2;
			renew_range(p, p->map_proj[i][k][0], p->map_proj[i][k][1]);
			k++;
		}
		i++;
	}
}

static void	move_proj_to_center(t_fdf_info *p)
{
	unsigned int	i;
	unsigned int	k;
	unsigned int	x_offset;
	unsigned int	y_offset;

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

static void	move_proj(t_fdf_info *p)
{
	unsigned int	i;
	unsigned int	k;

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
}

void	print_proj(t_fdf_info *p)
{
	unsigned int	i;
	unsigned int	k;

	mlx_clear_window(p->mp, p->wp);
	put_panel(p);
	i = 0;
	while (i < p->x)
	{
		k = 0;
		while (k < p->y)
		{
			mlx_pixel_put(p->mp, p->wp, p->map_proj[i][k][0],
				p->map_proj[i][k][1], p->map_color[i][k]);
			con_dots(p, i, k);
			k++;
		}
		i++;
	}
}

int	proj(t_fdf_info *p, int v_rot, int h_rot)
{
	p->map_proj = get_proj_slots(p);
	if (!p->map_proj)
		return (0);
	p->v_angle = v_rot;
	p->h_angle = h_rot;
	p->v_rad = v_rot * (PI / 180);
	p->h_rad = h_rot * (PI / 180);
	shoot_proj(p);
	if (p->x_min < 0 || p->y_min < 0)
		move_proj(p);
	move_proj_to_center(p);
	print_proj(p);
	return (1);
}
