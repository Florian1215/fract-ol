/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 13:36:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/07/24 13:36:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	launch_fractals(t_data *data, int k);
static void	set_hook_preset(t_data *data, int k);

int	key_event_press(int k, t_data *data)
{
	if ((k == LEFT || k == RIGHT) && !data->menu.animation && \
!data->color_animation && !data->appearance_animation)
		slide_page(data, k);
	else if (data->slide.animation)
		;
	else if (k == D)
		toggle_appearance(data);
	else if (k == C)
		edit_color(data);
	else if (k == KEY_X)
		set_bw(data, X);
	else if (k == KEY_Y)
		set_bw(data, Y);
	if (data->reset)
		return (ERROR);
	else if (k == PLUS)
		edit_iter(data, 10);
	else if (k == MINUS)
		edit_iter(data, -10);
	return (SUCCESS);
}

int	key_event(int k, t_data *data)
{
	if (data->slide.animation)
		;
	else if (k == TAB && !data->color_animation)
		toggle_menu_animation(data);
	else if (k == ESQ)
		close_mlx(data);
	else if (data->in_menu && !data->menu.animation && !data->color_animation)
		launch_fractals(data, k);
	else if (k == Q)
		start_reset_animation(data);
	else if (!data->menu.animation)
		set_hook_preset(data, k);
	return (SUCCESS);
}

static void	launch_fractals(t_data *data, int k)
{
	const int	key1[4] = {NUM_1, NUM_2, NUM_3, NUM_4};
	const int	key2[4] = {PAV_1, PAV_2, PAV_3, PAV_4};
	t_pos		i;

	i = POS_1;
	while (i <= POS_4)
	{
		if (k == key1[i] || k == key2[i])
		{
			data->f = data->fractals + data->menus[i];
			toggle_menu_animation(data);
		}
		i++;
	}
}

static void	set_hook_preset(t_data *data, int k)
{
	const int	key1[10] = {NUM_0, NUM_1, NUM_2, NUM_3, NUM_4, NUM_5, NUM_6, \
NUM_7, NUM_8, NUM_9};
	const int	key2[10] = {PAV_0, PAV_1, PAV_2, PAV_3, PAV_4, PAV_5, PAV_6, \
PAV_7, PAV_8, PAV_9};
	t_preset	p;

	p = PRESET_0;
	while (p <= PRESET_9 && data->f->max_preset >= p)
	{
		if (key1[p] == k || key2[p] == k)
		{
			data->f->animation_c.start = data->f->c;
			data->f->animation_c.end = data->f->preset(p);
			if (data->f->animation_c.start.x != data->f->animation_c.end.x && \
data->f->animation_c.start.y != data->f->animation_c.end.y)
			{
				data->edit = FALSE;
				data->edit_c = FALSE;
				data->c_animation = TRUE;
				data->i_c = 0;
			}
		}
		p++;
	}
}
