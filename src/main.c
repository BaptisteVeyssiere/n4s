/*
** main.c for n4s in /home/VEYSSI_B/rendu/C_Prog_Elem/CPE_2015_n4s
**
** Made by Baptiste veyssiere
** Login   <VEYSSI_B@epitech.net>
**
** Started on  Tue May 24 16:35:01 2016 Baptiste veyssiere
** Last update Wed May 25 20:55:35 2016 nathan scutari
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "ns.h"

int	send_command(char *command, double value)
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
  if (verif_command_one(buff) == -1)
    return (1);
  return (0);
}

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

  i = 9;
  distance = 0;
  while (++i < 22)
    distance += lid->lidar[i];
  distance /= 12;
  speed = ((distance - 100) * 0.8) / (2910) + 0.2;
  if (distance < 250)
    speed = 0;
  if ((value = double_to_char(speed)) == NULL)
    return (1);
  if (speed < 0)
    speed = 0;
  if (speed != lid->speed)
    {
      lid->speed = speed;
      if (write(1, "car_forward:", 12) < 1 ||
	  write(1, value, my_strlen(value)) < 1 ||
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

int		turn_left(t_info_lidar *lid)
{
  char		buff[501];
  char		*value;
  double	dir;
  int		i;
  double	distance;

  distance = 0;
  i = 13;
  while (++i < 18)
    distance += lid->lidar[i];
  distance /= 4;
  dir = 0.7 - (distance * 0.7) / 1200;
  if (dir < 0)
    dir = 0;
  if ((value = double_to_char(dir)) == NULL)
    return (1);
  if (dir != lid->wheels)
    {
      lid->wheels = dir;
      if (write(1, "wheels_dir:", 11) < 1 ||
	  write(1, value, my_strlen(value)) < 1 ||
	  write(1, "\n", 1) < 1 ||
	  (i = read(0, buff, 501)) < 1)
	return (1);
      free(value);
      buff[i] = 0;
      if (verif_command_one(buff))
	return (1);
    }
  return (0);
}

int		turn_right(t_info_lidar *lid)
{
  char		buff[501];
  char		*value;
  double	dir;
  int		i;
  double	distance;

  distance = 0;
  i = 13;
  while (++i < 18)
    distance += lid->lidar[i];
  distance /= 4;
  dir = 0.7 - (distance * 0.7) / 1200;
  if (dir < 0)
    dir = 0;
  if ((value = double_to_char(dir)) == NULL)
    return (1);
  if (dir != lid->wheels)
    {
      lid->wheels = dir;
      if (write(1, "wheels_dir:-", 12) < 1 ||
	  write(1, value, my_strlen(value)) < 1 ||
	  write(1, "\n", 1) < 1 ||
	  (i = read(0, buff, 501)) < 1)
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
  while (++i < 13)
    {
      distancel += lid->lidar[i];
      distancer += lid->lidar[31 - i];
    }
  distancel /= 13;
  distancer /= 13;
  if (distancel > distancer - 100)
    return (turn_left(lid));
  else if (distancer > distancel - 100)
    return (turn_right(lid));
  return (0);
}

int	manage_stabilisation(t_info_lidar *lid)
{
  if (lid->lidar[0] < 200 && lid->lidar[31] < 200)
    return (send_command("car_forward:", 0));
  else if (lid->lidar[0] < 250)
    {
      if (send_command("car_forward:", 0.1) ||
	  send_command("wheels_dir:-", 0.04))
	return (1);
    }
  else if (lid->lidar[31] < 250)
    {
      if (send_command("car_forward:", 0.1) ||
	  send_command("wheels_dir:", 0.04))
	return (1);
    }
  return (0);
}

int	start_driving(t_info_lidar *lid)
{
  char	buff[501];
  int	ret;

  while (lid->additional_info != 4)
    {
      write(1, "get_info_lidar\n", 15);
      ret = read(0, buff, 500);
      buff[ret] = 0;
      if (info_lidar(lid, buff) == -1 ||
	  manage_speed(lid) ||
	  manage_dir(lid) ||
	  manage_stabilisation(lid))
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
