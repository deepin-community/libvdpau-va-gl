/*
 * Copyright 2013-2016  Rinat Ibragimov
 *
 * This file is part of libvdpau-va-gl
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#pragma once

#include <signal.h>
#include <sys/syscall.h>
#include <unistd.h>

#ifdef __FreeBSD__
#include <sys/thr.h>
#endif


#if defined(__linux__)

typedef int thread_id_t;

static inline thread_id_t
get_current_thread_id()
{
    return syscall(__NR_gettid);
}

static inline size_t
thread_is_alive(thread_id_t tid)
{
    return kill(tid, 0) == 0;
}

#elif defined(__FreeBSD__)

typedef long thread_id_t;

static inline thread_id_t
get_current_thread_id()
{
    long thread_id;
    thr_self(&thread_id);
    return thread_id;
}

static inline size_t
thread_is_alive(thread_id_t tid)
{
    return thr_kill(tid, 0) == 0;
}

#else
#error Unknown OS
#endif
