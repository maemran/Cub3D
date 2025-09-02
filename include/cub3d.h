/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 17:31:14 by asaadeh           #+#    #+#             */
/*   Updated: 2025/08/26 12:48:39 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include <X11/keysym.h>
# include <math.h>
# include <mlx.h>
# include <stdlib.h>

# define WIDTH 1500
# define HIGHT 900
# define FOV_FACTOR 0.7071
# define MOVESPEED 0.05
# define ROTATSPEED 0.03
# define TEX_SIZE 64

typedef struct s_keys
{
	int				w;
	int				a;
	int				s;
	int				d;
	int				left;
	int				right;
	int				escape;
}					t_keys;

typedef struct s_colors
{
	int				c_mix;
	int				f_mix;
	int				ceil[3];
	int				floor[3];
}					t_colors;

typedef struct s_directions
{
	char			*north;
	char			*south;
	char			*east;
	char			*west;
}					t_directions;

typedef struct s_vars
{
	char			**map;
	void			*mlx;
	void			*win;
	void			*img_buffer;
	char			*img_addr;
	int				bpp;
	int				line_length;
	int				endian;
	char			facing_dir;
	double			xp_pos;
	double			yp_pos;
	int				map_height;
	int				map_width;
}					t_vars;

typedef struct s_ray_casting
{
	double			cx_plane;
	double			cy_plane;
	double			x_facing_dir;
	double			y_facing_dir;
	double			ray_dx;
	double			ray_dy;
	double			side_x;
	double			side_y;
	double			delta_x;
	double			delta_y;
	double			dist;
	int				line_height;
	int				map_x;
	int				map_y;
	int				step_x;
	int				step_y;
	int				side;
	int				start;
	int				end;
	int				tex_id;
	int				tex_x;
	int				tex_y;
	int				i;
	double			step;
	double			tex_pos;
}					t_ray_casting;

typedef struct s_texture
{
	void			*img;
	char			*addr;
	int				bpp;
	int				line_len;
	int				endian;
}					t_texture;

typedef struct s_parsing
{
	char			**file;
	int				first_ceil;
	int				last_ceil;
	int				ceil_line;
	char			*ceil;
	int				first_floor;
	int				last_floor;
	int				floor_line;
	char			*floor;
	int				last_line_map;
}					t_parsing;

typedef struct s_path_info
{
	int				line_index;
	int				start;
	int				end;
	int				j;
}					t_path_info;

typedef struct s_cub3d
{
	t_directions	*dir;
	t_colors		*color;
	t_vars			*data;
	t_ray_casting	*rc;
	t_texture		**tex;
	t_keys			keys;
}					t_cub3d;

void				keys_init(t_cub3d *g);
void				init_structs(t_cub3d *g);
void				free_structs(t_cub3d *g);
int					init_textures(t_cub3d *g);
void				free_textures(t_cub3d *g);
void				free_map(t_cub3d *g);
void				destroy_mlx(t_cub3d *g);
void				exit_window(t_cub3d *g);
void				smooth_keys(t_cub3d *g);
int					key_press(int key, t_cub3d *g);
int					key_release(int key, t_cub3d *g);
void				move_forward(t_cub3d *g);
void				move_backward(t_cub3d *g);
void				move_left(t_cub3d *g);
void				move_right(t_cub3d *g);
void				rotate_left(t_cub3d *g);
void				rotate_right(t_cub3d *g);
void				handle_escape(t_cub3d *g);
void				set_texture_index(t_cub3d *g);
void				texture_position(t_cub3d *g);
void				load_texture(t_cub3d *g, int index, char *path);
void				first_intersections(t_cub3d *g);
void				set_rc_values(t_cub3d *g, double camera_x);
void				dda_algorithm(t_cub3d *g);
void				find_distance(t_cub3d *g);
void				cast_ray(t_cub3d *g, int screen_x);
void				draw_ceiling(t_cub3d *g, int screen_x);
void				draw_walls(t_cub3d *g, int screen_x);
void				draw_floor(t_cub3d *g, int screen_x);
void				get_ceiling_color(t_cub3d *g);
void				get_floor_color(t_cub3d *g);
void				set_directions_values(t_cub3d *g);
int					check_map_cell(t_cub3d *g, int x, int y);
void				rotate_player(t_cub3d *g, double angle);
void				move_player(t_cub3d *g, double move_x, double move_y);
int					key_press(int key, t_cub3d *g);
void				put_pixel(t_cub3d *g, int x, int y, int color);
int					get_texture_pixel(t_texture *tex, int x, int y);
void				free_map(t_cub3d *g);
t_cub3d				*prepare_before_ray_casting(t_cub3d *g, t_colors *colors,
						t_vars *data, t_directions *dir);
void				init_directions(t_directions *directions);
int					set_dir_path(t_parsing *parsing, char **destination,
						char *str);
void				free_file(char **file);
void				free_directions(t_directions *directions);
void				free_parsing(t_parsing *parsing);
void				exit_and_error(t_parsing *parsing, t_directions *directions,
						char *str);
void				set_directions(t_parsing *parsing,
						t_directions *directions);

void				check_elements(t_parsing *parsing, t_vars *vars,
						t_directions *directions);
void				check_taps(t_parsing *parsing, t_vars *vars,
						t_directions *directions);
t_vars				*init_map(t_parsing *parsing);
void				check_walls(t_parsing *parsing, t_vars *vars,
						t_directions *directions);
int					first_line(t_parsing *parsing);

void				free_all_and_exit(t_parsing *parsing, t_vars *vars,
						t_directions *directions);

void				init_ceil(t_parsing *parsing, t_vars *vars,
						t_directions *directions);
t_colors			*get_ceil_number(t_parsing *parsing, t_vars *vars,
						t_directions *directions);
void				set_ceil(t_parsing *parsing, t_vars *vars,
						t_directions *directions);
void				check_comma_in_ceil(t_parsing *parsing, t_vars *vars,
						t_directions *directions);

void				init_floor(t_parsing *parsing, t_vars *vars,
						t_directions *directions);

void				set_floor(t_parsing *parsing, t_vars *vars,
						t_directions *directions);
void				check_comma_in_floor(t_parsing *parsing, t_vars *vars,
						t_directions *directions);

int					is_this_map(t_parsing *parsing, int i);
int					validate_map(t_vars *vars);
void				restore_map(t_vars *vars);
void				get_max_width(t_vars *vars);
int					init_parsing_directions(t_parsing *parsing,
						t_directions *directions, char *argv);
char				**read_file(char *file_name);
void				init_colors(t_parsing *parsing, t_vars *vars,
						t_directions *directions);
void				free_vars(t_vars *vars);
void				free_string(char **string, int i);
void				free_all_and_exit_two(t_parsing *parsing, t_vars *vars,
						t_directions *directions, char *line);
void				check_image_path(t_parsing *parsing, t_vars *vars,
						t_directions *directinos);
void				print_and_free(t_parsing *parsing, t_vars *vars,
						t_directions *directions, char *str);
void				check_walls_two(t_parsing *parsing, t_vars *vars,
						t_directions *directions);
int					get_last_line(t_vars *vars, t_parsing *parsing);
void				check_space_in_ceil(t_parsing *parsing, t_vars *vars,
						t_directions *directions);
void				check_space_in_floor(t_parsing *parsing, t_vars *vars,
						t_directions *directions);
void				check_taps(t_parsing *parsing, t_vars *vars,
						t_directions *dirs);
void				finish_game(t_parsing *parsing, t_vars *vars,
						t_directions *directions, t_colors *colors);
char				*init_floor_numbers(t_parsing *parsing, t_vars *vars,
						t_directions *directions);
char				*init_ceil_numbers(t_parsing *parsing, t_vars *vars,
						t_directions *directions);
char				**read_file(char *file_name);
void				check_lines(t_parsing *parsing, t_vars *vars,
						t_directions *directions);
int					match_identifier(char *line, int j, char *str);
int					check_before_dir(int i, int j, t_parsing *parsing);
int					check_after_path(int i, int check, t_parsing *parsing);
int					valid_extension(char **argv);
void				mlx_manage(t_cub3d *g);
#endif
