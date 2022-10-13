/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_put_panel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daejlee <daejlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 18:34:28 by daejlee           #+#    #+#             */
/*   Updated: 2022/10/13 18:34:28 by daejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "./libft_garage/libft/libft.h"
#include "./fdf.h"
#include "./mlx/mlx.h"

char	*ft_strjoin_m(char *s1, char *s2)
{
	int				i;
	unsigned int	s1_len;
	char			*res;

	if (!s1 || !s2)
		return (0);
	s1_len = ft_strlen(s1);
	res = (char *)malloc(sizeof(char) * (s1_len + ft_strlen(s2) + 1));
	if (res == 0)
		return (0);
	i = 0;
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		res[s1_len + i] = s2[i];
		i++;
	}
	res[s1_len + i] = '\0';
	free (s2);
	return (res);
}

int	purge_l(t_fdf_panel *l)
{
	if (l->map_name)
		free(l->map_name);
	if (l->x_size)
		free(l->x_size);
	if (l->y_size)
		free(l->y_size);
	if (l->x_offset)
		free(l->x_offset);
	if (l->y_offset)
		free(l->y_offset);
	if (l->map_zoom)
		free(l->map_zoom);
	if (l->h_rot_deg)
		free(l->h_rot_deg);
	if (l->v_rot_deg)
		free(l->v_rot_deg);
	if (l->z_zoom)
		free(l->z_zoom);
	return (0);
}

static int	init_l(t_fdf_panel *l, t_fdf_info *p)
{
	double	scale_ratio;

	scale_ratio = p->scale / p->init_scale;
	l->map_name = ft_strjoin("map name: ", p->map_name);
	l->x_size = ft_strjoin_m("x size: ", ft_itoa((int)p->x));
	l->y_size = ft_strjoin_m("y size: ", ft_itoa((int)p->y));
	l->x_offset = ft_strjoin_m("x_offset: ", ft_itoa(p->x_offset));
	l->y_offset = ft_strjoin_m("y_offset: ", ft_itoa(p->y_offset));
	l->map_zoom = ft_strjoin_m("map zoom rate: X", ft_itoa((int)scale_ratio));
	l->h_rot_deg = ft_strjoin_m("rotated deg(horizental): ", ft_itoa(p->h_angle));
	l->v_rot_deg = ft_strjoin_m("rotated deg(vertical): ", ft_itoa(p->v_angle));
	l->z_zoom = ft_strjoin_m("z zoom rate: ", ft_itoa((int)p->z_scale));
	if (!l->map_name || !l->x_size || !l->y_size || !l->x_offset
			|| !l->y_offset || !l->map_zoom || !l->h_rot_deg
			|| !l->v_rot_deg || !l->z_zoom)
		return (purge_l(l));
	else
		return (1);
}

void	put_panel(t_fdf_info *p)
{
	t_fdf_panel	*l;

	if (!init_l(p->l_addr, p))
		return ;
	l = p->l_addr;
	mlx_string_put(p->mp, p->wp, 50, 0, 10040319, "isometric view: 1");
	mlx_string_put(p->mp, p->wp, 50, 25, 10040319, "parallel view: 2 ~ 6");
	mlx_string_put(p->mp, p->wp, 300, 25, 10040319, "move map: keyboard cursors");
	mlx_string_put(p->mp, p->wp, 50, 50, 10040319, "rotate map: W A S D");
	mlx_string_put(p->mp, p->wp, 300, 50, 10040319, "zoom map: =, -, N, M");
	mlx_string_put(p->mp, p->wp, 50, 100, 10040319, l->map_name);
	mlx_string_put(p->mp, p->wp, 50, 125, 10040319, l->x_size);
	mlx_string_put(p->mp, p->wp, 50, 150, 10040319, l->y_size);
	mlx_string_put(p->mp, p->wp, 50, 175, 10040319, l->x_offset);
	mlx_string_put(p->mp, p->wp, 50, 200, 10040319, l->y_offset);
	mlx_string_put(p->mp, p->wp, 50, 225, 10040319, l->map_zoom);
	mlx_string_put(p->mp, p->wp, 50, 250, 10040319, l->h_rot_deg);
	mlx_string_put(p->mp, p->wp, 50, 275, 10040319, l->v_rot_deg);
	mlx_string_put(p->mp, p->wp, 50, 300, 10040319, l->z_zoom);
	purge_l(l);
}
