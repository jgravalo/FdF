/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   points.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgravalo <jgravalo@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:30:31 by jgravalo          #+#    #+#             */
/*   Updated: 2023/05/26 19:11:33 by jgravalo         ###   ########.fr       */
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
	if (x > 1 && x < vars->x - 1 && y > 1 && x < vars->y - 1)
		my_mlx_pixel_put(&vars->img, x, y, color);
}

void	draw_line(t_var *vars, t_point start, t_point end)
{
	t_point	tmp;
	t_point	pixel;
	int		points;
	int		len;

	tmp.pos_x = end.pos_x - start.pos_x;
	tmp.pos_y = end.pos_y - start.pos_y;
	points = sqrt((tmp.pos_x * tmp.pos_x) + \
			(tmp.pos_y * tmp.pos_y));
	len = points;
	tmp.pos_x /= points;
	tmp.pos_y /= points;
	pixel.pos_x = start.pos_x;
	pixel.pos_y = start.pos_y;
	while (points > 0)
	{
		if (points < len / 2)
			my_point(vars, pixel.pos_x, pixel.pos_y, end.color);
		else
			my_point(vars, pixel.pos_x, pixel.pos_y, start.color);
		pixel.pos_x += tmp.pos_x;
		pixel.pos_y += tmp.pos_y;
		points -= 1;
	}
}

void make_line(t_var *vars, t_point **fdf, int i, int j)
{
	if (j < vars->size.x - 1)
		draw_line(vars, fdf[i][j], fdf[i][j + 1]);
	if (i < vars->size.y - 1)
		draw_line(vars, fdf[i][j], fdf[i + 1][j]);
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
			make_line(vars, fdf, i, j);
			j++;
		}
		i++;
	}
}
