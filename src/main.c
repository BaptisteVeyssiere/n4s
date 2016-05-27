/*
** main.c for n4s in /home/VEYSSI_B/rendu/C_Prog_Elem/CPE_2015_n4s
**
** Made by Baptiste veyssiere
** Login   <VEYSSI_B@epitech.net>
**
** Started on  Tue May 24 16:35:01 2016 Baptiste veyssiere
** Last update Fri May 27 16:07:29 2016 nathan scutari
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "ns.h"

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

static int	init_simulation(t_info_lidar *lid)
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

int		manage_speed(t_info_lidar *lid)
{
  double	speed;
  double	distance;
  int		i;

  i = 12;
  distance = 0;
  while (++i < 19)
    distance += lid->lidar[i];
  distance /= 6;
  speed = ((distance - 200) * 0.7) / (2810) + 0.2;
  if (distance < 200)
    speed = 0;
  if (speed < 0)
    speed = 0;
  else if (speed > 1)
    speed = 1;
  if (speed != lid->speed)
    {
      lid->speed = speed;
      return (send_command("car_forward:", speed, lid));
    }
  return (0);
}

int		turn_left(t_info_lidar *lid)
{
  double	dir;
  int		i;
  double	distance;

  distance = 0;
  i = 13;
  while (++i < 18)
    distance += lid->lidar[i];
  distance /= 4;
  dir = 0.7 - (distance * 0.7) / 1000;
  if (dir < 0)
    dir = 0;
  if (lid->lidar[0] > 400)
    {
      if (dir != lid->wheels)
	lid->wheels = dir;
    }
  else
    lid->wheels = 0;
  return (0);
}

int		turn_right(t_info_lidar *lid)
{
  double	dir;
  int		i;
  double	distance;

  distance = 0;
  i = 13;
  while (++i < 18)
    distance += lid->lidar[i];
  distance /= 4;
  dir = 0.7 - (distance * 0.7) / 1000;
  if (dir < 0)
    dir = 0;
  if (lid->lidar[31] > 400)
    {
      if (dir != lid->wheels)
	{
	  lid->wheels = dir;
	}
    }
  else
    lid->wheels = 0;
  return (0);
}

void	change_memory(t_info_lidar *lid, double distancel, double distancer)
{
  if (distancel > lid->olda + 500)
    {
      lid->turn = 1;
      lid->memory = 1;
    }
  else if (distancer > lid->oldb + 500)
    {
      lid->turn = 2;
      lid->memory = 1;
    }
}

int	select_memory(t_info_lidar *lid, double distancel, double distancer)
{
  lid->memory = 1;
  if (distancel > distancer)
    {
      lid->turn = 1;
      return (turn_left(lid));
    }
  else
    {
      lid->turn = 2;
      return (turn_right(lid));
    }
  return (1);
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
  if (lid->memory && ++(lid->memory) < 5)
    {
      change_memory(lid, distancel, distancer);
      lid->olda = distancel;
      lid->oldb = distancer;
      if (lid->turn == 1)
	return (turn_left(lid));
      else if (lid->turn == 2)
	return (turn_right(lid));
    }
  else
    return (select_memory(lid, distancel, distancer));
  return (0);
}

int	manage_stabilisation(t_info_lidar *lid)
{
  if (lid->lidar[0] < 200 && lid->lidar[31] < 200)
    return (send_command("car_forward:", 0, lid));
  else if (lid->lidar[0] < 400 && lid->wheels < 0.1)
    {
      lid->warning = 1;
      if (send_command("wheels_dir:-", 0.2, lid) ||
	  send_command("wheels_dir:", 0, lid))
	return (1);
    }
  else if (lid->lidar[31] < 400 && lid->wheels < 0.1)
    {
      lid->warning = 1;
      if (send_command("wheels_dir:", 0.2, lid) ||
	  send_command("wheels_dir:", 0, lid))
	return (1);
    }
  return (0);
}

int	change_dir(t_info_lidar *lid)
{
  if (lid->turn == 1)
    {
      return (send_command("wheels_dir:", lid->wheels, lid));
    }
  else if (lid->turn == 2)
    {
      return (send_command("wheels_dir:-", lid->wheels, lid));
    }
  return (0);
}

int	try_backwards(t_info_lidar *lid)
{
  if (send_command("wheels_dir:", 0, lid) ||
      send_command("car_backwards:", 0.2, lid) ||
      send_command("cycle_wait:", 30, lid) ||
      send_command("car_forward:", 0, lid))
    return (1);
  return (0);
}

int	manage_close_turn(t_info_lidar *lid)
{
  if (lid->lidar[0] < 400 && lid->turn == 1 && lid->wheels >= 0.1)
    {
      lid->warning = 1;
      return (send_command("wheels_dir:-", 0.1, lid));
    }
  else if (lid->lidar[31] < 400 && lid->turn == 2 && lid->wheels >= 0.1)
    {
      lid->warning = 1;
      return (send_command("wheels_dir:", 0.1, lid));
    }
  return (0);
}

int	start_driving(t_info_lidar *lid)
{
  char	*value;
  char	buff[501];
  int	ret;

  while (lid->additionnal_info != 4)
    {
      write(1, "get_info_lidar\n", 15);
      ret = read(0, buff, 500);
      buff[ret] = 0;
      if (info_lidar(lid, buff) == -1 ||
	  manage_speed(lid) ||
	  manage_dir(lid) ||
	  manage_stabilisation(lid) ||
	  manage_close_turn(lid))
	return (1);
      if (lid->warning == 0 && change_dir(lid))
	return (1);
      lid->warning = 0;
      value = double_to_char(lid->speed);
      if (lid->speed < 0.1 && try_backwards(lid))
	return (1);
    }
  return (0);
}

int	main()
{
  t_info_lidar	lid;

  lid.speed = 0;
  lid.wheels = 0;
  lid.warning = 0;
  lid.turn = 0;
  lid.memory = 0;
  if (init_simulation(&lid))
    return (1);
  if (start_driving(&lid))
    return (1);
  return (0);
}
