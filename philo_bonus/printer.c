/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 11:23:15 by hrings            #+#    #+#             */
/*   Updated: 2022/06/07 10:12:45 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

void	print_action(t_philosopher *philosophers, char *msg)
{	
	sem_wait(philosophers->info->writing);
	printf("%li %i %s\n", timestamp() - philosophers->info->start_time, \
	philosophers->num, msg);
	sem_post(philosophers->info->writing);
}

void	print_dead(t_philosopher *philosophers)
{	
	sem_wait(philosophers->info->writing);
	printf("%li %i %s\n", timestamp() - philosophers->info->start_time, \
	philosophers->num, "died");
}
