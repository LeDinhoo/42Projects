.PHONY: all clean fclean re 

NAME = cub3D
CC = gcc -g
CFLAGS = -Wall -Werror -Wextra
MLXFLAGS = -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lrt -lz
INCLUDE_DIR = include
INCLUDES = -I$(INCLUDE_DIR) 

SRC_DIR = .
OBJ_DIR = .obj

LIBFT_A = libft.a
LIBFT_DIR = utils/libft/
LIBFT = $(addprefix $(LIBFT_DIR), $(LIBFT_A))

MLX_A		= libmlx.a
MLX_DIR 	= mlx_linux/
MLX			= $(addprefix $(MLX_DIR), $(MLX_A))

SRC = 	$(SRC_DIR)/main.c \
		$(SRC_DIR)/srcs/parsing/parsing.c \
		$(SRC_DIR)/srcs/parsing/parsing_digitcheck.c \
		$(SRC_DIR)/srcs/parsing/dup_color_pars.c \
		$(SRC_DIR)/srcs/parsing/add_line_pars.c \
		$(SRC_DIR)/srcs/parsing/parsing5.c \
		$(SRC_DIR)/srcs/parsing/parsing_utils.c \
		$(SRC_DIR)/srcs/parsing/errors.c \
		$(SRC_DIR)/srcs/parsing/parse_file/set_textures.c \
		$(SRC_DIR)/srcs/parsing/parse_file/set_textures_utils.c \
		$(SRC_DIR)/srcs/parsing/parse_file/set_map.c \
		$(SRC_DIR)/srcs/parsing/parse_file/set_map_utils.c \
		$(SRC_DIR)/srcs/parsing/parse_file/set_map_utils2.c \
		$(SRC_DIR)/srcs/parsing/parse_file/set_map_utils3.c \
		$(SRC_DIR)/srcs/parsing/parse_file/set_map_utils4.c \
		$(SRC_DIR)/srcs/display/display_textures.c \
		$(SRC_DIR)/srcs/display/display_floor.c \
		$(SRC_DIR)/srcs/display/display_ceiling.c \
		$(SRC_DIR)/srcs/display/display_utils.c \
		$(SRC_DIR)/srcs/display/drawing_utils.c \
		$(SRC_DIR)/srcs/display/drawing_utils2.c \
		$(SRC_DIR)/srcs/display/display_init.c \
		$(SRC_DIR)/srcs/display/raycasting_utils.c \
		$(SRC_DIR)/srcs/display/raycasting_utils2.c \
		$(SRC_DIR)/srcs/display/command.c \
		$(SRC_DIR)/srcs/display/move_and_check.c \
		$(SRC_DIR)/srcs/display/raycasting.c \
		$(SRC_DIR)/srcs/display/raycasting2.c \

OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

LIBFT_SRC = $(wildcard $(LIBFT_DIR)*.c)
LIBFT_OBJ = $(LIBFT_SRC:$(LIBFT_DIR)%.c=$(LIBFT_DIR).objs/%.o)
LIBFT_DEPS = $(LIBFT_OBJ:.o=.d)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) $(LIBFT) $(MLXFLAGS) $(MLX) -lreadline -o $@
	@echo "Compilation terminée avec succès ! ✔️"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -MMD -c $< -o $@

$(LIBFT): $(LIBFT_OBJ)
	@$(MAKE) -C $(LIBFT_DIR) -s
	@echo "Compilation de libft terminée ! ✔️"

$(LIBFT_DIR).objs/%.o: $(LIBFT_DIR)%.c
	@$(CC) $(CFLAGS) $(INCLUDES) -MMD -c $< -o $@

force: ;

clean:
	@echo "Suppression des fichiers objets... 🗑️"
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean -s

fclean: clean
	@echo "Suppression du programme final... 🗑️"
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean -s

re: fclean all

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)/srcs
	@mkdir -p $(OBJ_DIR)/srcs/parsing/
	@mkdir -p $(OBJ_DIR)/srcs/display/
	@mkdir -p $(OBJ_DIR)/srcs/parsing/parse_file
	@mkdir -p $(OBJ_DIR)/utils
	@mkdir -p $(LIBFT_DIR).objs

-include $(LIBFT_DEPS)


