/*
** close_act.c for ns in /home/scutar_n/rendu/CPE/CPE_2015_n4s/src
**
** Made by nathan scutari
** Login   <scutar_n@epitech.net>
**
** Started on  Sun May 29 16:49:19 2016 nathan scutari
** Last update Sun May 29 16:51:37 2016 nathan scutari
*/

#include "ns.h"

int	try_backwards(t_info_lidar *lid)
{
  (lid->try)++;
  if (lid->try > 2)
    return (2);
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
