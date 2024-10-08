/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bince < bince@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 13:03:41 by mel-yand          #+#    #+#             */
/*   Updated: 2024/09/27 11:54:07 by bince            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

void	ft_cd(t_data *data, char **arg);
void	ft_echo(t_data *data, char **arg);
void	ft_env(t_data *data, t_list *env, char **cmd);
void	ft_export(t_data *data, char **arg);
void	export_no_args(t_list *env);
int		print_error_export(t_data *data, char *varname);
int		valid_name(t_data *data, char *arg);
void	ft_pwd(t_data *data, char **arg);
void	ft_unset(t_data *data, char **arg);
void	ft_exit(t_data *data, char **arg);
int		only_digit(char *arg);
int		is_too_big(char *cmd);
#endif
