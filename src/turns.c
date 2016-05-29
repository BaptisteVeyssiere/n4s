/*
** turns.c for ns in /home/scutar_n/rendu/CPE/CPE_2015_n4s/src
**
** Made by nathan scutari
** Login   <scutar_n@epitech.net>
**
** Started on  Sun May 29 16:44:07 2016 nathan scutari
** Last update Sun May 29 16:47:35 2016 nathan scutari
*/

#include "ns.h"

static int		turn_left(t_info_lidar *lid)
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

static int		turn_right(t_info_lidar *lid)
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

static void	change_memory(t_info_lidar *lid, double distancel, double distancer)
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

static int	select_memory(t_info_lidar *lid, double distancel, double distancer)
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
