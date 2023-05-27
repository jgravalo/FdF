/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgravalo <jgravalo@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:44:32 by jgravalo          #+#    #+#             */
/*   Updated: 2023/05/27 20:47:48 by jgravalo         ###   ########.fr       */
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

void	vars_values(t_var *vars)
{
	float	rel;

	vars->x = 1240;
	vars->y = 1080;
	vars->size.start_x = vars->x / 2 - vars->size.x * cos(MPI / 4)
		+ vars->size.y * sin(MPI / 4);
	vars->size.start_y = vars->y * 2 / 5;
	vars->size.space = (vars->x * 2 / 3) / (vars->size.x + vars->size.y)
		/ cos(MPI / 4);
	rel = (vars->size.max_z - vars->size.min_z)
		/ (vars->size.y * sin(MPI / 4) + vars->size.x * cos(MPI / 4));
	if (rel > 1.5)
		vars->size.space /= rel;
}

void	max_values(t_var *vars, char *c)
{
	t_point	p;
	char	**m;
	char	**s;

	s = ft_split(c, ' ');
	p.x = 0;
	while (s[(int)p.x])
	{
		p.y = 0;
		while (s[(int)p.x][(int)p.y] && s[(int)p.x][(int)p.y] != ',')
			p.y++;
		p.z = ft_atoi(s[(int)p.x]);
		if (s[(int)p.x][(int)p.y] == ',')
		{
			m = ft_split(s[(int)p.x], ',');
			p.z = ft_atoi(m[0]);
			free_fdf((void **)m);
		}
		if (p.z > vars->size.max_z)
			vars->size.max_z = p.z;
		if (p.z < vars->size.min_z)
			vars->size.min_z = p.z;
		p.x++;
	}
	free_fdf((void **)s);
}

void	size_values(t_var *vars, int fd)
{
	int		j;
	int		i;
	char	*c;
	char	**m;

	c = get_next_line(fd);
	m = ft_split(c, ' ');
	i = 0;
	while (m[i])
		i++;
	i--;
	free_fdf((void **)m);
	j = 0;
	while (c)
	{
		max_values(vars, c);
		free(c);
		c = get_next_line(fd);
		j++;
	}
	free(c);
	vars->size.x = i;
	vars->size.y = j;
}

t_map	make_size(int argc, char **argv, t_var *vars)
{
	int		fd;

	if (argc != 2)
		exit(-1);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		exit(-1);
	size_values(vars, fd);
	vars_values(vars);
	close(fd);
	return (vars->size);
}
