/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 10:33:12 by hrings            #+#    #+#             */
/*   Updated: 2022/07/28 09:16:48 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

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

void	start_threads(t_philo *philo)
{
	int			index;
	pthread_t	thread_finished;
	pthread_t	thread_eaten;

	if (philo->num_must_eat > 0)
	{
		pthread_create(&thread_finished, NULL, finished_eaten, philo);
		pthread_create(&thread_eaten, NULL, philo_eaten, philo);
	}
	else
		pthread_create(&thread_finished, NULL, finished, philo);
	index = 0;
	while (index < philo->num_philo)
		waitpid(philo->philosophers[index++].id, NULL, WUNTRACED);
	pthread_join(thread_finished, NULL);
	if (philo->num_must_eat > 0)
		pthread_join(thread_eaten, NULL);
}

void	ft_usleep(long time)
{
	long	start;

	start = timestamp();
	while ((timestamp() - start) < time)
		usleep(SLEEPTIMER);
}
