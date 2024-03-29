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

void	init_img(t_img *img, char *path, void *mlx_ptr);

void	init_mlx(t_data *data)
{
	data->mlx_ptr = mlx_init();
	data->offset_color = 0;
	data->i_c = 0;
	data->slide.i = 0;
	data->appearance = LIGHT;
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
	data->c_animate = FALSE;
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

void	init_colors(t_data *data)
{
	static t_color	*(*colors_set[N_FRAC])(t_appearance app) = {set_green, \
	set_purple, set_electric_blue, set_red, set_blue_red, set_pink, \
	set_green_blue, set_blue_light, set_pastel_pink, set_night_blue, \
	set_blue, set_yellow};
	int				i;

	i = 0;
	while (i < N_FRAC)
		colors_set[i++](data->appearance);
}
