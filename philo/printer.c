/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 11:23:15 by hrings            #+#    #+#             */
/*   Updated: 2022/06/07 09:42:46 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	print_action(t_philosopher *philosophers, char *msg)
{	
	pthread_mutex_lock(philosophers->info->writing);
	if (not_done(philosophers->info))
	{
		printf("%li %i %s\n", timestamp() - philosophers->info->start_time, \
		philosophers->num, msg);
	}
	pthread_mutex_unlock(philosophers->info->writing);
}

void	print_dead(t_philosopher *philosophers)
{	
	pthread_mutex_lock(philosophers->info->writing);
	printf("%li %i %s\n", timestamp() - philosophers->info->start_time, \
	philosophers->num, "died");
	pthread_mutex_unlock(philosophers->info->writing);
}
