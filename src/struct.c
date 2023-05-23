/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgravalo <jgravalo@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:44:32 by jgravalo          #+#    #+#             */
/*   Updated: 2023/05/23 16:03:04 by jgravalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/fdf.h"

float	make_space(t_map size)
{
	float	space;
	float	i;
	float	j;

	space = 25;
	i = size.x * space;
	j = size.y * space * 0.8;
	if (1624 < i)
	{
		space = 1200 / size.x;
	}
	printf("space = %f\n", space);
	return (space);
}

void	win_len(t_var *vars)
{
	if (vars->size.x * vars->size.space + 80 > 1080)
	{
		vars->x = vars->size.x * vars->size.space + 40;
		vars->y = vars->x * 0.8;
	}
	else
	{
		vars->x = 1080;
		vars->y = 850;
	}
	printf("win: x=%f y=%f\n", vars->x, vars->y);
}

t_map   make_size(int argc, char **argv, t_var *vars)
{
	int     j;
	int     i;
	int     fd;
	char    *c;
	char    **m;

	if (argc != 2)
		exit(-1);
	fd = open(argv[1], O_RDONLY);
	c = get_next_line(fd);
	m = ft_split(c, ' ');
	i = 0;
	while (m[i])
        i++;
	j = 0;
	while (c)
	{
		c = get_next_line(fd);
		j++;
	}
	vars->size.x = i ;
	vars->size.y = j ;
	printf("map: x=%f y=%f\n", vars->size.x, vars->size.y);
	vars->size.space = make_space(vars->size);
	win_len(vars);
	vars->x = 1240;
	vars->y = 1080;
	vars->size.start_x = vars->x / 2;
	vars->size.start_y = vars->y / 2;
	close(fd);
	return (vars->size);
}

t_point	make_point(t_var *vars, char *src, int y, int x)
{
	t_point	p;
	int		n;
	char    **m;

	n = 0;
	p.x = x;
	p.y = y;
	while (src[n] && src[n] != ',')
		n++;
	if (src[n] == ',')
	{
		m = ft_split(src, ',');
		p.z = ft_atoi(m[0]) * vars->size.space;
		p.color = ft_atoill(m[1]);// PREGUNTAR VOID *
		free(m);
	}
	else
	{
		p.z = ft_atoi(src) * vars->size.space;
		p.color = 0x00FF0000;
	}
	p.pos_x = vars->size.start_x
		+ (p.x * vars->size.space * cos(MPI / 4))
		- (p.y * vars->size.space * sin(MPI / 4))
		;
	p.pos_y = vars->size.start_y
		+ (p.x * vars->size.space * pow(sin(MPI / 4), 2))
		+ (p.y * vars->size.space * pow(sin(MPI / 4), 2))
		- (p.z * sin(MPI / 4))
		;
	printf("(%d, %d)", y, x);
	printf("x=%f, y=%f, z=%f, ", p.x, p.y, p.z);
//	printf("color=%lu, ", p.color);
	printf("(%.2f, %.2f)\n", p.pos_y, p.pos_x);
	return (p);
}

t_point	**make_struct(int argc, char **argv, t_var *vars)
{
	t_point **p;
	int		fd;
	int		i;
	int		j;
	char    **m;
	
	if (argc != 2)
		exit(-1);
	fd = open(argv[1], O_RDONLY);
	i = 0;
	p = (t_point **)malloc(sizeof(t_point *) * vars->size.y);
	while (i < vars->size.y)
	{
//		printf("aqui\n");
		p[i] = (t_point *)malloc(sizeof(t_point) * (vars->size.x + 1));
		m = ft_split(get_next_line(fd), ' ');
		if (!m)
			break ;
		j = 0;
		while (j < vars->size.x)
		{
			p[i][j] = make_point(vars, m[j], i, j);
			j++;
		}
		free(m);// LEAKS ???
		i++;
	}
	close(fd);
	return (p);
}
