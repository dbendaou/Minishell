/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbendaou <dbendaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 13:24:32 by dbendaou          #+#    #+#             */
/*   Updated: 2016/10/23 17:51:48 by dbendaou         ###   ########.fr       */
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

void		list_free(t_env *begin)
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
