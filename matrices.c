/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapinto <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 11:35:25 by dapinto           #+#    #+#             */
/*   Updated: 2019/05/29 13:47:57 by dapinto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_m4b4	ft_m4b4rot(t_pos vec1, t_pos vec2, t_pos vec3)
{
	t_m4b4 mat;

	mat.mat[0][0] = vec1.x;
	mat.mat[1][0] = vec1.y;
	mat.mat[2][0] = vec1.z;
	mat.mat[3][0] = 0;
	mat.mat[0][1] = vec2.x;
	mat.mat[1][1] = vec2.y;
	mat.mat[2][1] = vec2.z;
	mat.mat[3][1] = 0;
	mat.mat[0][2] = vec3.x;
	mat.mat[1][2] = vec3.y;
	mat.mat[2][2] = vec3.z;
	mat.mat[0][3] = 0;
	mat.mat[1][3] = 0;
	mat.mat[2][3] = 0;
	mat.mat[3][2] = 0;
	mat.mat[3][3] = 1;
	return (mat);
}

t_m4b4	ft_m4b4scale(t_pos scale)
{
	t_m4b4	mat;

	mat.mat[0][0] = scale.x;
	mat.mat[0][1] = 0;
	mat.mat[0][2] = 0;
	mat.mat[0][3] = 0;
	mat.mat[1][0] = 0;
	mat.mat[1][1] = scale.y;
	mat.mat[1][2] = 0;
	mat.mat[1][3] = 0;
	mat.mat[2][0] = 0;
	mat.mat[2][1] = 0;
	mat.mat[2][2] = scale.z;
	mat.mat[2][3] = 0;
	mat.mat[3][0] = 0;
	mat.mat[3][1] = 0;
	mat.mat[3][2] = 0;
	mat.mat[3][3] = 1;
	return (mat);
}

t_m4b4	ft_m4b4trans(t_pos trans)
{
	t_m4b4	mat;

	mat.mat[0][0] = 1;
	mat.mat[0][1] = 0;
	mat.mat[0][2] = 0;
	mat.mat[0][3] = trans.x;
	mat.mat[1][0] = 0;
	mat.mat[1][1] = 1;
	mat.mat[1][2] = 0;
	mat.mat[1][3] = trans.y;
	mat.mat[2][0] = 0;
	mat.mat[2][1] = 0;
	mat.mat[2][2] = 1;
	mat.mat[2][3] = trans.z;
	mat.mat[3][0] = 0;
	mat.mat[3][1] = 0;
	mat.mat[3][2] = 0;
	mat.mat[3][3] = 1;
	return (mat);
}

t_m4b4	setrotation(double angle, int axis)
{
	t_m4b4 mat;

	mat = ft_m4b4rot(ft_setvec(0, 0, 0), ft_setvec(0, 0, 0),\
			ft_setvec(0, 0, 0));
	if (axis <= 0 || axis >= 4)
		return (mat);
	else if (axis == 1)
		mat = ft_m4b4rot(ft_setvec(1, 0, 0), ft_setvec(0, cos(angle),\
					sin(angle)), ft_setvec(0, -sin(angle), cos(angle)));
	else if (axis == 2)
		mat = ft_m4b4rot(ft_setvec(cos(angle), 0, sin(angle)),\
				ft_setvec(0, 1, 0), ft_setvec(-sin(angle), 0, cos(angle)));
	else if (axis == 3)
		mat = ft_m4b4rot(ft_setvec(cos(angle), sin(angle), 0),\
				ft_setvec(-sin(angle), cos(angle), 0), ft_setvec(0, 0, 1));
	return (mat);
}

t_pos	vectom4b4(t_pos pos, t_m4b4 mat)
{
	t_fdf *fdf;
	t_pos tmp;

	fdf = fetchenv();
	tmp.x = pos.x * mat.mat[0][0] + pos.y * mat.mat[0][1]\
			+ pos.z * mat.mat[0][2] + mat.mat[0][3];
	tmp.y = pos.x * mat.mat[1][0] + pos.y * mat.mat[1][1]\
			+ pos.z * mat.mat[1][2] + mat.mat[1][3];
	tmp.z = pos.x * mat.mat[2][0] + pos.y * mat.mat[2][1]\
			+ pos.z * mat.mat[2][2] + mat.mat[2][3];
	return (tmp);
}
