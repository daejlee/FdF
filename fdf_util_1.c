/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_util_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daejlee <daejlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 18:34:31 by daejlee           #+#    #+#             */
/*   Updated: 2022/10/13 18:34:33 by daejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "./fdf.h"
#include "./mlx/mlx.h"
#include "./libft_garage/ft_printf/ft_printf.h"
#include <stdio.h>
#include <stdlib.h>

int	err(void)
{
	perror("fdf error :");
	return (1);
}

int	terminate(t_fdf_info *p)
{
	unsigned int	i;

	mlx_destroy_window(p->mp, p->wp);
	i = 0;
	if (p->map_cord)
	{
		while (i < p->x)
			free (p->map_cord[i++]);
		free (p->map_cord);
	}
	i = 0;
	if (p->map_color)
	{
		while (i < p->x)
			free (p->map_color[i++]);
		free (p->map_color);
	}
	exit (0);
	return (0);
}

int	free_arr(char **arr)
{
	unsigned int	i;

	i = 0;
	while (arr[i])
		free (arr[i++]);
	free (arr);
	return (0);
}

void	*free_tri_arr(t_fdf_info *p)
{
	unsigned int	i;
	unsigned int	k;

	i = 0;
	while (i < p->x)
	{
		k = 0;
		while (k < p->y)
			free (p->map_proj[i][k++]);
		free (p->map_proj[i]);
		i++;
	}
	free (p->map_proj);
	return (0);
}
