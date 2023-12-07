#include "shell.h"

/**
 * exist_sts - exits shell.
 * @info: Structure containing constant function prototype.
 *  Return: exit status example -
 *         (0) if info.argv[0] != "exit"
 */
int exist_sts(pseuarg_ch *info)
{
	int ext_stat;

	if (info->argv[1])
	{
		ext_stat = _erratoi(info->argv[1]);
		if (ext_stat == -1)
		{
			info->tellstat = 2;
			errorprnt(info, "Illegal number: ");
			putide(info->argv[1]);
			charins('\n');
			return (1);
		}
		info->errn = exst_err(info->argv[1]);
		return (-2);
	}
	info->errn = -1;
	return (-2);
}

/**
 * cd_mine - changes current process directory.
 * @info: Structure containing potential fn prototype.
 *  Return: 0.
 */
int cd_mine(pseuarg_ch *info)
{
	char *s, *directry, buffer[1024];
	int retchld;

	s = getcwd(buffer, 1024);
	if (!s)
		strngin("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		directry = pop_env(info, "HOME=");
		if (!directry)
			retchld = /* TODO: what should this be? */
				ch_dir((directry = pop_env(info, "PWD=")) ? directry : "/");
		else
			retchld = ch_dir(directry);
	}
	else if (strn_cmp(info->argv[1], "-") == 0)
	{
		if (!pop_env(info, "OLDPWD="))
		{
			strngin(s);
			_putchar('\n');
			return (1);
		}
		strngin(pop_env(info, "OLDPWD=")), _putchar('\n');
		retchld = /* TODO: what should this be? */
			ch_dir((directry = pop_env(info, "OLDPWD=")) ? directry : "/");
	}
	else
		retchld = ch_dir(info->argv[1]);
	if (retchld == -1)
	{
		errorprnt(info, "can't cd to ");
		putide(info->argv[1]), charins('\n');
	}
	else
	{
		ptenv(info, "OLDPWD", pop_env(info, "PWD="));
		ptenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * help_inf - changes current directory.
 * @info: Structure containing potential fn prototype.
 *  Return: 0.
 */
int help_inf(pseuarg_ch *info)
{
	char **arr_arg;

	arr_arg = info->argv;
	strngin("help call works. Function not yet implemented \n");
	if (0)
		strngin(*arr_arg);
	return (0);
}
