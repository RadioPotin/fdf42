/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapinto <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 09:35:47 by dapinto           #+#    #+#             */
/*   Updated: 2019/07/09 09:43:01 by dapinto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <assert.h>

t_fdf			*fetchenv(void)
{
	static t_fdf *fdf = NULL;

	if (fdf == NULL)
	{
		if (!(fdf = ft_memalloc(sizeof(t_fdf))))
			return (NULL);
		fdf->mlx_server_ptr = mlx_init();
		fdf->mlx_img_ptr = mlx_new_image(fdf->mlx_server_ptr,\
				WIDTH, HEIGHT);
		fdf->img_tab = (int *)mlx_get_data_addr(fdf->mlx_img_ptr, &fdf->bpp,\
				&fdf->size_line, &fdf->endian);
		fdf->mlx_win = mlx_new_window(fdf->mlx_server_ptr, WIDTH, HEIGHT,\
				"FDF MAP");
		ft_bzero(&fdf->map, sizeof(t_map));
		ft_bzero(&fdf->eve, sizeof(t_eve));
	}
	return (fdf);
}

void			map_save(void)
{
	t_fdf	*fdf;
	int		j;
	int		i;

	fdf = fetchenv();
	j = 0;
	fdf->map.vanilla = ft_memalloc(sizeof(t_pos *) * fdf->map.l);
	while (j < fdf->map.l)
	{
		i = 0;
		fdf->map.vanilla[j] = ft_memalloc(sizeof(t_pos) * fdf->map.r);
		while (i < fdf->map.r)
		{
			fdf->map.vanilla[j][i] = ft_setvec(fdf->map.pos[j][i].x,\
					fdf->map.pos[j][i].y, fdf->map.pos[j][i].z);
			fdf->map.lowest = (fdf->map.lowest > fdf->map.vanilla[j][i].z)\
							? fdf->map.vanilla[j][i].z : fdf->map.lowest;
			fdf->map.highest = (fdf->map.highest < fdf->map.vanilla[j][i].z)\
							? fdf->map.vanilla[j][i].z : fdf->map.highest;
			i++;
		}
		j++;
	}
}

t_pos			ft_setvec(double x, double y, double z)
{
	t_pos pos;

	pos.x = x;
	pos.y = y;
	pos.z = z;
	return (pos);
}

void			init(int key)
{
	t_fdf	*fdf;
	double	scale;

	fdf = fetchenv();
	scale = (WIDTH - WIDTH * 0.50) / fdf->map.r;
	fdf->map.scale = ft_setvec(scale, scale, scale);
	fdf->map.rot = ft_setvec(M_PI / 6, M_PI / 6, 0);
	fdf->map.trans.x = WIDTH / 2 - (scale * fdf->map.r) / 2;
	fdf->map.trans.y = HEIGHT / 2 - (scale * fdf->map.l) / 2;
	fdf->map.trans.z = 0;
	fdf->map.colour = GREY;
	if (!key)
		map_save();
}

t_tracer		init_tracer(double xi, double yi, double xf, double yf)
{
	t_fdf		*fdf;
	t_tracer	tracer;

	fdf = fetchenv();
	tracer.x = xi;
	tracer.y = yi;
	tracer.x1 = xi;
	tracer.y1 = yi;
	tracer.x2 = xf;
	tracer.y2 = yf;
	tracer.derx = xf - xi;
	tracer.dery = yf - yi;
	tracer.xinc = (tracer.derx > 0) ? 1 : -1;
	tracer.yinc = (tracer.dery > 0) ? 1 : -1;
	tracer.derx = abs(tracer.derx);
	tracer.dery = abs(tracer.dery);
	tracer.z1 = fdf->map.vanilla[fdf->map.j1][fdf->map.i1].z;
	tracer.z2 = fdf->map.vanilla[fdf->map.j2][fdf->map.i2].z;
	return (tracer);
}
