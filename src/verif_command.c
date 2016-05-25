/*
** verif_command.c for verif_command in /home/semmao_i/rendu/CPE/CPE_2015_n4s/src
**
** Made by ilyas semmaoui
** Login   <semmao_i@epitech.net>
**
** Started on  Wed May 25 09:40:30 2016 ilyas semmaoui
** Last update Wed May 25 21:03:08 2016 ilyas semmaoui
*/

#include "ns.h"

int	verif_command_one(t_info_lidar *lidar, char *str)
{
  int	i;
  char	buff[] = "1:OK:No errors so far:";

  if (strnmatch(str, "Track Cleared") == 1)
    lidar->additionnal_info = 4;
  else
    lidar->additionnal_info = 0;
  i = -1;
  while (str && str[++i] && buff[i])
    if (str[i] != buff[i])
      return (-1);
  if (str[i] == '\0')
    return (-1);
  return (0);
}

int	verif_command_two(t_info_lidar *lidar, char *str)
{
  int	i;
  int	count;
  char	buff[] = "1:OK:No errors so far:";

  if ((i = -1) == -1 && strnmatch(str, "Track Cleared") == 1)
    lidar->additionnal_info = 4;
  else
    lidar->additionnal_info = 0;
  count = 0;
  while (str && str[++i] && buff[i])
    if (str[i] != buff[i])
      return (-1);
  if (str[i] == '\0')
    return (-1);
  while (str && str[i] && count < 32)
    {
      if (str[i] == ':')
        ++count;
      if ((str[i] < 48 || str[i] > 58) && str[i] != '.')
        return (-1);
      ++i;
    }
  if (count != 32 || str[i] == '\0')
    return (-1);
  return (0);
}

int	verif_command_three(t_info_lidar *lidar, char *str)
{
  int	i;
  char	buff[] = "1:OK:No errors so far:";

  if (strnmatch(str, "Track Cleared") == 1)
    lidar->additionnal_info = 4;
  else
    lidar->additionnal_info = 0;
  i = -1;
  while (str && str[++i] && buff[i])
    if (str[i] != buff[i])
      return (-1);
  if (str[i] == '\0')
    return (-1);
  --i;
  while (str && str[++i] && str[i] != ':')
    if ((str[i] < 48 || str[i] > 58) && str[i] != '.')
      return (-1);
  if (str[i] == '\0')
    return (-1);
  return (0);
}

int	verif_command_four(t_info_lidar *lidar, char *str)
{
  int	i;
  char	buff[] = "1:OK:No errors so far:";

  if (strnmatch(str, "Track Cleared") == 1)
    lidar->additionnal_info = 4;
  else
    lidar->additionnal_info = 0;
  i = -1;
  while (str && str[++i] && buff[i])
    if (str[i] != buff[i])
      return (-1);
  if (str[i] == '\0')
    return (-1);
  --i;
  while (str && str[++i] && str[i] != ':')
    if ((str[i] < 48 || str[i] > 58) && str[i] != '[' &&
        str[i] != ']' && str[i] != 's' && str[i] != 'n')
      return (-1);
  if (str[i] == '\0')
    return (-1);
  return (0);
}
