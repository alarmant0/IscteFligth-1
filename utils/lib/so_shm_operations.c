#include "common.h"
#include "utils.h"

/**
 * @brief Internal Private Function, not to be used by the students.
 */
int __shmGet( int nrElements, int shmFlags ) {
    int shmId = shmget( IPC_KEY, nrElements * sizeof(Aluno), shmFlags );
    if ( shmId < 0 ) {
        debug( "Could not create/open the Shared Memory with key=0x%x", IPC_KEY );
    } else {
        debug( "Using the Shared Memory with key=0x%x and id=%d", IPC_KEY, shmId );
    }
    return shmId;
}

/**
 * @brief Creates an IPC Shared Memory exclusively, associated with the IPC_KEY, of an array of size multiple of sizeof(Aluno)
 * 
 * @param nrElements Size of the array
 * @return int shmId. In case of error, returns -1
 */
int shmCreate( int nrElements ) {
    return __shmGet( nrElements, IPC_CREAT | IPC_EXCL | 0600 );
}

/**
 * @brief Opens an already created IPC Shared Memory associated with the IPC_KEY
 * 
 * @return int shmId. In case of error, returns -1
 */
int shmGet() {
    return __shmGet( 0, 0 );
}

/**
 * @brief Removes the IPC Shared Memory associated with the IPC_KEY
 * 
 * @return int 0 if success or if the Shared Memory already did not exist, or -1 if the Shared Memory exists and could not be removed
 */
int shmRemove() {
    int shmId = shmGet();
    // Ignore any errors here, as this is only to check if the shared memory exists and remove it
    if ( shmId > 0 ) {
        // If the shared memory with IPC_KEY already exists, remove it
        int result = shmctl( shmId, IPC_RMID, 0 );
        if ( result < 0) {
            debug( "Could not remove the Shared Memory with key=0x%x and id=%d", IPC_KEY, shmId );
        } else {
            debug( "Removed the Shared Memory with key=0x%x and id=%d", IPC_KEY, shmId );
        }
        return result;
    }
    return 0;
}

/**
 * @brief Attaches a shared memory associated with shmId with a local address
 * 
 * @param shmId Id of the Shared Memory
 * @return Aluno* 
 */
Aluno* shmAttach( int shmId ) {
    Aluno* array = (Aluno*) shmat( shmId, 0, 0 );
    if ( NULL == array ) {
        debug( "Could not Attach the Shared Memory with id=%d", shmId );
    } else {
        debug( "The Shared Memory with id=%d was Attached on the local address %p", shmId, array );
    }
    return array;
}

/**
 * @brief Detaches a shared memory attached at the passed local address
 * 
 * @param shm local address of the Shared Memory
 * @return success
 */
int shmDetach( Aluno* shm ) {
    int result = shmdt( shm );
    if ( result < 0 ) {
        debug( "Could not detach the Shared Memory attached on the local address %p", shm );
    } else {
        debug( "Detached the Shared Memory attached on the local address %p", shm );
    }
    return result;
}

/**
 * @brief Initiates the Shared Memory with default values
 * 
 * @param shm local address of the Shared Memory
 * @param nrElements Number of elements of the shared memory
 */
void shmInit( Aluno* shm, int nrElements ) {
    for ( int i = 0; i < nrElements; ++i ) {
        shm[i].numero = -1;
        strcpy( shm[i].nome, "[sem nada]" );
        shm[i].nota = 0.0;
    }
}

/**
 * @brief Displays the values of the shared memory
 *
 * @param shm Shared Memory
 * @param nrElements Number of elements of the shared memory
 * @param ignoreInvalid Do not display the elements that have the default value
 */
void shmView( Aluno* shm, int nrElements, int ignoreInvalid ) {
    debug( "Contents of the Shared Memory:" );
    for ( int i = 0; i < nrElements; ++i ) {
        if ( !ignoreInvalid || -1 != shm[i].numero ) {
            printf( "Index %2d: %6d | %-99s | %2.3f\n", i, shm[i].numero, shm[i].nome, shm[i].nota );
        }
    }
}

/**
 * @brief Asks the user about the information to fill a structure Aluno
 * 
 * @return Aluno 
 */
Aluno obter_dados_aluno() {
    Aluno a;

    printf("Diga o Número do aluno: ");
    scanf("%d", &a.numero);
	getchar();

    printf("Diga o Nome do aluno: ");
    my_gets(a.nome, 99);

    printf("Diga a Nota do aluno: ");
    scanf("%f", &a.nota);
	getchar();
 
    return a;   
}

/**
 * @brief Inserts a new Aluno in the shared memory if possible
 * 
 * @param shm Shared Memory
 * @param nrAlunos Number of elements of the shared memory
 * @param a Aluno to be inserted
 * @return int The index of the shared memory where the new Aluno was inserted or -1 if the shared memory is already full
 */
int registar_aluno( Aluno *shm, int nrAlunos, Aluno a ) {
    int i;
    for( i = 0; i < nrAlunos; ++i ) {
        if ( -1 == shm[i].numero ) {
            debug( "A inserir o aluno na posição %d", i );
            shm[i] = a;
            break;
        }
    }
    return i < nrAlunos ? i : -1;  // Registou aluno? retorna o índice, senão retorna -1
}