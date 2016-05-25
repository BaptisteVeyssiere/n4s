/*
** dtc.c for n4s in /home/scutar_n/rendu/CPE/CPE_2015_n4s
**
** Made by nathan scutari
** Login   <scutar_n@epitech.net>
**
** Started on  Tue May 24 17:35:38 2016 nathan scutari
** Last update Tue May 24 18:48:58 2016 nathan scutari
*/

#include <stdlib.h>
#include <stdio.h>

int	nbr_length(double nbr)
{
  int	save;
  int	length;

  save = (int)nbr;
  length = 0;
  while (save > 0)
    {
      save /= 10;
      length++;
    }
  length++;
  while (nbr - (int)nbr > 0.0001)
    {
      nbr *= 10;
      nbr -= (int)nbr;
      length++;
    }
  return (length);
}

int	int_length(int nbr)
{
  int	length;

  length = 0;
  while (nbr > 0)
    {
      nbr /= 10;
      length++;
    }
  return (length);
}

void	deci_to_char(double nbr, char *result, int i)
{
  while (nbr - (int)nbr > 0.0001)
    {
      nbr *= 10;
      result[++i] = ((int)nbr % 10) + 48;
      nbr -= (int)nbr;
    }
}

char	*double_to_char(double nbr)
{
  int	i;
  int	save;
  char	*result;

  if ((result = malloc(nbr_length(nbr) + 1)) == NULL)
    return (NULL);
  result[nbr_length(nbr)] = 0;
  i = int_length((int)nbr);
  save = (int)nbr;
  while (save > 0)
    {
      result[--i] = (save % 10) + 48;
      save /= 10;
    }
  i = int_length((int)nbr);
  result[i] = '.';
  deci_to_char(nbr, result, i);
  return (result);
}
