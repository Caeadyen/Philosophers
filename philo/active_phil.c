/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   active_phil.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 09:52:15 by hrings            #+#    #+#             */
/*   Updated: 2022/06/09 09:25:31 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	run_normal(t_philosopher *philosophers);
static void	run_eaten(t_philosopher *philosophers);

void	*active_phil(void *argv)
{
	t_philosopher	*philosophers;
	pthread_t		thread;

	philosophers = (t_philosopher *)argv;
	if (philosophers->num % 2 == 1)
		usleep(STARTDELAY);
	if (pthread_create(&thread, NULL, check_philo_status, philosophers))
		error_handler(philosophers->info, THREADERROR);
	if (philosophers->meals_needed > 0)
		run_eaten(philosophers);
	else
		run_normal(philosophers);
	pthread_join(thread, NULL);
	return (NULL);
}

static void	run_eaten(t_philosopher *philosophers)
{
	while (not_done(philosophers->info))
	{
		eat_num_meal(philosophers);
		sleeping(philosophers);
		think(philosophers);
	}
}

static void	run_normal(t_philosopher *philosophers)
{
	while (not_done(philosophers->info))
	{
		eat(philosophers);
		sleeping(philosophers);
		think(philosophers);
	}
}
