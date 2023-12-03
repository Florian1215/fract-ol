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

// UTILS ------------------------------------------------------------
enum e_bool
{
	FALSE,
	TRUE,
};

enum e_exit_status
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

enum e_pos
{
	POS_ERROR = -1,
	POS_1,
	POS_2,
	POS_3,
	POS_4,
};

void		cancel_animation(t_data *data);
double		get_value(double a, double b, int i);
int			close_mlx(t_data *data);
void		mlx_put_pixel_img(t_img *img, t_co co, int color);
void		dup_img(t_img *from, t_img *to);
t_time		get_timestamp(void);
void		sleep_until(t_time until);

// MENU -------------------------------------------------------------
struct s_slide
{
	t_img	img;
	int		side;
	int		i;
	int		start;
	int		pos;
	t_bool	animation;
};

void		set_menu(t_data *data);
void		set_names_fractal(t_data *data, void *img, int x_offset);
int			mouse_event_motion(int x, int y, t_data *data);
void		set_page(t_data *data, int page);
void		slide_page(t_data *data, int side);
void		render_slide(t_data *data);
void		hover_animation(t_data *data);

// FRACTAL ----------------------------------------------------------
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

struct s_fractal
{
	t_fractals		set;
	t_colors		color;
	t_co			c;
	t_delta			animation_c;
	t_delta			plan;
	t_delta			plan_default;
	t_delta			animation_plan;
	t_delta			menu;
	t_co			offset_menu;
	t_co			start_launch_plan;
	char			*name;
	int				offset_name;
	int				max_iter;
	double			size_zoom;
	t_preset		max_preset;
	t_co			(*preset)(t_preset);
	int				(*sequence)(t_data *, t_fractal *, t_co);
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
	t_bool					is_on;
	t_bool					animation;
};

struct s_data
{
	void			*mlx_ptr;
	void			*win_ptr;
	t_img			img;
	t_appearance	appearance;
	t_hover			hover[4];
	t_fractals		menu[4];
	t_fractal		fractals[N_FRAC];
	t_fractal		*f;
	t_colors		color;
	t_co			prev_pos;
	int				offset_color;
	int				page;
	t_bool			c_animate;
	int				i_c;
	t_bool			reset;
	t_bool			moving;
	t_bool			in_menu;
	t_bool			edit_c;
	t_slide			slide;
	t_bool			edit;
	t_bool			update;
	t_bool			zoom_size;
	pthread_mutex_t	mutex_line;
};

void		render_fractal(t_data *data);
void		c_animation(t_data *data);
void		launch_fractal(t_data *data, t_fractals set);
void		reset_animation(t_data *data);
void		edit_iter(t_data *data, double j);
void		move(t_data *data, int x, int y);

int			mandelbrot(t_data *data, t_fractal *frac, t_co c);
int			julia(t_data *data, t_fractal *frac, t_co z);
int			burning_shipe(t_data *data, t_fractal *frac, t_co c);
int			celtic(t_data *data, t_fractal *frac, t_co c);
int			buffalo(t_data *data, t_fractal *frac, t_co z);
int			burning_julia(t_data *data, t_fractal *frac, t_co c);
int			julia3(t_data *mlx, t_fractal *frac, t_co z);
int			celtic_mandelbar(t_data *data, t_fractal *frac, t_co z);
int			perpendicular_celtic(t_data *data, t_fractal *frac, t_co z);
int			heart(t_data *data, t_fractal *frac, t_co z);
int			mandelbar(t_data *data, t_fractal *frac, t_co z);
int			celtic_mandelbrot(t_data *data, t_fractal *frac, t_co z);

void		init_mandelbrot(t_fractal *f);
void		init_julia(t_fractal *f);
void		init_celtic(t_fractal *f);
void		init_burning_shipe(t_fractal *f);
void		init_buffalo(t_fractal *f);
void		init_burning_julia(t_fractal *f);
void		init_julia3(t_fractal *f);
void		init_celtic_mandelbar(t_fractal *f);
void		init_perpendicular_celtic(t_fractal *f);
void		init_heart(t_fractal *f);
void		init_mandelbar(t_fractal *f);
void		init_celtic_mandelbrot(t_fractal *f);

// THREAD -----------------------------------------------------------
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