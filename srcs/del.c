/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbendaou <dbendaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 13:24:32 by dbendaou          #+#    #+#             */
/*   Updated: 2016/10/28 19:07:52 by dbendaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Merci la norme
*/

void	ft_strdel2(char **as, char **as2)
{
	if (as)
	{
		free(*as);
		*as = NULL;
	}
	if (as2)
	{
		free(*as2);
		*as2 = NULL;
	}
}

/*
**	Free une liste
*/

void	list_free(t_env *begin)
{
	t_env	*tmp;
	t_env	*next;

	tmp = begin;
	if (!tmp)
		return ;
	while (tmp)
	{
		next = tmp->next;
		ft_strdel(&tmp->name);
		ft_strdel(&tmp->value);
		free(tmp);
		tmp = next;
	}
	tmp = NULL;
}

/*
**	Free un tableau
*/

void	ft_freestrtab(char ***to_free)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = *to_free;
	while (tmp[i])
	{
		ft_strdel(&tmp[i]);
		i++;
	}
	free(tmp);
	tmp = NULL;
	*to_free = NULL;
	return ;
}

/*
**	Free bien tous au moment d'exit
*/

void	ft_exit(t_env *env)
{
	list_free(env);
	ft_putstr("\033[33mGood bye ...\033[0m\n");
	exit(1);
}

/*
**	Merci la norme pt.2 \0/
*/

void	ft_clean(char **tab1, char **tab2, char **cmd, char **tmp)
{
	if (tab1[0] != NULL)
		ft_freestrtab(&tab1);
	if (tab2[0] != NULL)
		ft_freestrtab(&tab2);
	if (cmd != NULL)
		ft_strdel(cmd);
	if (tmp != NULL)
		ft_strdel(tmp);
}
