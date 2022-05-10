#include <unistd.h>
#include <signal.h>
#include "../ft_printf/includes/ft_printf.h"

static void	handleSigs(int sig, siginfo_t *info, void *data)
{
	static int	i;
	int			bit;
	static int	c;

	(void)data;
	if (sig == SIGUSR2)
		bit = 0;
	else
		bit = 1;
	c += (bit << i);
	i ++;
	if (i == 8)
	{
		write(1, &c, 1);
		if (c == '\0')
		{
			write(1, "\n", 1);
			kill(info->si_pid, SIGUSR1);
		}
		i = 0;
		c = 0;
	}
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	sa;

	sa.sa_sigaction = handleSigs;
	sa.sa_flags = SA_SIGINFO;
	pid = getpid();
	ft_putstr_fd("Talk to me!\n", 1);
	ft_putstr_fd("Server PID: ", 1);
	ft_putnbr_fd(pid, 1);
	ft_putchar_fd('\n', 1);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}