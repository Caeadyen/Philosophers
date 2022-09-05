/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 10:46:50 by hrings            #+#    #+#             */
/*   Updated: 2022/06/07 10:12:35 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

void	error_handler(t_philo *philo, int errrornum)
{
	if (errrornum == INPUTERROR)
	{
		printf("Error on input variables\n");
		free(philo);
		exit(1);
	}
	else if (errrornum == MUTEXERROR)
	{
		printf("Error on mutex\n");
		free(philo);
		exit(1);
	}
	else if (errrornum == THREADERROR)
	{
		printf("Error on thread\n");
		free(philo);
		exit(1);
	}
	else if (errrornum == SEMAERROR)
	{
		printf("Error on Semaphores\n");
		free(philo);
		exit(1);
	}
}
