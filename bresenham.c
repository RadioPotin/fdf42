/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapinto <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:32:07 by dapinto           #+#    #+#             */
/*   Updated: 2019/05/29 13:47:06 by dapinto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		trigger_px(double x, double y, t_tracer tracer)
{
	t_fdf	*fdf;
	double	i;

	fdf = fetchenv();
	i = 0 + y * WIDTH + x;
	if (x > 0 && x < WIDTH && y < HEIGHT && i < WIDTH * HEIGHT && i >= 0)
		fdf->img_tab[(unsigned int)i] = colorselector(tracer);
}

static void		verticalish_bresen_ham(t_tracer tracer)
{
	tracer.cumulate = tracer.dery / 2;
	tracer.i = 1;
	while (tracer.i <= tracer.dery)
	{
		tracer.y += tracer.yinc;
		tracer.cumulate += tracer.derx;
		if (tracer.cumulate >= tracer.dery)
		{
			tracer.cumulate -= tracer.dery;
			tracer.x += tracer.xinc;
		}
		trigger_px(tracer.x, tracer.y, tracer);
		tracer.i++;
	}
}

void			bresens_ham(double xi, double yi, double xf, double yf)
{
	t_tracer tracer;

	tracer = init_tracer(xi, yi, xf, yf);
	trigger_px(tracer.x, tracer.y, tracer);
	if (tracer.derx > tracer.dery)
	{
		tracer.cumulate = tracer.derx / 2;
		tracer.i = 1;
		while (tracer.i <= tracer.derx)
		{
			tracer.x += tracer.xinc;
			tracer.cumulate += tracer.dery;
			if (tracer.cumulate >= tracer.derx)
			{
				tracer.cumulate -= tracer.derx;
				tracer.y += tracer.yinc;
			}
			trigger_px(tracer.x, tracer.y, tracer);
			tracer.i++;
		}
	}
	else
		verticalish_bresen_ham(tracer);
}
