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
	data->prev_mode = data->bw;
	data->bw = OFF;
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

void	set_bw(t_data *data, t_bw_mode bw)
{
	if (data->bw_animation && data->i_bw < 20)
		return ;
	if (data->bw == bw)
	{
		if (data->offset_color)
			data->offset_color -= 1;
		else
			data->offset_color = YELLOW;
		return (edit_color(data));
	}
	data->prev_mode = data->bw;
	data->bw = bw;
	data->bw_animation = TRUE;
	data->i_bw = 0;
}

// TODO handle animation in menu
int get_color(t_data *data, t_fractal *frac, int i, double sqr, t_co co, t_co z)
{
	t_colors		set;
	double			op;
	int				color;
	int				cat;
	t_color			gradient;
	t_appearance	app;
	t_bool			prev_color_color;
	t_bool			prev_color_bw;
	t_bool			prev_bw_bw;
	t_bool			prev_bw_color;
	t_bw_mode		mode;
	t_color			bw_col;
	t_color			other_bw_col;

	if (data->in_menu)
	{
		prev_color_bw = data->bw_animation && co.x > data->bw_color_co.x && !data->prev_mode;
		prev_color_color = data->color_animation && co.x > data->color_co.x && !data->prev_mode;
		prev_bw_bw = data->bw_animation && co.x > data->bw_color_co.x && data->prev_mode;
		prev_bw_color = data->color_animation && co.x > data->color_co.x && data->prev_mode;
	}
	else
	{
		prev_color_bw = data->bw_animation && side_line(data->bw_color_co, co) < 0 && !data->prev_mode;
		prev_color_color = data->color_animation && side_line(data->color_co, co) < 0 && !data->prev_mode;
		prev_bw_bw = data->bw_animation && side_line(data->bw_color_co, co) < 0 && data->prev_mode;
		prev_bw_color = data->color_animation && side_line(data->color_co, co) < 0 && data->prev_mode;
	}
	(void)prev_color_bw;
	if ((data->in_menu && data->bw_animation && !data->prev_mode && co.x > data->bw_color_co.x) || (data->bw && data->appearance_animation) || (data->bw && !data->bw_animation) || (data->bw_animation && side_line(data->bw_color_co, co) > 0) || prev_bw_color || prev_bw_bw)
	{
		if (prev_bw_color || prev_bw_bw)// || prev_color_bw)
		{
			mode = data->prev_mode;
		}
		else
			mode = data->bw;
		if ((data->appearance == LIGHT && ((mode == X && z.x > 0) || (mode == Y && z.y > 0))) ||
		(data->appearance == DARK && ((mode == X && z.x < 0) || (mode == Y && z.y < 0))))
		{
			bw_col = (t_color) {FG};
			other_bw_col = (t_color) {WHITE};
		}
		else
		{
			bw_col = (t_color){WHITE};
			other_bw_col = (t_color){FG};
		}
		if (data->appearance_animation)
			bw_col = get_gradient_colors(data, other_bw_col, bw_col);
		return ((int)bw_col.color);
	}
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
		if (prev_color_color && data->color_animation)
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
