/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:15:53 by triedel           #+#    #+#             */
/*   Updated: 2024/05/31 01:42:47 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

// void	*ft_memcpy(void *dst, const void *src, size_t n)
// {
// 	unsigned int	i;

// 	if (!dst && !src && n > 0)
// 		return (NULL);
// 	i = 0;
// 	while (i < n)
// 	{
// 		((char *) dst)[i] = ((char *) src)[i];
// 		i++;
// 	}
// 	return (dst);
// }

char	*buffer_to_str(t_buffer *buf)
{
	char	*str;
	char	*s;
	size_t	len;

	if (!buf)
		return (ft_strdup(""));
	len = buffer_len(buf);
	if (len == 0)
		return (NULL);
	str = ft_malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	s = str;
	s[len] = '\0';
	while (buf->next)
	{
		ft_memcpy(s, buf->data, BUFFER_SIZE);
		s += BUFFER_SIZE;
		buf = buf->next;
	}
	ft_memcpy(s, buf->data, buf->pos);
	return (str);
}

// Takes a list of buffers, and feeds a filebuffer into it
//
// retvals
//  1 -> found sep
//  0 -> go on
// -1 -> error
int	buffer_feed_filebuffer(t_buffer **buf, t_filebuffer *filebuff, char sep)
{
	char		lastchar;
	t_buffer	*curbuf;

	if (!*buf)
		if (buffer_extend(buf) < 0)
			return (-1);
	curbuf = buffer_last(*buf);
	while (filebuff->pos < filebuff->end)
	{
		lastchar = filebuff->data[filebuff->pos];
		(filebuff->pos)++;
		if (buffer_feed(&curbuf, lastchar) < 0)
			return (-1);
		if (lastchar == sep)
			return (1);
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static t_filebuffer	filebuff = {.pos = BUFFER_SIZE, .end = BUFFER_SIZE};
	t_buffer			*tmpbuff;
	int					res;
	char				*str;

	if (fd < 0)
		return (NULL);
	tmpbuff = NULL;
	res = 1;
	while (res > 0)
	{
		res = buffer_feed_filebuffer(&tmpbuff, &filebuff, '\n');
		if (res == 1)
			break ;
		else if (res == -1)
			return ((char *)buffer_del(tmpbuff));
		res = read(fd, filebuff.data, BUFFER_SIZE);
		filebuff.pos = 0;
		filebuff.end = res;
		if (res < 0)
			return ((char *)buffer_del(tmpbuff));
	}
	str = buffer_to_str(tmpbuff);
	buffer_del(tmpbuff);
	return (str);
}

/*
#include <stdio.h>

int	main(void)
{
	char	*s;

	while ((s = get_next_line(0)))
	{
		printf("%s", s);
		ft_free(s);
	}
}
*/
