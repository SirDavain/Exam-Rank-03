#include "get_next_line.h"

int	ft_strlen(char *str)
{
	int i = 0;

	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr(char *str, int c)
{
	while (*str) 
	{
		if (*str == (char)c)
			return ((char *)str);
		str++;
	}
	return (NULL);
}

int	ft_strlcpy(char *dest, char *src, int dest_size)
{
	int i = 0;
	int src_size = ft_strlen(src);

	if (dest_size > 0)
	{
		while ((i < src_size) && (i < dest_size - 1))
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (src_size);
}

char	*ft_strdup(char *str)
{
	char	*dup;
	int		len;

	len = ft_strlen(str) + 1;
	dup = malloc(len * sizeof(char));
	if (!dup)
		return (NULL);
	ft_strlcpy(dup, str, len);
	return (dup);
}

char	*ft_strjoin(char *s1, char *s2, int len)
{
	int		s1_len;
	int		s2_len;
	char	*joined;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = len;
	joined = (char *)malloc((s1_len + s2_len + 1) * sizeof(char));
	if (!joined)
		return (NULL);
	ft_strlcpy(joined, s1, s1_len + 1);
	ft_strlcpy((joined + s1_len), s2, s2_len + 1);
	free(s1);
	return (joined);
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	char		*line;
	char		*newline;
	int			count;
	int			to_copy;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = ft_strdup(buf);
	while (!(ft_strchr(line, '\n')) && (count = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[count] = '\0';
		line = ft_strjoin(line, buf, count);
	}
	if (ft_strlen(line) == 0)
		return (free(line), NULL);
	newline = ft_strchr(line, '\n');
	if (newline)
	{
		to_copy = newline - line + 1;
		ft_strlcpy(buf, newline + 1, BUFFER_SIZE + 1);
	}
	else
	{
		to_copy = ft_strlen(line);
		ft_strlcpy(buf, "", BUFFER_SIZE + 1);
	}
	line[to_copy] = '\0';
	return (line);
}

int main(void)
{
	//int lines = 1;
	int fd = open("lorem.txt", O_RDONLY);
	char *line = get_next_line(fd);
	printf("%s", line);
	free(line);
	close(fd);

	/* while ((line = get_next_line(fd)))
	{
		printf("%d->%s", lines++, line);
		free(line);
	} */
	return (0);
}
