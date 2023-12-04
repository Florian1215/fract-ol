/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_menu.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 15:20:40 by fguirama          #+#    #+#             */
/*   Updated: 2023/12/04 15:20:40 by fguirama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	set_menu_animation_from_menu(t_data *data);
static void	set_menu_animation_from_fractal(t_data *data);
void		menu_animation(t_data *data);
static void	put_resize_image(t_data *data, int size);

// TODO fix when toggle quickly
void	toggle_menu_animation(t_data *data)
{
	if (data->in_menu)
		set_menu_animation_from_menu(data);
	else
	{
		data->menu.is_toggle = TRUE;
		if (!data->menu.animation && start_reset_animation(data))
			return ;
		set_menu_animation_from_fractal(data);
	}
	data->menu.pos = data->f->set % 4;
	dup_img(&data->img, &data->slide.img);
	data->menu.step = (t_co){1, 1};
	data->menu.v.x = WIN * (data->menu.pos % 2);
	data->menu.v.y = WIN * (data->menu.pos >= 2);
	if (data->menu.pos % 2)
		data->menu.step.x = -1;
	if (data->menu.pos >= 2)
		data->menu.step.y = -1;
	menu_animation(data);
}

static void	set_menu_animation_from_menu(t_data *data)
{
	data->in_menu = FALSE;
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
	data->offset_color = data->color - data->f->color;
	if (data->f->set < BUFFALO)
		data->page = 0;
	else if (data->f->set < PERPENDICULAR_CELTIC)
		data->page = 1;
	else
		data->page = 2;
	if (data->menu.animation)
		data->menu.start = data->menu.size;
	else
		data->menu.start = WIN * 2;
	data->menu.i = 0;
	data->menu.end = WIN;
	data->menu.animation = TRUE;
	set_page(data, data->page);
}

void	menu_animation(t_data *data)
{
	if (data->menu.i == FRAME_ANIMATION)
	{
		data->menu.animation = FALSE;
		data->menu.is_toggle = FALSE;
		if (data->in_menu)
			set_menu(data);
		else
			data->update = TRUE;
		return ;
	}
	data->menu.size = get_value(data->menu.start, data->menu.end, \
data->menu.i++);
	put_resize_image(data, data->menu.size);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0);
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
