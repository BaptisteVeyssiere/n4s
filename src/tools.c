/*
** tools.c for n4s in /home/scutar_n/rendu/CPE/CPE_2015_n4s
**
** Made by nathan scutari
** Login   <scutar_n@epitech.net>
**
** Started on  Wed May 25 16:50:38 2016 nathan scutari
** Last update Wed May 25 20:40:04 2016 ilyas semmaoui
*/

#include "ns.h"

int	my_strlen(char *str)
{
  int	i;

  i = -1;
  if (!str)
    return (0);
  while (str[++i]);
  return (i);
}

int	strnmatch(char *str, char *to_match)
{
  int	i;
  int	j;
  int	count;
  int	len;

  i = -1;
  j = 0;
  count = 0;
  len = my_strlen(to_match);
  while (str && str[++i])
    {
      if (str[i] == to_match[j])
        {
          ++j;
          ++count;
        }
      else
        {
          j = 0;
          count = 0;
        }
      if (count == len)
        return (1);
    }
  return (0);
}
