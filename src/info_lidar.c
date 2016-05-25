/*
** info_lidar.c for lidar in /home/semmao_i/rendu/CPE/CPE_2015_n4s/src
**
** Made by ilyas semmaoui
** Login   <semmao_i@epitech.net>
**
** Started on  Wed May 25 08:00:12 2016 ilyas semmaoui
** Last update Wed May 25 20:41:57 2016 ilyas semmaoui
*/

#include "ns.h"

int	(*verif_command[])(char *str) =
{
  verif_command_one,
  verif_command_two,
  verif_command_three,
  verif_command_four,
};

int	take_info_lidar(t_info_lidar *lidar, char *str)
{
  int	i;
  int	j;
  int	count;
  char	buff[48];

  i = 21;
  count = -1;
  while (++count < 32)
    {
      my_memset(buff, 48, 0);
      j = -1;
      while (str && str[++i] && str[i] != ':')
	buff[++j] = str[i];
      buff[++j] = '\0';
      my_getd(buff, &lidar->lidar[count]);
    }
  return (0);
}

int	info_lidar(t_info_lidar *lidar, char *str)
{
  if (strnmatch(str, "Track Cleared") == 1)
    lidar->additionnal_info = 4;
  else
    lidar->additionnal_info = 0;
  if (verif_command[1](str) == -1)
    {
      lidar->check_fail = 1;
      return (-1);
    }
  lidar->check_fail = 0;
  take_info_lidar(lidar, str);
  return (0);
}
