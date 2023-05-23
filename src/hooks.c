#include"../inc/fdf.h"

int	close_win(int keycode, t_var *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	exit(-1);
	if (keycode && vars)
		return (0);
	return (0);
}

int	key_hook(int keycode, t_var *vars)
{
	printf("Hello from key_hook!\n");
	if (keycode && vars)
		return (0);
	return (0);
}
