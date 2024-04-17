/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frac_celtic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 12:30:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/01/02 12:30:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_celtic(t_fractal *f)
{
	f->set = CELTIC;
	f->plan.start = (t_co){-2, 1.3};
	f->plan.end = (t_co){2, -2.7};
	f->sequence = celtic;
	f->color = ELECTRIC_BLUE;
	f->max_preset = PRESET_0;
	f->offset_name = 18;
}

int	celtic(t_data *data, t_fractal *frac, t_co c, t_co co)
{
	int		i;
	t_co	z;
	t_co	sqr;

	i = 0;
	z = (t_co){c.x, c.y};
	sqr = (t_co){pow(z.x, 2), pow(z.y, 2)};
	while (i < frac->max_iter)
	{
		z.y = (2 * z.x * z.y) + c.x + frac->c.x;
		z.x = fabs(sqr.x - sqr.y) + c.y + fabs(frac->c.y);
		sqr = (t_co){pow(z.x, 2), pow(z.y, 2)};
		if (sqr.x + sqr.y > 4)
			return (get_color(data, (t_color_data){frac, i, sqr.x + sqr.y}, \
co, z));
		i++;
	}
	return (FG);
}

#define ELECTRIC_BLUE_01	0x007882
#define ELECTRIC_BLUE_02	0x23AA8F
#define ELECTRIC_BLUE_03	0x86D780
#define ELECTRIC_BLUE_04	0xFAFA6E

void	init_electric_blue(t_data *data)
{
	data->pal[ELECTRIC_BLUE][LIGHT][0] = (t_color){0x2A4858};
	data->pal[ELECTRIC_BLUE][LIGHT][1] = (t_color){ELECTRIC_BLUE_01};
	data->pal[ELECTRIC_BLUE][LIGHT][2] = (t_color){ELECTRIC_BLUE_02};
	data->pal[ELECTRIC_BLUE][LIGHT][3] = (t_color){ELECTRIC_BLUE_03};
	data->pal[ELECTRIC_BLUE][LIGHT][4] = (t_color){ELECTRIC_BLUE_04};
	data->pal[ELECTRIC_BLUE][DARK][0] = (t_color){FG};
	data->pal[ELECTRIC_BLUE][DARK][1] = (t_color){ELECTRIC_BLUE_01};
	data->pal[ELECTRIC_BLUE][DARK][2] = (t_color){ELECTRIC_BLUE_02};
	data->pal[ELECTRIC_BLUE][DARK][3] = (t_color){ELECTRIC_BLUE_03};
	data->pal[ELECTRIC_BLUE][DARK][4] = (t_color){ELECTRIC_BLUE_04};
}
