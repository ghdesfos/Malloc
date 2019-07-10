/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 22:15:31 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/03/15 18:12:47 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# define PAGESIZE			4096
# define SMALL				104
# define MEDIUM				512
# define LARGE				2560
# define HEADERSIZE			116
# define HEADERSIZELARGE	16
# define SBLOCKS			100
# define MBLOCKS			100
# define BS ((area->bstatus)[i])
# define BL ((area->blocks)[i][j])

# include <sys/mman.h>
# include <unistd.h>
# include "b_printf/b_printf.h"

struct					s_bstatus
{
	unsigned char		free:1;
	unsigned char		nbblocks:7;
};

typedef struct			s_sarea
{
	struct s_sarea		*next;
	int					blocksize;
	int					nbpages;
	struct s_bstatus	bstatus[SBLOCKS];
	unsigned char		blocks[SBLOCKS][SMALL];
}						t_sarea;

typedef struct			s_marea
{
	struct s_marea		*next;
	int					blocksize;
	int					nbpages;
	struct s_bstatus	bstatus[MBLOCKS];
	unsigned char		blocks[MBLOCKS][MEDIUM];
}						t_marea;

typedef struct			s_larea
{
	struct s_larea		*next;
	int					blocksize;
	int					nbpages;
}						t_larea;

typedef struct			s_areas
{
	struct s_sarea		*sarea;
	struct s_marea		*marea;
	struct s_larea		*larea;
}						t_areas;

t_areas					g_areas;

void					*ft_malloc(size_t size);

t_sarea					*create_mmap_area_small(void);
int						check_if_enough_place_current_area_small(t_sarea \
						*area, size_t size);
t_sarea					*get_right_mmap_area_small(size_t size);
void					*malloc_small(size_t size);

char					*set_right_space_as_allocated_small(t_sarea *area, \
						int nb, int i);
void					*get_right_space_in_mmap_area_small(t_sarea *area, \
						size_t size);

t_marea					*create_mmap_area_medium(void);
int						check_if_enough_place_current_area_medium(t_marea \
						*area, size_t size);
t_marea					*get_right_mmap_area_medium(size_t size);
void					*malloc_medium(size_t size);

char					*set_right_space_as_allocated_medium(t_marea *area, \
						int nb, int i);
void					*get_right_space_in_mmap_area_medium(t_marea *area, \
						size_t size);

t_larea					*create_mmap_area_large(size_t size);
void					*malloc_large(size_t size);

void					ft_free(void *ptr);

t_sarea					*check_ptr_in_mmap_area_small(char *ptr);
int						free_blocks_in_mmap_area_small(t_sarea *area, int i);
int						free_small(void *ptr);

t_marea					*check_ptr_in_mmap_area_medium(char *ptr);
int						free_blocks_in_mmap_area_medium(t_marea *area, int i);
int						free_medium(void *ptr);

t_larea					*check_ptr_in_mmap_area_large(char *ptr);
void					remove_freed_mmap_area_from_list_large(char *ptr);
int						free_large(char *ptr);

char					check_which_type_mmap_ptr_is_in(char *ptr);
void					*ft_realloc(void *ptr, size_t size);

int						actual_change_curr_area_to_new_size_small(t_sarea \
						*area, int i, int nb);
int						set_curr_alloc_area_to_new_size_small(t_sarea *area, \
						int i, size_t size);
void					*transfer_alloc_to_new_area_small(char *ptr, \
						size_t size);
void					*realloc_small(char *ptr, size_t size);

int						actual_change_curr_area_to_new_size_medium(t_marea \
						*area, int i, int nb);
int						set_curr_alloc_area_to_new_size_medium(t_marea *area, \
						int i, size_t size);
void					*transfer_alloc_to_new_area_medium(char *ptr, \
						size_t size);
void					*realloc_medium(char *ptr, size_t size);

void					*realloc_large(char *ptr, size_t size);

void					print_mmap_area_small(t_sarea *area, int width, \
						int i, int k);
void					print_mmap_area_medium(t_marea *area, int width, \
						int i, int k);
void					print_mmap_area_large(t_larea *area, int width, \
						int i, int k);
void					print_mmap_areas(int width, int a, int b, int c);

void					print_blocks_area_small(t_sarea *area, int width, \
						int k);
void					print_blocks_area_medium(t_marea *area, int width, \
						int k);

int						show_alloc_mem_small(void);
int						show_alloc_mem_medium(void);
int						show_alloc_mem_large(void);
void					show_alloc_mem(void);
void					show_alloc_mem_ex(void);

#endif
