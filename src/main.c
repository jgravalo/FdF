/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgravalo <jgravalo@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:48:19 by jgravalo          #+#    #+#             */
/*   Updated: 2023/05/22 17:54:38 by jgravalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

int	main(int argc, char **argv)
{
	t_var	vars;
	t_point **fdf;

//	printf("sin(90) = %.2f\n", sin(MPI / 4));
	vars.size = make_size(argc, argv, &vars);
	fdf = make_struct(argc, argv, &vars);
//	vars.x = 1440;
//	vars.y = 1180;
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, vars.x, vars.y, "FdF");
	vars.img.img = mlx_new_image(vars.mlx, vars.x, vars.y);
	vars.img.addr = mlx_get_data_addr(vars.img.img, &vars.img.bits_per_pixel,
		&vars.img.line_length, &vars.img.endian);

//	my_point(&vars, vars.x / 2, vars.y / 2, 0x00FF0000);
//	printf("aqui\n");
	print_struct(&vars, fdf);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img.img, 0, 0);
	
/*
	my_point(&vars, vars.x / 2, vars.y / 2, 0x0000FFFF); //azul
	my_point(&vars, vars.x / 2, vars.y / 2 + 10, 0x00FF0000);//rojo
	my_point(&vars, vars.x / 2, vars.y / 2 + 20, 0x0000FF00);//amarillo
*/
//	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_hook(vars.win, 2, 1L<<0, close_win, &vars);
	mlx_hook(vars.win, 17, 1L<<0, close_win, &vars);
	mlx_loop(vars.mlx);
	free_fdf(fdf);
}

void	free_fdf(t_point **fdf)
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
