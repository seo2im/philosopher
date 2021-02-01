#include "philosoper.h"

static char	*semaphore_name(int i)
{
	char	*name;
	char	*id;

	if (!(id = ft_itoa(i)))
		return (NULL);
	name = ft_strdcat("Philo_", id);
	free(id);
	return (name);
}

static int	init_philosoper_list(t_manager *manager)
{
	char	*name;
	t_ph	*list;
	int		i;

	if (!(list = malloc(sizeof(t_ph) * (manager->ph_num + 1))))
		return (ft_error("Init_philosoper : malloc error", ERROR));
	i = -1;
	while (++i < manager->ph_num)
	{
		list[i].id = i;
		list[i].left_fork = i;
		list[i].right_fork = (i + 1) % manager->ph_num;
		list[i].eat_count = 0;
		list[i].is_end = FALSE;
		list[i].manager = manager;
		if (!(name = semaphore_name(i)))
			return (ft_error("Init_philo_list : malloc error", ERROR));
		sem_unlink(name);
		if ((list[i].live = sem_open(name, O_CREAT | O_EXCL, 0644, 1)) < 0)
			return (ft_error("Init_philo_list : open error", ERROR));
	}
	manager->ph_list = list;
	return (SUCCESS);
}

static int	init_semaphore(t_manager *manager)
{
	sem_unlink("FORKS");
	if ((manager->forks = 
		sem_open("FORKS", O_CREAT | O_EXCL, 0644, manager->ph_num)) < 0)
		return (ft_error("Init_semaphore : open error", ERROR));
	sem_unlink("MESSAGE");
	if ((manager->output = 
		sem_open("MESSAGE", O_CREAT | O_EXCL, 0644, 1)) < 0)
		return (ft_error("Init_semaphore : open error", ERROR));
	return (SUCCESS);
}

int 		init_manager(t_manager *manager, char *argv[], int argc)
{
	if ((manager->ph_num = ft_atoi(argv[0])) < 0)
		return (ft_error("Init_manager : argv[0] under 0", ERROR));
	if ((manager->dead_time = ft_atoi(argv[1])) < 0)
		return (ft_error("Init manager : argv[1] under 0", ERROR));
	if ((manager->eat_time = ft_atoi(argv[2])) < 0)
		return (ft_error("Init manager : argv[2] under 0", ERROR));
	if ((manager->sleep_time = ft_atoi(argv[3])) < 0)
		return (ft_error("Init manager : argv[3] under 0", ERROR));
	if (argc == 6)
	{
		if ((manager->must_eat_num = ft_atoi(argv[4])) < 0)
			return (ft_error("Init_manager : argv[4] under 0", ERROR));
	}
	else
		manager->must_eat_num = 0;
	manager->end_count = 0;
	manager->forks = NULL;
	manager->ph_list = NULL;
	if (init_philosoper_list(manager) == ERROR)
		return (ft_error("Init_manager : philosoper init error", ERROR));
	if (init_semaphore(manager) == ERROR)
		return (ft_error("Init_manager : mutex init error", ERROR));
	return (SUCCESS);
}

int		clear(t_manager *manager)
{
	char	*name;
	int		i;

	sem_unlink("FORKS");
	if (manager->ph_list)
	{
		i = -1;
		while (++i < manager->ph_num)
		{
			if (!(name = semaphore_name(i)))
				return (ft_error("Clear : malloc error", ERROR));
			sem_unlink(name);
			free(name);
		}
		free(manager->ph_list);
	}
	sem_unlink("MESSAGE");
	return (SUCCESS);
}