/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moguy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 02:28:25 by moguy             #+#    #+#             */
/*   Updated: 2020/02/26 08:42:53 by moguy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		deal_key_release(int key, void *env)
{
	((t_env*)env)->key[key] = false;
	return (0);
}

int		deal_key_press(int key, void *env)
{
	((t_env*)env)->key[key] = true;
	return (0);
}

int		deal_loop(void *env)
{
	t_env	*e;

	e = (t_env*)env;
	key_action(e, e->key);
	return (0);
}
