/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daejlee <daejlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 18:34:43 by daejlee           #+#    #+#             */
/*   Updated: 2022/10/13 18:34:43 by daejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "./mlx/mlx.h"
#include "./fdf.h"
#include "./libft_garage/libft/libft.h"
#include "./libft_garage/ft_printf/ft_printf.h"
#include <unistd.h>

enum
{
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

/*
	N
 z ----->x
 | 0 0 0 0
W| 0 1 1 0 E
 | 0 0 0 0
 | 0 0 0 0
 y	S
*/
int	terminate(t_fdf_info *p)
{
	unsigned int	i;

	mlx_destroy_window(p->mp, p->wp);
	i = 0;
	if (p->map_cord)
	{
		while (i < p->x)
			free (p->map_cord[i++]);
		free (p->map_cord);
	}
	i = 0;
	if (p->map_color)
	{
		while (i < p->x)
			free (p->map_color[i++]);
		free (p->map_color);
	}
	system("leaks fdf");
	exit (0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_fdf_info	p;
	t_fdf_panel	l;

	if (argc == 1)
		return (0);
	init_p(&p, &l);
	if (argc != 2 || !parse_arg(&p, argv))
		return (err());
	p.mp = mlx_init();
	p.wp = mlx_new_window(p.mp, 1600, 900, "fdf");
	if (!p.mp || !p.wp)
		return (err());
	if (p.x >= p.y)
		p.map_size = p.x;
	else
		p.map_size = p.y;
	p.map_size += p.z_max;
	p.scale = 900 / (double)p.map_size;
	p.init_scale = p.scale;
	proj(&p, 55, -45);
	mlx_hook(p.wp, ON_DESTROY, 0, terminate, &p);
	mlx_hook(p.wp, ON_KEYDOWN, 0, key_hook, &p);
	mlx_loop(p.mp);
	return (0);
}
