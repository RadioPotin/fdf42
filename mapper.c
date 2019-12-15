/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapinto <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 11:00:17 by dapinto           #+#    #+#             */
/*   Updated: 2019/05/29 13:47:51 by dapinto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		maptom4b4(t_m4b4 mat)
{
	int		j;
	int		i;
	t_fdf	*fdf;

	j = -1;
	fdf = fetchenv();
	while (++j < fdf->map.l)
	{
		i = -1;
		while (++i < fdf->map.r)
			fdf->map.pos[j][i] = vectom4b4(fdf->map.pos[j][i], mat);
	}
}

static void		coordinatesconversion(void)
{
	t_fdf	*fdf;
	t_m4b4	mat;

	fdf = fetchenv();
	mat = ft_m4b4scale(fdf->map.scale);
	maptom4b4(mat);
	mat = setrotation(fdf->map.rot.x, 1);
	maptom4b4(mat);
	mat = setrotation(fdf->map.rot.y, 2);
	maptom4b4(mat);
	mat = setrotation(fdf->map.rot.z, 3);
	maptom4b4(mat);
	mat = ft_m4b4trans(fdf->map.trans);
	maptom4b4(mat);
}

static void		drawline(double x, double y, int i, int j)
{
	t_fdf *fdf;

	fdf = fetchenv();
	if (i < fdf->map.r - 1 && j < fdf->map.l - 1)
	{
		fdf->map.i2 = i + 1;
		fdf->map.j2 = j;
		bresens_ham(x, y, fdf->map.pos[j][i + 1].x, fdf->map.pos[j][i + 1].y);
		fdf->map.i2 = i;
		fdf->map.j2 = j + 1;
		bresens_ham(x, y, fdf->map.pos[j + 1][i].x, fdf->map.pos[j + 1][i].y);
	}
	if (j == fdf->map.l - 1 && i != fdf->map.r - 1)
	{
		fdf->map.i2 = i + 1;
		fdf->map.j2 = j;
		bresens_ham(x, y, fdf->map.pos[j][i + 1].x, fdf->map.pos[j][i + 1].y);
	}
	if (i == fdf->map.r - 1 && j != fdf->map.l - 1)
	{
		fdf->map.i2 = i;
		fdf->map.j2 = j + 1;
		bresens_ham(x, y, fdf->map.pos[j + 1][i].x, fdf->map.pos[j + 1][i].y);
	}
}

int				mapper(void)
{
	int		i;
	int		j;
	t_fdf	*fdf;

	j = -1;
	fdf = fetchenv();
	ft_map_reset(fdf->map.pos, fdf->map.vanilla);
	coordinatesconversion();
	while (++j < fdf->map.l)
	{
		i = -1;
		fdf->map.j1 = j;
		while (++i < fdf->map.r)
		{
			fdf->map.i1 = i;
			drawline(fdf->map.pos[j][i].x, fdf->map.pos[j][i].y, i, j);
		}
	}
	mlx_put_image_to_window(fdf->mlx_server_ptr, fdf->mlx_win,\
			fdf->mlx_img_ptr, 0, 0);
	menudisplay();
	return (0);
}
