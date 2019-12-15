/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapinto <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 14:36:08 by dapinto           #+#    #+#             */
/*   Updated: 2019/05/30 14:09:45 by dapinto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	endcheck(char *feed)
{
	if (ft_strchr(feed, '\n'))
	{
		ft_strcpy(feed, ft_strchr(feed, '\n') + 1);
		return (0);
	}
	if (ft_strichr(feed, '\n'))
	{
		ft_strcpy(feed, ft_strchr(feed, '\0'));
		return (0);
	}
	return (1);
}

static int	get_line(const int fd)
{
	static char	*feed[OPNMX];
	int			rd;
	char		buf[BUFFSIZE + 1];
	char		*ptr;

	if (fd < 0 || fd > OPNMX || BUFFSIZE < 1
			|| read(fd, buf, 0) == -1)
		return (-1);
	if (!feed[fd])
		feed[fd] = NULL;
	while (!(ft_strchr(feed[fd], '\n')) && (rd = read(fd, buf, BUFFSIZE)) > 0)
	{
		buf[rd] = '\0';
		ptr = feed[fd];
		if (!(feed[fd] = ft_strjoin(ptr, buf)))
			return (-1);
		free(ptr);
	}
	if (!endcheck(feed[fd]))
		return (1);
	return (0);
}

static int	get_size(char *filename)
{
	int fd;
	int linenbr;

	linenbr = 0;
	if (!(fd = open(filename, O_RDONLY)))
		return (-1);
	while (get_line(fd) > 0)
		++linenbr;
	close(fd);
	return (linenbr);
}

static int	collector(char *linebyline, int i)
{
	t_fdf *fdf;

	fdf = fetchenv();
	if (i == 0)
	{
		if (!(fdf->map.tmp_a = malloc(sizeof(char *) * fdf->map.l + 1)))
			return (-1);
		fdf->map.tmp_a[fdf->map.l] = NULL;
	}
	fdf->map.tmp_a[i] = ft_strdup(linebyline);
	ft_strdel(&linebyline);
	return (0);
}

int			reader(char *filename, t_fdf *fdf)
{
	int		fd;
	int		i;
	char	*linebyline;

	i = 0;
	linebyline = NULL;
	if ((fdf->map.l = get_size(filename)) == -1
			|| (fd = open(filename, O_RDONLY)) == -1)
		return (-1);
	while (get_next_line(fd, &linebyline) > 0)
	{
		if (collector(linebyline, i++) == -1)
		{
			close(fd);
			return (-1);
		}
	}
	if (alts_storer() == -1)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}
