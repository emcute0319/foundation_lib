/* thread.h  -  Foundation library  -  Public Domain  -  2013 Mattias Jansson / Rampant Pixels
 *
 * This library provides a cross-platform foundation library in C11 providing basic support
 * data types and functions to write applications and games in a platform-independent fashion.
 * The latest source code is always available at
 *
 * https://github.com/rampantpixels/foundation_lib
 *
 * This library is put in the public domain; you can redistribute it and/or modify it without
 * any restrictions.
 */

#pragma once

/*! \file thread.h
\brief Threads

Thread management. If you use the foundation library in threads created by other
means than this thread interface you must remember to call #thread_finalize on thread
termination to avoid memory leaks.

Normal thread usage is to use the following flow:
<code>thread = thread_create(...);
thread_start(thread, data);
//...do other things...
//Optional if thread needs signal to terminate
//thread_terminate(thread);
thread_destroy(thread);</code> */

#include <foundation/platform.h>
#include <foundation/types.h>

/*! Create new thread.
\param fn Thread execution function
\param name Thread name
\param length Length of thread name
\param priority Thread priority
\param stacksize Thread stack size
\return New thread object */
FOUNDATION_API object_t
thread_create(thread_fn fn, const char* name, size_t length, thread_priority_t priority,
              unsigned int stacksize);

/*! Reference thread, explicitly increase the reference count of the thread object.
\param thread Thread
\return Object handle if thread object is still valid, 0 if thread object is no longer valid */
FOUNDATION_API object_t
thread_ref(object_t thread);

/*! Decrease reference count and destroy thread if it reaches zero (terminates the thread
if it is running). The destruction of the thread will block until thread terminates, then
joins the thread to free up system resources.
\param thread Thread */
FOUNDATION_API void
thread_destroy(object_t thread);

/*! Start a thread if it is not already running.
\param thread Thread
\param data Argument
\return true if thread was started, false if error or already running */
FOUNDATION_API bool
thread_start(object_t thread, void* data);

/*! Terminate thread execution.
\param thread Thread */
FOUNDATION_API void
thread_terminate(object_t thread);

/*! Query if thread is scheduled for termination.
\param thread Thread
\return true if thread should terminate, false if not (keep running) */
FOUNDATION_API bool
thread_should_terminate(object_t thread);

/*! Query if thread has been started.
\param thread Thread
\return true if started, false if not */
FOUNDATION_API bool
thread_is_started(object_t thread);

/*! Query if thread is running.
\param thread Thread
\return true if running, false if not */
FOUNDATION_API bool
thread_is_running(object_t thread);

/*! Query if object is a valid thread.
\param thread Thread object
\return true if a valid thread, false if not */
FOUNDATION_API bool
thread_is_thread(object_t thread);

/*! Query if calling thread is the main thread.
\return true if main thread, false if not */
FOUNDATION_API bool
thread_is_main(void);

/*! Mark the calling thread as the main thread */
FOUNDATION_API void
thread_set_main(void);

/*! Set name for calling thread.
\param name Thread name
\param length Length of thread name */
FOUNDATION_API void
thread_set_name(const char* name, size_t length);

/*! Set thread CPU core affinity for the calling thread.
\param mask CPU core mask for which the thread is allowed to execute on */
FOUNDATION_API void
thread_set_hardware(uint64_t mask);

/*! Get thread result (exit value).
\param thread Thread handle
\return Thread result */
FOUNDATION_API void*
thread_result(object_t thread);

/*! Get object handle for calling thread.
\return Thread object, null if not a foundation-created thread (like main application thread) */
FOUNDATION_API object_t
thread_self(void);

/*! Get name for calling thread.
\return Thread name */
FOUNDATION_API string_const_t
thread_name(void);

/*! Get calling thread system id.
\return Thread id */
FOUNDATION_API uint64_t
thread_id(void);

/*! Get the hardware thread the calling thread is running on.
\return Hardware thread id */
FOUNDATION_API unsigned int
thread_hardware(void);

/*! Sleep calling thread for specified time.
\param milliseconds Milliseconds to sleep */
FOUNDATION_API void
thread_sleep(unsigned int milliseconds);

/*! Yield calling thread remaining timeslice to other threads. */
FOUNDATION_API void
thread_yield(void);

/*! Finalize on thread exit and free thread local resources. */
FOUNDATION_API void
thread_finalize(void);

#if FOUNDATION_PLATFORM_ANDROID

/*! Android only. Attach the thread to the JVM to be able to do JVM calls through JNI.
Returns the JNI environment specific to the calling thread.
\return JNI environment (const struct JNINativeInterface**) for the calling thread,
        null if error */
FOUNDATION_API void*
thread_attach_jvm(void);

/*! Android only. Detach the thread from the JVM. No more calls to the JVM through JNI
can be made from this thread after a call to this function. */
FOUNDATION_API void
thread_detach_jvm(void);

#endif
