/*
** commands.c for n4s in /home/scutar_n/rendu/CPE/CPE_2015_n4s/src
**
** Made by nathan scutari
** Login   <scutar_n@epitech.net>
**
** Started on  Sun May 29 16:39:50 2016 nathan scutari
** Last update Sun May 29 16:43:42 2016 nathan scutari
*/

#include <stdlib.h>
#include <unistd.h>
#include "ns.h"

int	stop_sim(void)
{
  char	buff[501];
  int	ret;

  if (write(1, "stop_simulation\n", 17) < 1 ||
      (ret = read(0, buff, 500)) < 1)
    return (1);
  buff[ret] = 0;
  if (buff[3] != 'O' || buff[4] != 'K')
    return (1);
  return (0);
}

int	send_command(char *command, double value, t_info_lidar *lid)
{
  char	buff[501];
  char	*c_value;
  int	ret;

  if (write(1, command, my_strlen(command)) < 1 ||
      (c_value = double_to_char(value)) == NULL ||
      write(1, c_value, my_strlen(c_value)) < 1 ||
      write(1, "\n", 1) < 1 ||
      (ret = read(0, buff, 500)) < 1)
    return (1);
  buff[ret] = 0;
  free(c_value);
  if (buff[6] != 'C')
    if (verif_command_one(lid, buff) == -1)
      return (1);
  return (0);
}

int	init_simulation(t_info_lidar *lid)
{
  char	buff[501];
  int	ret;

  if (write(1, "start_simulation\n", 17) < 1 ||
      (ret = read(0, buff, 500)) < 1)
    return (1);
  buff[ret] = 0;
  if (verif_command_one(lid, buff))
    return (1);
  return (0);
}
