/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgomes-l <tgomes-l@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 19:43:26 by tgomes-l          #+#    #+#             */
/*   Updated: 2023/05/19 18:00:19 by tgomes-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void sig_int(int code)
{
    (void)code;

    // Handle SIGINT signal

    if (g_sig.pid == 0)
    {
        // If no child process is running
        ft_putstr_fd("\b\b  ", STDERR);  // Clear the current line
        ft_putstr_fd("\n", STDERR);  // Move to a new line
        ft_putstr_fd("\033[0;36m\033[1m🤬 minishell ▸ \033[0m", STDERR);  // Print the shell prompt
        g_sig.exit_status = 1;  // Set the exit status to 1
    }
    else
    {
        // If a child process is running
        ft_putstr_fd("\n", STDERR);  // Move to a new line
        g_sig.exit_status = 130;  // Set the exit status to 130
    }
    g_sig.sigint = 1;  // Set the sigint flag to indicate the SIGINT signal was received
}

void sig_quit(int code)
{
    char *nbr;

    nbr = ft_itoa(code);

    if (g_sig.pid != 0)
    {
        // If a child process is running
        ft_putstr_fd("Quit: ", STDERR);  // Print "Quit: "
        ft_putendl_fd(nbr, STDERR);  // Print the signal number
        g_sig.exit_status = 131;  // Set the exit status to 131
        g_sig.sigquit = 1;  // Set the sigquit flag to indicate the SIGQUIT signal was received
    }
    else
    {
        // If no child process is running
        ft_putstr_fd("\b\b  \b\b", STDERR);  // Erase the "^\" characters
    }
    ft_memdel(nbr);  // Free the memory allocated for the signal number
}

void sig_init(void)
{
    // Initialize the signal-related variables

    g_sig.sigint = 0;  // Initialize sigint flag to 0
    g_sig.sigquit = 0;  // Initialize sigquit flag to 0
    g_sig.pid = 0;  // Initialize pid to 0
    g_sig.exit_status = 0;  // Initialize exit_status to 0
}
