#include "defines.h"

/**
 * @brief Internal Private Function, not to be used by the students.
 */
int __semGet( int nrSemaforos, int semFlags ) {
    int semId = semget( IPC_KEY, nrSemaforos, semFlags );
    if ( semId < 0 ) {
        so_debug( "Could not create/open the Semaphores Group with key=0x%x", IPC_KEY );
    } else {
        so_debug( "Using the Semaphores Group with key=0x%x and id=%d", IPC_KEY, semId );
    }
    return semId;
}

/**
 * @brief Creates an IPC Semaphores Group non-exclusively, associated with the IPC_KEY, with the passed number of Semaphores
 *
 * @param nrElements Number of Semaphores of the Group
 * @return int semId. In case of error, returns -1
 */
int semCreate( int nrElements ) {
    return __semGet( nrElements, IPC_CREAT | 0666 );
}

/**
 * @brief Opens an already created IPC Semaphores Group associated with the IPC_KEY
 *
 * @return int semId. In case of error, returns -1
 */
int semGet() {
    return __semGet( 0, 0 );
}

/**
 * @brief Removes the IPC Semaphores Group associated with the IPC_KEY
 *
 * @param semId IPC SemId
 * @return int 0 if success or if the Semaphores Group already did not exist, or -1 if the Semaphores Group exists and could not be removed
 */
int semRemove( int semId ) {
    // Ignore any errors here, as this is only to check if the semaphore group exists and remove it
    if ( semId > 0 ) {
        // If the semaphore group with IPC_KEY already exists, remove it.
        int result = semctl( semId, 0, IPC_RMID, 0 );
        if ( result < 0) {
            so_debug( "Could not remove the Semaphores Group with key=0x%x and id=%d", IPC_KEY, semId );
        } else {
            so_debug( "Removed the Semaphores Group with key=0x%x and id=%d", IPC_KEY, semId );
        }
        return result;
    }
    return 0;
}

/**
 * @brief Sets the value of the Semaphore semNr of the Semaphore Group associated with IPC_KEY
 *
 * @param semId IPC SemId
 * @param semNr Index of the Semaphore to set value (starting in 0)
 * @param value Value to be defined in the Semaphore semNr
 * @return int success
 */
int semNrSetValue( int semId, int semNr, int value ) {
    int result = semctl( semId, semNr, SETVAL, value );
    if ( result < 0) {
        so_debug( "Could not set the value of the Semaphore %d of this Semaphore Group", semNr );
    } else {
        so_debug( "The Semaphore %d of this Semaphore Group was set with value %d", semNr, value );
    }
    return result;
}

/**
 * @brief Sets the value of the Semaphore 0 of the Semaphore Group associated with IPC_KEY
 *
 * @param semId IPC SemId
 * @param value Value to be defined in the Semaphore semNr
 * @return int success
 */
int semSetValue( int semId, int value ) {
    return semNrSetValue( semId, 0, value );
}

/**
 * @brief Gets the value of the Semaphore semNr of the Semaphore Group associated with IPC_KEY
 *
 * @param semId IPC SemId
 * @param semNr Index of the Semaphore to set value (starting in 0)
 * @return int Value of the Semaphore, or -1 in case of error
 */
int semNrGetValue( int semId, int semNr ) {
    int result = semctl( semId, semNr, GETVAL, 0 );
    if ( result < 0 ) {
        so_debug( "Could not get the value of the Semaphore %d of this Semaphore Group", semNr );
    } else {
        so_debug( "The Semaphore %d of this Semaphore Group has the value %d", semNr, result );
    }
    return result;
}

/**
 * @brief Gets the value of the Semaphore 0 of the Semaphore Group associated with IPC_KEY
 *
 * @param semId IPC SemId
 * @return int Value of the Semaphore, or -1 in case of error
 */
int semGetValue( int semId ) {
    return semNrGetValue( semId, 0 );
}

/**
 * @brief Adds a value to the current value the Semaphore semNr of the Semaphore Group associated with IPC_KEY
 *
 * @param semId IPC SemId
 * @param semNr Index of the Semaphore to set value (starting in 0)
 * @param value Value to be added to the value of the Semaphore semNr
 * @return int success
 */
int semNrAddValue( int semId, int semNr, int addValue ) {
    int result = semctl( semId, semNr, GETVAL, 0 );
    so_exit_on_error( result, "Error on semctl" );
    so_debug( "The Semaphore %d of this Semaphore Group had the value %d", semNr, result );

    struct sembuf operation = { semNr, addValue, 0 };
    result = semop( semId, &operation, 1 );

    if ( result < 0 ) {
        so_debug( "Could not add the value %d to the value of the Semaphore %d of this Semaphore Group", addValue, semNr );
    } else {
        result = semctl( semId, semNr, GETVAL, 0 );
        so_exit_on_error( result, "Error on semctl" );
        so_debug( "The Semaphore %d of this Semaphore Group now has the value %d", semNr, result );
    }
    return result;
}

/**
 * @brief Adds a value to the current value the Semaphore 0 of the Semaphore Group associated with IPC_KEY
 *
 * @param semId IPC SemId
 * @param value Value to be added to the value of the Semaphore semNr
 * @return int success
 */
int semAddValue( int semId, int addValue ) {
    return semNrAddValue( semId, 0, addValue );
}

/**
 * @brief Adds 1 (one) to the current value the Semaphore semNr of the Semaphore Group associated with IPC_KEY
 *
 * @param semId IPC SemId
 * @param semNr Index of the Semaphore to set value (starting in 0)
 * @return int success
 */
int semNrUp( int semId, int semNr ) {
    return semNrAddValue( semId, semNr, 1 );
}

/**
 * @brief Adds -1 (minus one) to the current value the Semaphore semNr of the Semaphore Group associated with IPC_KEY
 *
 * @param semId IPC SemId
 * @param semNr Index of the Semaphore to set value (starting in 0)
 * @return int success
 */
int semNrDown( int semId, int semNr ) {
    return semNrAddValue( semId, semNr, -1 );
}

/**
 * @brief Adds 1 (one) to the current value the Semaphore 0 of the Semaphore Group associated with IPC_KEY
 *
 * @param semId IPC SemId
 * @return int success
 */
int semUp( int semId ) {
    return semAddValue( semId, 1 );
}

/**
 * @brief Adds -1 (minus one) to the current value the Semaphore 0 of the Semaphore Group associated with IPC_KEY
 *
 * @param semId IPC SemId
 * @return int success
 */
int semDown( int semId ) {
    return semAddValue( semId, -1 );
}