/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapinto <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 09:36:10 by dapinto           #+#    #+#             */
/*   Updated: 2019/05/29 13:47:16 by dapinto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int		set_color(int z)
{
	t_fdf	*fdf;
	int		mid_height;
	int		colour;

	fdf = fetchenv();
	colour = ORANGE;
	mid_height = fdf->map.highest / 2;
	if (abs(z - fdf->map.lowest) <= abs(z - mid_height))
	{
		colour = GREEN;
		if (fabs(z - mid_height * 0.5) < abs(z - fdf->map.lowest)\
				&& fabs(z - mid_height * 0.5) < abs(z - mid_height))
			colour = BROWN;
	}
	if (abs(z - fdf->map.lowest) >= abs(z - fdf->map.highest))
	{
		colour = RED;
		if (abs(z - mid_height * 3) < abs(z - fdf->map.lowest)\
				&& abs(z - mid_height * 3) < abs(z - fdf->map.highest))
			colour = ORANGE;
	}
	else if (z <= 0)
		colour = BLUE;
	return (colour);
}

static double	percenter(int start, int end, int current)
{
	double placement;
	double distance;

	placement = current - start;
	distance = end - start;
	return ((distance == 0) ? 1.0 : (placement / distance));
}

static int		get_color(int start, int end, double percentage)
{
	return ((int)((1 - percentage) * start + percentage * end));
}

int				colorselector(t_tracer tracer)
{
	int		red;
	int		green;
	int		blue;
	double	percentage;
	t_fdf	*fdf;

	fdf = fetchenv();
	if (fdf->eve.event == 1)
	{
		tracer.startcolour = set_color(tracer.z1);
		tracer.endcolour = set_color(tracer.z2);
		if (tracer.derx > tracer.dery)
			percentage = percenter(tracer.y1, tracer.y2, tracer.y);
		else
			percentage = percenter(tracer.x1, tracer.x2, tracer.x);
		red = get_color((tracer.startcolour >> 16) & 0xFF,\
				(tracer.endcolour >> 16) & 0xFF, percentage);
		green = get_color((tracer.startcolour >> 8) & 0xFF,\
				(tracer.endcolour >> 8) & 0xFF, percentage);
		blue = get_color(tracer.startcolour & 0xFF,\
				tracer.endcolour & 0xFF, percentage);
		return ((1 << 24) | (red << 16) | (green << 8) | (blue << 0));
	}
	else
		return (fdf->map.colour);
}
