NAME        = scop
CC          = gcc
CFLAGS      = -Wall -Wextra -Werror- -g

SRCS_DIR    = ./src
OBJS_DIR    = ./obj
HEADERS_DIR = ./include
LIBFT_DIR   = ./libft

HEADERS     = events.h obj.h scop.h shaders.h gl_math.h
HEADERS    := $(addprefix $(HEADERS_DIR)/, $(HEADERS))

SRCS        = main.c events.c objparser.c parser_impl.c shaders.c skybox.c texture.c gl_math.c  m44.c drawing.c error.c frame_loop.c material.c mtlparser.c parse_utils.c submesh.c

OBJS        = $(SRCS:.c=.o)

INCLUDES    = -I include/
INCLUDES   += -I libft/include
INCLUDES   += -I ~/.brew/include

LIBFT       = $(LIBFT_DIR)/libft.a

LIBRARIES   = -lm -lpthread
LIBRARIES  += -F frameworks/
LIBRARIES  += -L libft/ -lft
LIBRARIES  += -L ~/.brew/Cellar/glew/2.1.0/lib -lGLEW
LIBRARIES  += -framework SDL2 -framework SDL2_image -framework SDL2_ttf -framework OpenGL

TO_LINKING  = $(addprefix $(OBJS_DIR)/, $(OBJS)) $(LIBRARIES) -rpath frameworks/

VPATH       = $(SRCS_DIR) $(OBJS_DIR) $(SRCS_DIR)/opencl $(SRCS_DIR)/scene $(SRCS_DIR)/math
VPATH      += $(SRCS_DIR)/gui $(SRCS_DIR)/parsing $(SRCS_DIR)/icons $(SRCS_DIR)/events

all         : $(NAME)

$(NAME)     : $(LIBFT) $(OBJS_DIR) $(OBJS) $(HEADERS)
	@$(CC) $(CFLAGS) -o $(NAME) $(TO_LINKING)
	@printf "\e[38;5;46m./$(NAME)   SUCCESSFUL BUILD 🖥\e[0m\n"

$(LIBFT)    :
	@make -C $(LIBFT_DIR)

$(OBJS_DIR) :
	@mkdir $(OBJS_DIR)
	@printf "\e[38;5;46m$(OBJS_DIR)    FOLDER CREATED\e[0m\n"

$(OBJS)     : %.o : %.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $< -o $(OBJS_DIR)/$@ $(INCLUDES)

clean       :
	@rm -rf $(OBJS_DIR)
	@make -C $(LIBFT_DIR) clean
	@printf "\e[38;5;226m$(OBJS_DIR)    FOLDER DELETED\e[0m\n"

fclean      : clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@printf "\e[38;5;226m./$(NAME)   DELETED\e[0m\n"

re          : fclean all

.PHONY: clean fclean re
