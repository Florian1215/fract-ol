/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:34:00 by fguirama          #+#    #+#             */
/*   Updated: 2024/04/16 14:34:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_color			render_color(t_data *data, t_color_data color_data, \
t_bool prev_render);
static t_color	render_bw(t_data *data, t_co z, t_bool prev_render);

int	get_color(t_data *data, t_color_data color_data, t_co co, t_co z)
{
	t_color	res;

	if ((data->bw_animation || data->color_animation) && ((\
!data->in_menu && side_line(data->color_co, co) < 0) || (\
data->in_menu && co.x < data->color_co.x)))
	{
		if (data->prev_mode)
			res = render_bw(data, z, TRUE);
		else
			res = render_color(data, color_data, data->color_animation);
	}
	else if (data->bw)
		res = render_bw(data, z, FALSE);
	else
		res = render_color(data, color_data, FALSE);
	return ((int)res.color);
}

static t_color	render_bw(t_data *data, t_co z, t_bool prev_render)
{
	t_bw_mode	mode;
	t_color		bw_col;

	if (prev_render)
		mode = data->prev_mode;
	else
		mode = data->bw;
	if ((data->appearance == LIGHT && ((mode == _X && z.x > 0) || (\
mode == _Y && z.y > 0))) || (data->appearance == DARK && ((mode == _X && \
z.x < 0) || (mode == _Y && z.y < 0))))
		bw_col = (t_color){FG};
	else
		bw_col = (t_color){WHITE};
	if (data->appearance_animation)
	{
		if (bw_col.color == FG)
			bw_col = get_gradient_colors(data, (t_color){WHITE}, bw_col);
		else
			bw_col = get_gradient_colors(data, (t_color){FG}, bw_col);
	}
	return (bw_col);
}

t_color	get_gradient_colors(t_data *data, t_color c1, t_color c2)
{
	t_color	res;

	res.rgb.r = get_value(c1.rgb.r, c2.rgb.r, data->i_appearance);
	res.rgb.g = get_value(c1.rgb.g, c2.rgb.g, data->i_appearance);
	res.rgb.b = get_value(c1.rgb.b, c2.rgb.b, data->i_appearance);
	return (res);
}
