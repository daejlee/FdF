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
#include "./libft_garage/ft_printf/ft_printf.h"
#include <stdio.h>
#include <stdlib.h>

void	init_p(t_fdf_info *p)
{
	p->map_name = NULL;
	p->mp = NULL;
	p->wp = NULL;
	p->v_angle = 0;
	p->h_angle = 0;
	p->z_scale = 1;
	p->scale = 0;
	p->x = 0;
	p->y = 0;
	p->z_max = 0;
	p->x_max = 0;
	p->x_min = 0;
	p->y_max = 0;
	p->y_min = 0;
	p->map_cord = NULL;
	p->map_color = NULL;
	p->map_proj = NULL;
	p->map_size = 0;
	p->x_offset = 0;
	p->y_offset = 0;
}

int	err(void)
{
	perror("fdf error :");
	return (1);
}

int	terminate(t_fdf_info *p)
{
	unsigned int	i;

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
	return (0);
}

void	print_int_arr(t_fdf_info p)
{
	unsigned int	i;
	unsigned int	k;

	i = 0;
	while (i < p.y)
	{
		k = 0;
		while (k < p.x)
			ft_printf("%i ", p.map_cord[k++][i]);
		ft_printf("\n");
		i++;
	}
	ft_printf("---------------------------------------------------------------\n");
	i = 0;
	while (i < p.y)
	{
		k = 0;
		while (k < p.x)
			ft_printf("%i ", p.map_color[k++][i]);
		ft_printf("\n");
		i++;
	}
	ft_printf("---------------------------------------------------------------\n");
	i = 0;
	while (i < p.y)
	{
		k = 0;
		while (k < p.x)
		{
			ft_printf("%i,", p.map_proj[k][i][0]);
			ft_printf("%i ", p.map_proj[k++][i][1]);
		}
		ft_printf("\n");
		i++;
	}
	ft_printf("---------------------------------------------------------------\n");
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
