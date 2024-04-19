/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_menu.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 15:20:40 by fguirama          #+#    #+#             */
/*   Updated: 2023/12/04 15:20:40 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	set_menu_animation_from_menu(t_data *data);
static void	set_menu_animation_from_fractal(t_data *data);
void		menu_animation(t_data *data, t_bool *render);
static void	put_resize_image(t_data *data, int size);

void	toggle_menu_animation(t_data *data)
{
	t_bool	menu;

	if (data->color_animation || data->bw_animation)
		return (lst_new(data, TAB));
	if (data->in_menu)
		set_menu_animation_from_menu(data);
	else
		set_menu_animation_from_fractal(data);
	menu = !data->in_menu;
	data->menu.pos = data->f->set % 4;
	data->menu.save_img = TRUE;
	set_page(data, data->page, FALSE);
	data->menu.save_img = FALSE;
	data->in_menu = menu;
	data->menu.step = (t_co){1, 1};
	data->menu.v.x = WIN * (data->menu.pos % 2);
	data->menu.v.y = WIN * (data->menu.pos >= 2);
	if (data->menu.pos % 2)
		data->menu.step.x = -1;
	if (data->menu.pos >= 2)
		data->menu.step.y = -1;
}

static void	set_menu_animation_from_menu(t_data *data)
{
	set_color(data, data->f->color);
	data->menu.i = 0;
	if (data->menu.animation)
		data->menu.start = data->menu.size;
	else
		data->menu.start = WIN;
	data->menu.animation = TRUE;
	data->menu.end = WIN * 2;
}

static void	set_menu_animation_from_fractal(t_data *data)
{
	init_hovers(data);
	cancel_animation(data);
	data->offset_color = data->color - data->f->color;
	if (data->menu.animation)
		data->menu.start = data->menu.size;
	else
		data->menu.start = WIN * 2;
	data->menu.i = 0;
	data->menu.end = WIN;
	data->menu.animation = TRUE;
}

void	menu_animation(t_data *data, t_bool *render)
{
	if (data->menu.i == FRAME_ANIMATION)
	{
		data->menu.animation = FALSE;
		data->update = TRUE;
		return ;
	}
	data->menu.size = get_value(data->menu.start, data->menu.end, \
data->menu.i++);
	if (data->appearance_animation)
	{
		appearance_animation(data);
		data->menu.save_img = TRUE;
		set_page(data, data->page, FALSE);
		data->menu.save_img = FALSE;
	}
	put_resize_image(data, data->menu.size);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0);
	*render = TRUE;
}

static void	put_resize_image(t_data *data, int size)
{
	t_co	t;
	t_co	i;
	int		color;
	double	increment;

	increment = (double)WIN / size;
	i.x = data->menu.v.x;
	t.x = data->menu.v.x;
	while ((i.x < WIN && !data->menu.v.x) || (i.x >= 0 && data->menu.v.x))
	{
		i.y = data->menu.v.y;
		t.y = data->menu.v.y;
		while ((i.y < WIN && !data->menu.v.y) || (i.y >= 0 && data->menu.v.y))
		{
			color = *(int *)(data->slide.img.addr + (int)t.x * \
data->slide.img.bit_ratio + (int)t.y * data->slide.img.line_length);
			mlx_put_pixel_img(&data->img, i, color);
			i.y += data->menu.step.y;
			t.y += increment * data->menu.step.y;
		}
		i.x += data->menu.step.x;
		t.x += increment * data->menu.step.x;
	}
}
