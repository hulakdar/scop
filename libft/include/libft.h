/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 15:05:07 by skamoza           #+#    #+#             */
/*   Updated: 2018/01/09 21:13:53 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <string.h>
# include <stdlib.h>
# include <sys/types.h>
# include <fcntl.h>
# define BUFF_SIZE 1024 * 4 - 1

# if defined(WIN32) || defined(_WIN32) 
#  include <corecrt_io.h>
# else
#  include <unistd.h>
# endif

typedef struct		s_array
{
	char			array[BUFF_SIZE + 1];
	size_t			size;
}					t_array;
typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;
typedef struct		s_vector
{
	unsigned char	*data;
	size_t			size_of_type;
	size_t			last;
	size_t			back;
	size_t			front;
}					t_vector;

typedef void(*t_for_each_predicate)(void *, void *);
typedef void(*t_map_predicate)(void *, const void *, void *);

int					get_next_line(const int fd, char **line);
void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
size_t				ft_strlen(const char *s);
char				*ft_strdup(const char *s1);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
size_t				ft_strlcat(char *dest, const char *src, size_t size);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *big, const char *little);
char				*ft_strnstr(const char *big, const char *little,
															size_t len);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_chrcnt(const char *str, char chr);
int					ft_atoi(char *str);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
void				*ft_memalloc(size_t size);
char				*ft_strnew(size_t size);
void				ft_memdel(void **ap);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
char				*ft_itoa(int n);
void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_put_size_t(size_t n);
void				ft_puttab(char *str);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
void				ft_lstprint(t_list *list);
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
t_vector			ft_vec_new(size_t size, size_t init);
void				*ft_vec_get(t_vector *vector, size_t index);
void				*ft_vec_set(t_vector *vector, size_t index,
															const void *content);
void				ft_vec_del(t_vector *vector);
void				ft_vec_init(t_vector *vector, size_t size, size_t init);
void				ft_vec_destruct(t_vector *vector, void (*destructor)(void *));
void				*ft_vec_pushback(t_vector *vector, const void *content);
void				*ft_vec_popback(t_vector *vector);
void				*ft_vec_popfront(t_vector *vector);
void				ft_vec_for_each(t_vector *vector,
						t_for_each_predicate function, void *payload);
t_vector			ft_vec_map(t_vector *vector,
						t_map_predicate function, void *payload);
int					ft_atoi_base(const char *str, int base);
void				ft_tabdel(char ***hint);
size_t				ft_tabcount(char **tab);
void				ft_sort(unsigned char *begin, unsigned char *end, size_t size,
										int (*f)(void *, void *));
float				ft_atof(const char *str);
long long			ft_atoll(const char *str);
size_t				ft_atoull(const char *str);
size_t				ft_wordlen(const char *s);
size_t				ft_intpow(unsigned base, unsigned power);
#endif
