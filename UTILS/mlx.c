/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 10:49:35 by fguirama          #+#    #+#             */
/*   Updated: 2022/12/10 10:49:36 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	mlx_put_pixel_img(t_img *img, t_co co, int color)
{
	int	x;
	int	y;

	x = (int)co.x;
	y = (int)co.y;
	if (x > WIN || y > WIN || y < 0 || x < 0)
		return ;
	*(unsigned int *)(img->addr + (y * img->line_length + x * (\
img->bits_per_pixel / 8))) = color;
}

void	draw_alpha(t_img *img, t_img *alpha, t_co pos, t_co color_ratio)
{
	t_co	size;
	t_co	texture;
	int		c;

	size = (t_co){alpha->width * color_ratio.y, alpha->height * color_ratio.y};
	texture.y = 0;
	while (texture.y < size.y)
	{
		texture.x = 0;
		while (texture.x < size.x)
		{
			c = *(int *)(alpha->addr + (int)(texture.x / color_ratio.y) \
*alpha->bit_ratio + (int)(texture.y / color_ratio.y) *alpha->line_length);
			if (!(c & 0xFF000000))
				mlx_put_pixel_img(img, (t_co){pos.x + texture.x, pos.y + \
texture.y}, (int)color_ratio.x);
			texture.x++;
		}
		texture.y++;
	}
}

int	close_mlx(t_data *data)
{
	int	i;

	i = 0;
	while (i < N_FRAC)
	{
		mlx_destroy_image(data->mlx_ptr, data->fractals[i].name.img);
		i++;
	}
	mlx_destroy_image(data->mlx_ptr, data->slide.img.img);
	mlx_destroy_image(data->mlx_ptr, data->img.img);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	pthread_mutex_destroy(&data->mutex_line);
	lst_clear(&data->kbuff);
	free(data->mlx_ptr);
	exit(SUCCESS);
}
