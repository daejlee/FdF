// #include "./minilibx-linux/mlx.h"
#include "./mlx/mlx.h"
#include "./fdf.h"
#include "./libft_garage/libft/libft.h"
#include "./libft_garage/ft_printf/ft_printf.h"
#include <unistd.h>

/*
starting view / scale configure
 -> For now, scale itself is a bit small.
 we can just adjust starting point to the middle of the screen. DONE

parallel projection
-> E, W, S, N, Z. DONE

// zoom in / out
// manipulate z scale
// map rotation
// simple UI

	N
 z ----->x
 | 0 0 0 0
W| 0 1 1 0 E
 | 0 0 0 0
 | 0 0 0 0
 y	S
*/

int	render_frame(fdf_t_info *p, int v_rot, int h_rot)
{
	
	if (!proj(p, v_rot, h_rot))
		return (0);
	else
		return (1);
}

int	mouse_hook(int mouse_code, fdf_t_info *p)
{
	double	prev_scale;

	prev_scale = p->scale;
	mlx_clear_window(p->mp, p->wp);
	ft_printf("keycode is %i.\n", mouse_code);
	if (mouse_code == 3)
		p->scale = 900 / (double)p->map_size;
	else if (mouse_code == 4)
		p->scale *= 10;
	else if (mouse_code == 5)
		p->scale *= 0.1;
	else
		return (1);
	proj(p, p->v_angle, p->h_angle);
	return (0);
}

int	main(int argc, char **argv)
{
	fdf_t_info	p;

	if (argc == 1)
		return (0);
	init_p(&p);
	if (argc != 2 || !parse_arg(&p, argv))
		return (err());
	p.mp = mlx_init();
	p.wp = mlx_new_window(p.mp, 1600, 900, "test");
	if (!p.mp || !p.wp)
		return (err());
	if (p.x >= p.y)
		p.map_size = p.x;
	else
		p.map_size = p.y;
	p.map_size += p.z_max;
	p.scale = 900 / (double)p.map_size;
	proj(&p, 55, -45);
	//mlx_loop_hook(p.mp, render_frame, &p);
	mlx_key_hook(p.wp, key_hook, &p);
	//mlx_mouse_hook(p.wp, mouse_hook, &p);
	mlx_hook(p.wp, 17, 1L<<0, mlx_destroy_window, &p);
	mlx_loop(p.mp);
	terminate(&p);
	return (0);
}