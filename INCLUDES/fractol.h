/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 18:37:22 by fguirama          #+#    #+#             */
/*   Updated: 2022/12/12 16:23:26 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "preprocessing.h"

// UTILS -----------------------------------------------------------------------
enum e_bool
{
	FALSE,
	TRUE,
};

enum e_exit
{
	SUCCESS,
	ERROR
};

struct	s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		bit_ratio;
	int		endian;
	int		width;
	int		height;
};

struct s_co
{
	double	x;
	double	y;
};

struct s_delta
{
	t_co	start;
	t_co	end;
};

struct s_list
{
	int		k;
	t_list	*next;
};

enum e_pos
{
	POS_ERROR = -1,
	POS_1,
	POS_2,
	POS_3,
	POS_4,
};

void		lst_new(t_data *data, int k);
void		lst_clear(t_list **lst);
t_bool		mem_cmp(const void *s1, const void *s2);
double		side_line(t_co color_line, t_co co);
void		cancel_animation(t_data *data);
double		get_value(double a, double b, int i);
int			close_mlx(t_data *data);
void		mlx_put_pixel_img(t_img *img, t_co co, int color);
t_time		get_timestamp(void);
void		sleep_until(t_time until);

// MENU ------------------------------------------------------------------------
struct s_slide
{
	t_img	img;
	int		side;
	int		i;
	int		start;
	int		value;
	t_bool	animation;
	t_bool	render_img;
};

struct	s_menu_animation
{
	int		start;
	int		end;
	int		i;
	int		size;
	t_pos	pos;
	t_bool	animation;
	t_bool	save_img;
	t_co	v;
	t_co	step;
};

struct s_hover_value
{
	double	value;
	double	start;
	double	end;
};

struct	s_hover
{
	struct s_hover_value	zoom;
	struct s_hover_value	max_iter;
	int						i;
	t_bool					hover;
	t_bool					unhover;
	t_bool					is_active;
	t_bool					animation;
};

void		set_menu(t_data *data);
void		toggle_menu_animation(t_data *data);
int			mouse_event_motion(int x, int y, t_data *data);
void		set_page(t_data *data, int page, t_bool update);
void		set_page_value(t_data *data);
void		slide_page(t_data *data, int side);
void		init_hovers(t_data *data);

// FRACTAL ---------------------------------------------------------------------
enum e_fractal
{
	MANDELBROT,
	JULIA,
	CELTIC,
	BURNING_SHIP,
	BUFFALO,
	BURNING_JULIA,
	JULIA3,
	CELTIC_MANDELBAR,
	PERPENDICULAR_CELTIC,
	HEART,
	MANDELBAR,
	CELTIC_MANDELBROT,
};

enum e_preset
{
	PRESET_0,
	PRESET_1,
	PRESET_2,
	PRESET_3,
	PRESET_4,
	PRESET_5,
	PRESET_6,
	PRESET_7,
	PRESET_8,
	PRESET_9,
};

enum e_level
{
	_100 = 1,
	_50 = 2,
	_25 = 3,
};

struct s_fractal
{
	t_fractals		set;
	t_colors		color;
	t_co			c;
	t_delta			animation_c;
	t_delta			plan;
	t_delta			plan_default;
	t_delta			plan_start_hover;
	t_delta			animation_plan;
	t_delta			menu;
	int				max_iter;
	t_preset		max_preset;
	t_img			name;
	t_co			(*preset)(t_preset);
	int				(*sequence)(t_data *, t_fractal *, t_co, t_co);
};

struct s_data
{
	void				*mlx_ptr;
	void				*win_ptr;
	t_img				img;
	t_appearance		appearance;
	t_hover				hover[4];
	t_fractals			menus[4];
	t_fractal			fractals[N_FRAC];
	t_fractal			*f;
	t_colors			color;
	t_colors			prev_color;
	t_co				prev_pos;
	int					offset_color;
	int					page;
	t_bool				edit_c;
	t_bool				c_animation;
	int					i_c;
	t_bool				color_animation;
	t_bool				appearance_animation;
	t_bw_mode			prev_mode;
	t_bw_mode			bw;
	t_bool				bw_animation;
	int					i_appearance;
	t_co				color_co;
	int					i_color;
	t_level				render_level;
	t_time				last_render;
	t_bool				prev_render;
	t_bool				reset;
	t_bool				moving;
	t_bool				in_menu;
	t_slide				slide;
	t_bool				edit;
	t_bool				update;
	t_bool				zoom_size;
	t_color				pal[12][2][5];
	t_menu_animation	menu;
	int					hwin;
	int					qwin;
	double				ratio_title;
	t_list				*kbuff;
	t_bool				is_key_buff;
	pthread_mutex_t		mutex_line;
};

void		render_fractal(t_data *data);
t_co		get_r(t_fractal *f);
t_bool		start_reset_animation(t_data *data);
void		edit_iter(t_data *data, double j);
void		move(t_data *data, int x, int y);
double		cross_multi_plan(double start, double end, double scale);

int			mandelbrot(t_data *data, t_fractal *frac, t_co c, t_co co);
int			julia(t_data *data, t_fractal *frac, t_co z, t_co co);
int			burning_shipe(t_data *data, t_fractal *frac, t_co c, t_co co);
int			celtic(t_data *data, t_fractal *frac, t_co c, t_co co);
int			buffalo(t_data *data, t_fractal *frac, t_co z, t_co co);
int			burning_julia(t_data *data, t_fractal *frac, t_co c, t_co co);
int			julia3(t_data *mlx, t_fractal *frac, t_co z, t_co co);
int			celtic_mandelbar(t_data *data, t_fractal *frac, t_co z, t_co co);
int			perpendicular_celtic(t_data *data, t_fractal *frac, t_co z, \
t_co co);
int			heart(t_data *data, t_fractal *frac, t_co z, t_co co);
int			mandelbar(t_data *data, t_fractal *frac, t_co z, t_co co);
int			celtic_mandelbrot(t_data *data, t_fractal *frac, t_co z, t_co co);

// THREAD ----------------------------------------------------------------------
struct s_thread
{
	t_data			*data;
	pthread_t		thread;
	int				*line;
};

struct s_thread_preview
{
	t_data		*data;
	pthread_t	thread;
	t_fractal	*frac;
	t_pos		pos;
};

#endif