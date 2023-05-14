/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaouassa <aaouassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 13:18:05 by aaouassa          #+#    #+#             */
/*   Updated: 2023/04/17 01:34:45 by aaouassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "Philosophers.h"

int	init_info(int argc, char **argv, t_philo_info *philos)
{
	philos->number_of_philosophers = ft_atoi(argv[1]);
	philos->time_to_die = ft_atoi(argv[2]);
	philos->time_to_eat = ft_atoi(argv[3]);
	philos->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philos->number_must_eat = ft_atoi(argv[5]);
	else
		philos->number_must_eat = -1;
	if (philos->number_of_philosophers <= 0 || philos->time_to_die <= 0
		|| philos->time_to_eat <= 0 || philos->time_to_sleep <= 0)
		return (-1);
	if (argc == 6 && philos->number_must_eat <= 0)
		return (-1);
	return (1);
}

int	ft_checkdeath(t_philos *philos)
{
	long long	time;
	long long	last;
	int			i;

	i = -1;
	pthread_mutex_lock(&(philos->checker));
	time = ft_gettime();
	last = philos->last_meal;
	if (time - last > philos->philo_info->time_to_die)
	{
		pthread_mutex_lock(&(philos->msg));
		printf("%lld %d %s", gettimeofnow(philos), philos->id + 1, "died\n");
		return (1);
	}
	pthread_mutex_unlock(&(philos->checker));
	return (0);
}

int	ft_checkstatus(t_philos *philos)
{
	int	i;

	i = -1;
	while (++i < philos->philo_info->number_of_philosophers)
	{
		if (ft_checkdeath(&philos[i]) != 0)
			return (1);
	}
	i = 0;
	if (philos->philo_info->number_must_eat != -1)
	{
		while (i < philos->philo_info->number_of_philosophers
			&& philos[i].nb_time_eat >= philos->philo_info->number_must_eat)
			i++;
		if (i == philos->philo_info->number_of_philosophers)
			return (1);
	}
	return (-1);
}

int	main(int ac, char **av)
{
	t_philos		*philos;
	t_philo_info	*philo_info;
	pthread_mutex_t	*forks;

	philo_info = malloc(sizeof(t_philo_info));
	if (!philo_info)
		return (ft_mallocfailed());
	if (ac < 5 || ac > 6 || init_info(ac, av, philo_info) == -1)
	{
		printf("Error\n");
		free(philo_info);
		return (1);
	}
	forks = creatforks(philo_info);
	if (!forks)
		return (ft_mallocfailed());
	philos = creatphilos(philo_info, forks);
	if (!philos)
		return (ft_mallocfailed());
	ft_creatthreads(philos, philo_info);
	while (1)
	{
		if (ft_checkstatus(philos) == 1)
			break ;
	}
}
