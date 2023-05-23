#include "../inc/minilibx_macos/mlx.h"

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct	s_line
{
	int	x;
	int	y;
}				t_line;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	my_line_img(void *mlx, void *mlx_win, t_data img, t_line start, t_line final)
{
	int lenx;
	int leny;
	int sumx;
	int sumy;
	int nx;
	int ny;

	lenx = final.x - start.x;
	leny = final.y - start.y;
	if (lenx < 0)
		lenx *= -1;
	if (leny < 0)
		leny *= -1;
	nx = 0;
	ny = 0;
	sumx = 1;
	sumy = 1;
	if (lenx > leny)
		sumx = lenx / leny;
	else
		sumy = leny / lenx;
//	while (nx <= lenx - 1 && nx >= -lenx + 1 && ny <= leny - 1 && ny >= -leny + 1)
	while (nx <= lenx && nx >= -lenx && ny <= leny && ny >= -leny)
	{
		mlx_put_image_to_window(mlx, mlx_win, img.img, start.x + nx, start.y + ny);
		nx += sumx;
		ny += sumy;
	}
}
/*
void	my_line_img(void *mlx, void *mlx_win, t_data img, t_line start, int sumx, int sumy, int lenx, int leny)
{
//	int nx = sumx;
//	int ny = sumy;
	int nx = 0;
	int ny = 0;
	while (nx <= lenx && nx >= -lenx && ny <= leny && ny >= -leny)
//	while (nx <= lenx - 1 && nx >= -lenx + 1 && ny <= leny - 1 && ny >= -leny + 1)
	{
		mlx_put_image_to_window(mlx, mlx_win, img.img, start.x + nx, start.y + ny);
		nx += sumx;
		ny += sumy;
	}
}
*/
void	my_map_creator(void *mlx, void *mlx_win, t_data img, t_line start, t_line map, int len)
{
	int i;
	int j;
	t_line	ptr;
	t_line	ptr2;
	t_line	final;

	i = 0;
	while (i < map.y)
	{
		j = 0;
		final.x = start.x + map.x * len;
		final.y = start.y + map.x * len;
//		my_line_img(mlx, mlx_win, img, start, -1, 1, map.x * len, map.x * len);
		my_line_img(mlx, mlx_win, img, start, final);
		ptr = start;
		ptr2.x = ptr.x - len;
		ptr2.y = ptr.y + len;
		while (j < map.x + 1)
		{
			my_line_img(mlx, mlx_win, img, ptr, ptr2);
			my_line_img(mlx, mlx_win, img, start, final);
			ptr.x -= len;
			ptr.y += len;
			ptr2.x -= len;
			ptr2.y += len;
			j++;
		}
		start.x += len;
		start.y += len;
		final.x += len;
		final.y += len;
		i++;
	}
	my_line_img(mlx, mlx_win, img, start, final);
}
/*
void	my_centre(void *mlx, void *mlx_win, t_data img, t_line start, int len)
{
	my_line_img(mlx, mlx_win, img, start, 0, -1, 0, len);//arriba
	my_line_img(mlx, mlx_win, img, start, 0, 1, 0, len);//abajo
	my_line_img(mlx, mlx_win, img, start, 1, 0, len, 0);//derecha
	my_line_img(mlx, mlx_win, img, start, -1, 0, len, 0);//izquierda
}
*/

#define WIDTH 1050
#define HEIGHT 680

int	main(void)
{
	void	*mlx;
	t_data	img;
//	int		x = 1050;
//	int		y = 680;
	void	*mlx_win;
	t_line	start;
	t_line	map;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, WIDTH, HEIGHT, "Hello world!");
	img.img = mlx_new_image(mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	my_mlx_pixel_put(&img, 1 / 10, 1 / 10, 0x00FF0000);
	start.x = WIDTH / 2;
	start.y = HEIGHT / 2;
	map.x = 3;
	map.y = 6;
	mlx_put_image_to_window(mlx, mlx_win, img.img, start.x, start.y);
//	my_map_creator(mlx, mlx_win, img, start, map, 30);
//	my_centre(mlx, mlx_win, img, start, 10);
//
	t_line	final = start;
	final.x += 20;
	final.y -= 60;

	my_line_img(mlx, mlx_win, img, start, final);
	mlx_loop(mlx);
}

/*
int	main(void)
{
	void	*mlx;
	void	*img;
	char	*relative_path = "./test.xpm";
	int		img_width;
	int		img_height;

	mlx = mlx_init();
	img = mlx_xpm_file_to_image(mlx, relative_path, &img_width, &img_height);
	mlx_loop(mlx);
}*/