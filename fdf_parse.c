/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daejlee <daejlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 18:34:12 by daejlee           #+#    #+#             */
/*   Updated: 2022/10/13 18:34:12 by daejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "./libft_garage/gnl/get_next_line.h"
#include "./libft_garage/libft/libft.h"
#include "./fdf.h"
#include <fcntl.h>
#include <unistd.h>

static void	get_map_b_seg(t_fdf_info *p, char **temp, unsigned int i)
{
	unsigned int	k;

	k = 0;
	while (k < p->x)
	{
		if (ft_strchr(temp[k], '\n'))
			*ft_strchr(temp[k], '\n') = '\0';
		if (ft_strchr(temp[k], ','))
		{
			p->map_color[k][i] = get_rgb_val(ft_strchr(temp[k], ',') + 1);
			*ft_strchr(temp[k], ',') = '\0';
		}
		else
			p->map_color[k][i] = 16777215;
		p->map_cord[k][i] = ft_atoi(temp[k]);
		if (p->map_cord[k][i] > p->z_max)
			p->z_max = p->map_cord[k][i];
		k++;
	}
}

static void	get_map_a_seg(t_fdf_info *p, int fd)
{
	char			**temp;
	char			*gnl_temp;
	unsigned int	i;

	i = 0;
	while (i < p->y)
	{
		gnl_temp = get_next_line(fd);
		temp = ft_split(gnl_temp, ' ');
		if (gnl_temp)
			free (gnl_temp);
		if (!temp)
		{
			free_arr((char **)p->map_color);
			free_arr((char **)p->map_cord);
			return ;
		}
		get_map_b_seg(p, temp, i);
		i++;
		free_arr(temp);
	}
}

static int	get_map(t_fdf_info *p, char *filename, int fd)
{
	p->map_cord = get_slots(p);
	p->map_color = get_slots(p);
	if (!p->map_cord || !p->map_color)
	{
		if (p->map_cord)
			free (p->map_cord);
		if (p->map_color)
			free (p->map_color);
	}
	close(fd);
	fd = open(filename, O_RDONLY);
	get_map_a_seg(p, fd);
	return (1);
}

int	parse_arg(t_fdf_info *p, char **argv)
{
	int		fd;
	char	**temp;
	char	*gnl_temp;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (0);
	gnl_temp = get_next_line(fd);
	temp = ft_split(gnl_temp, ' ');
	if (!temp)
		return (0);
	p->x = get_col_count(temp);
	p->y = 0;
	free_arr(temp);
	while (gnl_temp)
	{
		free(gnl_temp);
		gnl_temp = get_next_line(fd);
		p->y += 1;
	}
	if (!get_map(p, argv[1], fd))
		return (0);
	p->map_name = argv[1];
	return (1);
}
