/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 10:09:11 by hrings            #+#    #+#             */
/*   Updated: 2022/06/07 10:12:31 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

void	clean_up_phil(t_philosopher *philosophers)
{
	free(philosophers);
}

void	clean_up(t_philo *philo)
{
	int	index;

	if (philo->num_meal_check)
		sem_close(philo->num_meal_check);
	if (philo->writing)
		sem_close(philo->writing);
	if (philo->death_check)
		sem_close(philo->death_check);
	if (philo->forks)
		sem_close(philo->forks);
	if (philo->finished)
		sem_close(philo->finished);
	index = 0;
	if (philo->philosophers)
	{
		while (index < philo->num_philo)
		{
			if (philo->philosophers[index].meal_check)
				sem_close(philo->philosophers[index++].meal_check);
		}
		free(philo->philosophers);
	}
	free(philo);
}
