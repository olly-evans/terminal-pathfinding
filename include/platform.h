#ifndef PLATFORM_H
#define PLATFORM_H

#ifdef _WIN32
    /* Windows includes */
    #include <windows.h>
    #include <io.h>
    #include <stdio.h>

    /* Standard output file descriptor on Windows */
    #define STDOUT_FILENO 1

    /* Windows write - uses _write for console output */
    #define platform_write(fd, buf, count) _write(fd, buf, (unsigned int)(count))

    /* Windows sleep in milliseconds */
    static inline void platform_sleep_ms(int milliseconds) {
        Sleep((DWORD)milliseconds);
    }

#else
    /* POSIX includes */
    #include <unistd.h>
    #include <time.h>

    #define platform_write(fd, buf, count) write(fd, buf, count)

    /* POSIX sleep in milliseconds */
    static inline void platform_sleep_ms(int milliseconds) {
        struct timespec ts;
        ts.tv_sec = milliseconds / 1000;
        ts.tv_nsec = (milliseconds % 1000) * 1000000;
        nanosleep(&ts, NULL);
    }

#endif
#endif