#include "../inc/fractol.h"

int		mandelbar(t_data *data, t_complex_num *c)
{
	int				i;
	t_complex_num	z;

	i = 0;
	z = init(c->real, c->img);
	while (z.real * z.real + z.img * z.img <= 4
		   && i < data->max_iterations)
	{
		z.real = z.real * z.real - z.img * z.img + c->real;
		z.img = -2.0 * z.real * z.img + c->img;
		i++;
	}
	return (i);
}
