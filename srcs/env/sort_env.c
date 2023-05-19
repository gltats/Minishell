/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgomes-l <tgomes-l@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 17:03:04 by tgomes-l          #+#    #+#             */
/*   Updated: 2023/05/19 17:59:11 by tgomes-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int str_env_len(char **env)
{
    int i;

    i = 0;
    // Calculate the length of the env array
    while (env[i])
        i++;
    return (i);
}

void sort_env(char **tab, int env_len)
{
    int ordered;
    int i;
    char *tmp;

    ordered = 0;
    // Perform bubble sort until the array is ordered
    while (tab && ordered == 0)
    {
        ordered = 1;
        i = 0;
        while (i < env_len - 1)
        {
            if (ft_strcmp(tab[i], tab[i + 1]) > 0)
            {
                // Swap elements if they are out of order
                tmp = tab[i];
                tab[i] = tab[i + 1];
                tab[i + 1] = tmp;
                ordered = 0;
            }
            i++;
        }
        env_len--;
    }
}

void print_sorted_env(t_env *env)
{
    int i;
    char **tab;
    char *str_env;

    // Convert the environment list to a string
    str_env = env_to_str(env);

    // Split the string into an array of strings
    tab = ft_split(str_env, '\n');
    ft_memdel(str_env);

    // Sort the array of strings
    sort_env(tab, str_env_len(tab));

    i = 0;
    // Print each sorted environment variable
    while (tab[i])
    {
        ft_putstr("declare -x ");
        ft_putendl(tab[i]);
        i++;
    }

    // Free the memory allocated for the array
    free_tab(tab);
}
