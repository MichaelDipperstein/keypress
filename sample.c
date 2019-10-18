/***************************************************************************
*                      Keypress Library Usage Sample
*
*   File    : sample.c
*   Purpose : Demonstrates the usage of keypress library.
*   Author  : Michael Dipperstein
*   Date    : November 19, 2014
*
****************************************************************************
*
* sample: An example demonstrating proper usage of the keypress function
* Copyright (C) 2012, 2014 by
* Michael Dipperstein (mdipperstein@gmail.com)
*
* This file is part of the Keypress library.
*
* The Keypress library is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public License as
* published by the Free Software Foundation; either version 3 of the
* License, or (at your option) any later version.
*
* The Keypress library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser
* General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
***************************************************************************/

/***************************************************************************
*                             INCLUDED FILES
***************************************************************************/
#include <stdio.h>
#include <errno.h>
#include "keypress.h"

/***************************************************************************
*                            TYPE DEFINITIONS
***************************************************************************/

/***************************************************************************
*                               PROTOTYPES
***************************************************************************/

/***************************************************************************
*                                FUNCTIONS
***************************************************************************/

/****************************************************************************
*   Function   : main
*   Description: This is the main function for this program, it demonstrates
*                the keypress function in comarison with the ANSI C getchar
*                function.  Keypress is demonstrated with and without echo
*                enabled.
*   Parameters : argc - number of parameters
*                argv - parameter list
*   Effects    : Creates specified file from specified inputs
*   Returned   : 0 for success, otherwise errno.
****************************************************************************/
int main (int argc, char *argv[])
{
    int c;

    /* argc and argv aren't used in this example */
    (void)argc;
    (void)argv;

    printf("getchar() example\n");
    printf("Press any key followed by <enter>: ");
    c = getchar();

    if (c != EOF)
    {
        printf("You pressed %c\n", c);

        /* consume any extra keys */
        while ((c != '\n') && (c != EOF))
        {
            c = getchar();
        }
    }
    else
    {
        perror("getchar");
        return errno;
    }

    printf("\nkeypress(KP_ECHO_ON) example\n");
    printf("Press any key: ");
    c = keypress(KP_ECHO_ON);

    if (c != EOF)
    {
        printf("\nYou should have seen %c\n", c);
    }
    else
    {
        perror("\nkeypress(KP_ECHO_ON)");
        return errno;
    }

    printf("\nkeypress(KP_ECHO_OFF) example\n");
    printf("Press any key");
    c = keypress(KP_ECHO_OFF);

    if (c != EOF)
    {
        printf("\nYou pressed %c\n", c);
    }
    else
    {
        perror("\nkeypress(KP_ECHO_OFF)");
        return errno;
    }

    return 0;
}
