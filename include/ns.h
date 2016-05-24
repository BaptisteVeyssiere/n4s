/*
** ns.h for n4s in /home/VEYSSI_B/rendu/C_Prog_Elem/CPE_2015_n4s
**
** Made by Baptiste veyssiere
** Login   <VEYSSI_B@epitech.net>
**
** Started on  Tue May 24 16:34:27 2016 Baptiste veyssiere
** Last update Tue May 24 17:41:40 2016 Baptiste veyssiere
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

#endif /* !NS_H_ */
