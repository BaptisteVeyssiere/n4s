/*
** ns.h for n4s in /home/VEYSSI_B/rendu/C_Prog_Elem/CPE_2015_n4s
**
** Made by Baptiste veyssiere
** Login   <VEYSSI_B@epitech.net>
**
** Started on  Tue May 24 16:34:27 2016 Baptiste veyssiere
** Last update Sun May 29 16:51:36 2016 nathan scutari
*/

#ifndef NS_H_
# define NS_H_

typedef struct	s_info_lidar
{
  char		try;
  char		check_fail;
  char		additionnal_info;
  double	speed;
  double	wheels;
  double	olda;
  double	oldb;
  int		memory;
  int		warning;
  int		turn;
  double	lidar[32];
}		t_info_lidar;

/*
** info_lidar.c
*/
int	info_lidar(t_info_lidar *, char *);
int	take_info_lidar(t_info_lidar *, char *);

/*
** turns.c
*/
int	manage_dir(t_info_lidar *);


/*
** commands.c
*/
int	stop_sim();
int	send_command(char *, double, t_info_lidar *);
int	init_simulation(t_info_lidar *);

/*
** tools.c
*/
int	my_strlen(char *);
int	strnmatch(char *, char *);

/*
** dtc.c
*/
char	*double_to_char(double);

/*
** my_memset.c
*/
int	my_memset(char *, int, int);

/*
** verif_command.c
*/
int		verif_command_one(t_info_lidar *, char *);
int		verif_command_two(t_info_lidar *, char *);
int		verif_command_three(t_info_lidar *, char *);
int		verif_command_four(t_info_lidar *, char *);

/*
** my_getdouble.c
*/
void		my_getd(const char *, double *);
void		get_db(const char *, double, double *);
int		multd(const char *, double *, int);

/*
** close_act.c
*/
int	try_backwards(t_info_lidar *);
int	manage_close_turn(t_info_lidar *);

#endif /* !NS_H_ */
