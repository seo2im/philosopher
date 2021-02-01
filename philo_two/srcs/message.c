#include "philosoper.h"

static int	print_state(t_ph *philosoper, int time)
{
	char	*time_msg;
	char	*id;
	
	if (!(time_msg = ft_itoa(time)))
		return (ft_error("Print_time : malloc error", ERROR));
	ft_write(time_msg);
	ft_write(" : ");
	free(time_msg);
	if (!(id = ft_itoa(philosoper->id)))
		return (ft_error("Print_time : malloc error", ERROR));
	ft_write("Philosoper ");
	ft_write(id);
	free(id);
	return (SUCCESS);
}

int			message(t_ph *philosoper, int kind)
{
	sem_wait(philosoper->manager->output);
	if ((print_state(philosoper, 
			ft_gettime() - philosoper->manager->start_time)) == ERROR)
		return (ft_error("Print_time : malloc error", ERROR));
	if (kind == EAT)
		ft_writen(" is eating");
	else if (kind == FORK)
		ft_writen(" take forks");
	else if (kind == THINK)
		ft_writen(" is thinking");
	else if (kind == SLEEP)
		ft_writen(" is sleeping");
	else if (kind == DEAD)
		ft_writen(" is Dead");
	else if (kind == END)
		ft_writen(" is Finished");
	sem_post(philosoper->manager->output);
	return (SUCCESS);
}