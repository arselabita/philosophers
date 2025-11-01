
#include "../include/philo.h"

long getmillisec()
{
	struct timeval tv;
	if (gettimeofday(&tv, NULL) == -1)
		return (perror("Failed to give time of day.\n"), ERR_GET_TIME);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
	// Convering seconds to milliseconds and microseconds too
}
long calc_time(t_data *data)
{
	return (getmillisec() - data->start_time);
}