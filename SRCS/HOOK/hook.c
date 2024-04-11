/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 10:49:38 by fguirama          #+#    #+#             */
/*   Updated: 2022/12/10 10:49:39 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int			key_event_press(int k, t_data *data);
int			mouse_event_press(int button, int x, int y, t_data *data);
int			mouse_event_release(int button, int x, int y, t_data *data);
int			mouse_event_motion(int x, int y, t_data *data);
int			key_event(int k, t_data *data);
static int	hook_loop(t_data *data);
void		render_slide(t_data *data);
void		menu_animation(t_data *data);
void		hover_animation(t_data *data);
void		c_animation(t_data *data);
void		reset_animation(t_data *data);
static void	set_render_fractal(t_data *data, t_time start_render, \
				t_bool *render, t_bool *full_render);
static void	set_render_level(t_data *data, t_bool full_render, \
				t_time time_render);
t_bool		is_hover_animation(t_hover *hover);

void	set_hook(t_data *data)
{
	mlx_hook(data->win_ptr, 2, (1L << 0), key_event_press, data);
	mlx_hook(data->win_ptr, 4, (1L << 2), mouse_event_press, data);
	mlx_hook(data->win_ptr, 5, (1L << 3), mouse_event_release, data);
	mlx_hook(data->win_ptr, 6, (1L << 6), mouse_event_motion, data);
	mlx_hook(data->win_ptr, 17, 0, close_mlx, data);
	mlx_key_hook(data->win_ptr, key_event, data);
	mlx_loop_hook(data->mlx_ptr, hook_loop, data);
}

static int	hook_loop(t_data *data)
{
	t_time		start_render;
	t_bool		render;
	t_bool		full_render;

	render = FALSE;
	full_render = FALSE;
	start_render = get_timestamp();
	if (data->slide.animation)
		render_slide(data);
	else if (data->menu.animation)
		menu_animation(data);
	else if (data->in_menu && is_hover_animation(data->hover))
		hover_animation(data);
	else
		set_render_fractal(data, start_render, &render, &full_render);
	if (render)
		set_render_level(data, full_render, get_timestamp() - start_render);
	sleep_until(start_render + FPS);
	return (SUCCESS);
}

static void	set_render_fractal(t_data *data, t_time start_render, \
				t_bool *render, t_bool *full_render)
{
	*render = (data->edit || data->edit_c || data->zoom_size || \
data->c_animate || data->reset || data->update);
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
	if (data->c_animate)
		c_animation(data);
	if (data->reset)
		reset_animation(data);
	if (*render || *full_render)
		render_fractal(data);
	if (data->zoom_size == 1)
		data->update = TRUE;
	if (data->zoom_size)
		data->zoom_size--;
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
