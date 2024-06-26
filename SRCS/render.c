/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:30:55 by fguirama          #+#    #+#             */
/*   Updated: 2022/12/14 15:30:56 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		exec_key_buff(t_data *data);
void		render_slide(t_data *data, t_bool *render);
void		menu_animation(t_data *data, t_bool *render);
static void	set_render_menu(t_data *data, t_bool *render);
t_bool		is_hover_animation(t_hover *hover);
void		hover_animation(t_data *data);
static void	set_render_fractal(t_data *data, t_time start_render, \
t_bool *render, t_bool *full_render);
static void	set_full_render(t_data *data, t_time start_render, t_bool *render, \
t_bool *full_render);
void		c_animation(t_data *data);
void		reset_animation(t_data *data);
static void	set_render_level(t_data *data, t_bool full_render, \
				t_time time_render);

int	hook_loop(t_data *data)
{
	t_time		start_render;
	t_bool		render;
	t_bool		full_render;

	render = FALSE;
	full_render = FALSE;
	start_render = get_timestamp();
	if (data->kbuff)
		exec_key_buff(data);
	if (data->menu.animation)
		menu_animation(data, &render);
	else if (data->slide.animation)
		render_slide(data, &render);
	else if (data->in_menu)
		set_render_menu(data, &render);
	else
		set_render_fractal(data, start_render, &render, &full_render);
	if (render)
	{
		set_render_level(data, full_render, get_timestamp() - start_render);
		sleep_until(start_render + FPS);
		data->update = FALSE;
	}
	return (SUCCESS);
}

static void	set_render_menu(t_data *data, t_bool *render)
{
	*render = (data->update || is_hover_animation(data->hover) || \
data->color_animation || data->appearance_animation || data->bw_animation);
	if (is_hover_animation(data->hover))
		hover_animation(data);
	if (data->color_animation || data->bw_animation)
		color_animation(data);
	if (data->appearance_animation)
		appearance_animation(data);
	if (*render)
		set_menu(data);
}

static void	set_render_fractal(t_data *data, t_time start_render, \
t_bool *render, t_bool *full_render)
{
	*render = (data->edit || data->edit_c || data->zoom_size || \
data->c_animation || data->color_animation || data->appearance_animation || \
data->bw_animation || data->reset || data->update);
	set_full_render(data, start_render, render, full_render);
	if (data->c_animation)
		c_animation(data);
	if (data->reset)
		reset_animation(data);
	if (data->color_animation || data->bw_animation)
		color_animation(data);
	if (data->appearance_animation)
		appearance_animation(data);
	if (*render || *full_render)
		render_fractal(data);
	if (data->zoom_size == 1)
		data->update = TRUE;
	if (data->zoom_size)
		data->zoom_size--;
}

static void	set_full_render(t_data *data, t_time start_render, t_bool *render, \
t_bool *full_render)
{
	if (*render && data->prev_render)
	{
		data->render_level = _25;
		data->prev_render = FALSE;
	}
	else if (!*render && data->last_render + 1000 > start_render && \
data->render_level != _100)
	{
		*full_render = TRUE;
		data->render_level = _100;
		data->prev_render = TRUE;
	}
}

static void	set_render_level(t_data *data, t_bool full_render, t_time \
time_render)
{
	data->last_render = get_timestamp();
	if (!full_render && time_render < 20 && data->render_level != _100)
		data->render_level--;
	else if (!full_render && time_render > 120)
		data->render_level = _25;
	else if (!full_render && time_render > 80 && data->render_level != _25)
		data->render_level++;
}
