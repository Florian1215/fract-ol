/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 10:49:37 by fguirama          #+#    #+#             */
/*   Updated: 2022/12/10 10:49:38 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static t_color	get_gradient(t_color *pal, int color, double op, int cat);
static t_color	get_gradient_colors(t_data *data, t_color c1, t_color c2);

void	set_color(t_data *data, t_colors color)
{
	data->prev_color = data->color;
	data->color = (color + data->offset_color) % 12;
}

void	edit_color(t_data *data)
{
	if (data->color_animation && data->i_color < 20)
		return ;
	data->offset_color = (data->offset_color + 1) % 12;
	data->color_animation = TRUE;
	data->i_color = 0;
	if (!data->in_menu)
		set_color(data, data->f->color);
}

void	toggle_appearance(t_data *data)
{
	if (data->appearance_animation)
		return ;
	data->appearance = !data->appearance;
	data->appearance_animation = TRUE;
	data->i_appearance = 0;
	if (data->in_menu)
		set_menu(data);
}

int	get_color(t_data *data, t_fractal *frac, int i, double sqr, t_co co)
{
	t_colors		set;
	double			op;
	int				color;
	int				cat;
	t_color			gradient;
	t_appearance	app;

	op = 1 + ((log(log(2)) - log((0.5 * log(sqr)))) / log(2));
	if (op > 0.9999)
		op = 0.9999;
	if (op < 0)
		op = 0;
	op += i;
	cat = frac->max_iter / 4;
	if (!cat)
		cat = 1;
	color = i / cat;
	if (color < 0)
		color = 0;
	else if (color >= 4)
		color = 3;
	app = data->appearance;
	if (data->in_menu || data->menu.animation)
	{
		if (data->color_animation && co.x < data->color_co.x)
			set = (frac->color + data->offset_color - 1) % 12;
		else
			set = (frac->color + data->offset_color) % 12;
	}
	else
	{
		if (data->color_animation && side_line(data->color_co, co) < 0)
		{
			set = data->prev_color;
			if (data->appearance_animation && data->i_appearance < data->i_color)
				app = !app;
		}
		else
			set = data->color;
	}

	gradient = get_gradient(data->pal[set][app], color, op, cat);
	if (data->appearance_animation && app == data->appearance)
		gradient = get_gradient_colors(data, get_gradient(data->pal[set][!data->appearance], color, op, cat), gradient);
	return ((int)gradient.color);
}

static t_color	get_gradient(t_color *pal, int color, double op, int cat)
{
	t_color			col;

	col.rgb.r = pal[color].rgb.r + ((pal[color + 1].rgb.r - pal[color].rgb.r \
) * ((op - cat * color) / cat));
	col.rgb.g = pal[color].rgb.g + ((pal[color + 1].rgb.g - pal[color].rgb.g \
) * ((op - cat * color) / cat));
	col.rgb.b = pal[color].rgb.b + ((pal[color + 1].rgb.b - pal[color].rgb.b \
) * ((op - cat * color) / cat));
	return (col);
}

static t_color	get_gradient_colors(t_data *data, t_color c1, t_color c2)
{
	t_color	res;

	res.rgb.r = get_value(c1.rgb.r, c2.rgb.r, data->i_appearance);
	res.rgb.g = get_value(c1.rgb.g, c2.rgb.g, data->i_appearance);
	res.rgb.b = get_value(c1.rgb.b, c2.rgb.b, data->i_appearance);
	return (res);
}
