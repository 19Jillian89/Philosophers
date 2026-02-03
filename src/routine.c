/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilnassi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 15:18:08 by ilnassi           #+#    #+#             */
/*   Updated: 2026/02/03 02:10:02 by ilnassi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	think(t_philo *philo)
{
	int	plan;

	pthread_mutex_lock(&philo->data->sim_mutex);
	plan = philo->data->sim_running;
    pthread_mutex_unlock(&philo->data->sim_mutex);
	if (!plan)
		return ;
    print_plan(philo, "is thinking");
}

void    eat(t_philo *philo)
{
    int gnam;

    pthread_mutex_lock(&philo->data->sim_mutex);
    gnam = philo->data->sim_running;
    pthread_mutex_unlock(&philo->data->sim_mutex);
    if (!gnam)
        return ;
    pthread_mutex_lock(&philo->gnammy_mutex);
    print_plan(philo, "is eating");
    philo->food_eaten++;
    pthread_mutex_unlock(&philo->gnammy_mutex);
    pthread_mutex_lock(&philo->time_gnammy_mutex);
    philo->last_food_time = get_time();
    pthread_mutex_unlock(&philo->time_gnammy_mutex);
    usleep(philo->data->time_to_eat * 1000);
}

static void	sleep_step(long long end)
{
	long long	now;
	long long	remain;

	now = get_time();
	if (now >= end)
		return ;
	remain = end - now;
	if (remain > 10)
		usleep(10 * 1000);
	else
		usleep(remain * 1000);
}

void	sleep_philo(t_philo *philo)
{
	long long	end;

	if (!sim_is_running(philo->data))
    	return;
	print_plan(philo, "is sleeping");
	end = get_time() + philo->data->time_to_sleep;
	while (get_time() < end)
	{
		if (check_death(philo))
			return ;
		sleep_step(end);
	}
}