/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbendaou <dbendaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/04 19:07:11 by dbendaou          #+#    #+#             */
/*   Updated: 2016/10/05 20:24:35 by dbendaou         ###   ########.fr       */
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
# define E_CMD	"command not found \n"
# define E_usage "USAGE :\n./minishell\n"

/*	ft_env	*/ 
t_env	*ft_env(char **env);
void	classic_append(t_env *to_add, t_env *begin);
t_env	*new_maill(char *name, char *value);
char	*get_logname(t_env *env);

/*	ft_exec	*/
void	ft_exec(t_env *env);

#endif
