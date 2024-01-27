/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 16:22:30 by fguirama          #+#    #+#             */
/*   Updated: 2022/12/12 16:22:31 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		init_hovers(t_data *data);
static void	render_fractals(t_data *data, t_thread_preview *t);
static void	fractal_preview(t_thread_preview *t);
void		zoom_hover(t_fractal *f, double scale);
void		draw_alpha(t_img *img, t_img *alpha, t_co pos, double ratio);


void	set_menu(t_data *data)
{
	t_pos				i;
	t_thread_preview	t[4];

	if (!data->in_menu)
	{
		data->in_menu = TRUE;
		init_hovers(data);
		cancel_animation(data);
	}
	render_fractals(data, t);
	i = POS_1;
	while (i < 4)
		pthread_join(t[i++].thread, NULL);
	set_names_fractal(data, data->img.img, 0);
}

static void	render_fractals(t_data *data, t_thread_preview *t)
{
	t_pos				i;
	t_fractals			f;

	i = POS_1;
	while (i < 4)
	{
		f = i + data->page * 4;
		if (data->hover[i].is_active)
			data->fractals[f].max_iter = data->hover[i].max_iter.value;
		t[i].data = data;
		t[i].frac = data->fractals + f;
		t[i].pos = i;
		pthread_create(&t[i].thread, NULL, (void *)fractal_preview, &t[i]);
		i++;
	}
}

static void	fractal_preview(t_thread_preview *t)
{
	t_co	i;
	double	col;
	t_co	r;
	t_img	*img;

	if (t->data->slide.render_img || t->data->menu.save_img)
		img = &t->data->slide.img;
	else
		img = &t->data->img;
	if (t->data->hover[t->pos].is_active)
		zoom_hover(t->frac, t->data->hover[t->pos].zoom.value);
	r = get_r(t->frac);
	i.x = 0;
	while (i.x < WIN)
	{
		i.y = 0;
		while (i.y < WIN)
		{
			col = t->frac->sequence(t->data, t->frac, (t_co){\
t->frac->plan.start.x + i.x * r.x, t->frac->plan.end.y - i.y * r.y});
			mlx_put_pixel_img(img, (t_co){i.x / 2 + \
t->frac->menu.start.x, i.y / 2 + t->frac->menu.start.y}, col);
			i.y += 2;
		}
		i.x += 2;
	}
}

// TODO set name fractal
void	set_names_fractal(t_data *data, void *img, int x_offset)
{
	t_img		*name;
	int			i;
	t_co		offset;

	i = 0;
	while (i < 4)
	{
		printf("%d\n", i + data->page * 4);
		name = &data->fractals[i + data->page * 4].name;
		offset = (t_co){QWIN + x_offset, QWIN};
		if (i % 2)
			offset.x += HWIN;
		offset.x -= name->width / 2;
		if (i >= 2)
			offset.y += HWIN;
		offset.y -= name->height / 2;
		draw_alpha(&data->img, name, offset, 1);
		i++;
	}
	if (!data->slide.animation)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, img, x_offset, 0);
}
