/*
** get_next_line.c for gnl in /home/semmao_i/rendu/CPE/CPE_2015_n4s/src
** 
** Made by ilyas semmaoui
** Login   <semmao_i@epitech.net>
** 
** Started on  Wed May 25 07:59:23 2016 ilyas semmaoui
** Last update Wed May 25 07:59:24 2016 ilyas semmaoui
*/

#include "get_next_line.h"

int	my_len(char *str)
{
  int	i;

  i = -1;
  while (str[++i] != '\0');
  return (i);
}

char	*my_realloc(ln *nx)
{
  nx->buf = malloc(my_len(nx->line) + 1);
  nx->buf[0] = 0;
  while (nx->line[nx->i] != '\0')
    {
      nx->buf[nx->i] = nx->line[nx->i];
      nx->i++;
    }
  nx->buf[nx->i] = '\0';
  free(nx->line);
  if ((nx->ret = read(nx->fg, nx->e, READ_SIZE)) == -1)
    {
      free(nx->buf);
      return (NULL);
    }
  nx->i = 0;
  nx->line = malloc(my_len(nx->buf) + nx->ret + 1);
  nx->line[0] = 0;
  while (nx->buf[nx->i] != '\0')
    {
      nx->line[nx->i] = nx->buf[nx->i];
      nx->i++;
    }
  nx->line[nx->i] = '\0';
  free(nx->buf);
  return (nx->line);
}

char	*line(ln *nx)
{
  while ((nx->i = 0) == 0 && (nx->key[1] += 1) != -2)
    {
      if ((my_realloc(nx)) == NULL)
	return (NULL);
      while (nx->e[nx->p] != '\0' && nx->e[nx->p] != '\n')
        nx->line[nx->i++] = nx->e[nx->p++];
      if ((nx->line[nx->i] = 0) == 0 && nx->e[nx->p++] == '\n')
	return (nx->line);
      else if ((nx->p = 0) == 0)
        while (nx->e[nx->p] != '\0')
          nx->e[nx->p++] = 0;
      if ((nx->p = 0) == 0 && nx->ret == 0 &&
	  (nx->key[0] == 1 || nx->key[1] > 0) && (nx->i = 0) == 0)
        {
          while (nx->e[nx->i] != '\0' && (nx->p = 0) == 0)
            nx->e[nx->i++] = 0;
          return (nx->line);
        }
      else if (nx->ret == 0)
	{
	  free(nx->line);
	  return (NULL);
	}
    }
  return (NULL);
}

char	*next(ln *nx, char *eos, int pos, const int fd)
{
  nx->fg = fd;
  if ((nx->g = -1) == -1 && (nx->key[0] = 0) == 0 && (nx->key[1] = -1) == -1
      && (nx->line = malloc((my_len(eos) + 1))) == NULL)
    return (NULL);
  nx->line[0] = 0;
  while (++nx->g < READ_SIZE + 1)
    nx->e[nx->g] = eos[nx->g];
  nx->p = pos;
  if ((nx->ret = 0) == 0 && (nx->i = 0) == 0 &&
      nx->p > 0 && (nx->key[0] = 1) == 1)
    {
      while (nx->e[nx->p] != '\0' && nx->e[nx->p] != '\n')
        nx->line[nx->i++] = nx->e[nx->p++];
      nx->line[nx->i] = '\0';
      if ((nx->i = 0) == 0 && nx->e[++nx->p - 1] == '\n')
        return (nx->line);
      else if ((nx->p = 0) == 0)
        while (nx->i < READ_SIZE)
          nx->e[nx->i++] = 0;
      if (nx->line[0] == 0)
	nx->key[0] = 0;
    }
  return (line(nx));
}

char	*get_next_line(const int fd)
{
  static char	eos[READ_SIZE + 1] = {0};
  static int	pos = 0;
  static int	file_desc = 0;
  ln		nx;

  if (file_desc != fd && (file_desc = fd) == fd && (nx.g = -1) == -1
      && (pos = 0) == 0)
    while (++nx.g < READ_SIZE + 1)
      eos[nx.g] = 0;
  if ((nx.key[2] = 0) == 0 && (next(&nx, eos, pos, fd)) == NULL)
    nx.key[2] = -1;
  nx.g = -1;
  while (++nx.g < READ_SIZE + 1)
    eos[nx.g] = nx.e[nx.g];
  pos = nx.p;
  if (nx.key[2] == -1)
    return (NULL);
  else
    return (nx.line);
}
