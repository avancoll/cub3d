/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avancoll <avancoll@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 15:48:22 by avancoll          #+#    #+#             */
/*   Updated: 2023/07/04 15:54:44 by avancoll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "get_next_line.h"
# include "libft.h"
# include "map.h"
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

enum
{
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

enum
{
	KEY_ESC = 53,
	KEY_W = 13,
	KEY_A = 0,
	KEY_S = 1,
	KEY_D = 2,
	KEY_Q = 12,
	KEY_E = 14,
	KEY_LEFT = 123,
	KEY_RIGHT = 124,
	KEY_DOWN = 125,
	KEY_UP = 126,
	KEY_Z = 6,
	KEY_X = 7,
	KEY_PAD1 = 83,
	KEY_PAD2 = 84,
	KEY_PAD3 = 85,
	KEY_PAD4 = 86,
	KEY_PAD5 = 87,
	KEY_PAD6 = 88,
	KEY_MINUS = 27,
	KEY_PLUS = 24,
	KEY_R = 15,
	KEY_P = 35,
	KEY_TAB = 48
};

enum
{
	SIZE_X = 1920,
	SIZE_Y = 1080
};

typedef struct s_key
{
	int		offset_x;
	int		offset_y;
	int		mv_forward;
	int		mv_backward;
	int		mv_left;
	int		mv_right;
}			t_key;

typedef struct s_mlx_data
{
	t_key	*key;
	t_map	*map;
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*addr;
	int		bits_pixel;
	int		size_line;
	int		endian;
}			t_mlx_data;

void		mlx_put_pixel(t_mlx_data *data, int x, int y, int color);
void		mlx_handler(t_mlx_data *data);
int			key_pressed(int keycode, t_mlx_data *data);
int			key_released(int keycode, t_mlx_data *data);
int			exec_move(t_mlx_data *data);
int			ft_close(t_mlx_data *data);

#endif
