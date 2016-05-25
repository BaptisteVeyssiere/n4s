/*
** my_getdouble.c for my_getdouble in /home/semmao_i/rendu/Infographie/gfx_wolf3d
**
** Made by ilyas semmaoui
** Login   <semmao_i@epitech.net>
**
** Started on  Wed Dec 16 18:35:10 2015 ilyas semmaoui
** Last update Wed May 25 16:16:52 2016 nathan scutari
*/

int	multd(const char *str, double *up, int i)
{
  while (str[i + 1] != '\0')
    {
      if (str[i] != '.')
	*up *= 10;
      i++;
    }
  return (0);
}

void	get_db(const char *str, double nbr, double *res)
{
  int	i;
  double	up;
  double	tmp;

  up = 1;
  i = 0;
  while (str[i] != '.' && str[i] != '\0')
    i++;
  if (str[i] != '\0')
    while (str[i + 1] != '\0')
      {
	up *= 10;
	i++;
      }
  tmp = ((double)nbr / up);
  *res = tmp;
}

void	my_getd(const char *str, double *res)
{
  double	up;
  int		i;
  double	nbr;
  int		key;

  nbr = 0.0;
  i = 0;
  up = 1.0;
  if (str[0] == '-')
    i = 1;
  key = i;
  multd(str, &up, i);
  while (up > 0.1)
    {
      if (str[i] != '.')
	{
	  nbr += up * (str[i] - 48);
	  up /= 10.0;
	}
      i++;
    }
  if (key == 1)
    nbr = -nbr;
  get_db(str, nbr, res);
}
