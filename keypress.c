/***************************************************************************
*                       Blocking Key Press Reading
*
*   File    : keypress.c
*   Purpose : Provide a POSIX compliant to sleep until a key is pressed
*   Author  : Michael Dipperstein
*   Date    : December 3, 2012
*
****************************************************************************
*
* Keypress: A POSIX compliant key press reading function
* Copyright (C) 2012, 2014 by
* Michael Dipperstein (mdipper@alumni.engr.ucsb.edu)
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
#include <termios.h>
#include <unistd.h>
#include "keypress.h"

/***************************************************************************
*                                FUNCTIONS
***************************************************************************/

/****************************************************************************
*   Function   : keypress
*   Description: This routine sleeps the current process until a key press
*                is registered on stdin.  The key press will be echoed to
*                stdout if it isn't disabled by the echo parameter.
*   Parameters : echo - set to KP_ECHO_OFF to disable echo of the pressed
*                       key.
*   Effects    : Sleep until key is read from stdin.
*   Returned   : The value of the key pressed or EOF.  EOF is returned for
*                End of File or error.  In the event of an error, errno will
*                also be set.
****************************************************************************/
int keypress(const kp_echo_t echo)
{
    struct termios savedState;
    struct termios newState;
    unsigned char echo_bit;     /* enable/disable echo.  logic is reversed */
    int c;

    if (-1 == tcgetattr(STDIN_FILENO, &savedState))
    {
        return EOF;             /* error on tcgetattr */
    }

    newState = savedState;

    if (KP_ECHO_OFF == echo)
    {
        echo_bit = ECHO;        /* echo bit set to disable echo */
    }
    else
    {
        echo_bit = 0;           /* echo bit cleared to enable echo */
    }

    /* use canonical input and set echo.  set minimal input to 1. */
    newState.c_lflag &= ~(echo_bit | ICANON);
    newState.c_cc[VMIN] = 1;

    if (-1 == tcsetattr(STDIN_FILENO, TCSANOW, &newState))
    {
        return EOF;             /* error on tcsetattr */
    }

    c = getchar();      /* block (without spinning) until we get a key press */

    /* restore the saved state */
    if (-1 == tcsetattr(STDIN_FILENO, TCSANOW, &savedState))
    {
        return EOF;             /* error on tcsetattr */
    }

    return c;
}
