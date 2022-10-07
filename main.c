// #include "./minilibx-linux/mlx.h"
#include "./mlx/mlx.h"
#include "./fdf.h"
#include "./libft_garage/libft/libft.h"
#include "./libft_garage/ft_printf/ft_printf.h"
#include <unistd.h>

int	key_hook(int keycode, fdf_t_info *p)
{
	ft_printf("keycode is %i.\n", keycode);
	if (keycode == 53)
		mlx_destroy_window(p->mp, p->wp1);
	else if (keycode == )
	return (0);
}

int	render_frame(fdf_t_info *p)
{
	proj(&p);
}

int	main(int argc, char **argv)
{
	fdf_t_info	p;

	if (argc == 1)
		return (0);
	init_p(&p);
	if (!parse_arg(&p, argv))
		return (err());
	p.mp = mlx_init();
	p.wp1 = mlx_new_window(p.mp, 1600, 900, "test");
	if (!p.mp || !p.wp1)
		return (err());
	mlx_loop_hook(p.mp, render_frame, &p);
	mlx_loop(p.mp);
	mlx_hook(p.wp1, ON_KEYDOWN, 1L<<0, key_hook, &p);
	terminate(&p);
	return (0);
}