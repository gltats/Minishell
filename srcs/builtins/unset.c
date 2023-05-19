/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgomes-l <tgomes-l@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 12:39:37 by tgomes-l          #+#    #+#             */
/*   Updated: 2023/05/19 17:55:09 by tgomes-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t env_size(char *env)
{
    size_t i;

    i = 0;
    // Calculate the size of the environment variable until the '=' character
    while (env[i] && env[i] != '=')
        i++;
    return (i);
}

static void free_node(t_mini *mini, t_env *env)
{
    if (mini->env == env && env->next == NULL)
    {
        ft_memdel(mini->env->value);
        mini->env->value = NULL;
        mini->env->next = NULL;
        return;
    }
    ft_memdel(env->value);
    ft_memdel(env);
}

static int ft_unset_helper(char **a, t_mini *mini)
{
    t_env *env;

    env = mini->env;

    // Check if the first environment variable matches the given argument
    if (ft_strncmp(a[1], env->value, env_size(env->value)) == 0)
    {
        if (env->next)
        {
            mini->env = env->next;
        }
        free_node(mini, env);
        return (1);
    }

    return (0);
}

int ft_unset(char **a, t_mini *mini)
{
    t_env *env;
    t_env *tmp;

    env = mini->env;

    // Check if no arguments are provided
    if (!(a[1]))
        return (SUCCESS);

    if (ft_unset_helper(a, mini))
        return (SUCCESS);

    // Traverse the environment list to find the matching variable and remove it
    while (env && env->next)
    {
        if (ft_strncmp(a[1], env->next->value, env_size(env->next->value)) == 0)
        {
            tmp = env->next->next;
            free_node(mini, env->next);
            env->next = tmp;
            return (SUCCESS);
        }
        env = env->next;
    }

    return (SUCCESS);
}