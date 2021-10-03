/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 21:36:11 by ljulien           #+#    #+#             */
/*   Updated: 2021/10/03 23:55:47 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     ft_strcmp_sep(char *s1, char *s2, char sep)
{
    size_t	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] != sep && s2[i] != sep)
	{
		if (s1[i] != s2[i])
            return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
		i++;
	}
    if (s1[i] == sep && s1[i] != s2[i])
            return (-(unsigned char)(s2[i]));
    else if (s2[i] == sep && s1[i] != s2[i])
            return ((unsigned char)(s1[i]));
    else
	    return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
}

char    *smallest_export(t_shell *shell, char **str, char *min)
{
    int i;

    i = 0;
    *str = NULL;
    while(shell->env && shell->env[i])
    {
        if (ft_strcmp_sep(min, shell->env[i], '=') < 0)
            if (*str == 0 || ft_strcmp_sep(*str, shell->env[i], '=') > 0)
                *str = shell->env[i];
        i++;
    }
    i = 0;
    while(shell->exp && shell->exp[i])
    {
        if (ft_strcmp_sep(min, shell->exp[i], '=') < 0)
            if (*str == 0 || ft_strcmp_sep(*str, shell->exp[i], '=') > 0)
                *str = shell->exp[i];
        i++;
    }
    return (*str);
}

void    print_format_export(char *str)
{
    int i;

    i = 0;
    while (str[i] && str[i] != '=')
        i++;
    ft_putstr_fd("export ", 1);
    write(1, str, i);
    if (str[i] == '=')
    {
        ft_putstr_fd("=\"", 1);
        ft_putstr_fd(str + i + 1, 1);
        ft_putstr_fd("\"", 1);
    }
    write(1, "\n", 1);
}

void    print_export(t_shell *shell)
{
    char    *min;
    char    zero;
    char    *str;
    
    zero = 0;
    min = &zero;
    str = NULL;
    while(smallest_export(shell, &str, min))
    {
        min = str;
        print_format_export(str);
    }
}