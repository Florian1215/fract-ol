/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_page.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 16:54:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/01/07 16:54:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	init_slide_page(t_data *data, int side);

void	slide_page(t_data *data, int side)
{
	if (data->slide.animation)
	{
		if (data->slide.side == side && data->slide.i < 15)
			return ;
		data->slide.i = 0;
		if (side == LEFT)
			data->slide.start = data->slide.value - WIN;
		else
		{
			data->slide.start = data->slide.value + WIN; // TODO fix pb image
//			printf("PB %d\n", data->slide.start);
		}
	}
	else
	{
		data->slide.start = WIN;
		if (side == LEFT)
			data->slide.start *= -1;
	}
	data->slide.animation = TRUE;
	data->slide.render_img = TRUE;
	if (data->in_menu)
		set_menu(data);
	else
		render_fractal(data);
	data->slide.render_img = FALSE;
//	dup_img(&data->img, &data->slide.img);
	data->slide.side = side;
	init_slide_page(data, side);
}

static void	init_slide_page(t_data *data, int side)
{
	t_fractals	set;

	if (data->in_menu)
	{
		if (side == LEFT)
			set_page(data, data->page - 1);
		else
			set_page(data, data->page + 1);
	}
	else
	{
		if (side == LEFT && data->f->set)
			set = data->f->set - 1;
		else if (side == LEFT)
			set = CELTIC_MANDELBROT;
		else
			set = (data->f->set + 1) % 12;
		data->f = data->fractals + set;
		render_fractal(data);
	}
}

void	render_slide(t_data *data)
{
	int	x_from;

//	if (data->slide.i == 0)
//	{
//		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0);
//		data->slide.i++;
//		data->render = FALSE;
//		return;
//	}
//	if (data->slide.i == 1)
//	{
//		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->slide.img.img, 0, 0);
//		data->slide.i++;
//		data->render = FALSE;
//		return;
//	}
	if (data->slide.i == FRAME_ANIMATION)
	{
		cancel_animation(data);
		data->slide.i = 0;
		return ;
	}
	data->slide.value = get_value(data->slide.start, 0, data->slide.i++) * WIN / \
1000;
	if (data->slide.side == LEFT)
		x_from = data->slide.value + WIN;
	else
	{
//		printf("%d | %d - %d\n", data->slide.pos, data->slide.start, 0);
		x_from = data->slide.value - WIN;
	}
	if (data->in_menu)
		set_names_fractal(data, data->img.img, data->slide.value);
	else
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, \
data->slide.value, 0);
//	printf("put 2 at %d\n", x_from);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, \
data->slide.img.img, x_from, 0);
}
