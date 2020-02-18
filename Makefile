NAME = fractol

FILES = calculation.c draw.c formulas.c initialize.c loop.c main.c zoom.c formulas2.c

S_DIR = src/

O_DIR = obj/

SRC = $(addprefix $(S_DIR), $(FILES))

OBJ = $(addprefix $(O_DIR), $(FILES:.c=.o))

MLX_FLAGS = -lmlx -framework OpenGL -framework AppKit -Iminilibx_macos

FLAGS = -Wall -Wextra -Werror -O3

MLX = minilibx_macos/libmlx.a

LIB = libft/libft.a

all: $(NAME) libft/

$(NAME) : $(OBJ)
	@make -C libft/
	@gcc -o $(NAME) $(FLAGS) $(MLX_FLAGS) $(OBJ) -Iinc $(LIB) $(MLX)

$(O_DIR)%.o:$(S_DIR)%.c inc/
	@mkdir -p $(O_DIR)
	@gcc $(FLAGS) -Iinc -Iminilibx_macos -o $@ -c $<

clean:
	@make clean -C libft/
	@rm -rf $(O_DIR)

fclean: clean
	@make fclean -C libft/
	@rm -f $(NAME)

re: fclean all
