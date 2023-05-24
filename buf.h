#ifndef BUF_H
#define BUF_H

/**
    * _myhelp – change dir
    * @info: Structure
    * Return: 0
*/

int _myhelp(info_t *info)
{
char **arg_arr; arg_arr = info->argv;

_puts("help call works. Function not yet implemented \n");
if (0)
_puts(*arg_arr); /* temp att_unused workaround */ return (0);
}

/**
    * _myexit - exits
    * @info: Structure
    * Return: exit status
*/

int _myexit(info_t *info)
{
int exc;
if (info->argv[1])
{
exc = _erratoi(info->argv[1]); if (exc == -1)
{
info->status = 2;
print_error(info, "Illegal number: ");
_eputs(info->argv[1]);
_eputchar('\n'); return (1);
}
info->err_num = _erratoi(info->argv[1]); return (-2);
}
info->err_num = -1;
return (-2);
}

/**
    * _mycd - change directory
    * @info: Structure
    * Return: 0
*/

int _mycd(info_t *info)
{
char *s, *d, bf[1024]; int cd_ret;
s = getcwd(bf, 1024); if (!s)
_puts("TODO: >>getcwd failure emsg here<<\n");
if (!info->argv[1])
{
d = _getenv(info, "HOME="); if (!d)
cd_ret = /* TODO: what should this be? */ chdir((d = _getenv(info, "PWD=")) ? d : "/"); else
cd_ret = chdir(d);
}
else if (_strcmp(info->argv[1], "-") == 0)
{
if (!_getenv(info, "OLDPWD="))
{
_puts(s);
_putchar('\n'); return (1);
}
_puts(_getenv(info, "OLDPWD=")), _putchar('\n'); cd_ret = /* TODO: what should this be? */ chdir((d = _getenv(info, "OLDPWD=")) ? d : "/");
}
else
cd_ret = chdir(info->argv[1]); if (cd_ret == -1)
{
print_error(info, "can't cd to ");
_eputs(info->argv[1]), _eputchar('\n');
}
else
{
_setenv(info, "OLDPWD", _getenv(info, "PWD="));
_setenv(info, "PWD", getcwd(bf, 1024));
}
return (0);
}
#endif
