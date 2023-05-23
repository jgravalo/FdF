#include "../inc/minilibx_macos/mlx.h"
#include "../inc/fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void    line_img(void *mlx, void *mlx_win, t_data img, t_line line)
{
//	int nx = line.sumx;
//	int ny = line.sumy;
	int nx = 0;
	int ny = 0;
	while (nx <= line.lenx && nx >= -line.lenx
		&& ny <= line.leny && ny >= -line.leny)
//	while (nx <= line.lenx - 1 && nx >= -line.lenx + 1
//		&& ny <= line.leny - 1 && ny >= -line.leny + 1)
	{
		mlx_put_image_to_window(mlx, mlx_win, img.img, line.x1 + nx, line.y1 + ny);
		nx += line.sumx;
		ny += line.sumy;
    }
}

void	make_line(void *mlx, void *mlx_win, t_data img, t_point p1, t_point p2)
{
	t_line	line;

	line.x1 = p1.x;
	line.y1 = p1.y;
	line.x2 = p2.x;
	line.y2 = p2.y;
	line.lenx = line.x2 - line.x1;
	line.leny = line.y2 - line.y1;
	line.sumx = 1;
    line.sumy = 1;
	if (line.lenx > line.leny)
		line.sumx = (float)line.lenx / (float)line.leny;
	else
		line.sumy = (float)line.leny / (float)line.lenx;
	line_img(mlx, mlx_win, img, line);
/*	
	line.sumx = 1;
	if (line.x2 - line.x1 < 0)
		line.sumx = -1;
	line.sumy = 
*/
}



void    make_points(void *mlx, void *mlx_win, t_data img, t_point **p, t_map start, t_map size, int len)
{
	int i;
	int j;

	j = 0;
	while (j < size.x)
	{
		i = 0;
//		printf("(%d, %d): (%d, %d, %d)\n", i, j, p[i][j].x, p[i][j].y, p[i][j].z); // BORRAR
		while (i < size.y)
		{
			p[i][j].x = start.x - len * i;
			p[i][j].y = start.y + len * i - (p[i][j].z * 8);
			mlx_put_image_to_window(mlx, mlx_win, img.img, p[i][j].x, p[i][j].y);
			i++;
		}
		start.x += len;
		start.y += len;
//		printf("\n");// BORRAR
		j++;
	}
}

t_map	make_start_point(t_map size, t_map win, int len)
{
	t_map	start;

	start.y = win.y / 2 - ((size.x + size.y) * len) / 2 ;
	start.x = win.x / 2;
	return (start);
}

void	make_map(void *mlx, void *mlx_win, t_data img, t_point **p, t_map size)
{
	int j;
	int i;

	j = 0;
	while (j < size.x)
	{
		i = 0;
		while (i < size.y)
		{
			
			if (p[i + 1][j].x)
				make_line(mlx, mlx_win, img, p[i][j], p[i + 1][j]);
			if (p[i][j + 1].x)
				make_line(mlx, mlx_win, img, p[i][j], p[i][j + 1]);
			
			i++;
		}
		j++;
	}
}

int	main(int argc, char **argv)
{
	t_map	win;
	t_map	size;
	t_point	**p;
	
	if (argc != 2)
		return (0);
	win.x = 1050;
	win.y = 680;

	size = find_size(argv[1]);
	printf("x = %d, y = %d\n", size.x , size.y);
	p = (t_point **)malloc(sizeof(t_point *) * (size.y + 1));
	make_struct(p, size, argv[1]);


	int len = 20;
	t_map start = make_start_point(size, win, len);
	
//	printf("x = %d, y = %d\n", start.x , start.y);
//	print_values(p, size);
	
// MY_WINDOW


	void	*mlx;
	void	*mlx_win;
	t_data	img;
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, win.x, win.y, "FdF");
	img.img = mlx_new_image(mlx, win.x, win.y);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	my_mlx_pixel_put(&img, 1 / 10, 1 / 10, 0x00FF0000);
	make_points(mlx, mlx_win, img, p, start, size, len);
//	make_map(mlx, mlx_win, img, p, size);
/*
		make_line(mlx, mlx_win, img, p[0][0], p[0][1]);
		make_line(mlx, mlx_win, img, p[0][1], p[0][2]);
		make_line(mlx, mlx_win, img, p[1][0], p[1][1]);
		make_line(mlx, mlx_win, img, p[3][0], p[3][1]);
*/
//	mlx_put_image_to_window(mlx, mlx_win, img.img, win.x / 2, win.y / 2);
/*	mlx_put_image_to_window(mlx, mlx_win, img.img, p[1][0].x, p[1][0].y);
	mlx_put_image_to_window(mlx, mlx_win, img.img, p[1][1].x, p[1][1].y);
	mlx_put_image_to_window(mlx, mlx_win, img.img, p[2][0].x, p[2][0].y);
*/
	
		
	mlx_loop(mlx);

}
