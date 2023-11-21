NAME		= fdf
CC			= cc
CCFLAGS		= -Wall -Wextra -Werror -g3
INCLUDES	= includes
LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a
MLIX_DIR	= minilibx
MLIX		= $(MLIX_DIR)/libmlx_Linux.a
LIBS		= $(LIBFT) $(MLIX)
OBJ_DIR		= obj

SRCS		= main.c
OBJS		= ${addprefix $(OBJ_DIR)/, ${SRCS:.c=.o}}

$(NAME): $(OBJS) $(LIBS)
	@echo '* Assembling $@'
	@$(CC) $(CCFLAGS) $(OBJS) $(LIBS) -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
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

$(MLIX):
	@echo '* Making MinilibX'
	@make -C $(MLIX_DIR)

remlix:
	@echo '* Remaking MinilibX'
	@make re -C $(MLIX_DIR)

cleanmlix:
	@echo '* Cleaning MinilibX'
	@make clean -C $(MLIX_DIR)

fcleanmlix:
	@echo '* Cleaning MinilibX'
	@make fclean -C $(MLIX_DIR)

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

.PHONY: all clean fclean re