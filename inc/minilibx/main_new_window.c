
void    *mlx_new_window(t_xvar *xvar, int size_x, int size_y, char *title)

int main()
{
	t_xvar	*xvar;

	xvar->display			= ;
	xvar.root				= ;
	xvar.screen				= 1;
	xvar.depth				= ;
	xvar->visual			= ;
	xvar.cmap				= ;
	xvar.private_cmap		= ;
	xvar->win_list			= ;
	xvar->(*loop_hook)()	= ;
	xvar->loop_param		= ;
	xvar.use_xshm			= 1;
	xvar.pshm_format		= 1;
	xvar.do_flush			= 1;
	xvar.decrgb[6]			= 1;

	mlx_new_window(xvar, 105, 68, "UALA");
	return (0);
}
