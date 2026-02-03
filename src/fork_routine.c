/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_routine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilnassi <ilnassi@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 02:21:25 by ilnassi           #+#    #+#             */
/*   Updated: 2026/02/03 03:18:01 by ilnassi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int sim_is_running(t_data *data)
{
    int i;

	pthread_mutex_lock(&data->sim_mutex);
	i = data->sim_running;
	pthread_mutex_unlock(&data->sim_mutex);
	return (i);
}

static void lock_first(t_philo *philo)
{
    if (philo->id % 2 == 0)
        pthread_mutex_lock(philo->right_fork);
    else
        pthread_mutex_lock(philo->left_fork);
    print_plan(philo, "has taken a fork");
}

static void lock_second(t_philo *philo)
{
    if (philo->id % 2 == 0)
        pthread_mutex_lock(philo->left_fork);
    else
        pthread_mutex_lock(philo->right_fork);
    print_plan(philo, "has taken a fork");
}

void    take_forks(t_philo *philo)
{
    if (!sim_is_running(philo->data))
        return ;
    lock_first(philo);
    if (philo->data->num_philos == 1)
        return ;
    lock_second(philo);
}

void    drop_forks(t_philo *philo)
{
    if (philo->data->num_philos == 1)
    {
        pthread_mutex_unlock(philo->left_fork);
        return ;
    }
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
}