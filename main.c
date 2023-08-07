#include "minishell.h"

int main(int argc, char const *argv[], char **envp)
{
    char *str[2] = {"./script", "\0"};
    if (execve(str[0], str, envp) == -1)
        printf("failed");
    return 0;
}
