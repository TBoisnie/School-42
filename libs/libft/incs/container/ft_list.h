#ifndef LIBFT_CONTAINER_LIST_H
#define LIBFT_CONTAINER_LIST_H

#include "ft_types.h"

// Typedef ---------------------------------------------------------------------
typedef t_void   (* t_list_func_del) (t_void * _data);
typedef t_ssize  (* t_list_func_cmp) (t_void const * _data_1, t_void const * _data_2);
typedef t_void   (* t_list_func_itr) (t_void const * _data, t_size _index);
typedef t_void * (* t_list_func_map) (t_void * _data, t_size _index);
typedef t_bool   (* t_list_func_find)(t_void const * _data, t_size _index);

// Struct ----------------------------------------------------------------------
typedef struct s_list
{
	t_void * data;

	struct s_list * prev;
	struct s_list * next;
} t_list;

// Function --------------------------------------------------------------------
t_list * ft_lst_new(t_void * _data);
t_list * ft_lst_push_back(t_list * _lst, t_void * _data);
t_list * ft_lst_push_front(t_list * _lst, t_void * _data);
t_list * ft_lst_delete(t_list * _node, t_list_func_del _cleaner);
t_list * ft_lst_clear(t_list * _lst, t_list_func_del _cleaner);

t_list * ft_lst_merge(t_list * _lst_1, t_list * _lst_2);
t_list * ft_lst_swap(t_list * _node_1, t_list * _node_2);
t_list * ft_lst_reverse(t_list * _lst);

t_size   ft_lst_size(t_list const * _lst);
t_list * ft_lst_back(t_list const * _lst);
t_list * ft_lst_front(t_list const * _lst);
t_list * ft_lst_index(t_list const * _lst, t_size _index);
t_list * ft_lst_find(t_list const * _lst, t_list_func_find _matcher);
t_list * ft_lst_rfind(t_list const * _lst, t_list_func_find _matcher);
t_list * ft_lst_iterate(t_list const * _lst, t_list_func_itr _callable);

t_list * ft_lst_map(t_list * _lst, t_list_func_map _callable);
t_list * ft_lst_sort(t_list * _lst, t_list_func_cmp _compare, t_bool _reverse);
t_list * ft_lst_sort_range(t_list * _from, t_list * _to, t_list_func_cmp _compare, t_bool _reverse);

// t_list * ft_lst_filter(t_list * _lst, t_bool (* _filter)(t_void * _data, t_size index));
// t_list * ft_lst_clone(t_list const * _lst, t_void * (* _clone)(t_void const * _data));

#endif
