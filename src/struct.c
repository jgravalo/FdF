/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgravalo <jgravalo@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:44:32 by jgravalo          #+#    #+#             */
/*   Updated: 2023/05/27 20:47:03 by jgravalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/fdf.h"

void	p_val(t_point *p, t_var *vars, int x, int y)
{
	p->x = x;
	p->y = y;
	p->pos_x = vars->size.start_x
		+ (p->x * vars->size.space * cos(MPI / 4))
		- (p->y * vars->size.space * sin(MPI / 4));
	p->pos_y = vars->size.start_y
		+ (p->x * vars->size.space * pow(sin(MPI / 4), 2))
		+ (p->y * vars->size.space * pow(sin(MPI / 4), 2))
		- (p->z * sin(MPI / 4));
}

t_point	make_point(t_var *vars, char *src, int y, int x)
{
	t_point	p;
	int		n;
	char	**m;

	n = 0;
	while (src[n] && src[n] != ',')
		n++;
	if (src[n] == ',')
	{
		m = ft_split(src, ',');
		p.z = ft_atoi(m[0]) * vars->size.space;
		p.color = ft_atoill(m[1]);
		free_fdf((void **)m);
	}
	else
	{
		p.z = ft_atoi(src) * vars->size.space;
		p.color = 0x00FFFF00;
	}
	p_val(&p, vars, x, y);
	return (p);
}

t_point	**make_struct(char **argv, t_var *vars)
{
	t_point	**p;
	t_point	t;
	int		fd;
	char	**m;
	char	*c;

	fd = open(argv[1], O_RDONLY);
	t.y = 0;
	p = (t_point **)malloc(sizeof(t_point *) * vars->size.y);
	while (t.y < vars->size.y)
	{
		p[(int)t.y] = (t_point *)malloc(sizeof(t_point) * (vars->size.x + 1));
		c = get_next_line(fd);
		m = ft_split(c, ' ');
		t.x = 0;
		while (t.x < vars->size.x)
		{
			p[(int)t.y][(int)t.x] = make_point(vars, m[(int)t.x], t.y, t.x);
			t.x++;
		}
		free (c);
		free_fdf((void **)m);
		t.y++;
	}
	return (p);
}
