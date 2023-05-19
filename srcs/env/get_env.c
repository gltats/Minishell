/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgomes-l <tgomes-l@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 12:39:37 by tgomes-l          #+#    #+#             */
/*   Updated: 2023/05/19 17:56:45 by tgomes-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int is_env_char(int c)
{
    // Check if the character is alphanumeric or underscore
    if (ft_isalnum(c) == 1 || c == '_')
        return (1);
    return (0);
}

int is_valid_env(const char *env)
{
    int i;

    i = 0;
    // Check if the first character is a digit
    if (ft_isdigit(env[i]) == 1)
        return (0);

    // Check if the characters until '=' are alphanumeric
    while (env[i] && env[i] != '=')
    {
        if (ft_isalnum(env[i]) == 0)
            return (-1);
        i++;
    }

    // Check if '=' character is present
    if (env[i] != '=')
        return (2);

    return (1);
}

int env_value_len(const char *env)
{
    int i;
    int size_name;

    size_name = 0;
    i = 0;
    // Find the position after '=' character
    while (env[i] && env[i] != '=')
        i++;
    i += 1;
    // Calculate the length of the value
    while (env[i])
    {
        i++;
        size_name++;
    }
    return (size_name);
}

char *env_value(char *env)
{
    int i;
    int j;
    int size_alloc;
    char *env_value;

    size_alloc = env_value_len(env) + 1;
    env_value = malloc(sizeof(char) * size_alloc);
    if (!env_value)
        return (NULL);
    i = 0;
    // Find the position after '=' character
    while (env[i] && env[i] != '=')
        i++;
    i += 1;
    j = 0;
    // Copy the value from env to env_value
    while (env[i])
        env_value[j++] = env[i++];
    env_value[j] = '\0';
    return (env_value);
}

char *get_env_value(char *arg, t_env *env)
{
    char env_name[BUFF_SIZE];
    char *env_val;

    env_val = ft_strdup("");

    // Traverse the environment list to find the matching variable and get its value
    while (env && env->value)
    {
        get_env_name(env_name, env->value);
        if (ft_strcmp(arg, env_name) == 0)
        {
            ft_memdel(env_val);
            env_val = env_value(env->value);
            return (env_val);
        }
        env = env->next;
    }
    return (env_val);
}
