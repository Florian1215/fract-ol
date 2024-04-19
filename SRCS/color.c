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

void	set_color(t_data *data, t_colors color)
{
	data->prev_color = data->color;
	data->color = (color + data->offset_color) % 12;
}

void	edit_color(t_data *data)
{
	if (data->color_animation || data->bw_animation)
		return (lst_new(data, C));
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
		return (lst_new(data, D));
	data->appearance = !data->appearance;
	data->appearance_animation = TRUE;
	data->i_appearance = 0;
	if (data->in_menu)
		set_menu(data);
}

void	set_bw(t_data *data, int k)
{
	t_bw_mode	bw;

	if (data->bw_animation || data->color_animation)
		return (lst_new(data, k));
	if (k == X)
		bw = _X;
	else
		bw = _Y;
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
	data->i_color = 0;
}
