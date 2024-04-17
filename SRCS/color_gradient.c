/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_gradient.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:57:00 by fguirama          #+#    #+#             */
/*   Updated: 2024/04/16 15:57:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		init_gradient_color(t_color_data color_data, \
t_gradient_color_data *g);
static t_colors	init_set_color(t_data *data, t_color_data color_data, \
t_bool prev_render, t_appearance *app);
static t_color	get_gradient(t_color *pal, t_gradient_color_data *g);

t_color	render_color(t_data *data, t_color_data color_data, t_bool prev_render)
{
	t_gradient_color_data	g;
	t_appearance			app;
	t_colors				set;
	t_color					color;

	init_gradient_color(color_data, &g);
	app = data->appearance;
	set = init_set_color(data, color_data, prev_render, &app);
	color = get_gradient(data->pal[set][app], &g);
	if (data->appearance_animation && app == data->appearance)
		color = get_gradient_colors(data, \
get_gradient(data->pal[set][!data->appearance], &g), color);
	return (color);
}

static void	init_gradient_color(t_color_data color_data, \
t_gradient_color_data *g)
{
	g->op = 1 + ((log(log(2)) - log((0.5 * log(color_data.sqr)))) / log(2));
	if (g->op > 0.9999)
		g->op = 0.9999;
	if (g->op < 0)
		g->op = 0;
	g->op += color_data.i;
	g->cat = color_data.frac->max_iter / 4;
	if (!g->cat)
		g->cat = 1;
	g->color_shade = color_data.i / g->cat;
	if (g->color_shade < 0)
		g->color_shade = 0;
	else if (g->color_shade >= 4)
		g->color_shade = 3;
}

static t_colors	init_set_color(t_data *data, t_color_data color_data, \
t_bool prev_render, t_appearance *app)
{
	t_colors		set;

	if (data->in_menu || data->menu.animation)
	{
		if (prev_render)
			set = (color_data.frac->color + data->offset_color - 1) % 12;
		else
			set = (color_data.frac->color + data->offset_color) % 12;
	}
	else
	{
		if (prev_render)
		{
			set = data->prev_color;
			if (data->appearance_animation && data->i_appearance < \
data->i_color)
				*app = !*app;
		}
		else
			set = data->color;
	}
	return (set);
}

static t_color	get_gradient(t_color *pal, t_gradient_color_data *g)
{
	t_color			col;

	col.rgb.r = pal[g->color_shade].rgb.r + ((pal[g->color_shade + 1].rgb.r - \
pal[g->color_shade].rgb.r) * ((g->op - g->cat * g->color_shade) / g->cat));
	col.rgb.g = pal[g->color_shade].rgb.g + ((pal[g->color_shade + 1].rgb.g - \
pal[g->color_shade].rgb.g) * ((g->op - g->cat * g->color_shade) / g->cat));
	col.rgb.b = pal[g->color_shade].rgb.b + ((pal[g->color_shade + 1].rgb.b - \
pal[g->color_shade].rgb.b) * ((g->op - g->cat * g->color_shade) / g->cat));
	return (col);
}
