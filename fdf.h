#ifndef FDF_H
# define FDF_H

typedef struct s_fdf_info
{
	void			*mp;
	void			*wp1;
	unsigned int	row;
	unsigned int	col;
	int				**map_cord;
	int				**map_color;
}	fdf_t_info;

int			parse_arg(fdf_t_info *p, char **argv);
int			free_arr(char **arr);

# endif