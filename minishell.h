/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbendaou <dbendaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/04 19:07:11 by dbendaou          #+#    #+#             */
/*   Updated: 2016/10/28 19:55:27 by dbendaou         ###   ########.fr       */
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
**	Defines pour le built-in cd
*/

# define E_PATH 1
# define ME_PATH "cd: no such file or directory: "

# define E_STRING 2
# define ME_STRING "cd: string not in pwd: "

# define E_ARGS 4
# define ME_ARGS "cd: too many arguments\n"

# define E_NO_OPWD 8
# define ME_NO_OPWD "cd: OLDPWD not set\n"

# define E_NO_DIR 16
# define ME_NO_DIR "cd: not a directory: "

# define E_NO_RGT 32
# define ME_NO_RGT "cd: permisson denied: "

# define P_HOME "/Users/dbendaou"
# define OPN_HOME 1

# define OPN_PREV 2

/*
**		Structure ou est stocke l'environnement
*/
typedef struct		s_env
{
	char			*name;
	char			*value;

	struct s_env	*next;
}					t_env;

typedef struct		s_gitan
{
	int				i;
	int				ret;
}					t_gitan;

/*
**		ft_env.c
*/
t_env				*ft_env(char **env);
void				classic_append(t_env *to_add, t_env *begin);
t_env				*new_maill(char *name, char *value);
void				lst_del(char *name, t_env **begin);
int					lstlen(t_env *env);

/*
**		ft_exec.c
*/
void				ft_exec(t_env **env, char **cmd);
int					ft_execmd(char **args, char **mix, int i, char **envclean);
int					ft_compare(char **cmd, t_env **env);
int					executable(char **cmd, t_env **env);
void				ft_prompt(t_env *env, char **cmd);

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
int					set_env(t_env **env, char **cmd);
int					unset_env(t_env **begin, char **cmd);
t_env				*my_env_i();
int					shlvl_plus(t_env **env);

/*
**		ft_echo.c
*/
int					ft_echo(char **cmd, t_env *env);
void				ft_putstr2(char *str);

/*
**		del.c
*/
void				ft_strdel2(char **as, char **as2);
void				list_free(t_env *begin);
void				ft_freestrtab(char ***to_free);
void				ft_exit(t_env *env);
void				ft_clean(char **tab1, char **tab2, char **cmd, char **tmp);

/*
**		parser.c
*/
int					ln_check(char *cmd);
void				ft_exec_err(char **cmd);
t_gitan				*gitan_init(void);
void				line_cleaner(char **line);

/*
**		cd.c
*/
int					cd(char **cmd, t_env *env);

/*
**		cd2.c
*/
int					cd_error(char *path, int errnb);
int					edit_env(t_env *env);

/*
**********************
*/

#endif
