/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typdef.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 22:21:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/07/31 22:21:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPDEF_H
# define TYPDEF_H

// TYPEDEF ------------------------------------------------
typedef enum e_pos				t_pos;
typedef enum e_bool				t_bool;
typedef enum e_preset			t_preset;
typedef enum e_level			t_level;
typedef enum e_colors			t_colors;
typedef enum e_fractal			t_fractals;
typedef enum e_appearance		t_appearance;
typedef union u_color			t_color;
typedef struct s_co				t_co;
typedef struct s_data			t_data;
typedef struct s_img			t_img;
typedef struct s_delta			t_delta;
typedef struct s_slide			t_slide;
typedef struct s_hover			t_hover;
typedef struct s_thread			t_thread;
typedef struct s_fractal		t_fractal;
typedef struct s_menu_animation	t_menu_animation;
typedef struct s_thread_preview	t_thread_preview;
typedef unsigned long long int	t_time;

#endif
