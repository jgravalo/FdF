/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   points.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgravalo <jgravalo@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:30:31 by jgravalo          #+#    #+#             */
/*   Updated: 2023/05/26 18:36:39 by jgravalo         ###   ########.fr       */
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
	t_point	delta;
	t_point	pixel;
	int		pixels;
	int		len;

	delta.pos_x = end.pos_x - start.pos_x;
	delta.pos_y = end.pos_y - start.pos_y;
	pixels = sqrt((delta.pos_x * delta.pos_x) + \
			(delta.pos_y * delta.pos_y));
	len = pixels;
	delta.pos_x /= pixels;
	delta.pos_y /= pixels;
	pixel.pos_x = start.pos_x;
	pixel.pos_y = start.pos_y;
	while (pixels > 0)
	{
		if (pixels < len / 2)
			my_point(vars, pixel.pos_x, pixel.pos_y, end.color);
		else
			my_point(vars, pixel.pos_x, pixel.pos_y, start.color);
		pixel.pos_x += delta.pos_x;
		pixel.pos_y += delta.pos_y;
		pixels = pixels - 1;
	}
}

void make_line(t_var *vars, t_point **fdf, int i, int j)
{
	if (j < vars->size.x - 1)
//		print_line(vars, fdf[i][j], fdf[i][j + 1]);
//		my_line(vars, fdf[i][j], fdf[i][j + 1]);
		draw_line(vars, fdf[i][j], fdf[i][j + 1]);
	if (i < vars->size.y - 1)
//		print_line(vars, fdf[i][j], fdf[i + 1][j]);
//		my_line(vars, fdf[i][j], fdf[i + 1][j]);
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
//			printf("aqui[%d][%d]\n", i, j);
			
//			if (vars->size.space > 5)
				make_line(vars, fdf, i, j);
//			else
//				my_point(vars, fdf[i][j].pos_x, fdf[i][j].pos_y, fdf[i][j].color);
			j++;
		}
		i++;
	}
}
