#include "../inc/fractol.h"

int 	mandelbrot(t_data *data, t_complex_num *c)
{
	int				i;
	t_complex_num	z;

	i = 0;
	z = init(c->real, c->img);
	while (z.real * z.real + z.img * z.img <= 4 && i < data->max_iterations)
	{
		z = init(z.real * z.real - z.img * z.img + c->real,
				2.0 * z.real * z.img + c->img);
		i++;
	}
	return (i);
}

int		julia(t_data *data, t_complex_num *c)
{
	int				i;
	t_complex_num	z;

	i = 0;
	z = init(c->real, c->img);
	while (z.real * z.real + z.img * z.img <= 4 && i < data->max_iterations)
	{
		z = init(
				z.real * z.real - z.img * z.img + data->julia_c.real,
				2.0 * z.real * z.img + data->julia_c.img);
		i++;
	}
	return (i);
}

int		julia_flow(int x, int y, t_data *data)
{
	if (data->mode == JULIA && !data->hold_julia)
	{
		data->julia_c = init(
				4 * ((double)x / WIDTH - 0.5),
				4 * ((double)(HEIGHT - y) / HEIGHT - 0.5));
		draw_fractal(data);
	}
	return (0);
}

int		burning_ship(t_data *data, t_complex_num *c)
{
	int				iteration;
	double 			d;
	t_complex_num	z;

	iteration = 0;
	z = init(c->real, c->img);
	while (z.real * z.real + z.img * z.img <= 4 && iteration < data->max_iterations)
	{
		d = z.real * z.img;
		if (d < 0)
			d *= -1;
		z = init(z.real * z.real - z.img * z.img + c->real,
				-2.0 * d + c->img);
		iteration++;
	}
	return (iteration);
}
