/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlamnaou <hlamnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:51:12 by hlamnaou          #+#    #+#             */
/*   Updated: 2024/01/26 18:38:30 by hlamnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*tokenlast(t_token *lst)
{
	if (!lst || !lst->next)
		return (lst);
	lst = lst->next;
	return (tokenlast(lst));
}

t_token	*tokenfirst(t_token *lst)
{
	if (!lst || !lst->prev)
		return (lst);
	lst = lst->prev;
	return (tokenfirst(lst));
}

t_type	get_type(char *s)
{
	if (ft_strlen(s) == 1)
	{
		if (!ft_strncmp(s, ">", 1))
			return (GREAT);
		if (!ft_strncmp(s, "<", 1))
			return (LESS);
		if (!ft_strncmp(s, "|", 1))
			return (PIPE);
		if (!ft_strncmp(s, ";", 1) || (!ft_strncmp(s, "\\", 1))
			|| (!ft_strncmp(s, "&", 1)))
			return (BADCHAR);
	}
	else if (ft_strlen(s) == 2)
	{
		if (!ft_strncmp(s, ">>", 2))
			return (D_GREAT);
		if (!ft_strncmp(s, "<<", 2))
			return (D_LESS);
		if (!ft_strncmp(s, "||", 2))
			return (D_PIPE);
		if (!ft_strncmp(s, ";;", 2) || (!ft_strncmp(s, "\\\\", 2))
			|| (!ft_strncmp(s, "&&", 2)))
			return (D_BADCHAR);
	}
	return (ARG);
}

t_token	*init_tokens(char *s)
{
	t_token	*token;
	char	**arr;
	int		i;

	arr = ft_split(s, 31);
	i = -1;
	if (!arr)
		return (NULL);
	i = -1;
	token = tokennew(NULL, START);
	while (arr[++i])
		tokenadd_back(&token, tokennew(arr[i], 0));
	tokenadd_back(&token, tokennew(NULL, END));
	give_types(token);
	quote(token);
	free_tab((void **)arr);
	return (token);
}
