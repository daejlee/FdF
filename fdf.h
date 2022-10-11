#ifndef FDF_H
# define FDF_H

typedef struct s_fdf_info
{
	void			*mp;
	void			*wp;
	int				v_angle;
	int				h_angle;
	double			v_rad;
	double			h_rad;
	double			z_scale;
	double			scale;
	unsigned int	x;
	unsigned int	y;
	int				z_max;
	int				x_max;
	int				x_min;
	int				y_max;
	int				y_min;
	int				**map_cord;
	int				**map_color;
	int				***map_proj; 
	unsigned int	map_size;
}	fdf_t_info;

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

int			parse_arg(fdf_t_info *p, char **argv);
int			free_arr(char **arr);
void		init_p(fdf_t_info *p);
int			err(void);
int			terminate(fdf_t_info *p);
void		print_int_arr(fdf_t_info p);
int			proj(fdf_t_info *p, int v_rot, int h_rot);
void		*free_tri_arr(fdf_t_info *p);
void		con_dots(fdf_t_info *p, unsigned int x, unsigned int y);
void		print_proj(fdf_t_info *p);
int			key_hook(int keycode, fdf_t_info *p);

# endif