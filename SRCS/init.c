/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 13:35:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/11/28 15:32:18 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		init_img(t_img *img, char *path, void *mlx_ptr);
static void	init_colors(t_data *data);
void	init_mlx(t_data *data)
{
	data->mlx_ptr = mlx_init();
	data->offset_color = 0;
	data->i_c = 0;
	data->last_render = 0;
	data->prev_render = FALSE;
	data->render_level = _100;
	data->slide.i = 0;
	data->appearance = LIGHT;
	data->appearance_animation = FALSE;
	data->in_menu = TRUE;
	data->menu.animation = FALSE;
	data->menu.save_img = FALSE;
	data->slide.render_img = FALSE;
	cancel_animation(data);
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIN, WIN, \
"Fract-ol");
	init_img(&data->slide.img, NULL, data->mlx_ptr);
	init_img(&data->img, NULL, data->mlx_ptr);
	pthread_mutex_init(&data->mutex_line, NULL);
	init_colors(data);
//	init_hovers(data);
}

void	cancel_animation(t_data *data)
{
	data->reset = FALSE;
	data->moving = FALSE;
	data->edit = FALSE;
	data->update = FALSE;
	data->edit_c = FALSE;
	data->slide.animation = FALSE;
	data->zoom_size = FALSE;
	data->c_animation = FALSE;
	data->color_animation = FALSE;
}

void	init_img(t_img *img, char *path, void *mlx_ptr)
{
	if (path)
		img->img = mlx_xpm_file_to_image(mlx_ptr, path, \
	&img->width, &img->height);
	else
		img->img = mlx_new_image(mlx_ptr, WIN, WIN);
	if (!img->img)
		return ;
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, \
&img->line_length, &img->endian);
	img->bit_ratio = img->bits_per_pixel / 8;
}

static void	init_colors(t_data *data)
{
	static void	(*init_color[N_FRAC])(t_data *) = {init_green, \
	init_purple, init_electric_blue, init_red, init_blue_red, init_pink, \
	init_green_blue, init_blue_light, init_pastel_pink, init_night_blue, \
	init_blue, init_yellow};
	int			i;

	i = 0;
	while (i < N_FRAC)
		init_color[i++](data);
}
