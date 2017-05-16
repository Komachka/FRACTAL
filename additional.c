#include "FRACTOL.h"

char	*ft_toupper_str(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		str[i] = (char)ft_toupper(str[i]);
		i++;
	}
	return (str);

}

void	del_arrey(void **arrey, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		if (arrey[i] != NULL)
			free(arrey[i]);
		i++;
	}
	if (arrey != NULL)
		free(arrey);
}

void	swap(double *x1, double *x2)
{
	double	i;
	double	j;

	i = *x1;
	j = *x2;
	*x1 = j;
	*x2 = i;
}

int		get_index(int i)
{
	int index;

	index = 1;
	if (i == 1)
		index = 1;
	else if (i == 2)
		index = 4;
	else if (i == 3)
		index = 7;
	return (index);
}

double  to_radians(double degrees)
{
	return (degrees / 180.0 * M_PI);
}