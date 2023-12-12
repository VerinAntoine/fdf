NAME		= fdf
CC			= cc
CCFLAGS		= -Wall -Wextra -Werror -g3
INCLUDES	= includes
LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a
MLX_DIR		= mlx
MLX			= $(MLX_DIR)/libmlx_Linux.a
MLX_ARGS	= -L mlx -lXext -lX11 -lm
LIBS		= $(LIBFT) $(MLX)
OBJ_DIR		= obj

SRCS		= $(addprefix src/, main.c parser.c window.c map.c loop.c)
SRCS_O		= $(addprefix src_old/, main.c print_line.c parser.c map.c)
OBJS		= ${addprefix $(OBJ_DIR)/, ${SRCS:.c=.o}}

$(NAME): $(OBJS) $(LIBS)
	@echo '* Assembling $@'
	@$(CC) $(CCFLAGS) $(OBJS) $(LIBS) -o $(NAME) $(MLX_ARGS)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/src
	@echo '- Compiling $<'
	@$(CC) $(CCFLAGS) -c $< -o $@ -I $(INCLUDES)

####	LIBFT	####

$(LIBFT):
	@echo '* Making libft'
	@make -C $(LIBFT_DIR)

relib:
	@echo '* Remaking libft'
	@make re -C $(LIBFT_DIR)

cleanlib:
	@echo '* Cleaning libft'
	@make clean -C $(LIBFT_DIR)

fcleanlib:
	@echo '* Cleaning libft'
	@make fclean -C $(LIBFT_DIR)

####	MinilibX	####

$(MLX):
	@echo '* Making MinilibX'
	@make -C $(MLX_DIR)

remlx:
	@echo '* Remaking MinilibX'
	@make re -C $(MLX_DIR)

cleanmlx:
	@echo '* Cleaning MinilibX'
	@make clean -C $(MLX_DIR)

fcleanmlx:
	@echo '* Cleaning MinilibX'
	@make fclean -C $(MLX_DIR)

####    Project    ####

all: $(NAME)

clean:
	@echo '! Removing obj files'
	@rm -f $(OBJS)

fclean: clean
	@echo '! Removing $(NAME)'
	@rm -f $(NAME)

re: fclean $(NAME)

norm:
	norminette ${SRCS} | grep 'Error'

.PHONY: all clean fclean re relib cleanlib fcleanlib remlx cleanmlx fcleanmlx