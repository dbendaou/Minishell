/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbendaou <dbendaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/04 19:07:11 by dbendaou          #+#    #+#             */
/*   Updated: 2016/10/19 19:05:59 by dbendaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <sys/stat.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include "get_next_line.h"

/*
**********************
*/

# define LEN_BUF	512
# define FIRST		"\033[33mMinishell\nTaper \"exit\" pour quitter.\033[0m\n"

/*
**		Erreurs
*/

# define E_CMD		"minishell: command not found: "
# define E_USAGE	"USAGE: ./minishell\n"

/*
**		Environnement
*/

# define PATH		"/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin"

/*
**		Structure ou est stocke l'environnement
*/
typedef struct		s_env
{
	char			*name;
	char			*value;

	struct s_env	*next;
}					t_env;

/*
**		ft_env
*/

t_env				*ft_env(char **env);
void				classic_append(t_env *to_add, t_env *begin);
t_env				*new_maill(char *name, char *value);
void				lst_del(char *name, t_env **begin);
int					lstlen(t_env *env);

/*
**		ft_exec
*/
void				ft_exec(t_env **env, char **cmd);
int					ft_execmd(char **args, char *mix, int i, char **envclean);
int					ft_compare(char **cmd, t_env **env);
int					executable(char **cmd, t_env **env);
void				ft_prompt(t_env *env, char **cmd);
int					ln_check(char *cmd);

/*
**		get.c
*/

char				*get_path(t_env *env);
char				**get_envclean(t_env *env);
char				*get_logname(t_env *env);
t_env				*get_env(char *name, t_env *begin);

/*
**		env.c
*/
int					my_env(t_env *env);
int					set_env(t_env *env, char **cmd);
int					unset_env(t_env **begin, char **cmd);
t_env				*my_env_i();
int					shlvl_plus(t_env **env);

/*
**		ft_echo.c
*/
int					ft_echo(char **cmd, t_env *env);

/*
**		del.c
*/
void				ft_strdel2(char **as, char **as2);

/*
**		parser.c
*/
int					ln_check(char *cmd);

/*
**********************
*/

#endif
