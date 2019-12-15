/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapinto <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 13:58:06 by dapinto           #+#    #+#             */
/*   Updated: 2019/05/30 12:36:03 by dapinto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		ft_cleanclose(void)
{
	t_fdf	*fdf;
	int		j;

	j = 0;
	fdf = fetchenv();
	mlx_destroy_image(fdf->mlx_server_ptr, fdf->mlx_img_ptr);
	while (j < fdf->map.l)
	{
		free(fdf->map.pos[j]);
		free(fdf->map.vanilla[j]);
		j++;
	}
	free(fdf->map.pos);
	free(fdf->map.vanilla);
	free(fdf);
	exit(0);
}

int		ft_fdf(void)
{
	t_fdf *fdf;

	fdf = fetchenv();
	mapper();
	mlx_hook(fdf->mlx_win, 2, 0, &event_manager, &fdf->map.pos);
	mlx_hook(fdf->mlx_win, 17, 0, &ft_cleanclose, &fdf->map.pos);
	mlx_loop(fdf->mlx_server_ptr);
	return (0);
}

int		main(int argc, char **argv)
{
	t_fdf *fdf;

	fdf = fetchenv();
	if (argc != 2 || reader(argv[1], fdf) == -1)
	{
		if (argc != 2)
			ft_printf("Usage: ./fdf [Valid_FdF_Map_File]\n");
		return (-1);
	}
	init(0);
	ft_fdf();
	return (0);
}
