/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgomes-l <tgomes-l@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 12:39:37 by tgomes-l          #+#    #+#             */
/*   Updated: 2023/05/19 17:49:15 by tgomes-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_env(t_env *env)
{
    // Loop through the environment variables
    while (env && env->next != NULL)
    {
        // Print the value of each environment variable
        ft_putendl(env->value);
        env = env->next;
    }

    // Print the value of the last environment variable (if any)
    if (env)
        ft_putendl(env->value);

    return (SUCCESS);
}