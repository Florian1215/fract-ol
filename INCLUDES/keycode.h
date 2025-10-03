/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keycode.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguirama <fguirama@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 13:28:00 by fguirama          #+#    #+#             */
/*   Updated: 2023/07/24 13:28:00 by fguirama         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYCODE_H
# define KEYCODE_H

# ifdef __APPLE__

enum e_keycode
{
	C = 8,
	D = 2,
	Q = 12,
	X = 7,
	Z = 6,
	ESQ = 53,
	TAB = 48,
	PLUS = 69,
	MINUS = 78,
	LEFT = 123,
	RIGHT = 124,
	NUM_0 = 29,
	NUM_1 = 18,
	NUM_2 = 19,
	NUM_3 = 20,
	NUM_4 = 21,
	NUM_5 = 23,
	NUM_6 = 22,
	NUM_7 = 26,
	NUM_8 = 28,
	NUM_9 = 25,
	PAV_0 = 82,
	PAV_1 = 83,
	PAV_2 = 84,
	PAV_3 = 85,
	PAV_4 = 86,
	PAV_5 = 87,
	PAV_6 = 88,
	PAV_7 = 89,
	PAV_8 = 91,
	PAV_9 = 92,
	LEFT_CLICK = 1,
	RIGHT_CLICK = 2,
	SCROLL_IN = 4,
	SCROLL_OUT = 5,
};
# endif

# ifdef __linux__

enum e_keycode
{
	C = 99,
	D = 100,
	Q = 113,
	X = 120,
	Z = 122,
	ESQ = 65307,
	TAB = 65289,
	PLUS = 65451,
	MINUS = 65453,
	LEFT = 65361,
	RIGHT = 65363,
	NUM_0 = 48,
	NUM_1 = 49,
	NUM_2 = 50,
	NUM_3 = 51,
	NUM_4 = 52,
	NUM_5 = 53,
	NUM_6 = 54,
	NUM_7 = 55,
	NUM_8 = 56,
	NUM_9 = 57,
	PAV_0 = 65438,
	PAV_1 = 65436,
	PAV_2 = 65433,
	PAV_3 = 65435,
	PAV_4 = 65430,
	PAV_5 = 65437,
	PAV_6 = 65432,
	PAV_7 = 65429,
	PAV_8 = 65431,
	PAV_9 = 65434,
	LEFT_CLICK = 1,
	RIGHT_CLICK = 3,
	SCROLL_IN = 4,
	SCROLL_OUT = 5,
};
# endif

#endif
