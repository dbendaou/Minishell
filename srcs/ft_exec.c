/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbendaou <dbendaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/05 18:50:38 by dbendaou          #+#    #+#             */
/*   Updated: 2016/10/05 20:50:07 by dbendaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec(t_env *env)
{
	char	**cmd = NULL;

	while (1)
	{
		ft_putstr(get_logname(env));
		get_next_line(0, cmd);
		ft_putstr("\033[0m");

	}
}