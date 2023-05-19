/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgomes-l <tgomes-l@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 12:39:37 by tgomes-l          #+#    #+#             */
/*   Updated: 2023/05/19 17:53:01 by tgomes-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int env_add(const char *value, t_env *env)
{
    t_env *new;
    t_env *tmp;

    // Check if the environment is empty
    if (env && env->value == NULL)
    {
        env->value = ft_strdup(value);
        return (SUCCESS);
    }

    new = malloc(sizeof(t_env));
    if (!new)
        return (-1);
    new->value = ft_strdup(value);

    // Find the last node in the environment list
    while (env && env->next && env->next->next)
        env = env->next;

    tmp = env->next;
    env->next = new;
    new->next = tmp;

    return (SUCCESS);
}

char *get_env_name(char *dest, const char *src)
{
    int i;

    i = 0;
    // Copy characters from src to dest until '=' is encountered or the length exceeds BUFF_SIZE
    while (src[i] && src[i] != '=' && ft_strlen(src) < BUFF_SIZE)
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return (dest);
}

int is_in_env(t_env *env, char *args)
{
    char var_name[BUFF_SIZE];
    char env_name[BUFF_SIZE];

    // Extract the environment variable name from args
    get_env_name(var_name, args);

    // Search for the variable name in the environment list
    while (env && env->next)
    {
        // Extract the environment variable name from env->value
        get_env_name(env_name, env->value);

        // Check if the variable names match
        if (ft_strcmp(var_name, env_name) == 0)
        {
            ft_memdel(env->value);
            env->value = ft_strdup(args);
            return (1);
        }
        env = env->next;
    }

    return (SUCCESS);
}

int ft_export(char **args, t_env *env, t_env *secret)
{
    // Check if no arguments are provided, then print the sorted environment
    if (!args[1])
    {
        print_sorted_env(secret);
        return (SUCCESS);
    }
    else
    {
        return (ft_export_checker(args, env, secret));
    }
}
