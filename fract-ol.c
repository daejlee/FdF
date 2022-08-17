#include "./libft/libft.h"

int	print_available_args(char **sets)
{

}

int	check_set_name(char *input)
{

}

int	main(int argc, char **argv)
{
	char	**sets;

	if (argc < 2)
		return (1);
	else if (check_set_name(argv[1]))
		return (print_available_args(sets));
}