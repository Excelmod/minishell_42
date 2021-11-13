/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tokenizer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljulien <ljulien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 17:41:03 by ljulien           #+#    #+#             */
/*   Updated: 2021/10/29 23:48:24 by ljulien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*parsing_tokenizer(t_shell *shell, char *line)
{
	int	error;

	shell->str = line;
	error = tokenizer(shell, line);
	error = check_syntax_error(shell, error);
	if (!error)
		parsing(shell);
	free(line);
	shell->str = NULL;
	ft_tokenclear(&(shell->tokens));
	return (NULL);
}
