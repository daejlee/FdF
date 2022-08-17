/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daejlee <daejlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 15:27:54 by daejlee           #+#    #+#             */
/*   Updated: 2022/04/23 15:46:50 by daejlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <stdarg.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
size_t			ft_strlen(const char *s);
void			*ft_memset(void *s, int c, size_t n);
void			ft_bzero(void *s, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memmove(void *dest, const void *src, size_t n);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);
int				ft_toupper(int c);
int				ft_tolower(int c);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
char			*ft_strnstr(const char *s1, const char *s2, size_t n);
int				ft_atoi(const char *nptr);
void			*ft_calloc(size_t nmemb, size_t size);
char			*ft_strdup(const char *s);
char			*ft_substr(char const *s, unsigned int start, unsigned int len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s1, char const *set);
char			**ft_split(char const *s, char c);
char			*ft_itoa(int n);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
t_list			*ft_lstnew(void *content);
void			ft_lstadd_front(t_list **lst, t_list *new);
int				ft_lstsize(t_list *lst);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstdelone(t_list *lst, void (*del)(void *));
void			ft_lstclear(t_list **lst, void (*del)(void *));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *),
					void (*del)(void *));

typedef struct s_info
{
	char			spc;
	char			*flag;
	int				width;
	int				precision;
	int				length;
	unsigned int	padding;
	char			*raw_str;
	char			*res_str;
}	t_info;

int		ft_printf(const char *str, ...);
int		collect_format(const char *str, struct s_info *p, va_list ap);
int		print_res_str(struct s_info *p);
char	*process_raw_str(struct s_info *p);
char	*check_specifier(va_list ap, const char *str);
int		check_precision(const char *str, va_list ap);
int		check_width(const char *str, va_list ap);
char	*check_flag(const char *str);
char	*ft_write_c(va_list ap);
char	*ft_write_s(va_list ap);
char	*ft_write_p(va_list ap);
char	*ft_write_d(va_list ap);
char	*ft_write_i(va_list ap);
char	*ft_write_u(va_list ap);
char	*ft_write_lowerx(va_list ap);
char	*ft_write_upperx(va_list ap);
char	*ft_write_per(va_list ap);
void	num_no_padding(struct s_info *p, int raw_strlen);
void	num_padding_flag(struct s_info *p, unsigned int padding, int slots);
void	num_padding_noflag(struct s_info *p,
			unsigned int padding, int raw_strlen);
void	ptr_null(struct s_info *p, int raw_strlen);
void	str_or_char_flag(struct s_info *p, int raw_strlen);
void	str_or_char_noflag(struct s_info *p, int raw_strlen);
void	str_or_char_null(struct s_info *p, int raw_strlen);

typedef struct g_list
{
	char			*str;
	int				fd;
	struct g_list	*next;
	int				fst_call;
	char			*last_ret;
	int				eof_flag;
}	t_gnl;

t_gnl			*g_lstnew(int fd);
void			*g_lstdel(t_gnl **targ_adr, char *buf, t_gnl **head_adr);
unsigned int	g_strlcpy(char *dst, const char *src, unsigned int size);
unsigned int	g_strlen(const char *s);
char			*concat_buf(char *str, char *buf, int r_flag);
char			*get_next_line(int fd);

#endif

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 256
#endif