#include "shell.h"

/**
 * _exit_ - Exit Shell
 *
 * Description: built-in exit
 *
 * Return: Void (Exit Status)
 */

void  _exit_(void)
{
		exit(EXIT_SUCCESS);
}



/**
 * _cd - Change Directory
 * @cmd: Parsed Command
 * @er: Status of Last Command Executed
 * Return: 0 Success 1 Failed (For Old Pwd Always 0 Case No Old PWD)
 */
int _cd(char **cmd, __attribute__((unused))int er)
{
	int value = -1;
	char cwd[PATH_MAX];

	if (cmd[1] == NULL)
		value = chdir(getenv("HOME"));
	else if (_strcmp(cmd[1], "-") == 0)
	{
		value = chdir(getenv("OLDPWD"));
	}
	else
		value = chdir(cmd[1]);

	if (value == -1)
	{
		perror("hsh");
		return (-1);
	}
	else if (value != -1)
	{
		getcwd(cwd, sizeof(cwd));
		setenv("OLDPWD", getenv("PWD"), 1);
		setenv("PWD", cwd, 1);
	}
	return (0);
}
/**
 * this_env - Display Enviroment Variable
 * @cmd:Parsed Command
 * @er:Status of Last command Executed
 * Return:Always 0
 */
int this_env(__attribute__((unused)) char **cmd,
		__attribute__((unused)) int er)
{
size_t i;
	int len;

	for (i = 0; environ[i] != NULL; i++)
	{
		len = _strlen(environ[i]);
		write(1, environ[i], len);
		write(STDOUT_FILENO, "\n", 1);
	}
	return (0);
}
/**
 * _help - Displaying Help For Builtin
 * @cmd:Parsed Command
 * @er: Status Of Last Command Executed
 * Return: 0 Succes -1 Fail
 */
int _help(char **cmd, __attribute__((unused))int er)
{
	int fd, fw, rd = 1;
	char c;

	fd = open(cmd[1], O_RDONLY);
	if (fd < 0)
	{
		perror("Error");
		return (0);
	}
	while (rd > 0)
	{
		rd = read(fd, &c, 1);
		fw = write(STDOUT_FILENO, &c, rd);
		if (fw < 0)
		{
			return (-1);
		}
	}
	_putchar('\n');
	return (0);
}
/**
 * _echo - Execute Echo Cases
 * @st:Statue Of Last Command Executed
 * @cmd: Parsed Command
 * Return: Always 0 Or Execute Normal Echo
 */
int _echo(char **cmd, int st)
{
	char *path;
	unsigned int  pid = getppid();

	if (_strncmp(cmd[1], "$?", 2) == 0)
	{
		print_number_in(st);
		PRINTER("\n");
	}
	else if (_strncmp(cmd[1], "$$", 2) == 0)
	{
		print_number(pid);
		PRINTER("\n");

	}
	else if (_strncmp(cmd[1], "$PATH", 5) == 0)
	{
		path = _getenv("PATH");
		PRINTER(path);
		PRINTER("\n");
		free(path);

	}
	else
		return (print_echo(cmd));

	return (1);
}
