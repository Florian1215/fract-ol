/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocessing.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 22:21:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/07/31 22:21:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PREPROCESSING_H
# define PREPROCESSING_H

// INCLUDE ----------------------------------------------------------
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <pthread.h>
# include <semaphore.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <unistd.h>

# include "color.h"
# include "keycode.h"
# include "typdef.h"

# ifdef __APPLE__
#  define APPLE 1
#  include "../mlx/mac/mlx.h"
# endif

# ifdef __linux__
#  define APPLE 0
#  include "../mlx/linux/mlx.h"
# endif

// DEFINE -------------------------------------------------
# define MAX_SHADOW					7
# define MAX_ITER					50
# define MAX_ITER_HOVER				40
# define ZOOM_HOVER					0.90
# define ZOOM_MENU					1
# define N_FRAC						12
# define FPS						25
# define FRAME_ANIMATION			29
# define WIN						1000
# define HWIN						(WIN / 2)
# define QWIN						(WIN / 4)
# define RATIO_TITLE				(WIN * 0.9 / 1000)

# define PATH_MANDELBROT			"./ASSETS/01_mandelbrot.xpm"
# define PATH_JULIA					"./ASSETS/02_julia.xpm"
# define PATH_CELTIC				"./ASSETS/03_celtic.xpm"
# define PATH_BURNING_SHIP			"./ASSETS/04_burning_ship.xpm"
# define PATH_BUFFALO				"./ASSETS/05_buffalo.xpm"
# define PATH_BURNING_JULIA			"./ASSETS/06_burning_julia.xpm"
# define PATH_JULIA3				"./ASSETS/07_julia3.xpm"
# define PATH_CELTIC_MANDELBAR		"./ASSETS/08_celtic_mandelbar.xpm"
# define PATH_PERPENDICULAR_CELTIC	"./ASSETS/09_perpendicular_celtic.xpm"
# define PATH_HEART					"./ASSETS/10_heart.xpm"
# define PATH_MANDELBAR				"./ASSETS/11_mandelbar.xpm"
# define PATH_CELTIC_MANDELBROT		"./ASSETS/12_celtic_mandelbrot.xpm"

#endif
