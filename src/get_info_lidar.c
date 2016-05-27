/*
** get_info_lidar.c for n4s in /home/VEYSSI_B/rendu/C_Prog_Elem/CPE_2015_n4s
**
** Made by Baptiste veyssiere
** Login   <VEYSSI_B@epitech.net>
**
** Started on  Tue May 24 18:01:46 2016 Baptiste veyssiere
** Last update Tue May 24 18:07:50 2016 Baptiste veyssiere
*/

#include "ns.h"

int	get_info_lidar(t_info_lidar *lidar)
{
  char	*buf;

  if (!(buf = get_next_line(0)))
    return (-1);
  free(buf);
  return (0);
}
