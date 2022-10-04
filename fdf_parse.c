#include "./libft_garage/gnl/get_next_line.h"
#include "./libft_garage/libft/libft.h"
#include "./fdf.h"
#include <fcntl.h>
#include <unistd.h>

/* Remember that the goal of this project is not to parse maps! This doesn’t mean that
your program can crash when runned... it means that the map contained in the file will
be properly formatted. */

int	get_col_count(char **temp)
{
	unsigned int	i;

	i = 0;
	while (temp[i])
		i++;
	return (i);
}

int	**get_slots(fdf_t_info *p)
{
	int		**ret;
	unsigned int	i;

	ret = (int **)malloc(sizeof (int *) * (p->x));
	if (!ret)
		return (NULL);
	i = 0;
	while (i < p->x)
	{
		ret[i] = (int *)malloc(sizeof (int) * p->y);
		if (!ret[i++])
		{
			free_arr((char **)ret);
			return (NULL);
		}
	}
	return (ret);
}

int	get_rgb_val(char *str)
{
	char			*hex_idx;
	unsigned int	i;
	unsigned int	k;
	int				dig;
	int				ret;

	hex_idx = "0123456789ABCDEF";
	i = ft_strlen(str) - 1;
	ret = 0;
	dig = 1;
	while (str[i] != 'x')
	{
		k = 0;
		while (hex_idx[k])
		{
			if (str[i] == hex_idx[k])
			{
				ret += k * dig;
				break ;
			}
			k++;
		}
		dig *= 16;
		i--;
	}
	return (ret);
}

int	get_map(fdf_t_info *p, char *filename, int fd)
{
	char			**temp;
	char			*gnl_temp;
	unsigned int	i;
	unsigned int	k;

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
	i = 0;
	while (i < p->y)
	{
		k = 0;
		gnl_temp = get_next_line(fd);
		temp = ft_split(gnl_temp, ' ');
		if (gnl_temp)
			free (gnl_temp);
		if (!temp)
		{
			free_arr((char **)p->map_color);
			free_arr((char **)p->map_cord);
			return (0);
		}
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
			k++;
		}
		i++;
		free_arr(temp);
	}
	if (p->x < p-> y)
		p->map_size = p->y;
	else
		p->map_size = p->x;
	return (1);
}

int	parse_arg(fdf_t_info *p, char **argv)
{
	int	fd;
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
	return (1);
}
