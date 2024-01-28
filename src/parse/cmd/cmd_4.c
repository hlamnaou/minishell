/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlamnaou <hlamnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:49:46 by hlamnaou          #+#    #+#             */
/*   Updated: 2024/01/26 18:43:44 by hlamnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_append_redirection(t_cmd *cmd, t_redir *redir)
{
	t_redir	*current;

	if (!cmd->file)
	{
		cmd->file = redir;
		return ;
	}
	current = cmd->file;
	while (current->next)
		current = current->next;
	current->next = redir;
	redir->prev = current;
}

void	ft_assign_redirection_types(t_cmd *cmd)
{
	t_token	*t;

	while (cmd)
	{
		t = cmd->token;
		ft_redirect(t, cmd);
		cmd = cmd->next;
	}
}

t_redir	*ft_newredirection(char *file, t_type_redir type)
{
	t_redir	*new_redir;

	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return (NULL);
	new_redir->file = ft_strdup(file);
	new_redir->type = type;
	new_redir->fd = -1;
	new_redir->next = NULL;
	new_redir->prev = NULL;
	return (new_redir);
}

void	ft_redirect(t_token *t, t_cmd *cmd)
{
	t_redir	*new_redir;
	t_type	type;

	while (t->next)
	{
		if (t->content)
		{
			type = get_type(t->content);
			new_redir = ft_newredirection(t->next->content, 0);
			if (type == GREAT)
				new_redir->type = R_GREAT;
			else if (type == D_GREAT)
				new_redir->type = RD_GREAT;
			else if (type == LESS)
				new_redir->type = R_LESS;
			else if (type == D_LESS)
				new_redir->type = RD_LESS;
			ft_append_redirection(cmd, new_redir);
		}
		t = t->next;
	}
}
