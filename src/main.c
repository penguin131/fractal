#include "../inc/fractol.h"

void	usage()
{
	int	i;

	i = 0;
	write(1, "fractals: ", 10);
	while (i < FRACTAL_CNT)
	{
		ft_putstr(g_fractals[i]);
		if (i != FRACTAL_CNT - 1)
			write(1, ", ", 2);
		i++;
	}
	exit(0);
}

int 	read_args(int c, char **v, t_data *data)
{
	int	i;

	if (c != 2)
		usage();
	i = 0;
	while (i < FRACTAL_CNT)
	{
		if (ft_strcmp(v[1], g_fractals[i]) == 0)
		{
			data->mode = (char)i;
			return (1);
		}
		i++;
	}
	return (0);
}

int		main(int c, char **v)
{
	t_data data;

	ft_bzero(&data, sizeof(t_data));
	if (!read_args(c,v, &data))
		usage();
	data.fractals[MANDELBROT] = mandelbrot;
	data.fractals[JULIA] = julia;
	data.fractals[BURNING] = burning_ship;
	initialize_constant(&data);
	initialize_mlx(&data, "zdarova!");
	data.max_iterations = START_ITER;
	loop(&data);
	end_mlx(&data);
}
