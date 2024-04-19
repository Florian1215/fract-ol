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

int			key_event(int k, t_data *data);
static void	launch_fractals(t_data *data, int k);
static void	set_hook_preset(t_data *data, int k);

void	exec_key_buff(t_data *data)
{
	t_list	*tmp;

	data->is_key_buff = TRUE;
	key_event(data->kbuff->k, data);
	if (data->is_key_buff)
	{
		tmp = data->kbuff;
		data->kbuff = data->kbuff->next;
		free(tmp);
		data->is_key_buff = FALSE;
	}
}

int	key_event(int k, t_data *data)
{
	if (k == LEFT || k == RIGHT)
		slide_page(data, k);
	else if (data->slide.animation)
		lst_new(data, k);
	else if (k == D)
		toggle_appearance(data);
	else if (k == X || k == Z)
		set_bw(data, k);
	else if (k == C)
		edit_color(data);
	else if (k == TAB)
		toggle_menu_animation(data);
	else if (k == ESQ)
		close_mlx(data);
	else if (data->in_menu)
		launch_fractals(data, k);
	else if (!data->reset && k == PLUS)
		edit_iter(data, 10);
	else if (!data->reset && k == MINUS)
		edit_iter(data, -10);
	else if (k == Q)
		start_reset_animation(data);
	else
		set_hook_preset(data, k);
	return (SUCCESS);
}

static void	launch_fractals(t_data *data, int k)
{
	const int	key1[4] = {NUM_1, NUM_2, NUM_3, NUM_4};
	const int	key2[4] = {PAV_1, PAV_2, PAV_3, PAV_4};
	t_pos		i;

	if (data->menu.animation || data->color_animation || data->bw_animation)
	{
		lst_new(data, k);
		return ;
	}
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
	const int	key[2][10] = {{NUM_0, NUM_1, NUM_2, NUM_3, NUM_4, NUM_5, NUM_6, \
NUM_7, NUM_8, NUM_9}, {PAV_0, PAV_1, PAV_2, PAV_3, PAV_4, PAV_5, PAV_6, \
PAV_7, PAV_8, PAV_9}};
	t_preset	p;

	p = PRESET_0;
	while (p <= PRESET_9 && data->f->max_preset >= p)
	{
		if (key[0][p] == k || key[1][p] == k)
		{
			if (data->menu.animation)
				return (lst_new(data, k));
			data->f->animation_c.start = data->f->c;
			data->f->animation_c.end = data->f->preset(p);
			if (mem_cmp(&data->f->animation_c.start, &data->f->animation_c.end))
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
