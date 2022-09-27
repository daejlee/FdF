#include "./minilibx-linux/mlx.h"
#include "./minilibx-linux/mlx_int.h"

int	main()
{
	void	*mp;
	void	*wp1;
	unsigned int	i;

	mp = mlx_init();
	if (!mp)
		return (1);
	wp1 = mlx_new_window(mp, 1200, 900, "test");
	if (!wp1)
		return (1);
	i = 600;
	while (i < 800)
		mlx_pixel_put(mp, wp1, i++, 450, 16777215);
	mlx_string_put(mp, wp1, 620, 470, 16777215, "is this on air?\n");
	sleep(10);
	return (0);
}