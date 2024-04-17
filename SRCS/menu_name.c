/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_name.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:43:00 by fguirama          #+#    #+#             */
/*   Updated: 2024/04/17 13:43:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	set_name_fractal(t_data *data, int x_offset, t_img *img, int i);
void		draw_alpha(t_img *img, t_img *alpha, t_co pos, t_co color_ratio);

void	set_names_fractal(t_data *data, void *img_ptr, int x_offset)
{
	int		i;
	t_img	*img;

	if (data->slide.render_img || data->menu.save_img)
		img = &data->slide.img;
	else
		img = &data->img;
	i = 0;
	while (i < 4)
	{
		set_name_fractal(data, x_offset, img, i);
		i++;
	}
	if (!data->slide.animation)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, img_ptr, \
x_offset, 0);
}

static void	set_name_fractal(t_data *data, int x_offset, t_img *img, int i)
{
	t_co			offset;
	t_img			*name;
	int				i_shadow;

	name = &data->fractals[i + data->page * 4].name;
	offset = (t_co){MAX_SHADOW + data->qwin + x_offset, MAX_SHADOW + \
data->qwin};
	if (i % 2)
		offset.x += data->hwin;
	offset.x -= name->width * data->ratio_title / 2;
	if (i >= 2)
		offset.y += data->hwin;
	offset.y -= name->height * data->ratio_title / 2;
	i_shadow = 0;
	while (i_shadow < MAX_SHADOW)
	{
		draw_alpha(img, name, offset, (t_co){FG, data->ratio_title});
		offset = (t_co){offset.x - 1, offset.y - 1};
		i_shadow++;
	}
	draw_alpha(img, name, (t_co){offset.x - 1, offset.y - 1}, (t_co){\
FG, data->ratio_title});
	draw_alpha(img, name, offset, (t_co){WHITE, data->ratio_title});
}
