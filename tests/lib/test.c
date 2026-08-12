#include "test.h"


bool test_run(test_t *p_test_suite, int count)
{
    pid_t pid, wpid;
    int status;
    int i, failed=0, succeeded=0;
    for (i=0; i<count; i++)
    {
        pid = fork();

        if (!pid)
        {
            exit((p_test_suite[i].p_func()==FAILURE)?1:0);
        }
        else
        {
            printf("[%d/%d] Testing %s... ", i+1, count, p_test_suite[i].psz_desc);

            /* Wait for test result. */
            wpid = waitpid(pid, &status, 0);
            if (wpid < 0) {
                printf("ERR\n");
                return false;
            }

            /* Process has exited normally. */
            if (WIFEXITED(status))
            {
                if (WEXITSTATUS(status) == 0)
                {
                    succeeded++;
                    printf("OK\n");
                }
                else
                {
                    failed++;
                    printf("KO\n");
                }
            }

            /* Process has crashed. */
            else if (WIFSIGNALED(status))
            {
                failed++;
                printf("ERROR (%d)\n", WTERMSIG(status));
            }
        }
    }
    printf("Result: %d PASSED, %d FAILED, %d TOTAL\n", succeeded, failed, count);
    return (failed != 0);
}

