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

int			get_color(t_data *data, t_fractal *frac, int i, double sqr, t_co co);
void		color_animation(t_data *data);
void		init_colors(t_data *data);
void		toggle_appearance(t_data *data);
void		edit_color(t_data *data);
void		set_color(t_data *data, t_colors color);
t_color		*set_green(t_appearance new_app);
t_color		*set_purple(t_appearance new_app);
t_color		*set_electric_blue(t_appearance new_app);
t_color		*set_red(t_appearance new_app);
t_color		*set_blue_red(t_appearance new_app);
t_color		*set_pink(t_appearance new_app);
t_color		*set_green_blue(t_appearance new_app);
t_color		*set_blue_light(t_appearance new_app);
t_color		*set_pastel_pink(t_appearance new_app);
t_color		*set_night_blue(t_appearance new_app);
t_color		*set_blue(t_appearance new_app);
t_color		*set_yellow(t_appearance new_app);

#endif
