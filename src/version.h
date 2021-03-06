/*
 * Copyright © 2013 Intel Corporation
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that copyright
 * notice and this permission notice appear in supporting documentation, and
 * that the name of the copyright holders not be used in advertising or
 * publicity pertaining to distribution of the software without specific,
 * written prior permission.  The copyright holders make no representations
 * about the suitability of this software for any purpose.  It is provided "as
 * is" without express or implied warranty.
 *
 * THE COPYRIGHT HOLDERS DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
 * EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
 * OF THIS SOFTWARE.
 */

#ifndef WESTON_VERSION_H
#define WESTON_VERSION_H

#define WESTON_VERSION_MAJOR 1
#define WESTON_VERSION_MINOR 8
#define WESTON_VERSION_MICRO 0
#define WESTON_VERSION "1.8.0"

/* This macro may not do what you expect.  Weston doesn't guarantee
 * a stable API between 1.X and 1.Y, and thus this macro will return
 * FALSE on any WESTON_VERSION_AT_LEAST(1,X,0) if the actual version
 * is 1.Y.0 and X != Y).  In particular, it fails if X < Y, that is,
 * 1.3.0 is considered to not be "at least" 1.4.0.
 *
 * If you want to test for the version number being 1.3.0 or above or
 * maybe in a range (eg 1.2.0 to 1.4.0), just use the WESTON_VERSION_*
 * defines above directly.
 */

#define WESTON_VERSION_AT_LEAST(major, minor, micro) \
        (WESTON_VERSION_MAJOR == (major) && \
         WESTON_VERSION_MINOR == (minor) && \
         WESTON_VERSION_MICRO >= (micro))

#endif
