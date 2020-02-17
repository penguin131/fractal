#include "../inc/fractol.h"

void	usage(t_data *data)
{
	int	i;

	i = 0;
	write(1, "fractals: ", 10);
	while (i < FRACTAL_CNT)
	{
		ft_putstr(data->names[i]);
		if (i != FRACTAL_CNT - 1)
			write(1, ", ", 2);
		i++;
	}
	write(1, "\n", 1);
	exit(0);
}

int 	read_args(int c, char **v, t_data *data)
{
	int	i;

	if (c != 2)
		usage(data);
	i = 0;
	while (i < FRACTAL_CNT)
	{
		if (ft_strcmp(v[1], data->names[i]) == 0)
		{
			data->mode = (char)i;
			return (1);
		}
		i++;
	}
	return (0);
}

void	init_global(t_data *data)
{
	data->names[0] = "Mandelbrot";
	data->names[1] = "Julia";
	data->names[2] = "Burning ship";
	data->names[3] = "Buffalo";
	data->names[4] = "Mandelbar";
}

int		main(int c, char **v)
{
	t_data data;

	ft_bzero(&data, sizeof(t_data));
	init_global(&data);
	if (!read_args(c,v, &data))
		usage(&data);
	data.fractals[MANDELBROT] = mandelbrot;
	data.fractals[JULIA] = julia;
	data.fractals[BURNING] = burning_ship;
	data.fractals[BUFFALO] = buffalo;
	data.fractals[MANDELBAR] = mandelbar;
	initialize_constant(&data);
	initialize_mlx(&data, "zdarova!");
	data.max_iterations = START_ITER;
	loop(&data);
	end_mlx(&data);
}
