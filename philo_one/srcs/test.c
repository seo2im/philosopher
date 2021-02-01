#include "philo_one.h"

void print_info(t_manager *manager)
{
	printf("ph_num : %d\n", manager->ph_num);
	printf("eat : %d\n", manager->must_eat_num);
	int i = -1;
	while (++i < manager->ph_num)
	{
		printf("ph id : %d\n", manager->ph_list[i].id);
		printf("ph lfork : %d\n", manager->ph_list[i].left_fork);
		printf("ph rfork : %d\n", manager->ph_list[i].right_fork);
		
	}
}