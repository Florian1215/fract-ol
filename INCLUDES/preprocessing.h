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
# define MAX_ITER			50
# define MAX_ITER_HOVER		35
# define ZOOM_HOVER			0.87
# define ZOOM_MENU			1
# define N_FRAC				12
# define FPS				25
# define FRAME_ANIMATION	29
# define WIN				1000
# define HWIN				500
# define QWIN				250

#endif
