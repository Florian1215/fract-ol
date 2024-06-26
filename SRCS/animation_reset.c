/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_reset.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 19:29:38 by fguirama          #+#    #+#             */
/*   Updated: 2023/12/04 19:29:38 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		compute_value(t_data *data, int i, int start_max_iter);

t_bool	start_reset_animation(t_data *data)
{
	if (data->reset || !mem_cmp(&data->f->plan, &data->f->plan_default))
		return (FALSE);
	data->reset = TRUE;
	return (TRUE);
}

void	reset_animation(t_data *data)
{
	static int	i = 0;
	static int	start_max_iter = 0;

	if (i == 0)
	{
		data->f->animation_plan = data->f->plan;
		start_max_iter = data->f->max_iter;
	}
	else if (i == FRAME_ANIMATION)
	{
		data->reset = FALSE;
		data->f->plan = data->f->plan_default;
		i = 0;
		return ;
	}
	compute_value(data, i, start_max_iter);
	i++;
}

static void	compute_value(t_data *data, int i, int start_max_iter)
{
	data->f->plan.start.x = get_value(data->f->animation_plan.start.x, \
data->f->plan_default.start.x, i);
	data->f->plan.start.y = get_value(data->f->animation_plan.start.y, \
data->f->plan_default.start.y, i);
	data->f->plan.end.x = get_value(data->f->animation_plan.end.x, \
data->f->plan_default.end.x, i);
	data->f->plan.end.y = get_value(data->f->animation_plan.end.y, \
data->f->plan_default.end.y, i);
	data->f->max_iter = get_value(start_max_iter, MAX_ITER, i);
}
