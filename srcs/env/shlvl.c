/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgomes-l <tgomes-l@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 12:39:37 by tgomes-l          #+#    #+#             */
/*   Updated: 2023/05/19 17:58:04 by tgomes-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
char *copy_values_to_env(char *env, t_env *lst, int *i)
{
    int j;

    if (lst->value != NULL)
    {
        j = 0;
        // Copy the value of lst->value to env
        while (lst->value[j])
        {
            env[*i] = lst->value[j];
            (*i)++;
            j++;
        }
    }

    // Add a newline character if lst->next->next is not NULL
    if (lst->next->next != NULL)
        env[(*i)++] = '\n';

    return (env);
}

static int invalid_lvl(const char *str)
{
    int i;

    i = 0;
    // Check if all characters in str are digits
    while (str[i])
    {
        if (!(str[i] >= '0' && str[i] <= '9'))
            return (1);
        i++;
    }

    return (0);
}

static int get_lvl(const char *str)
{
    int i;
    int sign;
    int num;

    i = 0;
    sign = 1;
    num = 0;
    // Skip leading spaces and newlines
    ft_skip_spacenl(str, &i);

    // Check if the level is invalid
    if (invalid_lvl(str))
        return (0);

    // Check if the level is negative or positive
    if (str[i] == '-')
        sign = -1;
    if (str[i] == '-' || str[i] == '+')
        i++;

    // Convert the level to an integer
    while (str[i] >= '0' && str[i] <= '9')
        num = num * 10 + (str[i++] - '0');

    return (num * sign);
}

void increment_shell_level(t_env *env)
{
    int shell_level;
    char env_name[BUFF_SIZE];
    char *shlvl;
    char *shell_level_value;

    shell_level_value = get_env_value("SHLVL", env);

    // Check if the value of SHLVL is empty
    if (ft_strcmp(shell_level_value, "") == 0)
        return;

    shell_level = get_lvl(shell_level_value) + 1;
    ft_memdel(shell_level_value);

    // Update the value of SHLVL in the environment list
    while (env && env->next)
    {
        get_env_name(env_name, env->value);
        if (ft_strcmp("SHLVL", env_name) == 0)
        {
            ft_memdel(env->value);
            shlvl = ft_itoa(shell_level);
            env->value = ft_strjoin("SHLVL=", shlvl);
            ft_memdel(shlvl);
            return;
        }
        env = env->next;
    }
}