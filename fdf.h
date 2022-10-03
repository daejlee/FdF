#ifndef FDF_H
# define FDF_H

typedef struct s_fdf_info
{
	void			*mp;
	void			*wp1;
	unsigned int	x;
	unsigned int	y;
	int				**map_cord;
	int				**map_color;
	int				***map_proj;
}	fdf_t_info;

int			parse_arg(fdf_t_info *p, char **argv);
int			free_arr(char **arr);
int			err(void);
int			terminate(fdf_t_info *p);
void		print_int_arr(fdf_t_info p);
int			get_projection(fdf_t_info *p);

# endif