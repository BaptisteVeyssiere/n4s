/*
** tools.c for n4s in /home/scutar_n/rendu/CPE/CPE_2015_n4s
**
** Made by nathan scutari
** Login   <scutar_n@epitech.net>
**
** Started on  Wed May 25 16:50:38 2016 nathan scutari
** Last update Wed May 25 16:51:13 2016 nathan scutari
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
