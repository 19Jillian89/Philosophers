/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilnassi <ilnassi@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 01:47:11 by ilnassi           #+#    #+#             */
/*   Updated: 2026/02/03 02:10:35 by ilnassi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int  get_status(t_data *data)
{
    int status;

    pthread_mutex_lock(&data->sim_mutex);
    status = data->sim_running;
    pthread_mutex_unlock(&data->sim_mutex);
    return (status);
}

static long long    philo_last_meal(t_philo * philo)
{
    long long   last;

    pthread_mutex_lock(&philo->time_gnammy_mutex);
    last = philo->last_food_time;
    pthread_mutex_unlock(&philo->time_gnammy_mutex);
    return (last);
}

static void print_death(t_philo *philo)
{
    long long   time;

    pthread_mutex_lock(&philo->data->sim_mutex);
    if (philo->data->sim_running)
    {
        philo->data->someone_died = 1;
        philo->data->sim_running = 0;
    }
    pthread_mutex_unlock(&philo->data->sim_mutex);

    pthread_mutex_lock(&philo->data->print_mutex);
    time = get_time() - philo->data->start_time;
    printf("%lld %d died\n", time, philo->id);
    pthread_mutex_unlock(&philo->data->print_mutex);
}

int check_death(t_philo *philo)
{
    long long   now;
    long long   last;

    if (!get_status(philo->data))
        return (1);
    last = philo_last_meal(philo);
    now = get_time();
    if (now - last > philo->data->time_to_die)
    {
        print_death(philo);
        return (1);
    }
    return (0);
}