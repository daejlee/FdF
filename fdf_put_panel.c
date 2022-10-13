#include "./libft_garage/libft/libft.h"
#include "./fdf.h"
#include "./mlx/mlx.h"

typedef struct s_fdf_panel
{
	char	*map_name;
	char	*x_size;
	char	*y_size;
	char	*x_offset;
	char	*y_offset;
	char	*map_zoom;
	char	*h_rot_deg;
	char	*v_rot_deg;
	char	*z_zoom;
	char	*rot_how;
	char	*map_zoom_how;
	char	*z_zoom_how;
}	t_fdf_panel;

static int	init_l(t_fdf_panel *l, t_fdf_info *p)
{
	double	scale_ratio;

	scale_ratio = p->scale / p->init_scale;
	l->map_name = ft_strjoin("map name: ", p->map_name);
	l->x_size = ft_strjoin("x size: ", ft_itoa((int)p->x));
	l->y_size = ft_strjoin("y size: ", ft_itoa((int)p->y));
	l->x_offset = ft_strjoin("x_offset: ", ft_itoa(p->x_offset));
	l->y_offset = ft_strjoin("y_offset: ", ft_itoa(p->y_offset));
	l->map_zoom = ft_strjoin("map zoom rate: X", ft_itoa((int)scale_ratio));
	l->h_rot_deg = ft_strjoin("rotated deg(horizental): ", ft_itoa(p->h_angle));
	l->v_rot_deg = ft_strjoin("rotated deg(vertical): ", ft_itoa(p->v_angle));
	l->z_zoom = ft_strjoin("z zoom rate: ", ft_itoa((int)p->z_scale));
	// if (err)
	// 	return (0);
	// else
	return (1);
}

void	put_panel(t_fdf_info *p)
{
	t_fdf_panel	l;

	if (!init_l(&l, p))
		return ;
	mlx_string_put(p->mp, p->wp, 50, 0, 10040319, "isometric view: 1");
	mlx_string_put(p->mp, p->wp, 50, 25, 10040319, "parallel view: 2 ~ 6");
	mlx_string_put(p->mp, p->wp, 300, 25, 10040319, "move map: keyboard cursors");
	mlx_string_put(p->mp, p->wp, 50, 50, 10040319, "rotate map: W A S D");
	mlx_string_put(p->mp, p->wp, 300, 50, 10040319, "zoom map: =, -, N, M");
	mlx_string_put(p->mp, p->wp, 50, 100, 10040319, l.map_name);
	mlx_string_put(p->mp, p->wp, 50, 125, 10040319, l.x_size);
	mlx_string_put(p->mp, p->wp, 50, 150, 10040319, l.y_size);
	mlx_string_put(p->mp, p->wp, 50, 175, 10040319, l.x_offset);
	mlx_string_put(p->mp, p->wp, 50, 200, 10040319, l.y_offset);
	mlx_string_put(p->mp, p->wp, 50, 225, 10040319, l.map_zoom);
	mlx_string_put(p->mp, p->wp, 50, 250, 10040319, l.h_rot_deg);
	mlx_string_put(p->mp, p->wp, 50, 275, 10040319, l.v_rot_deg);
	mlx_string_put(p->mp, p->wp, 50, 300, 10040319, l.z_zoom);
}