/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgomes-l <tgomes-l@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 12:39:37 by tgomes-l          #+#    #+#             */
/*   Updated: 2023/05/19 17:54:02 by tgomes-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_pwd(void)
{
    char cwd[PATH_MAX];

    // Get the current working directory
    if (getcwd(cwd, PATH_MAX))
    {
        ft_putendl_fd(cwd, 1);  // Print the current working directory
        return (SUCCESS);
    }
    else
    {
        return (ERROR);  // Return error if unable to get the current working directory
    }
}
