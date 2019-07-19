#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *f;

/*
 * Function: permutation_util
 * --------------------------
 * prints the permutations of the index of the current set eq index
 * otherwise it recurs
 *
 * chosen[]:    permutation array
 * alph[]:      alphabet for the permutation
 * index:       current char
 * length:      length of the permutation to be generated
 * start:       starting index in alph[]
 * end:         ending index in alph[]
 *
 * returns:     void
 */
void permutation_util(int chosen[], char alph[], int index, int length, int end)
{
    /* index is length => ready to print */
    if (index == length)
    {
       for (int i = 0; i < length; i++)
           putc(alph[chosen[i]], f);
       putc('\n', f);
       return;
    }

    /* chose every elements (without considering whether it's chosen or not) */
    for (int i = 0; i <= end; i++)
    {
        chosen[index] = i;
        permutation_util(chosen, alph, index + 1, length, end);
    }
}

/*
 * Function: permutation_util_all
 * ------------------------------
 * prints the permutations of te index of the current set eq index
 * using a performance algorithm because the alphabet is equal to the
 * destination length
 *
 * chosen[]:    permutation array
 * alph[]:      alphabet for the permutation
 * index:       current char
 * length:      length of the permutation to be genrated
 * end:         ending index of the alphabet
 */
void permutation_util_all(int chosen[], char alph[], int index, int length, int end)
{
    for (int i = 0; i < length; i++)
    {
        chosen[index] = i;
        if (index == length)
        {
            for (int j = 0; j < length; j++)
                putc(alph[chosen[j]], f);
            putc('\n', f);
            return;
        }
        else
        {
            permutation_util_all(chosen, alph, index + 1, length, end);
        }
    }
}

/*
 * Function: permutation
 * ---------------------
 *  prepares the temporary vars for the recursion
 *
 *  alph[]:     the alphabet for the permutations
 *  n:          the length of the alphabet
 *  length:     the length of the permutations to be generated
 *
 *  returns:    void
 */
void permutation(char alph[], int n, int length)
{
    /* allocate memory */
    int chosen[length+1];

    /*
     * start recursive function 
     * using performance mode if the alphabet is equal to the expected length
     */
    if (n == length)
        permutation_util_all(chosen, alph, 0, length, n-1);
    else
        permutation_util(chosen, alph, 0, length, n-1);
}

/*
 * Function: main
 * --------------
 * main function that starts the code
 *
 * argc:        number of passed commandline arguments
 * argv[]:      the passed commandline arguments
 *
 * returns:     int
 *              -> 0 if everything is ok
 *              -> 1 if anything went false
 */
int main (int argc, char* argv[])
{
    if (argc < 4)
    {
        printf("./pw-gen <length> <alphabet> <outputfile>\n");
        return 0;
    }

    /* set length */
    char *tmp = argv[1];
    int length = atoi(tmp);

    /* alphabet */
    char *alph = argv[2];
    int n = strlen(argv[2]);
    
    /* open file to write*/
    f = fopen(argv[3], "w");

    /* prepare for recursion */
    permutation(alph, n, length);

    /* close the file */
    fclose(f);

    return 0;
}
