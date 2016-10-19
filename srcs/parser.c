/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbendaou <dbendaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 03:46:34 by dbendaou          #+#    #+#             */
/*   Updated: 2016/10/19 19:07:47 by dbendaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Return -1 si cmd contient que espace ou tab
*/

int			ln_check(char *cmd)
{
	int		i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] != ' ')
		{
			if (cmd[i] != '\t')
				return (0);
		}
		i++;
	}
	return (-1);
}
