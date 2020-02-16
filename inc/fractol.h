
#ifndef FRACTOL_H
#define FRACTOL_H

# include "../libft/inc/libft.h"
# include "../minilibx_macos/mlx.h"
# include <stdio.h>
# include <fcntl.h>
# include <math.h>

# define WIDTH 900
# define HEIGHT 900
# define MENU_HEIGHT 100

# define ITER_STEP 10
# define ZOOM_UP_STEP 0.8
# define ZOOM_DOWN_STEP 1.2
# define START_ITER 150

# define ESC 53
# define ITER_UP 18
# define ITER_DOWN 19
# define GET_ZOOM 1
# define ZOOM_REVERSE 20
# define THREAD_MODE 21
# define RIGHT 124
# define LEFT 123
# define SPACE 49

# define THREAD_CNT 50
# include <pthread.h>

# define FRACTAL_CNT 4

# define MANDELBROT 0
# define JULIA 1
# define BURNING 2
# define BUFFALO 3

typedef struct		s_complex_num
{
	double			img;
	double			real;
}					t_complex_num;

typedef struct		s_data
{
	char 			reverse_zoom;
	char 			solo_tread;
	char			hold_julia;
	int 			mode;
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	int				*mlx_map;
	int				size_line;
	int				endian;
	int 			max_iterations;
	int 			start;
	int 			end;
	t_complex_num	max;
	t_complex_num	min;
	t_complex_num	coeff;
	t_complex_num	julia_c;
	int				(*fractals[FRACTAL_CNT])(struct s_data *data, t_complex_num *c);
}					t_data;

void				loop(t_data *data);
void				fill_map(t_data *data);
void				fill_map_slow(t_data *data);
t_complex_num		init(double real, double img);
void				draw_fractal(t_data *data);
void				end_mlx(t_data *data);
int					zoom(int key, int x, int y, t_data *data);
void				initialize_constant(t_data *data);
int					get_color(int iteration, int max);
void				initialize_mlx(t_data *data, char *name);

int					julia(t_data *data, t_complex_num *c);
int					julia_flow(int x, int y, t_data *data);
int					mandelbrot(t_data *data, t_complex_num *c);
int					burning_ship(t_data *data, t_complex_num *c);
int					buffalo(t_data *data, t_complex_num *c);

static char			*g_fractals[] = {
		"Mandelbrot",
		"Julia",
		"Burning ship",
		"Buffalo"
};

#endif
