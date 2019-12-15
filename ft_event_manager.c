/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_event_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapinto <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 14:09:35 by dapinto           #+#    #+#             */
/*   Updated: 2019/05/29 16:52:05 by dapinto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int			ft_zscaler(int k, double scale)
{
	t_fdf *fdf;

	fdf = fetchenv();
	if (k == 126)
	{
		if (fdf->map.scale.z > 20)
			return (0);
		fdf->map.scale = ft_setvec(fdf->map.scale.x, fdf->map.scale.y,\
				fdf->map.scale.z * (1 + scale));
	}
	else if (k == 125)
	{
		if (fdf->map.scale.z <= 0.05)
			return (0);
		fdf->map.scale = ft_setvec(fdf->map.scale.x, fdf->map.scale.y,\
				fdf->map.scale.z * (1 - scale));
	}
	mapper();
	return (0);
}

static int			ft_scaler(int k)
{
	t_fdf	*fdf;
	double	scale;

	scale = 0.1;
	fdf = fetchenv();
	if ((k == 126 || k == 125) && !ft_zscaler(k, scale))
		return (0);
	else if (k == 69)
		fdf->map.scale = ft_setvec(fdf->map.scale.x * (1 + scale),\
				fdf->map.scale.y * (1 + scale), fdf->map.scale.z * (1 + scale));
	else if (k == 78)
		fdf->map.scale = ft_setvec(fdf->map.scale.x * (1 - scale),\
				fdf->map.scale.y * (1 - scale), fdf->map.scale.z * (1 - scale));
	mapper();
	return (0);
}

static int			ft_switch_projection(int k)
{
	t_fdf *fdf;

	fdf = fetchenv();
	if (k == 83)
	{
		fdf->eve.proj = ISO;
		fdf->map.rot = ft_setvec(M_PI / 4, 0.610865, M_PI / 6);
	}
	else if (k == 82)
	{
		fdf->eve.proj = PARA;
		fdf->map.rot = ft_setvec(M_PI / 6, M_PI / 6, 0);
	}
	else if (k == 76)
	{
		init(1);
		ft_map_reset(fdf->map.pos, fdf->map.vanilla);
	}
	mapper();
	return (0);
}

int					event_manager(int k)
{
	t_fdf *fdf;

	fdf = fetchenv();
	mlx_destroy_image(fdf->mlx_server_ptr, fdf->mlx_img_ptr);
	fdf->mlx_img_ptr = mlx_new_image(fdf->mlx_server_ptr,\
			WIDTH, HEIGHT);
	fdf->img_tab = (int *)mlx_get_data_addr(fdf->mlx_img_ptr, &fdf->bpp,\
			&fdf->size_line, &fdf->endian);
	if ((k == 78 || k == 69 || k == 125 || k == 126)\
			&& !ft_scaler(k))
		return (0);
	else if ((k == 91 || k == 86 || k == 87 || k == 88)\
			&& !ft_rotate(k))
		return (0);
	else if ((k == 115 || k == 119 || k == 121 || k == 117)\
			&& !ft_move_map(k))
		return (0);
	if (k == 53)
		ft_cleanclose();
	else if ((k == 82 || k == 83 || k == 76) && !ft_switch_projection(k))
		return (0);
	else if ((k == 279 || k == 116 || k == 65) && !ft_switch_colour(k))
		return (0);
	return (0);
}
