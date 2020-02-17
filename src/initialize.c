#include "../inc/fractol.h"

t_complex_num	init(double real, double img)
{
	t_complex_num	result;

	result.img = img;
	result.real = real;
	return (result);
}

void			initialize_mlx(t_data *data, char *name)
{
	int a = 0;

	data->size_line = 0;
	data->endian = 0;
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT + MENU_HEIGHT, name);
	data->img_ptr = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT + MENU_HEIGHT);
	data->mlx_map = (int*)mlx_get_data_addr(data->img_ptr, &a, &data->size_line, &data->endian);
}

void			end_mlx(t_data *data)
{
	mlx_destroy_image(data->mlx_ptr, data->img_ptr);//чищу имейдж
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);//чищу окно
	exit(0);
}

/**
 * по х реальная часть числа, по у мнимая
 */
void			initialize_constant(t_data *data)
{
	data->min = init(-2.0, -2.0);
	data->max = init(2.0, 2.0);
//	data->max.real = 2.0;
//	data->max.img = data->min.img + (data->max.real - data->min.real) * HEIGHT / WIDTH;
	data->julia_c = init(-0.4, 0.6);
}
