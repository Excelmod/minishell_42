/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 23:16:41 by ljulien           #+#    #+#             */
/*   Updated: 2021/10/06 17:19:29 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    ft_cutstr(char *str, char sep, int i)
{
    char    *tmp;
    int     cnt;

    cnt = 0;
    str = str + i;
    tmp = str + 1;
    while (i && *str != sep)
    {
       i--;
       str--;
    }
    while(tmp[cnt])
        cnt++;
    ft_memmove(str, tmp, cnt + 1);
    return(i);
}

char    *change_pwd(t_shell *shell, char *path)
{
    char    **tab;
    int     i;

    tab = malloc(sizeof(char *) * 3);
    tab[0] = ft_strdup("export");
    tab[2] = NULL;
    i = 0;
    while(path[i])
    {
        if (path[i] == '.' && (path[i - 1] == '/' || i == 0) && (!path[i + 1] || ft_isset("/.", path[i + 1])))
        {
            i = ft_cutstr(path, '/', i);
            if (path[i] == '.')
               i = ft_cutstr(path, '/', i);
            if (*path == 0)
            {
                path[0] = '/';
                path[1] = 0;
                i = 1;
            }
        }
        else if (path[i] == '/' && ((path[i + 1] == 0 && i) || path[i + 1] == '/'))
            ft_memmove(path + i, path + i + 1, ft_strlen(path + i + 1) + 1);
        else
            i++;
    }
    tab[1] = ft_strjoin("OLDPWD=",shell->pwd);
    builtin_export(shell, tab);
    free(tab[1]);
    free(shell->pwd);
    shell->pwd = path;
    tab[1] = ft_strjoin("PWD=",path);
    builtin_export(shell, tab);
    ft_freetabs(tab);
    return(path);
}

int     builtin_cd(t_shell *shell, char **arg)
{
    char    *path;
    char    *tmp;

    if (arg && arg[1])
    {
        if (arg[1][0] == '/')
            path = arg[1];
        else
        {
            if(shell->pwd[0] == '/' && !(shell->pwd[1]))
                tmp = ft_strdup(shell->pwd);
            else
                tmp = ft_strjoin(shell->pwd , "/");
            path = ft_strjoin(tmp, arg[1]);
            free(tmp);
        }
        if (chdir(path))
        {
            ft_putstr_fd("bash: cd: ", 2);
            perror(arg[1]);
            free(path);
            return(errno);
        }
        else
        {
            path = change_pwd(shell, path);
            shell->pwd = path;
            printf("%s\n", shell->pwd);
            return(0);
        }
        printf("%s\n", shell->pwd);
    }
    return (0);
}