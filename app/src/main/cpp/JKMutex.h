//
// Created by android on 18-12-18.
//

#ifndef FUCKCPP_JKMUTEX_H
#define FUCKCPP_JKMUTEX_H


#include <stdint.h>
#include <sys/types.h>
#include <time.h>

# include <pthread.h>


// ---------------------------------------------------------------------------
namespace jkframework {
// ---------------------------------------------------------------------------

    class Condition;

/*
 * NOTE: This class is for code that builds on Win32.  Its usage is
 * deprecated for code which doesn't build for Win32.  New code which
 * doesn't build for Win32 should use std::mutex and std::lock_guard instead.
 *
 * Simple mutex class.  The implementation is system-dependent.
 *
 * The mutex must be unlocked by the thread that locked it.  They are not
 * recursive, i.e. the same thread can't lock it multiple times.
 */
    class JKMutex {
    public:
        enum {
            PRIVATE = 0,
            SHARED = 1
        };

        JKMutex();
        explicit    JKMutex(const char* name);
        explicit    JKMutex(int type, const char* name = NULL);
        ~JKMutex();

        // lock or unlock the mutex
        int    lock();
        void        unlock();

        // lock if possible; returns 0 on success, error otherwise
        int    tryLock();

        // Manages the mutex automatically. It'll be locked when Autolock is
        // constructed and released when Autolock goes out of scope.
        class Autolock {
        public:
            inline explicit Autolock(JKMutex& mutex) : mLock(mutex)  { mLock.lock(); }
            inline explicit Autolock(JKMutex* mutex) : mLock(*mutex) { mLock.lock(); }
            inline ~Autolock() { mLock.unlock(); }
        private:
            JKMutex& mLock;
        };

    private:
        friend class Condition;

        // A mutex cannot be copied
        JKMutex(const JKMutex&);
        JKMutex&      operator = (const JKMutex&);

        pthread_mutex_t mMutex;
    };

// ---------------------------------------------------------------------------


    inline JKMutex::JKMutex() {
        pthread_mutex_init(&mMutex, NULL);
    }
    inline JKMutex::JKMutex(__attribute__((unused)) const char* name) {
        pthread_mutex_init(&mMutex, NULL);
    }
    inline JKMutex::JKMutex(int type, __attribute__((unused)) const char* name) {
        if (type == SHARED) {
            pthread_mutexattr_t attr;
            pthread_mutexattr_init(&attr);
            pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);
            pthread_mutex_init(&mMutex, &attr);
            pthread_mutexattr_destroy(&attr);
        } else {
            pthread_mutex_init(&mMutex, NULL);
        }
    }
    inline JKMutex::~JKMutex() {
        pthread_mutex_destroy(&mMutex);
    }
    inline int JKMutex::lock() {
        return -pthread_mutex_lock(&mMutex);
    }
    inline void JKMutex::unlock() {
        pthread_mutex_unlock(&mMutex);
    }
    inline int JKMutex::tryLock() {
        return -pthread_mutex_trylock(&mMutex);
    }


// ---------------------------------------------------------------------------

/*
 * Automatic mutex.  Declare one of these at the top of a function.
 * When the function returns, it will go out of scope, and release the
 * mutex.
 */

    typedef JKMutex::Autolock AutoMutex;

// ---------------------------------------------------------------------------
}; // namespace android
// ---------------------------------------------------------------------------




#endif //FUCKCPP_JKMUTEX_H
