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

	start_render = get_timestamp();
	pthread_mutex_lock(&data->render);
	if (data->slide.animation)
		render_slide(data);
	else if (data->menu.animation)
		menu_animation(data);
	else if (data->in_menu && is_hover_animation(data->hover))
		hover_animation(data);
	else
	{
		render = (data->edit || data->zoom_size || data->c_animate || \
data->reset || data->update);
		if (data->c_animate)
			c_animation(data);
		if (data->reset)
			reset_animation(data);
		if (render)
			render_fractal(data);
		if (data->zoom_size == 1)
			data->update = TRUE;
		if (data->zoom_size)
			data->zoom_size--;
	}
	pthread_mutex_unlock(&data->render);
	sleep_until(start_render + FPS);
	return (SUCCESS);
}
