/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsudo <rsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 10:43:21 by rsudo             #+#    #+#             */
/*   Updated: 2021/11/25 10:27:35 by rsudo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <stdbool.h>
# include <string.h>
# include <limits.h>
# include <assert.h>
# include <errno.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				nb;
	int				left_fork;
	int				right_fork;
	int				cnt_eat;
	pthread_t		thread;
	pthread_t		death_thread;
	unsigned long	time_last_eat;
	struct s_info	*info;
}	t_philo;

typedef struct s_info
{
	int				nb_philo;
	unsigned long	time_die;
	int				time_eat;
	int				time_sleep;
	int				times_must_eat;
	bool			end_flag;
	pthread_mutex_t	*fork;
	pthread_mutex_t	mu_time;
	pthread_mutex_t	mu_died;
	t_philo			*philo;
}	t_info;

int				ft_atoi(const char *str, bool *err);
void			ft_putstr_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
bool			philo_init(char **argv, t_info *info);
unsigned long	get_ms_timestamp(void);
int				philo_eat(t_philo *philo);
void			philo_sleep(t_philo *philo);
void			philo_die(t_philo *philo);
void			philo_think(t_philo *philo);
unsigned long	put_act(t_philo *philo, char *msg);
void			divide_sleep(unsigned long ms);

#endif
