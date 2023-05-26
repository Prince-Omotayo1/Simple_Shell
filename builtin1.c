#include "shell.h"

/**
* _myhistory - displays the history list, one command by line, preceded
*              with line numbers, starting at 0.
* @info: Structure containing potential arguments. Used to maintain
*        constant function prototype.
*  Authors: Omotayo and Bright
*  Return: Always 0
*/

int _myhistory(info_t *info)
{
print_list(info->history);
return (0);
}

/**
* unset_alias - sets alias to string
* @info: parameter struct
* @str: the string alias
*
* Return: Always 0 on success, 1 on error
*/

int unset_alias(info_t *info, char *str)
{
char *e, b;
int ret;

e = _strchr(str, '=');

if (!e)
return (1);
b = *e;
*e = 0;
ret = delete_node_at_index(&(info->alias),
get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
*e = b;
return (ret);
}

/**
* set_alias - sets alias to string
* @info: parameter struct
* @str: the string alias
*
* Return: Always 0 on success, 1 on error
*/
int set_alias(info_t *info, char *str)
{
char *e;

e = _strchr(str, '=');
if (!e)
return (1);
if (!*++e)
return (unset_alias(info, str));

unset_alias(info, str);
return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
* print_alias - prints an alias string
* @node: the alias node
*
* Return: Always 0 on success, 1 on error
*/
int print_alias(list_t *node)
{
char *n = NULL, *m = NULL;

if (node)
{
n = _strchr(node->str, '=');
for (m = node->str; m <= n; m++)
_putchar(*m);
_putchar('\'');
_puts(n + 1);
_puts("'\n");
return (0);
}
return (1);
}

/**
* _myalias - mimics the alias builtin (man alias)
* @info: Structure containing potential arguments. Used to maintain
*          constant function prototype.
*  Return: Always 0
*/
int _myalias(info_t *info)
{
int i = 0;
char *e = NULL;
list_t *node = NULL;

if (info->argc == 1)
{
node = info->alias;
while (node)
{
print_alias(node);
node = node->next;
}
return (0);
}
for (i = 1; info->argv[i]; i++)
{
e = _strchr(info->argv[i], '=');
if (e)
set_alias(info, info->argv[i]);
else
print_alias(node_starts_with(info->alias, info->argv[i], '='));
}

return (0);
}
