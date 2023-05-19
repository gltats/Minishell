/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgomes-l <tgomes-l@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 12:39:37 by tgomes-l          #+#    #+#             */
/*   Updated: 2023/05/19 17:47:31 by tgomes-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *get_env_path(t_env *env, const char *var, size_t len)
{
    int i;
    int j;
    char *oldpwd;

    // Loop through the environment variables
    while (env && env->next != NULL)
    {
        // Check if the current variable matches the given var
        if (ft_strncmp(env->value, var, len) == 0)
        {
            // Check the value of the "oldpwd" variable
            oldpwd = oldpwd_checker(env, len);
            if (oldpwd == NULL)
                return (NULL);
            
            i = 0;
            j = 0;
            // Copy the remaining characters of the variable's value after the given var into "oldpwd"
            while (env->value[i++])
            {
                if (i > (int)len)
                    oldpwd[j++] = env->value[i];
            }
            oldpwd[j] = '\0';
            return (oldpwd);
        }
        env = env->next;
    }
    return (NULL);
}

static int update_oldpwd(t_env *env)
{
    char cwd[PATH_MAX];
    char *oldpwd;

    // Get the current working directory
    if (getcwd(cwd, PATH_MAX) == NULL)
        return (ERROR);

    // Create a string "oldpwd" in the format "OLDPWD=current_working_directory"
    oldpwd = ft_strjoin("OLDPWD=", cwd);
    if (!oldpwd)
        return (ERROR);

    // Check if "oldpwd" is already present in the environment, if not, add it
    if (is_in_env(env, oldpwd) == 0)
        env_add(oldpwd, env);
    
    ft_memdel(oldpwd);
    return (SUCCESS);
}

static int go_to_path(int option, t_env *env)
{
    int ret;
    char *env_path;

    env_path = NULL;

    if (option == 0)
    {
        // Update the "oldpwd" variable
        update_oldpwd(env);

        // Get the value of the "HOME" variable from the environment
        env_path = get_env_path(env, "HOME", 4);
        if (!env_path)
            ft_putendl_fd("minishell: cd: HOME not set", STDERR);
        if (!env_path)
            return (ERROR);
    }
    else if (option == 1)
    {
        // Get the value of the "OLDPWD" variable from the environment
        env_path = get_env_path(env, "OLDPWD", 6);
        if (!env_path)
            ft_putendl_fd("minishell: cd: OLDPWD not set", STDERR);
        if (!env_path)
            return (ERROR);

        // Update the "oldpwd" variable
        update_oldpwd(env);
    }

    // Change the current directory to the specified path
    ret = chdir(env_path);
    ft_memdel(env_path);
    return (ret);
}

int ft_cd(char **args, t_env *env)
{
    int cd_ret;

    // Check if no argument is provided, then go to the "HOME" directory
    if (!args[1])
        return (go_to_path(0, env));

    // Check if the argument is "-", then go to the "OLDPWD" directory
    if (ft_strcmp(args[1], "-") == 0)
        cd_ret = go_to_path(1, env);
    else
    {
        // Update the "oldpwd" variable
        update_oldpwd(env);

        // Change the current directory to the specified path
        cd_ret = chdir(args[1]);
        if (cd_ret < 0)
            cd_ret *= -1;
        if (cd_ret != 0)
            print_error_cd(args);
    }
    return (cd_ret);
}
