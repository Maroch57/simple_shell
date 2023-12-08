#include "shell.h"

/**
 * histfile_fetch - Fetches the history file
 * @info: The structure denoting possible arguments
 * Return: History file string
 */
char *histfile_fetch(pseuarg_ch *info)
{
	char *buff, *directry;

	directry = pop_env(info, "HOME=");
	if (!directry)
		return (NULL);
	buff = malloc(sizeof(char) * (lngth_str(directry) + lngth_str(FILE_H) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	strngcop(buff, directry);
	strn_cat(buff, "/");
	strn_cat(buff, FILE_H);
	return (buff);
}

/**
 * hist_updt - Creates new file, appends existing one
 * @info: The structure denoting possible arguments
 * Return: 1 if successful, -1 if unsuccessful
 */
int hist_updt(pseuarg_ch *info)
{
	ssize_t fd;
	char *file = histfile_fetch(info);
	lst_m *node = NULL;

	if (!file)
		return (-1);

	fd = open(file, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(file);
	if (fd == -1)
		return (-1);
	for (node = info->hst; node; node = node->next)
	{
		fndpt(node->strng, fd);
		fputer('\n', fd);
	}
	fputer(BUFFER_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * rdhist - Reads history
 * @info: The structure denoting possible arguments
 * Return: The history count if successful, 0 if anything else
 */
int rdhist(pseuarg_ch *info)
{
	int a, count = 0, final = 0;
	ssize_t fd, mag, readlen = 0;
	struct det pr;
	char *buff = NULL, *file = histfile_fetch(info);

	if (!file)
		return (0);

	fd = open(file, O_RDONLY);
	free(file);
	if (fd == -1)
		return (0);
	if (!det(fd, &pr))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_history_list(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_history_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - adds entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber_history - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->histcount = i);
}
