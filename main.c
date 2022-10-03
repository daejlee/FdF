#include "./minilibx-linux/mlx.h"
#include "./minilibx-linux/mlx_int.h"
#include "./fdf.h"
#include "./libft_garage/libft/libft.h"
#include "./libft_garage/ft_printf/ft_printf.h"

int	main(int argc, char **argv)
{
	unsigned int	i;
	fdf_t_info	p;

	if (argc == 1)
		return (0);
	if (!parse_arg(&p, argv))
		return (err());
	print_int_arr(p);
	p.mp = mlx_init();
	if (!p.mp)
		return (err());
	p.wp1 = mlx_new_window(p.mp, 1200, 900, "test");
	if (!p.wp1)
		return (err());
	i = 600;
	while (i < 800)
		mlx_pixel_put(p.mp, p.wp1, i++, 450, 16777215);
	mlx_string_put(p.mp, p.wp1, 620, 470, 16777215, "is this on air?\n");
	//sleep(10);
	mlx_destroy_window(p.mp, p.wp1);
	terminate(&p);
	return (0);
}