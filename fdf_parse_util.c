#include "./libft_garage/libft/libft.h"
#include "./fdf.h"

int	get_col_count(char **temp)
{
	unsigned int	i;

	i = 0;
	while (temp[i])
		i++;
	return (i);
}

int	**get_slots(t_fdf_info *p)
{
	int				**ret;
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
			if (str[i] == hex_idx[k] || str[i] == ft_tolower(hex_idx[k]))
				ret += k * dig;
			k++;
		}
		dig *= 16;
		i--;
	}
	return (ret);
}
