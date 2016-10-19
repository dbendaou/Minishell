/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbendaou <dbendaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 13:24:32 by dbendaou          #+#    #+#             */
/*   Updated: 2016/10/13 21:24:59 by dbendaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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