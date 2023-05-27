/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgravalo <jgravalo@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:48:19 by jgravalo          #+#    #+#             */
/*   Updated: 2023/05/26 19:08:33 by jgravalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

int	main(int argc, char **argv)
{
	t_var	vars;
	t_point **fdf;

	vars.size = make_size(argc, argv, &vars);
	fdf = make_struct(argc, argv, &vars);
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, vars.x, vars.y, "FdF");
	vars.img.img = mlx_new_image(vars.mlx, vars.x, vars.y);
	vars.img.addr = mlx_get_data_addr(vars.img.img, &vars.img.bits_per_pixel,
		&vars.img.line_length, &vars.img.endian);
	print_struct(&vars, fdf);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img.img, 0, 0);
	mlx_hook(vars.win, 2, 1L<<0, key_hook, &vars);
	mlx_hook(vars.win, 17, 0, close_win, &vars);
	mlx_loop(vars.mlx);
	free_fdf((void **)fdf);
	return (0);
}

void	free_fdf(void **fdf)
{
	int	i;

	i = 0;
	while(fdf[i])
	{
		free(fdf[i]);
		i++;
	}
	free(fdf);
}
