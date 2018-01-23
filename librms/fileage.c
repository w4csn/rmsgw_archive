/*
 *			f i l e a g e . c
 * $Revision: 171 $
 * $Author: eckertb $
 *
 * RMS Gateway
 *
 * Copyright (c) 2004-2014 Hans-J. Barthen - DL5DI
 * Copyright (c) 2008-2014 Brian R. Eckert - W3SG
 *
 * Questions or problems regarding this program can be emailed
 * to linux-rmsgw@w3sg.org
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Description:
 *	determine the age of a file (in seconds)
 *	based on its atime
 */
#ifndef lint
static char svnid[] = "$Id: fileage.c 171 2014-10-19 10:00:22Z eckertb $";
#endif /* lint */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
#include <endian.h>
#include <syslog.h>
#include <errno.h>
#include <limits.h>

#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>


/***
 *  fileage(file)
 *
 *  file = file path to be checked
 *
 *  returns: age of file in seconds
 */
time_t fileage(char *the_file)
{
     struct stat st;
     time_t now;

     if (stat(the_file, &st) < 0) {
	  /* can't stat file, check why */
	  switch (errno) {
	  case ENOENT: /* file doesn't exist */
	       /*
		* proceed
		*/
	       st.st_mtime = (time_t) 0;
	       break;
	  default:
	       syslog(LOG_WARNING, "Can't stat %s (errno = %d)",
		      the_file, errno);
	       st.st_mtime = (time_t) 0;
	       break; /* pretend we're okay anyway */
	  }
     }

     /* compute age of file in seconds */
     time(&now);
     return ((time_t) (now - st.st_mtime));
}
