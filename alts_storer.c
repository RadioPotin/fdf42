/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alts_storer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapinto <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 09:43:37 by dapinto           #+#    #+#             */
/*   Updated: 2019/05/29 16:41:55 by dapinto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		posarrayfreer(int size)
{
	t_fdf	*fdf;
	int		j;

	j = 0;
	fdf = fetchenv();
	if (size)
	{
		while (j < size)
			free(fdf->map.pos[j++]);
		free(fdf->map.pos);
	}
	free(fdf);
}

static int		intscounter(char *str)
{
	char	*s;
	int		ints;

	s = str;
	ints = 0;
	while (*s && *s != '\n')
	{
		while (!ft_isdigit(*s))
			s++;
		ints++;
		while (ft_isdigit(*s))
			s++;
		if (*s == '\n')
			break ;
	}
	return (ints);
}

static int		max_int_per_line(char **tab, int tab_size)
{
	int		size;
	int		ints;
	int		check;
	int		line;
	int		j;

	size = 0;
	line = 0;
	j = 0;
	while (j < tab_size - 1)
	{
		ints = intscounter(tab[j]);
		check = intscounter(tab[j + 1]);
		if (ints > check)
			return (line);
		size = (ints > size) ? ints : size;
		line--;
		j++;
	}
	return (size);
}

static int		intstorer(t_fdf **fdf, int *j, int i, int src_i)
{
	while (*j < (*fdf)->map.l)
	{
		src_i = 0;
		i = 0;
		if (!((*fdf)->map.pos[*j] = malloc(sizeof(t_pos) * (*fdf)->map.r)))
			return (-1);
		ft_bzero(&(*fdf)->map.pos[*j][i], sizeof(t_pos) * (*fdf)->map.r);
		while ((*fdf)->map.tmp_a[*j][src_i]\
				&& (*fdf)->map.tmp_a[*j][src_i] != '\n')
		{
			if (!ft_isdigit((*fdf)->map.tmp_a[*j][src_i]))
				src_i++;
			else
			{
				(*fdf)->map.pos[*j][i] = ft_setvec(i, *j,\
						ft_atoi(&((*fdf)->map.tmp_a[*j][src_i])));
				i++;
				while (ft_isdigit((*fdf)->map.tmp_a[*j][src_i]))
					src_i++;
			}
		}
		*j += 1;
	}
	return (0);
}

int				alts_storer(void)
{
	t_fdf	*fdf;
	int		j;
	int		i;
	int		src_i;

	i = 0;
	j = 0;
	src_i = 0;
	fdf = fetchenv();
	fdf->map.r = max_int_per_line(fdf->map.tmp_a, fdf->map.l);
	if (fdf->map.r <= 0 || file_checker(j) ||\
			!(fdf->map.pos = malloc(sizeof(t_pos *) * fdf->map.l))\
			|| intstorer(&fdf, &j, i, src_i) == -1)
	{
		ft_tabdel(fdf->map.l - 1, &fdf->map.tmp_a);
		posarrayfreer(j);
		ft_printf("Error in fdf_map_file. Possibly at line %d or %d.\n",\
				j, -fdf->map.r + 1);
		return (-1);
	}
	ft_tabdel(fdf->map.l - 1, &fdf->map.tmp_a);
	return (0);
}
