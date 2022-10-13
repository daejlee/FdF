/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_util_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daejlee <daejlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 18:34:36 by daejlee           #+#    #+#             */
/*   Updated: 2022/10/13 18:34:37 by daejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "./fdf.h"
#include <stdlib.h>

int	***get_proj_slots(t_fdf_info *p)
{
	int				***ret;
	unsigned int	i;
	unsigned int	k;

	ret = (int ***)malloc(sizeof (int *) * (p->x));
	if (!ret)
		return (NULL);
	i = 0;
	while (i < p->x)
	{
		ret[i] = (int **)malloc(sizeof (int *) * p->y);
		if (!ret[i])
		{
			free_arr((char **)ret);
			return (NULL);
		}
		k = 0;
		while (k < p->y)
		{
			ret[i][k] = (int *)malloc(sizeof (int) * 2);
			if (!ret[i][k++])
				return (free_tri_arr(p));
		}
		i++;
	}
	return (ret);
}

void	init_range(t_fdf_info *p)
{
	p->x_max = 0;
	p->x_min = 0;
	p->y_max = 0;
	p->y_min = 0;
}

void	renew_range(t_fdf_info *p, int x, int y)
{
	if (x > p->x_max)
		p->x_max = x;
	if (x < p->x_min)
		p->x_min = x;
	if (y > p->y_max)
		p->y_max = y;
	if (y < p->y_min)
		p->y_min = y;
}
