#include "shell.h"

/**
 * shellmain - The main loop fn in shell.
 * @feed: struct param in subject.
 * @arv: argument vector in subject.
 * Return: 0 if successful, else 1.
 */
int shellmain(pseuarg_ch *feed, char **arv)
{
	ssize_t g = 0;
	int ret_bld = 0;

	while (g != -1 && ret_bld != -2)
	{

		infclr(feed);
		if (actv_int(feed))
			strngin("$ ");
		charins(BUFFER_FLUSH);
		g = inpt_gt(feed);
		if (g != -1)
		{
			infprs(feed, arv);
			ret_bld = go_emb(feed);
			if (ret_bld == -1)
				loc_comm(feed);
		}
		else if (actv_int(feed))
			_putchar('\n');
		infree(feed, 0);
	}
	hist_updt(feed);
	infree(feed, 1);
	if (!actv_int(feed) && feed->tellstat)
		exit(feed->tellstat);
	if (ret_bld == -2)
	{
		if (feed->errn == -1)
			exit(feed->tellstat);
		exit(feed->errn);
	}
	return (ret_bld);
}

/**
 * go_emb - This function searches for builtin command.
 * @feed: Structure denoting possible arguments.
 * Return: -1 if builtin command is not found,
 *		0 if successful,
 *		1 if not successful,
 *		-2 if the fn is supposed to exit.
 */
int go_emb(pseuarg_ch *feed)
{
	int g, retn_b = -1;
	embed_str tbl_build[] = {
		{"exit", exist_sts},
		{"env", myown_env},
		{"help", help_inf},
		{"history", hist_rep},
		{"setenv", good_env},
		{"unsetenv", bad_env},
		{"cd", cd_mine},
		{"alias", alum_hist},
		{NULL, NULL}
	};

	for (g = 0; tbl_build[g].cflg; g++)
		if (strn_cmp(feed->argv[0], tbl_build[g].cflg) == 0)
		{
			feed->cnterr++;
			retn_b = tbl_build[g].resfunc(feed);
			break;
		}
	return (retn_b);
}

/**
 * loc_comm - Responsible for finding a command in a certain path.
 * @feed: Structure denoting possible arguments.
 * Return: NULL.
 */
void loc_comm(pseuarg_ch *feed)
{
	char *way = NULL;
	int l, m;

	feed->way = feed->argv[0];
	if (feed->cntline_flg == 1)
	{
		feed->cnterr++;
		feed->cntline_flg = 0;
	}
	for (l = 0, m = 0; feed->arg[l]; l++)
		if (!prser(feed->arg[l], " \t\n"))
			m++;
	if (!m)
		return;

	way = locpath(feed, pop_env(feed, "PATH="), feed->argv[0]);
	if (way)
	{
		feed->way = way;
		loc_fork(feed);
	}
	else
	{
		if ((actv_int(feed) || pop_env(feed, "PATH=")
			|| feed->argv[0][0] == '/') && cmdprt(feed, feed->argv[0]))
			loc_fork(feed);
		else if (*(feed->arg) != '\n')
		{
			feed->tellstat = 127;
			errorprnt(feed, "not found\n");
		}
	}
}

/**
 * loc_fork - Enables forking of an executable thread.
 * @feed: Structure denoting possible arguments.
 * Return: void.
 */
void loc_fork(pseuarg_ch *feed)
{
	pid_t chld_pid;

	chld_pid = fork();
	if (chld_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (chld_pid == 0)
	{
		if (execve(feed->way, feed->argv, aqrenv(feed)) == -1)
		{
			infree(feed, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(feed->tellstat));
		if (WIFEXITED(feed->tellstat))
		{
			feed->tellstat = WEXITSTATUS(feed->tellstat);
			if (feed->tellstat == 126)
				errorprnt(feed, "Permission denied\n");
		}
	}
}
