/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_status.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilnassi <ilnassi@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 17:45:13 by ilnassi           #+#    #+#             */
/*   Updated: 2026/02/01 18:27:38 by ilnassi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

long long   get_time(void)
{
    struct timeval  clock_time;

    gettimeofday(&clock_time, NULL);
    return (clock_time.tv_sec * 1000 + clock_time.tv_usec / 1000);
}

void    print_plan(t_philo *philo, char *plan)
{
    long long   time;
    int         ok;

    pthread_mutex_lock(&philo->data->print_mutex);
    pthread_mutex_lock(&philo->data->sim_mutex);
    ok = (philo->data->sim_running && !philo->data->someone_died);
    pthread_mutex_unlock(&philo->data->sim_mutex);
    time = get_time() - philo->data->start_time;
    if (!philo->data->someone_died)
        printf("%lld %d %s\n", time, philo->id, plan); //stampa: tempo  id  messaggio
    pthread_mutex_unlock(&philo->data->print_mutex);
}
