#include "minilibx_macos/mlx.h"

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct	s_point
{
	int	x;
	int	y;
}				t_point;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	my_line_img(void *mlx, void *mlx_win, t_data img, t_point start, int sumx, int sumy, int lenx, int leny)
{
	int nx = sumx;
	int ny = sumy;
/*	int nx = 0;
	int ny = 0;
	while (nx <= lenx && nx >= -lenx && ny <= leny && ny >= -leny)
*/	while (nx <= lenx - 1 && nx >= -lenx + 1 && ny <= leny - 1 && ny >= -leny + 1)
	{
		mlx_put_image_to_window(mlx, mlx_win, img.img, start.x + nx, start.y + ny);
		nx += sumx;
		ny += sumy;
	}
}
/*
void	my_square_img(void *mlx, void *mlx_win, t_data img, int x, int y, int sum, int len)
{
	my_line_img(mlx, mlx_win, img, x, y - len, -sum, sum, len, len * 2);
	my_line_img(mlx, mlx_win, img, x, y - len, sum, sum, len, len * 2);
	my_line_img(mlx, mlx_win, img, x - len, y, sum, sum, len, len * 2);
	my_line_img(mlx, mlx_win, img, x + len, y  , -sum, sum, len, len / 2);
}

void	my_map_img(void *mlx, void *mlx_win, t_data img, int x, int y, int sum, int len)
{

//	my_square_img(mlx, mlx_win, img, x / 2 - len, y / 2 - len, sum, len / 2);
	my_square_img(mlx, mlx_win, img, x / 2 - len / 2, y / 2 - len / 2, sum, len / 2);//Noroeste
	my_square_img(mlx, mlx_win, img, x / 2, y / 2 - len, sum, len / 2);//Norte
	my_square_img(mlx, mlx_win, img, x / 2 + len / 2, y / 2 - len / 2, sum, len / 2);//Noreste
	my_square_img(mlx, mlx_win, img, x / 2 - len, y / 2, sum, len / 2);//Oeste
	my_square_img(mlx, mlx_win, img, x / 2, y / 2, sum, len / 2);//Centro
	my_square_img(mlx, mlx_win, img, x / 2 - len / 2, y / 2 + len / 2, sum, len / 2);//Sudoeste
	my_square_img(mlx, mlx_win, img, x / 2 + len / 2, y / 2 + len / 2, sum, len / 2);//Sudeste
	my_square_img(mlx, mlx_win, img, x / 2, y / 2 + len, sum, len / 2);//Sur
	my_square_img(mlx, mlx_win, img, x / 2 + len, y / 2, sum, len / 2);//Este
//	my_square_img(mlx, mlx_win, img, x / 2 + len, y / 2, sum, len / 2);
}*/

void	my_map_creator(void *mlx, void *mlx_win, t_data img, t_point start, t_point map, int len)
{
//	int x = start.x + (map.x / 2) * len;
//	if (map)
	int i = 0;
	while (i < map.y - 1)
	{
		int j = 0;
		my_line_img(mlx, mlx_win, img, start, -1, 1, (map.x - 1) * len, (map.x - 1) * len);
		t_point	ptr = start;
		while (j < map.x)
		{
			my_line_img(mlx, mlx_win, img, ptr, 1, 1, len, len);
			ptr.x -= len;
			ptr.y += len;
			j++;
		}
		start.x += len;
		start.y += len;
		i++;
	}
	my_line_img(mlx, mlx_win, img, start, -1, 1, (map.x - 1) * len, (map.x - 1) * len);
//	while ()
//	my_line_img(mlx, mlx_win, img, start, -1, 1, map.x, map.x);

}

int	main(void)
{
	void	*mlx;
	t_data	img;
	int		x = 1050;
	int		y = 680;
	void	*mlx_win;
	t_point	start;
	t_point	map;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, x, y, "Hello world!");
	img.img = mlx_new_image(mlx, x, y);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	my_mlx_pixel_put(&img, 1 / 10, 1 / 10, 0x00FF0000);
	start.x = x / 2;
	start.y = y / 2;
	map.x = 6;
	map.y = 5;
	mlx_put_image_to_window(mlx, mlx_win, img.img, start.x, start.y);

	my_map_creator(mlx, mlx_win, img, start, map, 30);

//	my_map_img(mlx, mlx_win, img, x, y, 1, 60);
/*	
	int i = x / 2; //coordenada horizontal
	int j = y / 2 - 100; //coordenada vertical
	int n1 = 0;
	int n2 = 0;
	while (n1 < 100 && n2 < 100)
	{
		mlx_put_image_to_window(mlx, mlx_win, img.img, i - n1, j + n2);
		mlx_put_image_to_window(mlx, mlx_win, img.img, i + n1, j + n2);
		n1 += 10;
		n2 += 10;
	}
*/
/*
	while (n1 > 0 && n2 > 0)
	{
		mlx_put_image_to_window(mlx, mlx_win, img.img, i - n1, j + n2);
		mlx_put_image_to_window(mlx, mlx_win, img.img, i + n1, j + n2);
		n1 -= 10;
		n2 -= 10;
	}
*/
/*	mlx_put_image_to_window(mlx, mlx_win, img.img, i, j);
	mlx_put_image_to_window(mlx, mlx_win, img.img, i + 50, j + 50);
	mlx_put_image_to_window(mlx, mlx_win, img.img, i + 100, j + 100);
*/
/*	char	*relative_path = "./test.xpm";
	int		img_width;
	int		img_height;
	img.img = mlx_xpm_file_to_image(mlx, relative_path, &img_width, &img_height);
*/	mlx_loop(mlx);
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
