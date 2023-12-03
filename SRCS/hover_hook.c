/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hover_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 18:18:06 by fguirama          #+#    #+#             */
/*   Updated: 2023/12/03 18:18:06 by fguirama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_hovers(t_data *data)
{
	t_pos	i;

	i = POS_1;
	while (i < 4)
	{
		data->hover[i].is_on = FALSE;
		data->hover[i].animation = FALSE;
		data->hover[i].hover = FALSE;
		i++;
	}
}

t_bool	is_hover_animation(t_hover *hover)
{
	t_pos	i;

	i = POS_1;
	while (i < 4)
	{
		if (hover[i].animation)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

t_pos	get_last_hover(t_hover *hover)
{
	t_pos	i;

	i = POS_1;
	while (i < 4)
	{
		if (hover[i].hover)
			return (i);
		i++;
	}
	return (POS_ERROR);
}
