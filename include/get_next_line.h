/*
** get_next_line.h for gnl in /home/semmao_i/rendu/CPE/CPE_2015_n4s/include
** 
** Made by ilyas semmaoui
** Login   <semmao_i@epitech.net>
** 
** Started on  Wed May 25 07:58:59 2016 ilyas semmaoui
** Last update Wed May 25 07:59:04 2016 ilyas semmaoui
*/

#ifndef		_GET_NEXT_LINE_H_
# define	_GET_NEXT_LINE_H_

# ifndef READ_SIZE
#  define READ_SIZE (19)

# endif /* !READ_SIZE */

#include <unistd.h>
#include <stdlib.h>

typedef struct line
{
  char          *buf;
  char          *line;
  int           i;
  int           ret;
  int           key[3];
  int		fg;
  char		e[READ_SIZE + 1];
  int		p;
  int		g;
}ln;

char	*get_next_line(const int fd);
char	*my_realloc(ln *);
char	*line(ln *);
char	*next(ln *, char *, int, const int);
int	my_len(char *);

#endif
