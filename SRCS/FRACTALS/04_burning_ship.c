/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frac_burning_ship.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 12:31:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/01/02 12:31:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_burning_shipe(t_fractal *f)
{
	f->set = BURNING_SHIP;
	f->plan.start = (t_co){-2.4, 1.6};
	f->plan.end = (t_co){1.6, -2.4};
	f->sequence = burning_shipe;
	f->max_preset = PRESET_0;
	f->color = RED;
}

int	burning_shipe(t_data *data, t_fractal *frac, t_co c, t_co co)
{
	t_co	z;
	t_co	sqr;
	int		i;

	z = (t_co){frac->c.x, frac->c.y};
	sqr = (t_co){pow(z.x, 2), pow(z.y, 2)};
	i = 0;
	while (i < frac->max_iter)
	{
		z.y = 2 * fabs(z.x * z.y) + c.y;
		z.x = sqr.x - sqr.y + c.x;
		sqr = (t_co){pow(z.x, 2), pow(z.y, 2)};
		if (sqr.x + sqr.y > 4)
			return (get_color(data, (t_color_data){frac, i, sqr.x + sqr.y}, \
co, z));
		i++;
	}
	return (FG);
}

void	init_red(t_data *data)
{
	data->pal[RED][LIGHT][0] = (t_color){0xF45D4C};
	data->pal[RED][LIGHT][1] = (t_color){0xF7A541};
	data->pal[RED][LIGHT][2] = (t_color){0xFACA66};
	data->pal[RED][LIGHT][3] = (t_color){0xFEE5AD};
	data->pal[RED][LIGHT][4] = (t_color){0xA1DBB2};
	data->pal[RED][DARK][0] = (t_color){FG};
	data->pal[RED][DARK][1] = (t_color){0x374140};
	data->pal[RED][DARK][2] = (t_color){0x817A63};
	data->pal[RED][DARK][3] = (t_color){0xD9CB9E};
	data->pal[RED][DARK][4] = (t_color){0xDC3522};
}
