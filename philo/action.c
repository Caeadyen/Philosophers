/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 08:25:38 by hrings            #+#    #+#             */
/*   Updated: 2022/06/09 09:40:58 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	eat(t_philosopher *philosophers)
{
	pthread_mutex_lock(philosophers->left_fork);
	print_action(philosophers, FORKTAKEN);
	pthread_mutex_lock(philosophers->right_fork);
	pthread_mutex_lock(philosophers->meal_check);
	print_action(philosophers, FORKTAKEN);
	print_action(philosophers, EATING);
	philosophers->last_meal = timestamp();
	pthread_mutex_unlock(philosophers->meal_check);
	ft_usleep(philosophers->info->time_to_eat);
	pthread_mutex_unlock(philosophers->left_fork);
	pthread_mutex_unlock(philosophers->right_fork);
}

void	eat_num_meal(t_philosopher *philosophers)
{
	pthread_mutex_lock(philosophers->left_fork);
	print_action(philosophers, FORKTAKEN);
	pthread_mutex_lock(philosophers->right_fork);
	pthread_mutex_lock(philosophers->meal_check);
	print_action(philosophers, FORKTAKEN);
	print_action(philosophers, EATING);
	philosophers->last_meal = timestamp();
	philosophers->meals_needed -= 1;
	if (philosophers->meals_needed == 0)
		set_phil_meal(philosophers);
	pthread_mutex_unlock(philosophers->meal_check);
	ft_usleep(philosophers->info->time_to_eat);
	pthread_mutex_unlock(philosophers->left_fork);
	pthread_mutex_unlock(philosophers->right_fork);
}

void	sleeping(t_philosopher *philosophers)
{
	print_action(philosophers, SLEEPING);
	ft_usleep(philosophers->info->time_to_sleep);
}

void	think(t_philosopher *philosophers)
{
	print_action(philosophers, THINKING);
}
