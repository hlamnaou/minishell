/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbazart <gabriel.bazart@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 18:03:39 by gbazart           #+#    #+#             */
/*   Updated: 2024/01/28 01:12:58 by gbazart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief exec for pipe.
 *
 * @param data (t_data *) data
 */
static void	exec_pipe(t_cmd *cmd, t_data *data)
{
	int	code;

	if (!cmd->argv[0])
	{
		free_and_close(data);
		return ;
	}
	if (is_builtin(cmd->argv[0]) == true)
	{
		code = builtin(cmd, data, 0);
		free_and_close(data);
		exit(code);
	}
	else
		exec_cmd(data, cmd);
	exit(0);
}

/**
 * @brief wait for all children.
 *
 * @param cmd (t_cmd *)
 */
static void	wait_for_children(t_cmd *cmd)
{
	int	status;

	signal(SIGINT, SIG_IGN);
	while (cmd)
	{
		waitpid(cmd->pid, &status, 0);
		g_exit_code = WEXITSTATUS(status);
		cmd = cmd->next;
	}
	signal(SIGINT, sig_handler);
}

/**
 * @brief funciton that execute the child of the pipe.
 *
 * @param cmd (t_cmd *)
 * @param data (t_data *)
 * @return (int) 1 if it works, 0 if don't.
 */
static void	child(t_cmd *cmd, t_data *data)
{
	if (cmd_open(cmd) == -1)
	{
		g_exit_code = 1;
		return ;
	}
	cmd->pid = fork();
	if (cmd->pid < 0)
	{
		perror("fork failed ");
		g_exit_code = 1;
	}
	else if (cmd->pid == 0)
	{
		signal(SIGQUIT, sigquit_handler);
		if (cmd->fd[0][0] > 0)
			dup2(cmd->fd[0][0], STDIN_FILENO);
		else if (cmd->prev)
			dup2(cmd->prev->fd[1][0], STDIN_FILENO);
		if (cmd->fd[0][1] > 1)
			dup2(cmd->fd[0][1], STDOUT_FILENO);
		else
			dup2(cmd->fd[1][1], STDOUT_FILENO);
		ft_close_fd(data->cmd);
		exec_pipe(cmd, data);
	}
}

/**
 * @brief funciton the last command of the pipe.
 *
 * @param cmd (t_cmd *)
 * @param data (t_data *)
 * @return (int) 1 if it works, 0 if don't.
 */
static void	end_pipe(t_cmd *cmd, t_data *data)
{
	if (cmd_open(cmd) == -1)
	{
		g_exit_code = 1;
		return ;
	}
	cmd->pid = fork();
	if (cmd->pid < 0)
	{
		perror("fork failed ");
		g_exit_code = 1;
	}
	else if (cmd->pid == 0)
	{
		signal(SIGQUIT, sigquit_handler);
		if (cmd->fd[0][0] > 0)
			dup2(cmd->fd[0][0], STDIN_FILENO);
		else
			dup2(cmd->prev->fd[1][0], STDIN_FILENO);
		if (cmd->fd[0][1] > 1)
			dup2(cmd->fd[0][1], STDOUT_FILENO);
		ft_close_fd(data->cmd);
		exec_pipe(cmd, data);
		exit(0);
	}
}

/**
 * @brief funciton that execute the pipe.
 *
 * @param cmd (t_cmd *)
 * @param data (t_data *)
 * @return (int) 1 if it works, 0 if don't.
 */
int	execute_pipe(t_cmd *cmd, t_data *data)
{
	t_cmd	*cmd2;

	cmd2 = data->cmd;
	while (cmd2)
	{
		if (pipe(cmd2->fd[1]) == -1)
		{
			perror("pipe failed");
			ft_close_fd(data->cmd);
			g_exit_code = 1;
			return (-1);
		}
		cmd2 = cmd2->next;
	}
	while (cmd->next)
	{
		child(cmd, data);
		cmd = cmd->next;
	}
	end_pipe(cmd, data);
	ft_close_fd(data->cmd);
	wait_for_children(data->cmd);
	return (1);
}
