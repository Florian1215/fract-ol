/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frac_buffalo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 12:33:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/01/02 12:33:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static t_co	preset_buffalo(t_preset preset);

void	init_buffalo(t_fractal *f)
{
	f->set = BUFFALO;
	f->plan.start = (t_co){-2.1, 2.1};
	f->plan.end = (t_co){2.1, -2.1};
	f->sequence = buffalo;
	f->animation_c.start = (t_co){-1, 1};
	f->preset = preset_buffalo;
	f->max_preset = PRESET_9;
	f->color = BLUE_RED;
	f->offset_name = 25;
}

int	buffalo(t_data *data, t_fractal *frac, t_co z, t_co co)
{
	int		i;
	t_co	sqr;

	i = 0;
	sqr = (t_co){pow(z.x, 2), pow(z.y, 2)};
	while (i < frac->max_iter)
	{
		z.y = 2 * fabs(z.x * z.y) + frac->c.y;
		z.x = fabs(sqr.x - sqr.y) + frac->c.x;
		sqr = (t_co){pow(z.x, 2), pow(z.y, 2)};
		if (sqr.x + sqr.y > 4)
			return (get_color(data, (t_color_data){frac, i, sqr.x + sqr.y}, \
co, z));
		i++;
	}
	return (FG);
}

static t_co	preset_buffalo(t_preset preset)
{
	static double	presets[PRESET_9 + 1][2] = {
	{-1.14, 0.06},
	{0.406, -0.936},
	{-0.936, 0.052},
	{0.536, -1.026},
	{-1.752, -0.544},
	{0.366, -0.676},
	{-1.552, -1.772},
	{-1.13, 0.08},
	{-0.428, -1.52},
	{0.426, -0.716},
	};

	return ((t_co){presets[preset][0], presets[preset][1]});
}

void	init_blue_red(t_data *data)
{
	data->pal[BLUE_RED][LIGHT][0] = (t_color){0x00748E};
	data->pal[BLUE_RED][LIGHT][1] = (t_color){0xE3DFBB};
	data->pal[BLUE_RED][LIGHT][2] = (t_color){0xF4BA4D};
	data->pal[BLUE_RED][LIGHT][3] = (t_color){0xE3753C};
	data->pal[BLUE_RED][LIGHT][4] = (t_color){0xDA3B3A};
	data->pal[BLUE_RED][DARK][0] = (t_color){FG};
	data->pal[BLUE_RED][DARK][1] = (t_color){0x263248};
	data->pal[BLUE_RED][DARK][2] = (t_color){0x7E8AA2};
	data->pal[BLUE_RED][DARK][3] = (t_color){0xE3DFBB};
	data->pal[BLUE_RED][DARK][4] = (t_color){0xF0642A};
}
