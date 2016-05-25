/*
** ns.h for n4s in /home/VEYSSI_B/rendu/C_Prog_Elem/CPE_2015_n4s
**
** Made by Baptiste veyssiere
** Login   <VEYSSI_B@epitech.net>
**
** Started on  Tue May 24 16:34:27 2016 Baptiste veyssiere
** Last update Wed May 25 17:02:15 2016 ilyas semmaoui
*/

#ifndef NS_H_
# define NS_H_

typedef struct	s_info_lidar
{
  char		check_fail;
  char		additionnal_info;
  double	lidar[32];
}		t_info_lidar;

typedef struct	s_instruction_return
{
  char		check_fail;
  char		additionnal_info;
}		t_instruction_return;


/*
** info_lidar.c
*/
static int	take_info_lidar(t_info_lidar *, char *);
int		info_lidar(t_info_lidar *, char *);

/*
** verif_command.c
*/
int		verif_command_one(char *);
int		verif_command_two(char *);
int		verif_command_three(char *);
int		verif_command_four(char *);

/*
** my_memset.c
*/
int		my_memset(char *, int, int);

/*
** my_getdouble.c
*/
void		my_getd(const char *, double *);
void		get_db(const char *, double, double *);
int		multd(const char *, double *, int);

#endif /* !NS_H_ */
