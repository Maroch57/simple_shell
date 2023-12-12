#include "shell.h"

/**
 * shellmain - the main loop fn in shell.
 * @info: struct param in subject.
 * @arv: argument vector in subject.
 *
 * Return: 0 if successful, else 1.
 */
int shellmain(pseuarg_ch *info, char **arv)
{
	ssize_t g = 0;
	int ret_bld = 0;

	while (g != -1 && ret_bld != -2)
	{

		infclr(info);
		if (actv_int(info))
			strngin("$ ");
		charins(BUFFER_FLUSH);
		g = inpt_gt(info);
		if (g != -1)
		{
			infprs(info, arv);
			ret_bld = go_emb(info);
			if (ret_bld == -1)
				loc_comm(info);
		}
		else if (actv_int(info))
			_putchar('\n');
		infree(info, 0);
	}
	hist_updt(info);
	infree(info, 1);
	if (!actv_int(info) && info->tellstat)
		exit(info->tellstat);
	if (ret_bld == -2)
	{
		if (info->errn == -1)
			exit(info->tellstat);
		exit(info->errn);
	}
	return (ret_bld);
}

/**
 * go_emb - fn searches for a builtin command.
 * @info: struct param in subject.
 *
 * Return: -1 if builtin command is not found,
 *		0 if successful,
 *		1 if not successful,
 *		-2 if the fn is supposed to exit.
 */
int go_emb(pseuarg_ch *info)
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
		if (strn_cmp(info->argv[0], tbl_build[g].cflg) == 0)
		{
			info->cnterr++;
			retn_b = tbl_build[g].func(info);
			break;
		}
	return (retn_b);
}

/**
 * loc_comm - responsible for finding a command in a certain path.
 * @info: struct param in subject.
 *
 * Return: NULL.
 */
void loc_comm(pseuarg_ch *info)
{
	char *way = NULL;
	int l, m;

	info->way = info->argv[0];
	if (info->cntline_flg == 1)
	{
		info->cnterr++;
		info->cntline_flg = 0;
	}
	for (l = 0, m = 0; info->arg[l]; l++)
		if (!prser(info->arg[l], " \t\n"))
			m++;
	if (!m)
		return;

	way = locpath(info, pop_env(info, "PATH="), info->argv[0]);
	if (way)
	{
		info->way = way;
		loc_fork(info);
	}
	else
	{
		if ((actv_int(info) || pop_env(info, "PATH=")
			|| info->argv[0][0] == '/') && cmdprt(info, info->argv[0]))
			loc_fork(info);
		else if (*(info->arg) != '\n')
		{
			info->tellstat = 127;
			errorprnt(info, "not found\n");
		}
	}
}

/**
 * loc_fork - enables forking of an executable thread.
 * @info: struct param in subject.
 *
 * Return: void.
 */
void loc_fork(pseuarg_ch *info)
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
		if (execve(info->way, info->argv, aqrenv(info)) == -1)
		{
			infree(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->tellstat));
		if (WIFEXITED(info->tellstat))
		{
			info->tellstat = WEXITSTATUS(info->tellstat);
			if (info->tellstat == 126)
				errorprnt(info, "Permission denied\n");
		}
	}
}
