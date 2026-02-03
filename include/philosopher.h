/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilnassi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 14:28:32 by ilnassi           #+#    #+#             */
/*   Updated: 2025/11/04 15:47:20 by ilnassi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <unistd.h> //usleep
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h> //gettimeoftheday

typedef struct s_data
{
    int             num_philos;         // Numero di filosofi
    long long       time_to_die;        // Tempo massimo prima che un filosofo muoia
    long long       time_to_eat;        // Tempo che impiega a mangiare
    long long       time_to_sleep;      // Tempo che impiega a dormire
    long long       start_time;         // Tempo di inizio della simulazione
    int         someone_died;       // Flag per sapere se qualcuno è morto
    int			sim_running;

    pthread_mutex_t print_mutex;        // Protegge le stampe su schermo
    pthread_mutex_t *forks;             // Array di mutex (uno per ogni forchetta)
    pthread_mutex_t sim_mutex;
}   t_data;

typedef struct s_philo
{
    int             id;                // Numero del filosofo
    int             food_eaten;       // Quante volte ha mangiato
    long long          last_food_time;    // Tempo dell'ultimo pasto
    pthread_t       thread_id;         // ID del thread
    pthread_mutex_t *left_fork;        // Puntatore al mutex della forchetta sinistra
    pthread_mutex_t *right_fork;       // Puntatore al mutex della forchetta destra
    pthread_mutex_t gnammy_mutex;
    pthread_mutex_t time_gnammy_mutex;
    struct s_data   *data;             // Puntatore alla struct generale
}   t_philo;


void	think(t_philo *philo);
void    eat(t_philo *philo);
void    sleep_philo(t_philo *philo);

long long   get_time(void);
int check_death(t_philo *philo);
int sim_is_running(t_data *data);
void    take_forks(t_philo *philo);
void    drop_forks(t_philo *philo);


#endif