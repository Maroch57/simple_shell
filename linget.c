#include "shell.h"

/**
 * bfer_inpt - buffer commands in subject.
 * @feed: struct parameter in subject.
 * @buff: buffer address in subject.
 * @leng: lngth var address.
 * Return: no. of bytes present.
 */
ssize_t bfer_inpt(pseuarg_ch *feed, char **buff, size_t *leng)
{
	ssize_t w = 0;
	size_t en_lnth = 0;

	if (!*leng)
	{
		free(*buff);
		*buff = NULL;
		signal(SIGINT, mngint);
#if FOR_GETLINE
		w = getline(buff, &en_lnth, stdin);
#else
		w = get_delim(feed, buff, &en_lnth);
#endif
		if (w > 0)
		{
			if ((*buff)[w - 1] == '\n')
			{
				(*buff)[w - 1] = '\0';
				w--;
			}
			feed->cntline_flg = 1;
			rm_comm(*buff);
			histlst_b(feed, *buff, feed->tellhist++);
			{
				*leng = w;
				feed->cdbuffer = buff;
			}
		}
	}
	return (w);
}

/**
 * inpt_gt - fn gets a line without newline.
 * @feed: struct param in subject.
 *
 * Return: total number bytes.
 */
ssize_t inpt_gt(pseuarg_ch *feed)
{
	static char *buff;
	static size_t f, g, leng;
	ssize_t h = 0;
	char **bf_ptr = &(feed->arg), *q;

	_putchar(BUFFER_FLUSH);
	h = bfer_inpt(feed, &buff, &leng);
	if (h == -1)
		return (-1);
	if (leng)
	{
		g = f;
		q = buff + f;

		look_ch(feed, buff, &g, f, leng);
		while (g < leng)
		{
			if (str_ch(feed, buff, &g))
				break;
			g++;
		}

		f = g + 1;
		if (f >= leng)
		{
			f = leng = 0;
			feed->cdbuffertype = NORMAL_CMND;
		}

		*bf_ptr = q;
		return (lngth_str(q));
	}

	*bf_ptr = buff;
	return (h);
}

/**
 * rd_buf - reads a buff in subject.
 * @feed: struct param in subject.
 * @buff: the bufferin subject.
 * @i: demonstrates size.
 * Return: val.
 */
ssize_t rd_buf(pseuarg_ch *feed, char *buff, size_t *i)
{
	ssize_t h = 0;

	if (*i)
		return (0);
	h = read(feed->telldes, buff, READ_BUFFER_SIZE);
	if (h >= 0)
		*i = h;
	return (h);
}

/**
 * get_delim - fn gets next input line from stndard input.
 * @feed: struct param in subject.
 * @ptrr: ptr address to buff.
 * @llength: ptr buff size after allocation.
 * Return: val
 */
int get_delim(pseuarg_ch *feed, char **ptrr, size_t *llength)
{
	static char buff[READ_BUFFER_SIZE];
	static size_t m, leng;
	size_t n;
	ssize_t q = 0, d = 0;
	char *t = NULL, *new_pt = NULL, *a;

	t = *ptrr;
	if (t && llength)
		d = *llength;
	if (m == leng)
		m = leng = 0;

	q = rd_buf(feed, buff, &leng);
	if (q == -1 || (q == 0 && leng == 0))
		return (-1);

	a = str_imp(buff + m, '\n');
	n = a ? 1 + (unsigned int)(a - buff) : leng;
	new_pt = mem_ralloc(t, d, d ? d + n : n + 1);
	if (!new_pt) /* MALLOC FAILURE! */
		return (t ? free(t), -1 : -1);

	if (d)
		strngmod(new_pt, buff + m, n - m);
	else
		cppy_strng(new_pt, buff + m, n - m + 1);

	d += n - m;
	m = n;
	t = new_pt;

	if (llength)
		*llength = d;
	*ptrr = t;
	return (d);
}

/**
 * mngint - it blocks control C shortcut.
 * @sig_nmber: signal no.
 *
 * Return: NULL.
 */
void mngint(__attribute__((unused))int sig_nmber)
{
	strngin("\n");
	strngin("$ ");
	_putchar(BUFFER_FLUSH);
}
