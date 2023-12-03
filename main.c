/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 18:36:42 by fguirama          #+#    #+#             */
/*   Updated: 2022/12/05 14:48:22 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_mlx(t_data *data);
void	init_fractal(t_data *data);
void	set_hook(t_data *data);

int	main(void)
{
	t_data	data;

	init_mlx(&data);
	init_fractal(&data);
	set_page(&data, 0);
	set_hook(&data);
	mlx_loop(data.mlx_ptr);
}
