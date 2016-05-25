/*
** my_memset.c for memset in /home/semmao_i/rendu/CPE/CPE_2015_n4s/src
** 
** Made by ilyas semmaoui
** Login   <semmao_i@epitech.net>
** 
** Started on  Wed May 25 09:39:32 2016 ilyas semmaoui
** Last update Wed May 25 09:39:52 2016 ilyas semmaoui
*/

int	my_memset(char *str, int size, int c)
{
  int	i;

  i = -1;
  while (++i < size)
    str[i] = c;
  return (0);
}
