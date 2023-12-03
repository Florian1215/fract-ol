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

static void	launch_factals(t_data *data, int k);
static void	set_hook_preset(t_data *data, int k);

int	key_event_press(int k, t_data *data)
{
	if (k == LEFT || k == RIGHT)
		slide_page(data, k);
	if (data->slide.animation)
		return (ERROR);
	if (k == D)
		toggle_appearance(data);
	else if (k == C) // TODO dont work
		edit_color(data);
	if (data->reset)
		return (ERROR);
	if (data->in_menu)
		launch_factals(data, k);
	else if (k == PLUS)
		edit_iter(data, 10);
	else if (k == MINUS)
		edit_iter(data, -10);
	return (SUCCESS);
}

static void	launch_factals(t_data *data, int k)
{
	const int	key1[4] = {NUM_1, NUM_2, NUM_3, NUM_4};
	const int	key2[4] = {PAV_1, PAV_2, PAV_3, PAV_4};
	t_pos		i;

	i = POS_1;
	while (i <= POS_4)
	{
		if (k == key1[i] || k == key2[i])
			launch_fractal(data, data->menu[i]);
		i++;
	}
}

int	key_event(int k, t_data *data)
{
	if (data->slide.animation)
		return (ERROR);
	if (k == ESQ)
		close_mlx(data);
	if (data->in_menu)
		return (ERROR);
	else if (k == Q && !data->reset)
		data->reset = TRUE;
	else if (k == SPACE && !data->reset)
		launch_fractal(data, data->f->set);
	else if (k == TAB)
	{
		if (data->f->set < BUFFALO)
			data->page = 0;
		else if (data->f->set < PERPENDICULAR_CELTIC)
			data->page = 1;
		else
			data->page = 2;
		set_page(data, data->page);
	}
	else
		set_hook_preset(data, k);
	return (SUCCESS);
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
				data->c_animate = TRUE;
				data->i_c = 0;
			}
		}
		p++;
	}
}
