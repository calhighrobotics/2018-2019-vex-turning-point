#ifndef MUTEXVAR_HPP
#define MUTEXVAR_HPP

#include <API.h>

/**
 * Value container that guards against concurrent modification using a mutex.
 * @tparam T Contained type.
 */
template<typename T>
class MutexVar
{
public:
    MutexVar(): value{}, mutex{ nullptr } {}
    MutexVar(T value): value{ value }, mutex{ nullptr } {}

    /** Initializes the mutex. Should be called after/around `initialize()`. */
    void init()
    {
        mutex = mutexCreate();
    }

    /** Converts this MutexVar to its contained type. */
    operator T() const
    {
        if (!mutex) return T{};
        mutexTake(mutex, 0);
        T result = value;
        mutexGive(mutex);
        return result;
    }

    /** Assigns a new value. */
    MutexVar& operator=(T newValue)
    {
        if (mutex)
        {
            mutexTake(mutex, 0);
            value = newValue;
            mutexGive(mutex);
        }
        return *this;
    }

private:
    /** Contained value. */
    T value;
    /** Mutex that protects this value. */
    Mutex mutex;
};

#endif // MUTEXVAR_HPP
