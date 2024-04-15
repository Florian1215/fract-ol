/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:30:55 by fguirama          #+#    #+#             */
/*   Updated: 2022/12/14 15:30:56 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	create_fractal(t_thread *t);
static void	compute_pixel(t_thread *t, t_co *i, t_co r);

void	render_fractal(t_data *data)
{
	int				i;
	int				line;
	t_thread		t[8];

	line = 0;
	i = -1;
	while (++i < 8)
	{
		t[i].line = &line;
		t[i].data = data;
		pthread_create(&t[i].thread, NULL, (void *)create_fractal, &t[i]);
	}
	i = -1;
	while (++i < 8)
		pthread_join(t[i].thread, NULL);
	if (!data->slide.animation && !data->menu.animation)
		mlx_put_image_to_window(data->mlx_ptr,
			data->win_ptr, data->img.img, 0, 0);
}

static void	create_fractal(t_thread *t)
{
	t_co	i;
	t_co	r;

	r = get_r(t->data->f);
	while (TRUE)
	{
		pthread_mutex_lock(&t->data->mutex_line);
		i.x = *t->line;
		++*t->line;
		if (t->data->render_level == _25)
			++*t->line;
		pthread_mutex_unlock(&t->data->mutex_line);
		if (i.x >= WIN)
			break ;
		i.y = 0;
		while (i.y < WIN)
		{
			compute_pixel(t, &i, r);
			i.y++;
		}
	}
}

static void	compute_pixel(t_thread *t, t_co *i, t_co r)
{
	double	col;
	int		k;
	t_co	c;

	col = t->data->f->sequence(t->data, t->data->f, (t_co){t->data->f->\
plan.start.x + i->x * r.x, t->data->f->plan.end.y - i->y * r.y}, *i);
	k = 0;
	while (k < 4)
	{
		c.x = i->x + (k >= 2);
		c.y = i->y + (k % 2 == 1);
		if (t->data->slide.render_img)
			mlx_put_pixel_img(&t->data->slide.img, c, col);
		else
			mlx_put_pixel_img(&t->data->img, c, col);
		if (t->data->render_level == _100)
			return ;
		else if (t->data->render_level == _50 && k == 1)
			return ;
		k++;
	}
	i->y++;
}
