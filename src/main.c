/*
** main.c for n4s in /home/VEYSSI_B/rendu/C_Prog_Elem/CPE_2015_n4s
**
** Made by Baptiste veyssiere
** Login   <VEYSSI_B@epitech.net>
**
** Started on  Tue May 24 16:35:01 2016 Baptiste veyssiere
** Last update Sun May 29 16:49:41 2016 nathan scutari
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "ns.h"

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
  speed = distance * 0.8 / 2000;
  if (distance < 200)
    speed = 0;
  if (speed < 0)
    speed = 0;
  else if (speed > 0.8)
    speed = 0.8;
  if (speed > 0.4 && lid->wheels > 0)
    speed = 0.4;
  if (speed != lid->speed)
    {
      lid->speed = speed;
      return (send_command("car_forward:", speed, lid));
    }
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

int	start_driving(t_info_lidar *lid)
{
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
      if (lid->speed < 0.1 && (ret = try_backwards(lid)) == 1)
	return (1);
      else if (ret == 2)
	return (stop_sim());
    }
  if (stop_sim())
    return (1);
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
  lid.try = 0;
  if (init_simulation(&lid))
    return (1);
  if (start_driving(&lid))
    return (1);
  return (0);
}
