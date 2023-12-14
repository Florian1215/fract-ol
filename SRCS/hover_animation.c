/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hover_animation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 18:19:34 by fguirama          #+#    #+#             */
/*   Updated: 2023/12/03 18:19:34 by fguirama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	init_unhover(t_hover *hover, t_pos i);
static void	init_new_hover(t_hover *hover, t_pos new);

void	new_hover(t_hover *hover, t_pos new)
{
	t_pos	i;

	i = POS_1;
	while (i < 4)
	{
		if (hover[i].hover)
			init_unhover(hover, i);
		i++;
	}
	if (new != POS_ERROR)
		init_new_hover(hover, new);
}

static void	init_unhover(t_hover *hover, t_pos i)
{
	if (hover[i].animation)
	{
		hover[i].zoom.start = hover[i].zoom.value;
		hover[i].max_iter.start = hover[i].max_iter.value;
	}
	else
	{
		hover[i].zoom.start = ZOOM_HOVER;
		hover[i].max_iter.start = MAX_ITER_HOVER;
	}
	hover[i].zoom.end = ZOOM_MENU;
	hover[i].max_iter.end = MAX_ITER;
	hover[i].hover = FALSE;
	hover[i].unhover = TRUE;
	hover[i].animation = TRUE;
	hover[i].i = 0;
}

static void	init_new_hover(t_hover *hover, t_pos new)
{
	if (hover[new].animation)
	{
		hover[new].zoom.start = hover[new].zoom.value;
		hover[new].max_iter.start = hover[new].max_iter.value;
	}
	else
	{
		hover[new].zoom.start = ZOOM_MENU;
		hover[new].max_iter.start = MAX_ITER;
	}
	hover[new].zoom.end = ZOOM_HOVER;
	hover[new].max_iter.end = MAX_ITER_HOVER;
	hover[new].i = 0;
	hover[new].unhover = FALSE;
	hover[new].hover = TRUE;
	hover[new].animation = TRUE;
	hover[new].is_active = TRUE;
}

void	hover_animation(t_data *data)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (!data->hover[i].animation)
			continue ;
		if (data->hover[i].i == 28)
		{
			data->hover[i].animation = FALSE;
			if (data->hover[i].unhover)
				data->hover[i].is_active = FALSE;
			continue ;
		}
		data->hover[i].zoom.value = get_value(data->hover[i].zoom.start, \
data->hover[i].zoom.end, data->hover[i].i);
		data->hover[i].max_iter.value = get_value(data->hover[i].max_iter. \
start, data->hover[i].max_iter.end, data->hover[i].i);
		data->hover[i].i += 4;
	}
	set_menu(data);
}

void	zoom_hover(t_fractal *f, double scale)
{
	f->plan.start.x = cross_multi_plan(0, f->plan_default.start.x, scale);
	f->plan.start.y = cross_multi_plan(0, f->plan_default.start.y, scale);
	f->plan.end.x = cross_multi_plan(0, f->plan_default.end.x, scale);
	f->plan.end.y = cross_multi_plan(0, f->plan_default.end.y, scale);
}
