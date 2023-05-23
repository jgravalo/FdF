/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   points.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgravalo <jgravalo@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:30:31 by jgravalo          #+#    #+#             */
/*   Updated: 2023/05/23 16:04:45 by jgravalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/fdf.h"

void    my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char    *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	my_point(t_var *vars, int x, int y, int color)
{
	my_mlx_pixel_put(&vars->img, x, y, color);
//	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, x, y);
}

void print_line(t_var *vars, t_point p_i, t_point p_f)
{
	int		i;
	float	h;
	float	ang;

	i = 0;
	h = sqrt(pow((p_f.pos_y - p_i.pos_y), 2) * pow((p_f.pos_x - p_i.pos_x), 2));
	ang = asin((p_f.pos_y - p_i.pos_y) / h);
	printf("h = %f\n", h);
	printf("ang = %f\n", ang);
	while (i < h)
	{
		if (i < h / 2)
			my_point(vars, p_i.pos_x + i * cos(ang), p_i.pos_y + i * sin(ang), p_i.color);
		else
			my_point(vars, p_i.pos_x + i * cos(ang), p_i.pos_y + i * sin(ang), p_f.color);
		i++;
	}
}

void make_line(t_var *vars, t_point **fdf, int i, int j)
{
	if (j != 0)
		print_line(vars, fdf[i][j - 1], fdf[i][j]);
	if (i != 0)
		print_line(vars, fdf[i - 1][j], fdf[i][j]);
}

void print_point(t_var *vars, t_point **fdf, int i, int j)
{
	fdf[i][j].pos_x = vars->size.start_x - (fdf[i][j].x * vars->size.space * cos(MPI / 4));
	fdf[i][j].pos_y = vars->size.start_y + (fdf[i][j].y * vars->size.space
		* sin(MPI / 4) * sin(MPI / 4)) - (fdf[i][j].z * sin(MPI / 4));
	my_point(vars, fdf[i][j].pos_x, fdf[i][j].pos_y, fdf[i][j].color);
//	make_line(vars, fdf, i, j);
}
/*
{
	if (i == 0 && j == 0)
	{
		fdf[i][j].pos_x = vars->size.start_x;
		fdf[i][j].pos_y = vars->size.start_y;
	}
	else if (i != 0 && j == 0)
	{
		fdf[i][j].pos_x = fdf[i - 1][j].pos_x - (vars->size.space * cos(MPI / 4));
		fdf[i][j].pos_y = fdf[i - 1][j].pos_y + (vars->size.space * sin(MPI / 4) * sin(MPI / 4))
			- (fdf[i][j].z * sin(MPI / 4));
	}
	else
	{
		fdf[i][j].pos_x = fdf[i][j - 1].pos_x + (vars->size.space * cos(MPI / 4));
		fdf[i][j].pos_y = fdf[i][j - 1].pos_y + (vars->size.space * sin(MPI / 4) * sin(MPI / 4))
			- (fdf[i][j].z * sin(MPI / 4));
	}
//	printf("(%d, %d)=( %f, %f)\n", i, j, fdf[i][j].pos_x, fdf[i][j].pos_y);
	my_point(vars, fdf[i][j].pos_x, fdf[i][j].pos_y, fdf[i][j].color);
}
*/
void print_struct(t_var	*vars, t_point **fdf)
{
	int	i;
	int j;

	i = 0;
//	while (fdf[i])
	while (i < vars->size.y)
	{
		j = 0;
//		while (fdf[i][j].color)
		while (j < vars->size.x)
		{
//			printf("aqui[%d][%d]\n", i, j);
//			print_point(vars, fdf, i, j);
			my_point(vars, fdf[i][j].pos_x, fdf[i][j].pos_y, fdf[i][j].color);
//			make_line(vars, fdf, i, j);
			j++;
		}
		i++;
	}
}
