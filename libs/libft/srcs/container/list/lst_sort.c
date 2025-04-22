#include "libft.h"

// Declaration -----------------------------------------------------------------
static t_list * _split(t_list * _lst);
static t_list * _merge(t_list * _lst_1, t_list * _lst_2, t_list_func_cmp _compare, t_bool _reverse);
static t_list * _merge_sort(t_list * _lst, t_list_func_cmp _compare, t_bool _reverse);

// static t_void _quick_sort(t_list * _from, t_list * _to, t_list_func_cmp _compare, t_bool _reverse);
// static t_list * _partition(t_list * _from, t_list * _to, t_list_func_cmp _compare, t_bool _reverse);

// Function --------------------------------------------------------------------
t_list *
ft_lst_sort(
	t_list * _lst,
	t_list_func_cmp _compare,
	t_bool _reverse
)
{
	return (ft_lst_sort_range(_lst, ft_lst_back(_lst), _compare, _reverse));
}

t_list *
ft_lst_sort_range(
	t_list * _from,
	t_list * _to,
	t_list_func_cmp _compare,
	t_bool _reverse
)
{
	if (!_from)
		return (nullptr);

	if (!_to)
		_to = ft_lst_back(_from);

	t_list * prev = _from->prev;
	t_list * next = _to->next;

	_from->prev = nullptr;
	_to->next = nullptr;

	t_list * lst_sorted = _merge_sort(_from, _compare, _reverse);

	t_list * front = lst_sorted;
	t_list * back = ft_lst_back(lst_sorted);

	if (prev)
	{
		front->prev = prev;
		prev->next = front;
	}
	if (next)
	{
		back->next = next;
		next->prev = back;
	}

	return (ft_lst_front(front));
}

// Static ----------------------------------------------------------------------
static t_list *
_split(
	t_list * _lst
)
{
	t_list * fast = _lst;
	t_list * slow = _lst;

	while (fast->next && fast->next->next)
	{
		fast = fast->next->next;
		slow = slow->next;
	}

	t_list * tmp = slow->next;

	slow->next = nullptr;

	return (tmp);
}

static t_list *
_merge(
	t_list * _lst_1,
	t_list * _lst_2,
	t_list_func_cmp _compare,
	t_bool _reverse
)
{
	if (!_lst_1)
		return (_lst_2);

	if (!_lst_2)
		return (_lst_1);

	t_ssize diff = _compare(_lst_1->data, _lst_2->data);

	if ((diff <= 0 && !_reverse) || (diff >= 0 && _reverse))
	{
		_lst_1->next = _merge(_lst_1->next, _lst_2, _compare, _reverse);
		_lst_1->next->prev = _lst_1;
		_lst_1->prev = nullptr;
		return (_lst_1);
	}

	_lst_2->next = _merge(_lst_1, _lst_2->next, _compare, _reverse);
	_lst_2->next->prev = _lst_2;
	_lst_2->prev = nullptr;
	return (_lst_2);
}

static t_list *
_merge_sort(
	t_list * _lst,
	t_list_func_cmp _compare,
	t_bool _reverse
)
{
	if (!_lst || !_lst->next)
		return (_lst);

	t_list * lst_2 = _split(_lst);

	_lst = _merge_sort(_lst, _compare, _reverse);
	lst_2 = _merge_sort(lst_2, _compare, _reverse);

	return _merge(_lst, lst_2, _compare, _reverse);
}
