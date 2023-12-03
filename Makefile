# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/09 22:01:38 by fguirama          #+#    #+#              #
#    Updated: 2023/05/09 22:01:38 by fguirama         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #


# VAR ---------------------------------------------------------------
OBJS_DIR		=	.OBJS/
SRCS			=	SRCS/animation_fractal.c SRCS/animation_page.c SRCS/color.c SRCS/edit_fractal.c SRCS/hover_animation.c SRCS/hover_hook.c SRCS/init.c SRCS/init_fractal.c SRCS/menu.c SRCS/page_menu.c SRCS/render.c \
					SRCS/FRACTALS/01_mandelbrot.c SRCS/FRACTALS/02_julia.c SRCS/FRACTALS/03_celtic.c SRCS/FRACTALS/04_burning_ship.c SRCS/FRACTALS/05_buffalo.c SRCS/FRACTALS/06_burning_julia.c SRCS/FRACTALS/07_julia3.c SRCS/FRACTALS/08_celtic_mandelbar.c SRCS/FRACTALS/09_perpendicular_celtic.c SRCS/FRACTALS/10_heart.c SRCS/FRACTALS/11_mandelbar.c SRCS/FRACTALS/12_celtic_mandelbrot.c \
					SRCS/HOOK/hook.c SRCS/HOOK/key.c SRCS/HOOK/mouse.c \
					UTILS/mlx.c UTILS/time.c \
					main.c
DEP				=	$(addprefix $(OBJS_DIR), $(SRCS:.c=.d))
OBJS			=	$(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

NAME			=	fractol
HEAD			=	INCLUDES/

CC				=	cc
RM				=	rm -rf
FLAGS			=	-Wall -Wextra -Werror -pthread -O3 -MMD -MP# -fsanitize=thread -g3

MLX_NAME		=	libmlx.a

UNAME			=	$(shell uname -s)

ifeq ($(UNAME), Linux)
MLX_DIR			=	mlx/linux/
MLX_FLAGS		=	-lXext -lX11 -lm -lz
endif

ifeq ($(UNAME), Darwin)
MLX_DIR			=	mlx/mac/
MLX_FLAGS		=	-framework OpenGL -framework AppKit
endif

# RULES -------------------------------------------------------------
all:				mlx $(NAME)

run:				all
					./$(NAME)

norm:
					norminette $(SRCS) $(HEAD)/*.h | grep -E "(Error|Warning)"

$(NAME):			$(OBJS)
					$(CC) $(FLAGS) $(OBJS) $(MLX_DIR)$(MLX_NAME) $(MLX_FLAGS) -o $(NAME)

-include $(DEP)
$(OBJS_DIR)%.o:		%.c | dir
					$(CC) $(FLAGS) -I $(HEAD) -c $< -o $@

dir:
					@mkdir -p $(OBJS_DIR)
					@mkdir -p $(OBJS_DIR)SRCS
					@mkdir -p $(OBJS_DIR)SRCS/FRACTALS
					@mkdir -p $(OBJS_DIR)SRCS/HOOK
					@mkdir -p $(OBJS_DIR)UTILS

mlx:
					make --jobs=3 -C $(MLX_DIR)

clean:
					$(RM) $(OBJS_DIR)
					make clean -C $(MLX_DIR)

fclean:				clean
					$(RM) $(NAME)

re:					fclean run

.PHONY:				all run dir norm mlx clean fclean re
