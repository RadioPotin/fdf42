/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapinto <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 14:11:45 by dapinto           #+#    #+#             */
/*   Updated: 2019/05/29 13:51:47 by dapinto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <mlx.h>
# include <math.h>
# include <fcntl.h>
# include "libft.h"
# include "ft_printf.h"
# define WIDTH 1920
# define HEIGHT 1080
# define OPNMX 4896
# define BUFFSIZE 4096
# define BLACK 0
# define GREY 0x939395
# define WHITE 0xffffff
# define GREEN 0x006c26
# define CACADOIE 0x6d7512
# define RADIOACTIVE 0x6bff01
# define TURQUOISE 0x3ef9b6
# define DARKBLUE 0x000045
# define BLUE 0x166fe7
# define BLUEGREY 0x497182
# define RED 0xb11a13
# define PINK 0xff59a5
# define PURPLE 0x66108c
# define CYAN 0x16effe
# define ORANGE 0xff5100
# define BROWN 0x4d2600
# define YELLOW 0xfffb20
# define ISO 150
# define PARA 7454

typedef struct	s_tracer
{
	int			x;
	int			y;
	int			x1;
	int			y1;
	int			x2;
	int			y2;
	int			z1;
	int			z2;
	int			derx;
	int			xinc;
	int			dery;
	int			yinc;
	int			i;
	int			cumulate;
	int			startcolour;
	int			endcolour;
}				t_tracer;

typedef struct	s_eve
{
	int			state;
	int			event;
	int			axis;
	int			proj;
}				t_eve;

typedef struct	s_pos
{
	double		x;
	double		y;
	double		z;
}				t_pos;

typedef struct	s_map
{
	char		**tmp_a;
	t_pos		**vanilla;
	t_pos		**pos;
	t_pos		scale;
	int			l;
	int			r;
	t_pos		trans;
	int			i1;
	int			j1;
	t_pos		rot;
	int			i2;
	int			j2;
	int			highest;
	int			lowest;
	int			colour;
}				t_map;

typedef struct	s_m4b4
{
	double		mat[4][4];
}				t_m4b4;

typedef struct	s_fdf
{
	void		*mlx_server_ptr;
	void		*mlx_img_ptr;
	void		*mlx_win;
	int			*img_tab;
	int			endian;
	t_map		map;
	int			bpp;
	t_eve		eve;
	int			size_line;
}				t_fdf;

int				main(int argc, char **argv);
t_fdf			*fetchenv(void);
int				reader(char *filename, t_fdf *fdf);
int				alts_storer(void);
int				file_checker(int fg);
void			init(int key);
t_pos			ft_setvec(double x, double y, double z);
t_m4b4			ft_m4b4rot(t_pos vec1, t_pos vec2, t_pos vec3);
t_m4b4			ft_m4b4scale(t_pos scale);
t_m4b4			ft_m4b4trans(t_pos trans);
t_m4b4			setrotation(double angle, int axis);
t_pos			pos_finder(t_pos pos);
t_pos			vectom4b4(t_pos pos, t_m4b4 mat);
int				mapper(void);
void			bresens_ham(double x1, double y1, double x2, double y2);
t_tracer		init_tracer(double xi, double yi, double xf, double yf);
void			menudisplay(void);
int				event_manager(int key);
int				ft_cleanclose(void);
int				ft_move_map(int key);
int				ft_rotate(int key);
int				ft_map_reset(t_pos **dest, t_pos **src);
int				ft_switch_colour(int key);
int				colorselector(t_tracer tracer);
#endif
