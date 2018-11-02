CC=clang
CFLAGS=-Wall -Wextra -Werror -g
ZADANIE=ft_memset ft_memcpy ft_bzero ft_memccpy ft_memmove ft_memchr ft_memcmp ft_strlen ft_strdup ft_strcpy ft_strncpy ft_strcat ft_strncat ft_strlcat ft_strchr ft_strrchr ft_strstr ft_strnstr ft_strcmp ft_strncmp ft_atoi ft_isalpha ft_isdigit ft_isalnum ft_isascii ft_isprint ft_toupper ft_tolower ft_memalloc ft_memdel ft_strnew ft_strdel ft_strclr ft_striter ft_striteri ft_strmap ft_strmapi ft_strequ ft_strnequ ft_strsub ft_strjoin ft_strtrim ft_strsplit ft_itoa ft_putchar ft_putstr ft_putendl ft_putnbr ft_putchar_fd  ft_putstr_fd ft_putendl_fd  ft_putnbr_fd ft_lstnew ft_lstdelone ft_lstdel ft_lstadd ft_lstiter ft_lstmap ft_islower ft_isupper ft_stacknew ft_stackpush ft_stackpop ft_vectornew ft_vectorset ft_vectorget ft_vectordel ft_lstprint ft_vectorinit ft_vectordestruct ft_vec_pushback get_next_line ft_quickmove ft_vec_popback ft_atoi_base ft_tabdel ft_tabcount ft_vec_popfront ft_puttab ft_sort ft_put_size_t
OBJ=$(addsuffix .o, $(ZADANIE))
NAME=libft.a

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@echo "Library is done!📚"
%.o: %.c
	@$(CC) -c $^ -o $@ $(CFLAGS) -I include
clean:
	@rm -f $(OBJ)
fclean: clean
	@rm -f $(NAME)
re: fclean all

.PHONY: clean fclean re
