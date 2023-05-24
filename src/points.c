/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   points.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgravalo <jgravalo@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:30:31 by jgravalo          #+#    #+#             */
/*   Updated: 2023/05/24 16:20:55 by jgravalo         ###   ########.fr       */
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
	if (x > 10 && x < vars->x - 10 && y > 10 && x < vars->y - 10)
		my_mlx_pixel_put(&vars->img, x, y, color);
}

void print_line(t_var *vars, t_point p_i, t_point p_f)
{
	float	x;
	float	y;
	float	sum_x;
	float	sum_y;
	float	nx;
	float	ny;
/*	int		i;
	float	h;
	float	ang;

	i = 0;
*/	x = p_f.pos_x - p_i.pos_x;
	y = p_f.pos_y - p_i.pos_y;
	nx = 0.0;
	ny = 0.0;
	sum_x = 0.1;
	if (x > y)
		sum_x = x / y;
	else
		sum_y = y / x;
	while ((nx <= x && nx >= -x) && (ny <= y && ny >= -y))
	{
		if (nx <= x / 2)
			my_point(vars, p_i.pos_x + nx, p_i.pos_y + ny, p_i.color);
		else
			my_point(vars, p_i.pos_x + nx, p_i.pos_y + ny, p_f.color);
		nx += sum_x * 0.01;
		ny += sum_y * 0.01;
	}

/*	
	h = sqrt(y * y * x * x);
	ang = asin(abs(y) / h);
	printf("x = %d\n", x);
	printf("y = %d\n", y);
	printf("h = %f\n", h);
	printf("ang = %f\n", ang);
	while (i < h)
	{
		if (i < h / 2)
			my_point(vars, p_i.pos_x + i * cos(ang), p_i.pos_y + i * sin(ang)
				, p_i.color);
		else
			my_point(vars, p_i.pos_x + i * cos(ang), p_i.pos_y + i * sin(ang)
				, p_f.color);
		i++;
	}
*/
}

void make_line(t_var *vars, t_point **fdf, int i, int j)
{
	if (j > 0)
		print_line(vars, fdf[i][j - 1], fdf[i][j]);
	if (i > 0)
		print_line(vars, fdf[i - 1][j], fdf[i][j]);
}

void print_struct(t_var	*vars, t_point **fdf)
{
	int	i;
	int j;

	i = 0;
	while (i < vars->size.y)
	{
		j = 0;
		while (j < vars->size.x)
		{
//			printf("aqui[%d][%d]\n", i, j);
//			my_point(vars, fdf[i][j].pos_x, fdf[i][j].pos_y, fdf[i][j].color);
			make_line(vars, fdf, i, j);
			j++;
		}
		i++;
	}
}
