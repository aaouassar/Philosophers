/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaouassa <aaouassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 00:27:04 by aaouassa          #+#    #+#             */
/*   Updated: 2023/04/17 01:36:10 by aaouassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "Philosophers.h"

void	ft_thinking(t_philos *philos)
{
	pthread_mutex_lock(&(philos->msg));
	printf("%lld %d is thinking\n", gettimeofnow(philos), philos->id + 1);
	pthread_mutex_unlock(&(philos->msg));
}

void	ft_sleeping(t_philos *philos)
{
	pthread_mutex_lock(&(philos->msg));
	printf("%lld %d is sleeping\n", gettimeofnow(philos), philos->id + 1);
	pthread_mutex_unlock(&(philos->msg));
	ft_usleeping(philos, philos->philo_info->time_to_sleep);
}

void	ft_eating(t_philos *philos)
{
	pthread_mutex_lock(&philos->forks[philos->id]);
	printstatus(philos, "has taken a fork\n");
	if (philos->id + 1 == philos->philo_info->number_of_philosophers)
		pthread_mutex_lock(&philos->forks[0]);
	else
		pthread_mutex_lock(&philos->forks[philos->id + 1]);
	printstatus(philos, "has taken a fork\n");
	pthread_mutex_lock(&(philos->checker));
	philos->last_meal = ft_gettime();
	philos->nb_time_eat++;
	pthread_mutex_unlock(&(philos->checker));
	printstatus(philos, "is eating\n");
	ft_usleeping(philos, philos->philo_info->time_to_eat);
	pthread_mutex_unlock(&philos->forks[philos->id]);
	if (philos->id + 1 == philos->philo_info->number_of_philosophers)
		pthread_mutex_unlock(&philos->forks[0]);
	else
		pthread_mutex_unlock(&philos->forks[philos->id + 1]);
}

void	*threadstatus(void *arg)
{
	t_philos	*philos;

	philos = (t_philos *)arg;
	while (1)
	{
		ft_eating(philos);
		ft_sleeping(philos);
		ft_thinking(philos);
	}
}

void	ft_creatthreads(t_philos *philos, t_philo_info *philo_info)
{
	int	i;

	i = 0;
	while (i < philo_info->number_of_philosophers)
	{
		if (pthread_create(&philos[i].threads[i], NULL, &threadstatus,
				&philos[i]))
		{
			printf("error in thread creation\n");
			return ;
		}
		usleep(50);
		i++;
	}
}
