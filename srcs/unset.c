/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 20:40:35 by ljulien           #+#    #+#             */
/*   Updated: 2021/10/06 16:27:36 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**delete_env(char **ap, char *str)
{
	int i;
    int j;
	char **new;

	i = 0;
    j = 0;
	while (ap && ap[i] != NULL)
		i++;
	new = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (ap && ap[i] != NULL)
	{
        if (ft_strcmp_sep(ap[i], str, '='))
		    new[i - j] = ap[i];
        else
        {
            free(ap[i]);
            j++;
        }
		i++;
    }
    free(ap);
	new[i - j] = NULL;
	return (new);
}

int builtin_unset(t_shell *shell, char **args)
{
    int i;

    i = 1;
    if(args && args[1])
    {
        while(args[i])
        {
            if (search_env(shell->env, args[i]) == NULL)
            {
                if (search_env(shell->exp, args[i]) != NULL)
                    shell->exp = delete_env(shell->exp, args[i]);
            }
            else
            {
                shell->env = delete_env(shell->env, args[i]);
            }
                i++;
        }
    }
    return(0);
}