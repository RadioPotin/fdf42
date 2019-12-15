/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_event_manager2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapinto <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 14:37:44 by dapinto           #+#    #+#             */
/*   Updated: 2019/05/29 13:47:30 by dapinto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		colourtabset(int *colour_tab)
{
	colour_tab[0] = BLACK;
	colour_tab[1] = GREY;
	colour_tab[2] = WHITE;
	colour_tab[3] = YELLOW;
	colour_tab[4] = ORANGE;
	colour_tab[5] = PINK;
	colour_tab[6] = RED;
	colour_tab[7] = CACADOIE;
	colour_tab[8] = GREEN;
	colour_tab[9] = TURQUOISE;
	colour_tab[11] = RADIOACTIVE;
	colour_tab[12] = CYAN;
	colour_tab[13] = BLUE;
	colour_tab[14] = PURPLE;
	colour_tab[15] = BLUEGREY;
}

int				ft_switch_colour(int key)
{
	static int	i = 1;
	t_fdf		*fdf;
	int			colour_tab[16];

	fdf = fetchenv();
	colourtabset(colour_tab);
	if (key == 65)
		fdf->eve.event = 1;
	else if (key == 279 || key == 116)
	{
		fdf->eve.event = 0;
		i = (key == 279) ? i - 1 : i + 1;
		if (i < 0 || i > 15)
			i = (i > 15) ? 0 : 15;
		fdf->map.colour = colour_tab[i];
	}
	mapper();
	return (0);
}

int				ft_move_map(int key)
{
	t_fdf	*fdf;
	double	trans;

	fdf = fetchenv();
	trans = 5;
	if (key == 115)
		fdf->map.trans.y += -trans;
	else if (key == 119)
		fdf->map.trans.y += trans;
	else if (key == 117)
		fdf->map.trans.x += -trans;
	else if (key == 121)
		fdf->map.trans.x += trans;
	mapper();
	return (0);
}

int				ft_rotate(int k)
{
	t_fdf	*fdf;
	double	angle;

	fdf = fetchenv();
	fdf->eve.proj = 0;
	angle = M_PI / 90;
	if (k == 86)
		fdf->map.rot.y += angle;
	else if (k == 88)
		fdf->map.rot.y -= angle;
	if (k == 91)
		fdf->map.rot.x += angle;
	else if (k == 87)
		fdf->map.rot.x -= angle;
	mapper();
	return (0);
}
