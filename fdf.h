/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daejlee <daejlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 18:42:00 by daejlee           #+#    #+#             */
/*   Updated: 2022/10/13 18:42:10 by daejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef FDF_H
# define FDF_H

typedef struct s_fdf_info
{
	char			*map_name;
	void			*mp;
	void			*wp;
	int				v_angle;
	int				h_angle;
	double			v_rad;
	double			h_rad;
	double			z_scale;
	double			init_scale;
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
	int				x_offset;
	int				y_offset;
}	t_fdf_info;


int			parse_arg(t_fdf_info *p, char **argv);
int			get_col_count(char **temp);
int			**get_slots(t_fdf_info *p);
int			get_rgb_val(char *str);
int			free_arr(char **arr);
void		init_p(t_fdf_info *p);
int			err(void);
int			terminate(t_fdf_info *p);
void		print_int_arr(t_fdf_info p);
int			proj(t_fdf_info *p, int v_rot, int h_rot);
void		*free_tri_arr(t_fdf_info *p);
void		con_dots(t_fdf_info *p, unsigned int x, unsigned int y);
void		print_proj(t_fdf_info *p);
int			key_hook(int keycode, t_fdf_info *p);
int			***get_proj_slots(t_fdf_info *p);
void		init_range(t_fdf_info *p);
void		renew_range(t_fdf_info *p, int x, int y);
void		put_panel(t_fdf_info *p);

#endif
