/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohel-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 21:13:37 by mohel-mo          #+#    #+#             */
/*   Updated: 2025/08/30 21:13:38 by mohel-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

void					parsing(void);
void					args_count_error(void);
void					ft_bzero(void *s, size_t len);

typedef struct s_philo	t_philo;
typedef struct s_data	t_data;
typedef struct s_fork	t_fork;
typedef pthread_mutex_t	t_mutex;

typedef enum s_type
{
	EVEN,
	ODD
}						t_type;

typedef struct s_philo
{
	long				id;
	pthread_t			thread_id;
	t_data				*data;
	t_fork				*right_fork;
	t_fork				*left_fork;
	t_mutex				mutex_full;
	t_mutex				mutex_ate;
	t_mutex				mutex_last_meal;
	long				last_meal_time;
	bool				full;
	bool				ate;
	long				cycles;
}						t_philo;

typedef struct s_fork
{
	int					id;
	t_mutex				mutex;
	bool				taken;
}						t_fork;

typedef struct s_data
{
	int					philos_count;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				cycle_count;
	t_fork				*forks;
	t_philo				*philos;
	pthread_t			monitor;
	t_type				turn;
	bool				death;
	bool				monitor_ready;
	t_mutex				mutex_monitor_ready;
	t_mutex				mutex_death;
	t_mutex				mutex_eaters;
	t_mutex				mutex_turn;
	t_mutex				mutex_print;
	t_mutex				mutex_full;
	long				start_time;
	long				eaters;
}						t_data;

void					init_data(t_data data);
int						parse_args(int argc, char **argv, t_data *data);
long					get_timestamp(void);
void					ft_usleep(long ms);
void					*philo_routine(void *arg);
int						init_extra_data(t_data *data);
void					*ft_calloc(int size);
void					clean_data(t_data *data);
bool					start_dinner(t_data *data);
;
void					*monitor_routine(void *arg);
void					init_evens_turn(t_data *data);
void					declare_creation(t_data *data);
long					get_time_ms(void);
void					switch_turn(t_data *data);
long					get_current_time(t_data *data);
bool					start_cycle(t_philo *philo);
bool					check_death(t_data *data);
bool					take_forks(t_philo *philo);
void					ft_printf(char *s, long philo_id, t_data *data);
void					release_forks(t_philo *philo);
int						ft_atoi(const char *str);

#endif
