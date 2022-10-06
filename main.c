// #include "./minilibx-linux/mlx.h"
#include "./mlx/mlx.h"
#include "./fdf.h"
#include "./libft_garage/libft/libft.h"
#include "./libft_garage/ft_printf/ft_printf.h"
#include <unistd.h>

void	init_p(fdf_t_info *p)
{
	p->mp = NULL;
	p->wp1 = NULL;
	p->x = 0;
	p->y = 0;
	p->x_max = 0;
	p->x_min = 0;
	p->y_max = 0;
	p->y_min = 0;
	p->map_cord = NULL;
	p->map_color = NULL;
	p->map_proj = NULL;
	p->map_size = 0;
}
// when considering map size, z axis must be reflected.
// we gotta rotate our view
// linear system needs improvement
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
	if (!p.mp)
		return (err());
	if (!p.wp1)
		return (err());
	if (!proj(&p))
		return (terminate(&p));
	//print_int_arr(p);
	mlx_loop(p.mp);
	mlx_destroy_window(p.mp, p.wp1);
	terminate(&p);
	return (0);
}