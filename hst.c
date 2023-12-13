#include "shell.h"

/**
 * histfile_fetch - Fetches the history file
 * @feed: The structure denoting possible arguments
 * Return: The history file string
 */
char *histfile_fetch(pseuarg_ch *feed)
{
	char *directry, *buff;

	directry = pop_env(feed, "HOME=");
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
 * hist_updt - Creates ands appends file
 * @feed: The structure denoting possible arguments
 * Return: 1 if successful, -1 if unsuccessful
 */
int hist_updt(pseuarg_ch *feed)
{
	lst_m *node = NULL;
	ssize_t fd;
	char *file = histfile_fetch(feed);

	if (!file)
		return (-1);

	fd = open(file, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(file);
	if (fd == -1)
		return (-1);
	for (node = feed->hst; node; node = node->next)
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
 * @feed: The structure denoting possible arguments
 * Return: The history count
 */
int rdhist(pseuarg_ch *feed)
{
	int a, count = 0, final = 0;
	ssize_t fd, readsize, readlen = 0;
	char *buff = NULL, *file = histfile_fetch(feed);
	struct stat st;

	if (!file)
		return (0);

	fd = open(file, O_RDONLY);
	free(file);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		readsize = st.st_size;
	if (readsize < 2)
		return (0);
	buff = malloc(sizeof(char) * (readsize + 1));
	if (!buff)
		return (0);
	readlen = read(fd, buff, readsize);
	buff[readsize] = 0;
	if (readlen <= 0)
		return (free(buff), 0);
	close(fd);
	for (a = 0; a < readsize; a++)
		if (buff[a] == '\n')
		{
			buff[a] = 0;
			histlst_b(feed, buff + final, count++);
			final = a + 1;
		}
	if (final != a)
		histlst_b(feed, buff + final, count++);
	free(buff);
	feed->tellhist = count;
	while (feed->tellhist-- >= MAX_H)
		indxnode_del(&(feed->hst), 0);
	nmber_hist(feed);
	return (feed->tellhist);
}

/**
 * histlst_b - History list entry
 * @feed: Structure denoting possible arguments
 * @buff: The buffer
 * @count: The linecount denoting the history
 * Return: 0
 */
int histlst_b(pseuarg_ch *feed, char *buff, int count)
{
	lst_m *node = NULL;

	if (feed->hst)
		node = feed->hst;
	endnode_add(&node, buff, count);

	if (!feed->hst)
		feed->hst = node;
	return (0);
}

/**
 * nmber_hist - Renumbers the list
 * @feed: Structure denoting possible arguments
 * Return: 0
 */
int nmber_hist(pseuarg_ch *feed)
{
	lst_m *node = feed->hst;
	int a = 0;

	while (node)
	{
		node->nmber = a++;
		node = node->next;
	}
	return (feed->tellhist = a);
}
