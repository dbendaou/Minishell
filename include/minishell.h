/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbendaou <dbendaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/04 19:07:11 by dbendaou          #+#    #+#             */
/*   Updated: 2016/10/13 05:02:48 by dbendaou         ###   ########.fr       */
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

typedef struct		s_env
{
	char			*name;
	char			*value;

	struct s_env	*next;
}					t_env;

# define LEN_BUF	512
# define FIRST	"\033[33mMinishell\nTaper \"exit\" pour quitter.\033[0m\n"
# define E_CMD	": command not found \n"
# define E_usage "USAGE :\n./minishell\n"

/*	ft_env	*/ 
t_env	*ft_env(char **env);
void	classic_append(t_env *to_add, t_env *begin);
t_env	*new_maill(char *name, char *value);
void 	lst_del(char *name, t_env **begin);
int		lstlen(t_env *env);

/*	ft_exec	*/
void	ft_exec(t_env **env,char **cmd);
int		ft_execmd(char **args, char *mix, int i, char **envclean);
int		ft_compare(char **cmd, t_env **env);
void	ft_prompt(t_env *env, char **cmd);

/*	get.c	*/
char	*get_path(t_env *env);
char	**get_envclean(t_env *env);
char	*get_logname(t_env *env);
char 	*get_pwd(t_env *env);

/*	ft_signal.c	*/
void	ft_signal();

/*	env.c 	*/
void	my_env(t_env *env);
void 	set_env(t_env *env, char **cmd);
void	unset_env(t_env **begin, char **cmd);


/* 	ft_echo.c */
void	ft_echo(char **cmd, t_env *env);

#endif
