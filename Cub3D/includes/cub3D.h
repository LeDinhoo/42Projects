/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbacquet <cbacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:44:22 by clement           #+#    #+#             */
/*   Updated: 2023/12/20 13:52:40 by cbacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

# include "../mlx_linux/mlx.h"
# include "../utils/libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <time.h>
# include <unistd.h>

# define PI 3.14159265359
# define RED_BRICK 0xA52A2A
# define DARK_RED_BRICK 0x8B2323
# define MIDNIGHT_BLUE 0x191970
# define DARK_BLUE 0x00008B
# define DARK_GREEN 0x006400
# define DARK_RED 0x8B0000
# define WHITE 0xFFFFFF
# define BLACK 0x000000
# define YELLOW 0xFFFF00
# define ORANGE 0xFFA500

enum
{
	NO,
	SO,
	WE,
	EA,
	F,
	C
};

typedef struct s_direction_params
{
	int					dir_x;
	int					dir_y;
	double				plan_x;
	double				plan_y;
}						t_direction_params;

typedef struct s_image
{
	void				*img;
	char				*addr;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
	int					width;
	int					height;
}						t_img;

typedef struct s_perso
{
	int					orientation;
	int					pos[2];
	float				px;
	float				py;
	float				pdx;
	float				pdy;
	float				pa;
}						t_perso;

typedef struct s_ceiling
{
	int					r_value;
	int					g_value;
	int					b_value;
	int					index;

}						t_ceiling;

typedef struct s_floor
{
	int					r_value;
	int					g_value;
	int					b_value;
	int					index;

}						t_floor;

typedef struct s_map
{
	char				**map;
	int					height;
	int					width;
	char				**good_map;
	char				**copy_map;
}						t_map;

typedef struct s_vector
{
	int					x;
	int					y;
}						t_vector;

typedef struct s_window
{
	void				*ref;
	t_vector			size;
}						t_window;

typedef struct s_minimap
{
	int					mapsize;
	int					posx;
	int					posy;
}						t_minimap;

typedef struct s_ray
{
	double				wall_x;
	int					tex_x;
	double				step;
	double				tex_pos;
	int					y;
	int					tex_y;
	double				pos_x;
	double				pos_y;
	double				dir_x;
	double				dir_y;
	double				old_dir_x;
	double				old_plane_x;
	double				plan_x;
	double				plan_y;
	double				camera_x;
	double				ray_dir_x;
	double				ray_dir_y;
	double				move_speed;
	double				rot_speed;
	int					map_x;
	int					map_y;
	double				side_dist_x;
	double				side_dist_y;
	double				delta_dist_x;
	double				delta_dist_y;
	double				perp_wall_dist;
	int					step_x;
	int					step_y;
	int					hit;
	int					side;
	int					line_height;
	int					draw_start;
	int					draw_end;
	int					color;
	int					x;
}						t_ray;

typedef struct s_image_node
{
	t_img				image;
	struct s_image_node	*next;
}						t_image_node;

typedef struct s_game
{
	void				*mlx;
	t_window			win;
	t_img				buffer1;
	t_img				buffer2;
	t_img				wall_so;
	t_img				wall_no;
	t_img				wall_ea;
	t_img				wall_we;
	int					floor_color;
	int					ceiling_color;
	t_ray				ray;
	int					is_buffer;
	double				old_time;
	double				time;
	double				frame_time;
	double				move_speed;
	double				rot_speed;
	int					fps;
	int					square_size;
	int					player_size;
	int					mapx;
	int					mapy;
	int					maps;
	int					color;
	int					angle;
	int					w;
	int					s;
	int					a;
	int					d;
}						t_game;

typedef struct s_data_map_file
{
	int					save;
	int					nb_lines;
	int					i;
	int					empty_line;
	int					*fd;
	int					fd1;
	char				*read;
	char				*no;
	char				*so;
	char				*we;
	char				*ea;
	char				*f;
	char				*c;
	char				**textures;
	char				*file;
	t_map				map;
	t_floor				floor;
	t_ceiling			ceiling;
	t_perso				player;
	t_game				game;
	t_image_node		*g_image_list;
	t_minimap			minimap;

}						t_data;

//////////////////SRCS//////////////////////////////////////
//////////////////SRCS/PARSING//////////////////////////////
//////////////////SRCS/PARSING/errors.c/////////////////////
void					ft_error(t_data *data, char *str, char *line);
void					handle_line_map(t_data *data, char *line);

//////////////////SRCS/PARSING/parsing.c////////////////////
void					ft_parse_file(t_data *data, int fd);
void					ft_parsing(char *file, t_data *data);
int						ft_cub(char *str, t_data *data);

//////////////////SRCS/PARSING/parsing_utils.c/////////////
int						ft_count_line(int fd);
int						ft_check_save(char *str);
int						ft_same_str(char *s1, char *s2);
void					ft_print_file(int fd);
void					switch_space(char **map);
int						check_border(t_map *map);

//////////////////SRCS/PARSING/PARSE_FILE/set_textures.c///
int						ft_check_elem(t_data *data, char *str);
int						ft_no_dble(char *line, int fd, t_data *data);
char					*ft_skip_empy_line(char *line, int fd);
int						ft_check_dble(t_data *data, char *line, int fd);
void					ft_set_textures(t_data *data, int fd);

//////////////////SRCS/PARSING/PARSE_FILE/set_textures.c///
int						ft_get_ident(char *line, t_data *file);
void					ft_free_ident(t_data *data);

//////////////////SRCS/PARSING/PARSE_FILE/set_map.c///
int						ft_size_map(t_map *map, int fd);
void					ft_save_map(t_map *map, char *file);
int						ft_check_map(t_map *map, int fd, t_data *data);
void					ft_edit_good_map(t_map *map);
void					ft_set_map(char *file, t_data *data, int fd);

//////////////////SRCS/PARSING/PARSE_FILE/set_map_utils.c///
void					ft_copy_map(t_map *map);
int						ft_check_border(t_map *map);
int						ft_check_intern_walls(t_map *map);
int						ft_check_walls(t_map *map);
void					ft_free_map(char **map);

//////////////////SRCS/PARSING/PARSE_FILE/set_map_utils2.c///
void					ft_print_map(char **map);
void					ft_set_pos_perso(t_perso *player, char orientation,
							int x, int y);
void					ft_check_perso(t_map *map, t_perso *player);
char					*ft_go_top_map(int fd);
int						ft_pre_end(t_data *data);
int						ft_end_set_map(t_data *data);

//////////////////SRCS/PARSING/PARSE_FILE/set_map_utils3.c///
int						check_if_only_good_elem(t_map *map);
int						ft_player_good_pos(t_map *map, int y, int x);
int						check_player_are_only(t_map *map);
int						ft_map_elem(t_map *map, int fd, t_data *data);

//////////////////SRCS/PARSING/PARSE_FILE/set_map_utils4.c///
int						ft_check_border_up(t_map *map, int x);
int						ft_check_border_right(t_map *map, int y);
int						ft_check_border_down(t_map *map, int x);
int						ft_check_border_left(t_map *map, int y);

//////////////////SRCS/DISPLAY/display_textures.c/////////////
char					*ft_get_file_name(char *line);
int						set_texture(char *file, char **dest, char *direction,
							t_data *data);

int						ft_display_walls(int id, t_data *data, char *str);

//////////////////SRCS/DISPLAY/display_floor.c/////////////
int						ft_display_floor(t_data *data, char *str);
int						ft_get_rgb_value(char *str, t_floor *floor, int i);
int						ft_good_rgb_format(char *str, t_floor *floor);
int						ft_check_rgb(t_floor *floor, char *str);

//////////////////SRCS/DISPLAY/display_ceiling.c/////////////
int						ft_display_ceiling(t_data *data, char *str);
int						ft_get_rgb_value_ce(char *str, t_ceiling *ceiling,
							int i);
int						ft_good_rgb_format_ce(char *str, t_ceiling *ceiling);
int						ft_check_rgb_ce(t_ceiling *ceiling, char *str);

//////////////////SRCS/DISPLAY/display_utils.c/////////////
long long int			init_fps(void);
int						calculate_steps(int dx, int dy);
int						get_color_from_pixel(t_img *img, int x, int y);
void					my_mlx_pixel_put(t_data *data, int x, int y, int color);
int						darken_color(int color, float factor);

//////////////////SRCS/DISPLAY/drawing_utils.c/////////////
void					draw_square(t_data *data, int x, int y, int side);
void					drawbackground(t_data *data, int x, int y);
void					draw_map(t_data *data);
void					draw_player(t_data *data);
void					draw_player_direction(t_data *data);

//////////////////SRCS/DISPLAY/display_init.c/////////////
void					init_game(t_data *data);
t_img					ft_new_sprite(void *mlx, char *path, t_data *prog);
void					create_buffer_and_image(t_data *data);
int						display3d(t_data *data);

//////////////////SRCS/DISPLAY/raycasting_utils.c/////////////
t_window				ft_new_window(void *mlx, int widht, int height,
							char *name);
void					set_direction(t_ray *ray,
							const t_direction_params *params);
void					set_player_orientation(t_data *data, char orientation);
void					find_start_pos(t_data *data);
void					double_buffering(t_data *data);

//////////////////SRCS/DISPLAY/raycasting_utils2.c/////////////
float					degtorad(float a);
float					fixang(float a);

//////////////////SRCS/DISPLAY/command.c/////////////
void					ft_free_images(t_data *data);
int						ft_end(t_data *data);
int						key_press(int key, void *da);
int						key_release(int key, void *da);

//////////////////SRCS/DISPLAY/move.c/////////////
void					check_and_move_up(t_data *data);
void					check_and_move_down(t_data *data);
void					check_and_rotate_right(t_data *data);
void					check_and_rotate_left(t_data *data);
int						move_and_redraw(void *d);

//////////////////SRCS/DISPLAY/raycasting.c/////////////
void					perp_wall_dist_and_line_height(t_data *data);
void					calculate_wall_collision(t_data *data);
void					choose_wall_texture(t_data *data);
void					draw_walls(t_data *data);
void					raycasting2d(t_data *data);

//////////////////SRCS/DISPLAY/raycasting2.c/////////////
void					set_ray_dir_x(t_data *data);
void					set_ray_dir_y(t_data *data);
void					update_ray_data(t_data *data);
void					increment_ray(t_data *data);

int						ft_close(void *da);

//////////////////SRCS/PARSING/parsing2.c/////////////
int						ft_check_extension(char *line);
int						check_color(char *line);
void					ft_free_tab(char **tab);
int						is_digit(char *str);
int						valid_color(char *line);

//////////////////SRCS/PARSING/parsing3.c/////////////
void					dup_line2(t_data *data, char *line, int id);
void					set_floor_rgb(t_data *data, char *line);
void					set_ceiling_rgb(t_data *data, char *line);
void					dup_color(t_data *data, char *line, int id);
void					dup_line(t_data *data, char *line, int id);

//////////////////SRCS/PARSING/parsing4.c/////////////
void					set_texture1(t_data *data, char *line, int id);
void					set_color1(t_data *data, char *line, int id);
int						settings_full(t_data *data);
void					print_map(char **map);
void					add_line_to_map(t_data *data, char *line);

//////////////////SRCS/PARSING/parsing5.c/////////////
void					handle_identifier(t_data *data, char *line);
void					ft_parse_file(t_data *data, int fd);
int						find_max_width(char **map);
int						is_map_valid(char **map);
int						diffusion_algorithm(char **map, int x, int y,
							t_data *data);

#endif