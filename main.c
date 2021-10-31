#include "philo.h"
#include <pthread.h>
#include <stdio.h>

unsigned long	get_ms_timestamp(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);//
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	*philo_routine(void *philo)
{
	t_info	*info;

	info = ((t_philo*)philo)->info;
	if (((t_philo*)philo)->nb % 2)
	{
		usleep(100);
	}
	while (1)
	{
		if (info->end_flag == true)
			break ;
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

void	*observe_philo_dead(void *philo_ptr)
{
	t_philo	*philo;
	t_info	*info;

	philo = philo_ptr;
	info = philo->info;
	while (info->end_flag == false)
	{
		pthread_mutex_lock(&(info->death_check));
		if (get_ms_timestamp() - philo->time_last_eat > info->time_die)
		{
			philo_die(philo);
			info->end_flag = true;
		}
		pthread_mutex_unlock(&(info->death_check));
	}
	return (NULL);
}

void	start_dining(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->nb_philo)
	{
		pthread_create(&(info->philo[i].thread), NULL, philo_routine, &info->philo[i]);
		pthread_create(&(info->philo[i].death_thread), NULL, observe_philo_dead, &info->philo[i]);
		i++;
	}
}

void	join_thread(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->nb_philo)
	{
		pthread_join(info->philo[i].thread, NULL);
		pthread_join(info->philo[i].death_thread, NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (argc < 5 || argc > 6)
	{
		ft_putstr_fd("invalid argument\n", STDERR_FILENO);
		return (1);
	}
	if (philo_init(argv, &info))
	{
		ft_putstr_fd("error\n", STDERR_FILENO);
		return (1);
	}
	start_dining(&info);
	join_thread(&info);
	return (0);
}
