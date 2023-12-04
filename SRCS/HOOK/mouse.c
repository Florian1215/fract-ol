/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_mouse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 18:02:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/01/02 18:02:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static t_pos	select_fractal(t_co co);
t_pos			get_last_hover(t_hover *hover);
void			new_hover(t_hover *hover, t_pos new);
static void		mouse_event_fractal(t_data *data, int button, t_co click);
void			zoom(t_data *data, t_bool scroll_in, t_co co);

int	mouse_event_press(int button, int x, int y, t_data *data)
{
	if (data->slide.animation || data->reset)
		return (ERROR);
	if (data->in_menu && button == LEFT_CLICK)
	{
		data->f = data->fractals + data->menus[select_fractal((t_co){x, y})];
		toggle_menu_animation(data);
	}
	else
		mouse_event_fractal(data, button, (t_co){x, y});
	return (SUCCESS);
}

int	mouse_event_release(int button, int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	if (!data->in_menu)
	{
		if (button == LEFT_CLICK)
		{
			data->moving = FALSE;
			data->edit = FALSE;
			data->update = TRUE;
		}
		else if (button == RIGHT_CLICK)
		{
			data->edit = FALSE;
			data->edit_c = FALSE;
			data->update = TRUE;
		}
	}
	return (SUCCESS);
}

int	mouse_event_motion(int x, int y, t_data *data)
{
	t_pos	current;

	if (data->slide.animation || data->reset)
		return (ERROR);
	if (data->in_menu)
	{
		current = select_fractal((t_co){x, y});
		if (current != get_last_hover(data->hover))
			new_hover(data->hover, current);
	}
	else if (data->moving)
		move(data, x, y);
	else if (data->edit_c)
		data->f->c = (t_co){(double)(x - HWIN) / QWIN, (double)(y - HWIN) / \
QWIN};
	return (SUCCESS);
}

static t_pos	select_fractal(t_co co)
{
	int	hsize;

	if (co.x > WIN - 50 || co.y > WIN - 50 || co.x < 50 || \
co.y < 50)
		return (POS_ERROR);
	hsize = WIN / 2;
	if (co.x < hsize && co.y < hsize)
		return (POS_1);
	else if (co.x > hsize && co.y < hsize)
		return (POS_2);
	else if (co.x < hsize && co.y > hsize)
		return (POS_3);
	else
		return (POS_4);
}

static void	mouse_event_fractal(t_data *data, int button, t_co click)
{
	t_co		co;

	if (button == SCROLL_IN || button == SCROLL_OUT)
	{
		co.x = (double)click.x / (WIN / (data->f->plan.end.x - \
data->f->plan.start.x)) + data->f->plan.start.x;
		co.y = (double)click.y / (WIN / (data->f->plan.end.y - \
data->f->plan.start.y)) * -1 + data->f->plan.end.y;
		zoom(data, button == SCROLL_IN, co);
		data->zoom_size++;
	}
	else if (button == LEFT_CLICK)
	{
		data->prev_pos = click;
		data->moving = TRUE;
		data->edit = TRUE;
	}
	else if (button == RIGHT_CLICK)
	{
		data->edit_c = TRUE;
		data->edit = TRUE;
		mouse_event_motion(click.x, click.y, data);
	}
}
