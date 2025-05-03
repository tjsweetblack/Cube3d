/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joandre <joandre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:29:34 by joandre           #+#    #+#             */
/*   Updated: 2025/01/16 13:10:48 by joandre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

char	*get_next_line(int descritor_arquivo);
char	*f_strjoin(char *s1, char *s2);
int		f_strlen(const char *s);
char	*f_strchr(const char *s, int c);
char	*ler_primeira_linha(int descritor_arquivo, char *texto);
char	*obter_linha(char *texto);
char	*limpar_primeira_linha(char *texto);
void	*f_calloc(unsigned int count, unsigned int size);
void	f_bzero(void *s, unsigned int n);

#endif
