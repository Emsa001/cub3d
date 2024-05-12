/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:26:07 by triedel           #+#    #+#             */
/*   Updated: 2024/05/12 14:47:40 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

// for NULL and size_t
# include <stdbool.h>
# include <stdlib.h>

// include ft_alloc
# include "../ft_destructor/ft_alloc.h"

/* ft_atoi.c */
int					ft_charinset(int c, const char *set);
int					ft_isspace(int c);
int					ft_atoi(const char *str);
int					ft_atoi_ref(const char **s);
/* ft_bzero.c */
void				ft_bzero(void *s, size_t n);
/* ft_calloc.c */
void				*ft_calloc(size_t nitems, size_t size);

/* ft_isalnum.c */
int					ft_isalnum(int c);
/* ft_isalpha.c */
int					ft_islower(int c);
int					ft_isupper(int c);
int					ft_isalpha(int c);
/* ft_isascii.c */
int					ft_isascii(int c);
/* ft_isdigit.c */
int					ft_isdigit(int c);
/* ft_isprint.c */
int					ft_isprint(int c);

/* ft_isinset.c */
int					ft_isinset(char c, char *set);

/* ft_itoa.c */
size_t				ft_intlen(int n);
char				*ft_itoa(int n);
char				*ft_itoa_sign(int n, bool with_sign);
/* ft_memchr.c */
void				*ft_memchr(const void *s, int c, size_t n);
/* ft_memcmp.c */
int					ft_memcmp(const void *s1, const void *s2, size_t n);
/* ft_memcpy.c */
void				*ft_memcpy(void *dst, const void *src, size_t n);
/* ft_memmove.c */
void				*ft_memmove(void *dst, const void *src, size_t len);
/* ft_memset.c */
void				*ft_memset(void *b, int c, size_t len);
/* ft_putchar_fd.c */
void				*ft_putchar_fd(char c, int fd);
/* ft_putendl_fd.c */
void				ft_putendl_fd(char *s, int fd);
/* ft_putnbr_fd.c */
void				ft_putlong_fd(long n, int fd);
void				ft_putnbr_fd(int n, int fd);
/* ft_putstr_fd.c */
void				ft_putstr_fd(char *s, int fd);
size_t				ft_putstr_fd_len(char *s, int fd);
void				ft_putstr(char *s);
/* ft_split.c */
int					ft_countwords(char const *s, char c);
void				ft_strarr_del(char **strarr);
char				*ft_nextword(char **s, char c);
char				**ft_split(char const *s, char c);
char				**ft_split_precise(char *str, char c);
/* ft_strchr.c */
char				*ft_strchr(const char *s, int c);
/* ft_strdup.c */
char				*ft_strdup(const char *src);
char				**ft_strduparr(const char **src);

/* ft_striteri.c */
void				ft_striteri(char *s, void (*f)(unsigned int, char *s));
/* ft_strjoin.c */
char				*ft_strjoin(char const *s1, char const *s2);
/* ft_strlcat.c */
size_t				ft_strlcat(char *dst, const char *src, size_t size);
/* ft_strlcpy.c */
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
/* ft_strlen.c */
size_t				ft_strlen(const char *s);
size_t				ft_arrlen(char **arr);
/* ft_strmapi.c */
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
/* ft_strncmp.c */
int					ft_strncmp(const char *s1, const char *s2, size_t n);
/* ft_strnstr.c */
char				*ft_strnstr(const char *haystack, const char *needle,
						size_t len);
/* ft_strrchr.c */
char				*ft_strrchr(const char *s, int c);
/* ft_strtrim.c */
char				*ft_strtrim(char const *s1, char const *set);
/* ft_substr.c */
char				*ft_substr(char const *s, unsigned int start, size_t len);
/* ft_tolower.c */
int					ft_tolower(int c);
/* ft_toupper.c */
int					ft_toupper(int c);

// ===== bonus =====

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

