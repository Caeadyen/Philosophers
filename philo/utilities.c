/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 10:33:12 by hrings            #+#    #+#             */
/*   Updated: 2022/07/28 09:16:14 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	ft_atoi_phil(const char *str, t_philo *philo)
{
	long int	result;

	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	result = 0;
	if (*str < '0' || *str > '9')
		philo->error = 1;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
		if (result > INT_MAX)
			philo->error = 1;
	}
	if ((*str < '0' || *str > '9') && *str)
		philo->error = 1;
	if (result == 0)
		philo->error = 1;
	return ((int) result);
}

void	set_phil_meal(t_philosopher *philosophers)
{
	pthread_mutex_lock(philosophers->info->meal_check);
	philosophers->info->philo_eaten += 1;
	pthread_mutex_unlock(philosophers->info->meal_check);
}

void	run_eat_checker(t_philo *philo)
{
	pthread_t		thread;	

	if (pthread_create(&thread, NULL, check_philo_status_eaten, philo))
		error_handler(philo, THREADERROR);
	pthread_join(thread, NULL);
}

void	ft_usleep(long time)
{
	long	start;

	start = timestamp();
	while ((timestamp() - start) < time)
		usleep(SLEEPTIMER);
}
