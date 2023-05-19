/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgomes-l <tgomes-l@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 12:39:37 by tgomes-l          #+#    #+#             */
/*   Updated: 2023/05/19 17:48:23 by tgomes-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int nb_args(char **args)
{
    int size;

    size = 0;
    // Count the number of arguments by iterating through the array until a NULL pointer is encountered
    while (args[size])
        size++;
    return (size);
}

int ft_echo(char **args)
{
    int i;
    int n_option;

    i = 1;
    n_option = 0;

    // Check if there are more than one arguments
    if (nb_args(args) > 1)
    {
        // Loop through the arguments and check if they are "-n" options
        while (args[i] && ft_strcmp(args[i], "-n") == 0)
        {
            n_option = 1;
            i++;
        }

        // Print the arguments to the standard output
        while (args[i])
        {
            ft_putstr_fd(args[i], 1);
            // Add a space after each argument, except the last one
            if (args[i + 1] && args[i][0] != '\0')
                write(1, " ", 1);
            i++;
        }
    }

    // If the "-n" option was not provided, add a newline character to the output
    if (n_option == 0)
        write(1, "\n", 1);

    return (SUCCESS);
}
