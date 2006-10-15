//
// Linked List Library
// Omar Cornut, 1999-2001
//

#include "liblist.h"

#include <stdio.h> // for list_print_str
void    *malloc(int);
void    free(void *);

// LIST_ADD.C ---------------------------------------------------------------

void		list_add(t_list **list, void *elem)
{
  t_list	*new;

  new = malloc(sizeof (t_list));
  new->elem = elem;
  new->next = *list;
  *list = new;
}

void		list_add_to_end(t_list **list, void *elem)
{
  t_list	*new;
  t_list	*list2;

  new = malloc(sizeof (t_list));
  new->elem = elem;
  new->next = 0;
  if (*list == 0)
    *list = new;
  else
    {
      list2 = *list;
      while (list2->next)
	list2 = list2->next;
      list2->next = new;
    }
}

// LIST_CONTACT.C -----------------------------------------------------------

void		list_concat(t_list **list1, t_list *list2)
{
  t_list	*l;

  if (*list1)
    {
      l = *list1;
      while (l->next)
	l = l->next;
      l->next = list2;
    }
  else
    {
      *list1 = list2;
    }
}

// LIST_FREE.C --------------------------------------------------------------

void		list_free(t_list **list)
{
  t_list	*next;

  while (*list)
    {
      next = (*list)->next;
      free((*list)->elem);
      free(*list);
      *list = next;
    }
}

void		list_free_no_elem(t_list **list)
{
  t_list	*next;
  while (*list)
    {
      next = (*list)->next;
      free(*list);
      *list = next;
    }
}

void            list_free_custom(t_list **list, void (*custom_free)())
{
  t_list	*next;

  while (*list)
    {
      next = (*list)->next;
      custom_free((*list)->elem);
      free(*list);
      *list = next;
    }
}

// LIST_MERGE.C -------------------------------------------------------------

void		list_merge(t_list **list1, t_list *list2, int (*cmp)(void *elem1, void *elem2))
{
  t_list	*l;
  int		found_flag;

  while (list2)
    {
      l = *list1;
      found_flag = 0;
      while (l)
	{
	  if (cmp(l->elem, list2->elem) == 0)
	    {
	      found_flag = 1;
	      break;
	    }
	  l = l->next;
	}
      if (found_flag == 0)
	list_add(list1, list2->elem);
      list2 = list2->next;
    }
}

// LIST_PRINT.C -------------------------------------------------------------

void	list_print_str(t_list *list)
{
  while (list)
    {
      printf("%s\n", (char *)list->elem);
      list = list->next;
    }
}

// LIST_REMOVE.C ------------------------------------------------------------

void            list_remove(t_list **list, void *elem, void (*freer)())
{
  t_list        *elem_prev;
  t_list        *save;
  t_list        *tmp;

  elem_prev = 0;
  save = *list;
  while (*list)
    {
      if ((*list)->elem == elem)
        {
          tmp = *list;
          *list = (*list)->next;
	  if (freer)
	    freer(tmp->elem);
          free(tmp);
          if (!elem_prev)
            save = *list;
          else
            elem_prev->next = *list;
        }
      if ((elem_prev = *list))
        *list = (*list)->next;
    }
  *list = save;
}

// LIST_REVERSE.C -----------------------------------------------------------

void		list_reverse(t_list **list)
{
  t_list	*src;
  t_list	*dest;

  if (*list == 0)
    return;
  src = 0;
  while ((*list)->next)
    {
      dest = (*list)->next;
      (*list)->next = src;
      src = *list;
      *list = dest;
    }
  (*list)->next = src;
}

// LIST_SIZE.C --------------------------------------------------------------

int	list_size(t_list *list)
{
  int	cnt;

  cnt = 0;
  while (list)
    {
      cnt += 1;
      list = list->next;
    }
  return (cnt);
}

// LIST_SORT.C --------------------------------------------------------------

void		list_sort(t_list **list, int (*fct)(void *elem1, void *elem2))
{
  t_list	*i;
  t_list	*j;
  t_list	*temp;

  i = *list;
  while (i)
    {
      j = i->next;
      while (j)
	{
	  if (fct(i->elem, j->elem) >= 0)
	    {
	      temp = i->elem;
	      i->elem = j->elem;
	      j->elem = temp;
	    }
	  j = j->next;
	}
      i = i->next;
    }
}

// LIST_TO_TAB.C ------------------------------------------------------------

void	*list_to_tab(t_list *list)
{
  int	i;
  void	**table;
  int	size;

  size = list_size(list);
  table = malloc(sizeof (void *) * (size + 1));
  for (i = 0; i < size; i++)
    {
      table[i] = list->elem;
      list = list->next;
    }
  table[i] = 0;
  return (table);
}