/* ft_lstadd_back_bonus.c */
void				ft_lstadd_back(t_list **lst, t_list *nnew);
void				ft_lstadd(t_list **lst, t_list *nnew);
/* ft_lstadd_front_bonus.c */
void				ft_lstadd_front(t_list **lst, t_list *nnew);
/* ft_lstclear_bonus.c */
void				ft_lstclear(t_list **lst, void (*del)(void *));
t_list				*ft_lstclear_null(t_list **lst, void (*del)(void *));
/* ft_lstdelone_bonus.c */
void				ft_lstdelone(t_list *lst, void (*del)(void *));
/* ft_lstiter_bonus.c */
void				ft_lstiter(t_list *lst, void (*f)(void *));
/* ft_lstlast_bonus.c */
t_list				*ft_lstlast(t_list *lst);
/* ft_lstmap_bonus.c */
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
/* ft_lstnew_bonus.c */
t_list				*ft_lstnew(void *content);
/* ft_lstsize_bonus.c */
int					ft_lstsize(t_list *lst);

// ===== get_next_line =====

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

typedef struct s_filebuffer
{
	int				pos;
	int				end;
	char			data[BUFFER_SIZE];
}					t_filebuffer;

typedef struct s_buffer
{
	int				pos;
	struct s_buffer	*next;
	char			data[BUFFER_SIZE];
}					t_buffer;

/* get_next_line.c */
void				*ft_memcpy(void *dst, const void *src, size_t n);
char				*buffer_to_str(t_buffer *buf);
int					buffer_feed_filebuffer(t_buffer **buf,
						t_filebuffer *filebuff, char sep);
char				*get_next_line(int fd);
/* get_next_line_utils.c */
int					buffer_extend(t_buffer **buf);
void				*buffer_del(t_buffer *buf);
t_buffer			*buffer_last(t_buffer *buf);
int					buffer_feed(t_buffer **buf, char c);
size_t				buffer_len(t_buffer *buf);

// ===== extra =====
/* ft_file_as_str.c */
char				*ft_file_as_str(const char *file);

/* ft_hex.c */
char				ft_digit_inttohex(int n);
int					ft_digit_hextoint(const char c);
unsigned int		ft_atoi_hex_ref(const char **s);

/* ft_atoi_parse.c */
int					ft_parse_uint(const char **s);
const char			*ft_atoi_parse(const char *s, int *num);

/* ft_lstget.c */
t_list				*ft_lstget(t_list *lst, int index);

/* ft_strutils.c */
bool				ft_endswith(const char *s, const char *end);
bool				ft_startswith(const char *s, const char *start);

/* ft_strcmp.c */
int					ft_strcmp(const char *s1, const char *s2);

/* ft_min.c */
int					ft_min(int a, int b);
int					ft_min_int(int a, int b);
float				ft_min_float(float a, float b);

/* ft_max.c */
int					ft_max(int a, int b);
int					ft_max_int(int a, int b);
float				ft_max_float(float a, float b);

/* ft_ternary.c */
int					ft_ternary_int(bool cond, int a, int b);
float				ft_ternary_float(bool cond, float a, float b);

/* ft_split_set.c */
int					ft_countwords_set(char const *s, char *set, char *quotes);
char				*ft_nextword_set(char **s, char *set, char *quotes);
char				**ft_split_set(char const *s, char *set, char *quotes);

/* ft_array.c */
void				ft_arrdel(void **arr);
void				ft_arrarrdel(void ***arr);
void				ft_arriter(void **arr, void (*f)(void **));
void				ft_strarr_print(char **arr);
int					ft_strarr_len(char **arr);
void				ft_arrarrprint(void ***arr);
char				*ft_arrjoin(char **arr, char *s);
// void			*ft_setalloc(size_t num, size_t size, int value);

/* ft_strjoin.c */
char				*ft_strappend(char const *s1, char const *s2);

/* ft_strstrip.c */
int					ft_strcount(const char *s, const char *set);
char				*ft_strstrip(const char *s, const char *set);
void				ft_strstrip_char(const char *s, const char c);

/* ft_strtok */
char				*ft_strtok(char *str, const char *delims);

/* ft_strncpy */
char				*ft_strncpy(char *dest, const char *src, size_t n);

char				*add_char(char *str, char c);

# define FT_WHITESPACE "\t\n\v\f\r "

#endif