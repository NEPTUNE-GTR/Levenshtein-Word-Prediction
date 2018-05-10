
#include "engine.h"

#define MAX 50

static char line[MAX];
static char input[MAX];
static char suggestion[MAX];


void start(char const * const q)
{
    assert(q != NULL);

    int result = 0;
    int steps  = 5;
    
    FILE * file = NULL;

    if(q != NULL)
    {
        printf("%s", q);

        file = fopen(q, "r");

        assert(file != NULL);
        if(file != NULL)
        {
            userInput();

            while(fgets(line, MAX, file) != NULL)
            {
                result = levenshtein(line, input);

                if(result < 5)
                {
                    insert(line);

                    if(result < steps)
                    {
                        strcpy(suggestion, line);
                        steps = result;
                    }
                }
            }
            if(suggestion[0] != 0)
            {
                printf("Did you mean.... %s", suggestion);
                pager();
            }
            else
            {
                printf("Nothing to suggest, your enetry is very weird........\n");
            }
        }
        fclose(file);
    }
    else if(q == NULL)
    {
        printf ("Invalid directory given.... '%s'\n", q);
    }
}

void userInput()
{
    printf("\nWhat word should I check?:");
    fgets(input, MAX, stdin);

    for(int i = 0; input[i] && &input[i] != NULL; i++)
    {
        input[i] = tolower((unsigned char)input[i]);
    }
}

void pager()
{
    int   numItems = 0;
    char *item     = NULL;
    char  c;

    item = firstItem();

    while(item)
    {
        numItems++;
        item = nextItem();
    }

    if(numItems > 0)
    {
        printf("There are %d other similar words, would you like to see them? (y/n)", numItems);

        c    = getchar();
        item = firstItem();

        while(c != 'y' && c != 'Y' && c != 'N' && c != 'n')
        {   
            printf("Thats not a valid response.....would you like to see them? (y/n)\n");
            c = getchar();

            if(c == 'Y' || c == 'y') 
            {
                c = getchar();

                if(c == '\n')
                {
                    c = 'y';
                }
            }
            else if( c == 'N'|| c == 'n')
            {
                c = getchar();

                if(c == '\n')
                {
                    c = 'n';
                }
            }
            else
            {
                c = getchar();
            }
        }

        if(item && (c == 'Y' || c == 'y') )
        {   
            while(item)
            {
                c = getchar();

                if(c == '\n')
                {
                    for(int i = 0; i < 10 && item != NULL; i++)
                    {
                        printf("A similar word: %s", item);
                        item = nextItem();
                    }
                }
                else if(c == 'q' || c == 'Q') 
                {
                    c = getchar();

                    if(c == '\n')
                    {
                        break;
                    }
                }
            }
        }
    }
}