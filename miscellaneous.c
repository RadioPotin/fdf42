/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miscellaneous.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapinto <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 13:24:13 by dapinto           #+#    #+#             */
/*   Updated: 2019/05/29 13:48:04 by dapinto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int				file_checker(int fg)
{
	int		j;
	int		i;
	t_fdf	*fdf;

	j = 0;
	fdf = fetchenv();
	if (fg > 0)
		return (0);
	while (j < fdf->map.l)
	{
		i = 0;
		while (i < fdf->map.r)
		{
			if (ft_isalpha(fdf->map.tmp_a[j][i])\
					|| fdf->map.tmp_a[j][i] == '.')
				return (1);
			i++;
		}
		j++;
	}
	return (0);
}

int				ft_map_reset(t_pos **dest, t_pos **src)
{
	int		j;
	int		i;
	t_fdf	*fdf;

	j = 0;
	fdf = fetchenv();
	while (j < fdf->map.l)
	{
		i = 0;
		while (i < fdf->map.r)
		{
			dest[j][i] = ft_setvec(src[j][i].x,\
					src[j][i].y, src[j][i].z);
			i++;
		}
		j++;
	}
	return (0);
}

void			projection_display(void)
{
	t_fdf *fdf;

	fdf = fetchenv();
	if (fdf->eve.proj)
	{
		(fdf->eve.proj == ISO) ? mlx_string_put(fdf->mlx_server_ptr,\
				fdf->mlx_win, WIDTH * 0.725, 320, fdf->map.colour,\
				"Projection mode: ISOMETRIC.") :\
						mlx_string_put(fdf->mlx_server_ptr, fdf->mlx_win,\
								WIDTH * 0.725, 320, fdf->map.colour,\
								"Projection mode: PARALLEL.");
	}
	else
		mlx_string_put(fdf->mlx_server_ptr, fdf->mlx_win, WIDTH * 0.725, 320,\
				fdf->map.colour, "Projection mode: FREE.");
	mlx_string_put(fdf->mlx_server_ptr, fdf->mlx_win, WIDTH * 0.725, 340,\
			fdf->map.colour, "Projection switch: 1 and 0 on num keypad.");
	mlx_string_put(fdf->mlx_server_ptr, fdf->mlx_win, WIDTH * 0.725, 360,\
			fdf->map.colour, "Reset map: ENTER on num keypad.");
}

void			menudisplay(void)
{
	t_fdf *fdf;

	fdf = fetchenv();
	mlx_string_put(fdf->mlx_server_ptr, fdf->mlx_win, WIDTH * 0.725, 300,\
			fdf->map.colour, "Close window: ESC or RED CROSS.");
	mlx_string_put(fdf->mlx_server_ptr, fdf->mlx_win, WIDTH * 0.725, 380,\
			fdf->map.colour, "Zoom in/out: + and - on num keypad.");
	mlx_string_put(fdf->mlx_server_ptr, fdf->mlx_win, WIDTH * 0.725, 400,\
			fdf->map.colour, "Rotate on X axis: 4(-) and 6(+) on num keypad.");
	mlx_string_put(fdf->mlx_server_ptr, fdf->mlx_win, WIDTH * 0.725, 420,\
			fdf->map.colour, "Rotate on Y axis: 5(-) and 8(+) on num keypad.");
	mlx_string_put(fdf->mlx_server_ptr, fdf->mlx_win, WIDTH * 0.725, 440,\
			fdf->map.colour, "Translate on Y axis: END(-) and HOME(+).");
	mlx_string_put(fdf->mlx_server_ptr, fdf->mlx_win, WIDTH * 0.725, 460,\
			fdf->map.colour, "Translate on X axis: DELETE(-) and PAGEDOWN(+).");
	mlx_string_put(fdf->mlx_server_ptr, fdf->mlx_win, WIDTH * 0.725, 480,\
			fdf->map.colour, "Scaling of Z: UP and DOWN arrows.");
	mlx_string_put(fdf->mlx_server_ptr, fdf->mlx_win, WIDTH * 0.725, 500,\
			fdf->map.colour, "Colour switch: FN(-) and PAGEUP(+).");
	mlx_string_put(fdf->mlx_server_ptr, fdf->mlx_win, WIDTH * 0.725, 520,\
			fdf->map.colour, "Gradient: DOT on num keypad.");
	projection_display();
}
