/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 13:31:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/07/24 13:31:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# include "typdef.h"

enum e_color_hex
{
	FG = 0x202020,
	WHITE = 0xFFFFFF,
};

enum e_colors
{
	GREEN,
	PURPLE,
	ELECTRIC_BLUE,
	RED,
	BLUE_RED,
	PINK,
	GREEN_BLUE,
	BLUE_LIGHT,
	PASTEL_PINK,
	NIGHT_BLUE,
	BLUE,
	YELLOW,
};

enum e_appearance
{
	LIGHT,
	DARK,
};

enum e_bw_mode
{
	OFF,
	X,
	Y,
};

struct s_rgb
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
};

union u_color
{
	unsigned int	color;
	struct s_rgb	rgb;
};

int			get_color(t_data *data, t_fractal *frac, int i, double sqr, t_co co, t_co z);
void		color_animation(t_data *data);
void		appearance_animation(t_data *data);
void		bw_animation(t_data *data);
void		toggle_appearance(t_data *data);
void		set_bw(t_data *data, t_bw_mode bw);
void		edit_color(t_data *data);
void		set_color(t_data *data, t_colors color);
void		init_green(t_data *data);
void		init_purple(t_data *data);
void		init_electric_blue(t_data *data);
void		init_red(t_data *data);
void		init_blue_red(t_data *data);
void		init_pink(t_data *data);
void		init_green_blue(t_data *data);
void		init_blue_light(t_data *data);
void		init_pastel_pink(t_data *data);
void		init_night_blue(t_data *data);
void		init_blue(t_data *data);
void		init_yellow(t_data *data);

#endif
