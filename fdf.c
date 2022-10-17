/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
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

static void	init_p(t_fdf_info *p)
{
	p->map_name = NULL;
	p->mp = NULL;
	p->wp = NULL;
	p->v_angle = 0;
	p->h_angle = 0;
	p->z_scale = 1;
	p->scale = 0;
	p->x = 0;
	p->y = 0;
	p->z_max = 0;
	p->x_max = 0;
	p->x_min = 0;
	p->y_max = 0;
	p->y_min = 0;
	p->map_cord = NULL;
	p->map_color = NULL;
	p->map_proj = NULL;
	p->map_size = 0;
	p->x_offset = 0;
	p->y_offset = 0;
}

static int	prep_mlx(t_fdf_info *p)
{
	p->mp = mlx_init();
	p->wp = mlx_new_window(p->mp, 1600, 900, "fdf");
	if (!p->mp || !p->wp)
		return (0);
	if (p->x >= p->y)
		p->map_size = p->x;
	else
		p->map_size = p->y;
	p->map_size += p->z_max;
	p->scale = 900 / (double)p->map_size;
	p->init_scale = p->scale;
	return (1);
}

int	main(int argc, char **argv)
{
	t_fdf_info	p;

	if (argc == 1)
		return (0);
	init_p(&p);
	if (argc != 2 || !parse_arg(&p, argv))
		return (err());
	if (!prep_mlx(&p))
		return (err());
	proj(&p, 55, -45);
	mlx_hook(p.wp, ON_DESTROY, 0, terminate, &p);
	mlx_hook(p.wp, ON_KEYDOWN, 0, key_hook, &p);
	mlx_loop(p.mp);
	return (0);
}
