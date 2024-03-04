#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>

void	ft_putstr(char *str, int *len)
{
	if (!str)
		str = "(null)";
	while (*str)
		*len += write(1, str++, 1);
}

void	ft_putnbr(long long int nbr, int base, int *len)
{
	char *hex = "0123456789abcdef";

	if (nbr < 0)
	{
		nbr *= -1;
		*len += write(1, "-", 1);
	}
	if (nbr >= base)
		ft_putnbr((nbr / base), base, len);
	*len += write(1, &hex[nbr % base], 1);
}

int ft_printf(const char *format, ... )
{
	int	i = 0;
	int	len = 0;
	va_list	args;

	if (!format)
		return (1);
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%' && ((format[i + 1] == 's') || (format[i + 1] == 'd') || (format[i + 1] == 'x')))
		{
			i++;
			if (format[i] == 's')
				ft_putstr(va_arg(args, char *), &len);
			else if (format[i] == 'd')
				ft_putnbr((long long int)va_arg(args, int), 10, &len);
			else if (format[i] == 'x')
				ft_putnbr((long long int)va_arg(args, unsigned int), 16, &len);
		}
		else
			len += write(1, &format[i], 1);
		i++;
	}
	return (va_end(args), len);
}

int main(void)
{
	char	*str = "Hello";
	int		nbr = 2435345;

	ft_printf("%s\n", str);
	printf("%s\n", str);
	ft_printf("%d\n", nbr);
	printf("%d\n", nbr);
	ft_printf("Hexadecimal for %d is %x\n", nbr, nbr);
	printf("Hexadecimal for %d is %x\n", nbr, nbr);
}
