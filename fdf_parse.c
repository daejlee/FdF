#include "./libft_garage/gnl/get_next_line.h"
#include "./libft_garage/libft/libft.h"
#include "./fdf.h"
#include <fcntl.h>
#include <unistd.h>

/* Remember that the goal of this project is not to parse maps! This doesn’t mean that
your program can crash when runned... it means that the map contained in the file will
be properly formatted. */

int	no_color(char *str)
{
	char	*itoa_temp;

	itoa_temp = ft_itoa(ft_atoi(str));
	if (ft_strchr(str, '\n'))
	{
		if (ft_strncmp(itoa_temp, str, ft_strlen(str) - 1))
			return (0);
	}
	else
	{
		if (ft_strncmp(itoa_temp, str, ft_strlen(str)))
			return (0);
	}
	if (itoa_temp)
		free (itoa_temp);
	return (1);
}

int	color(char *str)
{
	char	**split_temp;

	split_temp = ft_split(str, ',');
	if (!split_temp)
		return (-1);
	if (!no_color(split_temp[0]))
	{
		free_arr(split_temp);
		return (-1);
	}
	free_arr(split_temp);
	return (1);
}

int	get_row_count(char **temp)
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

	ret = (int **)malloc(sizeof (int *) * (p->col + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (i < p->col)
	{
		ret[i] = (int *)malloc(sizeof (int) * p->row);
		if (!ret[i++])
		{
			free_arr((char **)ret);
			return (NULL);
		}
	}
	ret[p->col] = NULL;
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
	while (p->map_cord[i])
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
		while (k < p->row)
		{
			if (ft_strchr(temp[k], '\n'))
				*ft_strchr(temp[k], '\n') = '\0';
			if (ft_strchr(temp[k], ','))
			{
				p->map_color[i][k] = get_rgb_val(ft_strchr(temp[k], ',') + 1);
				*ft_strchr(temp[k], ',') = '\0';
			}
			else
				p->map_color[i][k] = 0;
			p->map_cord[i][k] = ft_atoi(temp[k]);
			k++;
		}
		i++;
		free_arr(temp);
	}
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
	p->row = get_row_count(temp);
	p->col = 0;
	free_arr(temp);
	while (gnl_temp)
	{
		free(gnl_temp);
		gnl_temp = get_next_line(fd);
		p->col += 1;
	}
	if (!get_map(p, argv[1], fd))
		return (0);
	return (1);
}