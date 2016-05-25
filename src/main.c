/*
** main.c for n4s in /home/VEYSSI_B/rendu/C_Prog_Elem/CPE_2015_n4s
**
** Made by Baptiste veyssiere
** Login   <VEYSSI_B@epitech.net>
**
** Started on  Tue May 24 16:35:01 2016 Baptiste veyssiere
** Last update Wed May 25 18:16:24 2016 nathan scutari
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "ns.h"

static int	init_simulation(void)
{
  char	buff[501];
  int	ret;

  if (write(1, "start_simulation\n", 17) < 1 ||
      (ret = read(0, buff, 500)) < 1)
    return (1);
  buff[ret] = 0;
  if (verif_command_one(buff))
    return (1);
  return (0);
}

int		manage_speed(t_info_lidar *lid)
{
  char		buff[501];
  double	speed;
  char		*value;
  double	distance;
  int		i;

  i = 13;
  distance = 0;
  while (++i < 18)
    distance += lid->lidar[i];
  distance /= 4;
  speed = ((distance - 100)) / (2910);
  if ((value = double_to_char(speed)) == NULL)
    return (1);
  if (speed < 0)
    speed = 0;
  if (speed != lid->speed)
    {
      lid->speed = speed;
      if (write(1, "car_forward:", 12) < 1 ||
	  write(1, value, my_strlen(value)) < 1 ||
	  write(2, value, my_strlen(value)) < 1 ||
	  write(2, "\n", 1) < 1 ||
	  write(1, "\n", 1) < 1 ||
	  (i = read(0, buff, 500)) < 1)
	return (1);
      free(value);
      buff[i] = 0;
      if (verif_command_one(buff))
	return (1);
    }
  return (0);
}

int	manage_dir(t_info_lidar *lid)
{
  double	distancel;
  double	distancer;
  int		i;

  i = -1;
  distancel = 0;
  distancer = 0;
  while (++i < 10)
    {
      distancel += lid->lidar[i];
      distancer += lid->lidar[31 - i];
    }
  distancel /= 10;
  distancer /= 10;
  if (distancel > distancer - 100)
    return (turn_left(lid));
  else if (distancer > distancel - 100)
    return (turn_right(lid));
  return (0);
}

int	start_driving(t_info_lidar *lid)
{
  char	buff[501];
  int	ret;

  while (1)
    {
      write(1, "get_info_lidar\n", 15);
      ret = read(0, buff, 500);
      buff[ret] = 0;
      if (info_lidar(lid, buff) == -1 ||
	  manage_speed(lid) ||
	  manage_dir(lid))
	return (1);
    }
  return (0);
}

int	main()
{
  t_info_lidar	lid;

  lid.speed = 0;
  lid.wheels = 0;
  if (init_simulation())
    return (1);
  if (start_driving(&lid))
    return (1);
  return (0);
}
