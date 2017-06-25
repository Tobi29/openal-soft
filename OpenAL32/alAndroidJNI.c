
#include <AL/al.h>
#include <AL/alc.h>

#include <jni.h>

#include <stdlib.h>
#include <string.h>

#define logV(...)
#define logE(...)

static ALCdevice* device = NULL;
static ALCcontext* context = NULL;

// This function must be called once, before calling other AL functions:
JNIEXPORT jboolean JNICALL Java_paulscode_android_sound_ALAN_create( JNIEnv* env, jclass klass, jintArray context_attribs )
{
    logV( "Starting up ALAN..." );
    logV( "    Opening Android audio device" );
    device = alcOpenDevice( NULL );
    if( !device )
    {
        logE( "    Failed to open Android audio device!" );
        return JNI_FALSE;
    }

    logV( "    Creating AL context" );
    jint *elements;
    if( context_attribs )
        elements = (*env)->GetIntArrayElements( env, context_attribs, NULL );
    else
        elements = NULL;
    context = alcCreateContext( device, (const ALint *) elements );
    if( context_attribs )
        (*env)->ReleaseIntArrayElements( env, context_attribs, elements, 0 );

    if( !context )
    {
        logE( "    Failed to create AL context!" );
        if( device )
            alcCloseDevice( device );
        return JNI_FALSE;
    }
    alcMakeContextCurrent( context );
    logV( "ALAN lives! (MWAHAHAhahahaha...)" );
	logV( "    Author: Paul Lamb, www.paulscode.com" );
    return JNI_TRUE;
}

// This function must be called before shutting down the app:
JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_destroy( JNIEnv* env, jclass klass )
{
	logV( "Shutting down ALAN" );
	logV( "    Destroying AL context" );
    if( context )
    {
        alcMakeContextCurrent( NULL );
        alcDestroyContext( context );
    }
    
    logV( "    Closing Android audio device" );
    if( device )
        alcCloseDevice( device );

	logV( "ALAN was destroyed (NOOOOOooooo...)" );
	logV( "    Author: Paul Lamb, www.paulscode.com" );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alAuxiliaryEffectSlotf( JNIEnv* env, jclass klass, jint asid, jint param, jfloat value )
{
    alAuxiliaryEffectSlotf( (ALuint) asid, (ALenum) param, (ALfloat) value );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alAuxiliaryEffectSlotfv( JNIEnv* env, jclass klass, jint asid, jint param, jfloatArray values )
{
    jfloat *elements = (*env)->GetFloatArrayElements( env, values, NULL );  // array is copied or pinned.. WTF, I can't specify which?!
    alAuxiliaryEffectSlotfv( (ALuint) asid, (ALenum) param, (ALfloat *) elements );
    (*env)->ReleaseFloatArrayElements( env, values, elements, 0 );  // commit any changes, free the copy if it exists
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alAuxiliaryEffectSloti( JNIEnv* env, jclass klass, jint asid, jint param, jint value )
{
    alAuxiliaryEffectSloti( (ALuint) asid, (ALenum) param, (ALint) value );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alAuxiliaryEffectSlotiv( JNIEnv* env, jclass klass, jint asid, jint param, jintArray values )
{
    jint *elements = (*env)->GetIntArrayElements( env, values, NULL );
    alAuxiliaryEffectSlotiv( (ALuint) asid, (ALenum) param, (ALint *) elements );
    (*env)->ReleaseIntArrayElements( env, values, elements, 0 );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alBuffer3f( JNIEnv* env, jclass klass, jint bid, jint param, jfloat value1, jfloat value2, jfloat value3 )
{
    alBuffer3f( (ALuint) bid, (ALenum) param, (ALfloat) value1, (ALfloat) value2, (ALfloat) value3 );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alBuffer3i( JNIEnv* env, jclass klass, jint bid, jint param, jint value1, jint value2, jint value3 )
{
    alBuffer3i( (ALuint) bid, (ALenum) param, (ALint) value1, (ALint) value2, (ALint) value3 );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alBufferData( JNIEnv* env, jclass klass, jint bid, jint format, jbyteArray data, jint size, jint freq )
{
/*
	// Check if there is already a buffer referenced by 'bid'.  If so, release that byte array back to Java.
	linkedlist *oldLink = removeHashBuffer( bid );
	if( oldLink )
	{
logV( "found a copy of 'bid' in the bufferMap" );
		jbyteArray *oldData = oldLink->data;
		jbyte *oldBuffer = oldLink->buffer;
logV( "    releasing the elements" );
		if( oldData != NULL && oldBuffer != NULL )
			(*env)->ReleaseByteArrayElements( env, *oldData, oldBuffer, JNI_ABORT );
//logV( "    freeing old buffer" );
//		free( oldBuffer );
logV( "    freeing old link" );
		free( oldLink );
logV( "    done with that copy of 'bid'" );
	}
*/
    // So.. tell me again why I can't specify if the data should be copied or pinned?  
    jbyte *buffer = (*env)->GetByteArrayElements( env, data, NULL );  
    alBufferData( (ALuint) bid, (ALenum) format, (const ALvoid *) buffer, (ALsizei) size, (ALsizei) freq );
	(*env)->ReleaseByteArrayElements( env, data, buffer, JNI_ABORT );
/*
    // Can't release this array back to Java here, because it might be pinned.  Remember to call alDeleteBuffers, people!

    // Store the jbyteArray and buffer so the array can be released back to Java later:
    addHashBuffer( bid, data, buffer );
*/
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alBufferf( JNIEnv* env, jclass klass, jint bid, jint param, jfloat value )
{
    alBufferf( (ALuint) bid, (ALenum) param, (ALfloat) value ); 
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alBufferfv( JNIEnv* env, jclass klass, jint bid, jint param, jfloatArray values )
{
    jfloat *elements = (*env)->GetFloatArrayElements( env, values, NULL );
    alBufferfv( (ALuint) bid, (ALenum) param, (const ALfloat *) elements );
    (*env)->ReleaseFloatArrayElements( env, values, elements, 0 );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alBufferi( JNIEnv* env, jclass klass, jint bid, jint param, jint value )
{
    alBufferi( (ALuint) bid, (ALenum) param, (ALint) value); 
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alBufferiv( JNIEnv* env, jclass klass, jint bid, jint param, jintArray values )
{
    jint *elements = (*env)->GetIntArrayElements( env, values, NULL );
    alBufferiv( (ALuint) bid, (ALenum) param, (const ALint *) elements );
    (*env)->ReleaseIntArrayElements( env, values, elements, 0 );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alDeleteAuxiliaryEffectSlots( JNIEnv* env, jclass klass, jint n, jintArray slots )
{
    jint *elements = (*env)->GetIntArrayElements( env, slots, NULL );
    alDeleteAuxiliaryEffectSlots( (ALsizei) n, (ALuint *) elements ); 
    (*env)->ReleaseIntArrayElements( env, slots, elements, 0 );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alDeleteBuffers( JNIEnv* env, jclass klass, jint n, jintArray buffers )
{
    jint *elements = (*env)->GetIntArrayElements( env, buffers, NULL );
    alDeleteBuffers( (ALsizei) n, (const ALuint *) elements );
/*
    // Iterate through the buffers, and release their associated arrays back to Java (in case they're pinned):
    int arrayLength = (*env)->GetArrayLength( env, buffers );
    jint bid;
    jint *element = elements;
    int x;
    for( x = 0; x < arrayLength; x++ )
    {
    	linkedlist *oldLink = removeHashBuffer( (jint) *(element++) );
    	if( oldLink )
    	{
logV( "Removing deleted buffer from list" );
    		jbyteArray *data = oldLink->data;
			jbyte *buffer = oldLink->buffer;
logV( "    removing array elements" );
			if( data != NULL && buffer != NULL )
				(*env)->ReleaseByteArrayElements( env, *data, buffer, JNI_ABORT );
//logV( "    freeing buffer" );
//			free( buffer );
logV( "    freeing old link" );
			free( oldLink );
logV( "    done removing deleted buffer from the list" );
       	}
    }
*/
    (*env)->ReleaseIntArrayElements( env, buffers, elements, 0 );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alDeleteEffects( JNIEnv* env, jclass klass, jint n, jintArray effects )
{
    jint *elements = (*env)->GetIntArrayElements( env, effects, NULL );
    alDeleteEffects( (ALsizei) n, (ALuint *) elements );
    (*env)->ReleaseIntArrayElements( env, effects, elements, 0 );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alDeleteFilters( JNIEnv* env, jclass klass, jint n, jintArray filters )
{
    jint *elements = (*env)->GetIntArrayElements( env, filters, NULL );
    alDeleteFilters( (ALsizei) n, (ALuint *) elements );
    (*env)->ReleaseIntArrayElements( env, filters, elements, 0 );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alDeleteSources( JNIEnv* env, jclass klass, jint n, jintArray sources )
{
    jint *elements = (*env)->GetIntArrayElements( env, sources, NULL );
    alDeleteSources( (ALsizei) n, (const ALuint *) elements );
    (*env)->ReleaseIntArrayElements( env, sources, elements, 0 );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alDisable( JNIEnv* env, jclass klass, jint capability )
{
    alDisable( (ALenum) capability );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alDistanceModel( JNIEnv* env, jclass klass, jint distanceModel )
{
    alDistanceModel( (ALenum) distanceModel );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alDopplerFactor( JNIEnv* env, jclass klass, jfloat value )
{
    alDopplerFactor( (ALfloat) value );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alDopplerVelocity( JNIEnv* env, jclass klass, jfloat value )
{
    alDopplerVelocity( (ALfloat) value );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alEffectf( JNIEnv* env, jclass klass, jint eid, jint param, jfloat value )
{
    alEffectf( (ALuint) eid, (ALenum) param, (ALfloat) value);
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alEffectfv( JNIEnv* env, jclass klass, jint eid, jint param, jfloatArray values )
{
    jfloat *elements = (*env)->GetFloatArrayElements( env, values, NULL );
    alEffectfv( (ALuint) eid, (ALenum) param, (ALfloat *) elements );
    (*env)->ReleaseFloatArrayElements( env, values, elements, 0 );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alEffecti( JNIEnv* env, jclass klass, jint eid, jint param, jint value )
{
    alEffecti( (ALuint) eid, (ALenum) param, (ALint) value );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alEffectiv( JNIEnv* env, jclass klass, jint eid, jint param, jintArray values )
{
    jint *elements = (*env)->GetIntArrayElements( env, values, NULL );
    alEffectiv( (ALuint) eid, (ALenum) param, (ALint) * elements );
    (*env)->ReleaseIntArrayElements( env, values, elements, 0 );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alEnable( JNIEnv* env, jclass klass, jint capability )
{
    alEnable( (ALenum) capability );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alFilterf( JNIEnv* env, jclass klass, jint fid, jint param, jfloat value )
{
    alFilterf( (ALuint) fid, (ALenum) param, (ALfloat) value );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alFilterfv( JNIEnv* env, jclass klass, jint fid, jint param, jfloatArray values )
{
    jfloat *elements = (*env)->GetFloatArrayElements( env, values, NULL );
    alFilterfv( (ALuint) fid, (ALenum) param, (ALfloat *) elements );
    (*env)->ReleaseFloatArrayElements( env, values, elements, 0 );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alFilteri( JNIEnv* env, jclass klass, jint fid, jint param, jint value )
{
    alFilteri( (ALuint) fid, (ALenum) param, (ALint) value );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alFilteriv( JNIEnv* env, jclass klass, jint fid, jint param, jintArray values )
{
    jint *elements = (*env)->GetIntArrayElements( env, values, NULL );
    alFilteriv( (ALuint) fid, (ALenum) param, (ALint *) elements );
    (*env)->ReleaseIntArrayElements( env, values, elements, 0 );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alGenAuxiliaryEffectSlots( JNIEnv* env, jclass klass, jint n, jintArray slots )
{
    jint *elements = (*env)->GetIntArrayElements( env, slots, NULL );
    alGenAuxiliaryEffectSlots( (ALsizei) n, (ALuint *) elements );
    (*env)->ReleaseIntArrayElements( env, slots, elements, 0 );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alGenBuffers( JNIEnv* env, jclass klass, jint n, jintArray buffers )
{
    jint *elements = (*env)->GetIntArrayElements( env, buffers, NULL );
    alGenBuffers( (ALsizei) n, (ALuint *) elements );
    (*env)->ReleaseIntArrayElements( env, buffers, elements, 0 );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alGenEffects( JNIEnv* env, jclass klass, jint n, jintArray effects )
{
    jint *elements = (*env)->GetIntArrayElements( env, effects, NULL );
    alGenEffects( (ALsizei) n, (ALuint *) elements );
    (*env)->ReleaseIntArrayElements( env, effects, elements, 0 );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alGenFilters( JNIEnv* env, jclass klass, jint n, jintArray filters )
{
    jint *elements = (*env)->GetIntArrayElements( env, filters, NULL );
    alGenFilters( (ALsizei) n, (ALuint *) elements );
    (*env)->ReleaseIntArrayElements( env, filters, elements, 0 );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alGenSources( JNIEnv* env, jclass klass, jint n, jintArray sources )
{
    jint *elements = (*env)->GetIntArrayElements( env, sources, NULL );
    alGenSources( (ALsizei) n, (ALuint *) elements );
    (*env)->ReleaseIntArrayElements( env, sources, elements, 0 );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alGetAuxiliaryEffectSlotf( JNIEnv* env, jclass klass, jint asid, jint pname, jfloatArray value )
{
    jfloat *elements = (*env)->GetFloatArrayElements( env, value, NULL );
    alGetAuxiliaryEffectSlotf( (ALuint) asid, (ALenum) pname, (ALfloat *) elements );
    (*env)->ReleaseFloatArrayElements( env, value, elements, 0 );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alGetAuxiliaryEffectSlotfv( JNIEnv* env, jclass klass, jint asid, jint pname, jfloatArray values )
{
    jfloat *elements = (*env)->GetFloatArrayElements( env, values, NULL );
    alGetAuxiliaryEffectSlotfv( (ALuint) asid, (ALenum) pname, (ALfloat *) elements );
    (*env)->ReleaseFloatArrayElements( env, values, elements, 0 );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alGetAuxiliaryEffectSloti( JNIEnv* env, jclass klass, jint asid, jint pname, jintArray value )
{
    jint *elements = (*env)->GetIntArrayElements( env, value, NULL );
    alGetAuxiliaryEffectSloti( (ALuint) asid, (ALenum) pname, (ALint *) elements );
    (*env)->ReleaseIntArrayElements( env, value, elements, 0 );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alGetAuxiliaryEffectSlotiv( JNIEnv* env, jclass klass, jint asid, jint pname, jintArray values )
{
    jint *elements = (*env)->GetIntArrayElements( env, values, NULL );
    alGetAuxiliaryEffectSlotiv( (ALuint) asid, (ALenum) pname, (ALint *) elements );
    (*env)->ReleaseIntArrayElements( env, values, elements, 0 );
}

JNIEXPORT jboolean JNICALL Java_paulscode_android_sound_ALAN_alGetBoolean( JNIEnv* env, jclass klass, jint param )
{
    return( (alGetBoolean( (ALenum) param ) == AL_TRUE) ? JNI_TRUE : JNI_FALSE );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alGetBooleanv( JNIEnv* env, jclass klass, jint param, jbooleanArray data )
{
    jboolean *elements = (*env)->GetBooleanArrayElements( env, data, NULL );
    alGetBooleanv( (ALenum) param, (ALboolean *) elements );  // Should work, since ALboolean and jboolean are both 8-bit
    (*env)->ReleaseBooleanArrayElements( env, data, elements, 0 );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alGetBuffer3f( JNIEnv* env, jclass klass, jint bid, jint param, jfloatArray value1, jfloatArray value2, jfloatArray value3 )
{
    jfloat *elements1 = (*env)->GetFloatArrayElements( env, value1, NULL );
    jfloat *elements2 = (*env)->GetFloatArrayElements( env, value2, NULL );
    jfloat *elements3 = (*env)->GetFloatArrayElements( env, value3, NULL );
    alGetBuffer3f( (ALuint) bid, (ALenum) param, (ALfloat *) elements1, (ALfloat *) elements2, (ALfloat *) elements3);
    (*env)->ReleaseFloatArrayElements( env, value1, elements1, 0 );
    (*env)->ReleaseFloatArrayElements( env, value2, elements2, 0 );
    (*env)->ReleaseFloatArrayElements( env, value3, elements3, 0 );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alGetBuffer3i( JNIEnv* env, jclass klass, jint bid, jint param, jintArray value1, jintArray value2, jintArray value3 )
{
    jint *elements1 = (*env)->GetIntArrayElements( env, value1, NULL );
    jint *elements2 = (*env)->GetIntArrayElements( env, value2, NULL );
    jint *elements3 = (*env)->GetIntArrayElements( env, value3, NULL );
    alGetBuffer3i( (ALuint) bid, (ALenum) param, (ALint *) elements1, (ALint *) elements2, (ALint *) elements3 );
    (*env)->ReleaseIntArrayElements( env, value1, elements1, 0 );
    (*env)->ReleaseIntArrayElements( env, value2, elements2, 0 );
    (*env)->ReleaseIntArrayElements( env, value3, elements3, 0 );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alGetBufferf( JNIEnv* env, jclass klass, jint bid, jint param, jfloatArray value )
{
    jfloat *elements = (*env)->GetFloatArrayElements( env, value, NULL );
    alGetBufferf( (ALuint) bid, (ALenum) param, (ALfloat *) elements );
    (*env)->ReleaseFloatArrayElements( env, value, elements, 0 );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alGetBufferfv( JNIEnv* env, jclass klass, jint bid, jint param, jfloatArray values )
{
    jfloat *elements = (*env)->GetFloatArrayElements( env, values, NULL );
    alGetBufferfv( (ALuint) bid, (ALenum) param, (ALfloat *) elements );
    (*env)->ReleaseFloatArrayElements( env, values, elements, 0 );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alGetBufferi( JNIEnv* env, jclass klass, jint bid, jint param, jintArray value )
{
    jint *elements = (*env)->GetIntArrayElements( env, value, NULL );
    alGetBufferi( (ALuint) bid, (ALenum) param, (ALint *) elements );
    (*env)->ReleaseIntArrayElements( env, value, elements, 0 );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alGetBufferiv( JNIEnv* env, jclass klass, jint bid, jint param, jintArray values )
{
    jint *elements = (*env)->GetIntArrayElements( env, values, NULL );
    alGetBufferiv( (ALuint) bid, (ALenum) param, (ALint *) elements );
    (*env)->ReleaseIntArrayElements( env, values, elements, 0 );
}

JNIEXPORT jdouble JNICALL Java_paulscode_android_sound_ALAN_alGetDouble( JNIEnv* env, jclass klass, jint param )
{
    return (jdouble) alGetDouble( (ALenum) param );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alGetDoublev( JNIEnv* env, jclass klass, jint param, jdoubleArray data )
{
    jdouble *elements = (*env)->GetDoubleArrayElements( env, data, NULL );
    alGetDoublev( (ALenum) param, (ALdouble *) elements );
    (*env)->ReleaseDoubleArrayElements( env, data, elements, 0 );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alGetEffectf( JNIEnv* env, jclass klass, jint eid, jint pname, jfloatArray value )
{
    jfloat *elements = (*env)->GetFloatArrayElements( env, value, NULL );
    alGetEffectf( (ALuint) eid, (ALenum) pname, (ALfloat *) elements );
    (*env)->ReleaseFloatArrayElements( env, value, elements, 0 );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alGetEffectfv( JNIEnv* env, jclass klass, jint eid, jint pname, jfloatArray values )
{
    jfloat *elements = (*env)->GetFloatArrayElements( env, values, NULL );
    alGetEffectfv( (ALuint) eid, (ALenum) pname, (ALfloat *) elements );
    (*env)->ReleaseFloatArrayElements( env, values, elements, 0 );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alGetEffecti( JNIEnv* env, jclass klass, jint eid, jint pname, jintArray value )
{
    jint *elements = (*env)->GetIntArrayElements( env, value, NULL );
    alGetEffecti( (ALuint) eid, (ALenum) pname, (ALint *) elements );
    (*env)->ReleaseIntArrayElements( env, value, elements, 0 );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alGetEffectiv( JNIEnv* env, jclass klass, jint eid, jint pname, jintArray values )
{
    jint *elements = (*env)->GetIntArrayElements( env, values, NULL );
    alGetEffectiv( (ALuint) eid, (ALenum) pname, (ALint *) elements );
    (*env)->ReleaseIntArrayElements( env, values, elements, 0 );
}

JNIEXPORT jint JNICALL Java_paulscode_android_sound_ALAN_alGetEnumValue( JNIEnv* env, jclass klass, jstring ename )
{
    const char *nativeString = (*env)->GetStringUTFChars( env, ename, 0 );
    jint retVal = (jint) alGetEnumValue( (const ALchar *) nativeString );
    (*env)->ReleaseStringUTFChars( env, ename, nativeString );
    return retVal;
}

JNIEXPORT jint JNICALL Java_paulscode_android_sound_ALAN_alGetError( JNIEnv* env, jclass klass )
{
    return (jint) alGetError();
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alGetFilterf( JNIEnv* env, jclass klass, jint fid, jint pname, jfloatArray value )
{
    jfloat *elements = (*env)->GetFloatArrayElements( env, value, NULL );
    alGetFilterf( (ALuint) fid, (ALenum) pname, (ALfloat *) elements );
    (*env)->ReleaseFloatArrayElements( env, value, elements, 0 );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alGetFilterfv( JNIEnv* env, jclass klass, jint fid, jint pname, jfloatArray values )
{
    jfloat *elements = (*env)->GetFloatArrayElements( env, values, NULL );
    alGetFilterfv( (ALuint) fid, (ALenum) pname, (ALfloat *) elements );
    (*env)->ReleaseFloatArrayElements( env, values, elements, 0 );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alGetFilteri( JNIEnv* env, jclass klass, jint fid, jint pname, jintArray value )
{
    jint *elements = (*env)->GetIntArrayElements( env, value, NULL );
    alGetFilteri( (ALuint) fid, (ALenum) pname, (ALint *) elements );
    (*env)->ReleaseIntArrayElements( env, value, elements, 0 );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alGetFilteriv( JNIEnv* env, jclass klass, jint fid, jint pname, jintArray values )
{
    jint *elements = (*env)->GetIntArrayElements( env, values, NULL );
    alGetFilteriv( (ALuint) fid, (ALenum) pname, (ALint *) elements );
    (*env)->ReleaseIntArrayElements( env, values, elements, 0 );
}


JNIEXPORT jfloat JNICALL Java_paulscode_android_sound_ALAN_alGetFloat( JNIEnv* env, jclass klass, jint param )
{
    return (jfloat) alGetFloat( (ALenum) param );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alGetFloatv( JNIEnv* env, jclass klass, jint param, jfloatArray data )
{
    jfloat *elements = (*env)->GetFloatArrayElements( env, data, NULL );
    alGetFloatv( (ALenum) param, (ALfloat *) elements );
    (*env)->ReleaseFloatArrayElements( env, data, elements, 0 );
}


JNIEXPORT jint JNICALL Java_paulscode_android_sound_ALAN_alGetInteger( JNIEnv* env, jclass klass, jint param )
{
    return (jint) alGetInteger( (ALenum) param );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alGetIntegerv( JNIEnv* env, jclass klass, jint param, jintArray data )
{
    jint *elements = (*env)->GetIntArrayElements( env, data, NULL );
    alGetIntegerv( (ALenum) param, (ALint *) elements );
    (*env)->ReleaseIntArrayElements( env, data, elements, 0 );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alGetListener3f( JNIEnv* env, jclass klass, jint param, jfloatArray value1, jfloatArray value2, jfloatArray value3 )
{
    jfloat *elements1 = (*env)->GetFloatArrayElements( env, value1, NULL );
    jfloat *elements2 = (*env)->GetFloatArrayElements( env, value2, NULL );
    jfloat *elements3 = (*env)->GetFloatArrayElements( env, value3, NULL );
    alGetListener3f( (ALenum) param, (ALfloat *) elements1, (ALfloat *) elements2, (ALfloat *) elements3 );
    (*env)->ReleaseFloatArrayElements( env, value1, elements1, 0 );
    (*env)->ReleaseFloatArrayElements( env, value2, elements2, 0 );
    (*env)->ReleaseFloatArrayElements( env, value3, elements3, 0 );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alGetListener3i( JNIEnv* env, jclass klass, jint param, jintArray value1, jintArray value2, jintArray value3 )
{
    jint *elements1 = (*env)->GetIntArrayElements( env, value1, NULL );
    jint *elements2 = (*env)->GetIntArrayElements( env, value2, NULL );
    jint *elements3 = (*env)->GetIntArrayElements( env, value3, NULL );
    alGetListener3i( (ALenum) param, (ALint *) elements1, (ALint *) elements2, (ALint *) elements3);
    (*env)->ReleaseIntArrayElements( env, value1, elements1, 0 );
    (*env)->ReleaseIntArrayElements( env, value2, elements2, 0 );
    (*env)->ReleaseIntArrayElements( env, value3, elements3, 0 );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alGetListenerf( JNIEnv* env, jclass klass, jint param, jfloatArray value )
{
    jfloat *elements = (*env)->GetFloatArrayElements( env, value, NULL );
    alGetListenerf( (ALenum) param, (ALfloat *) elements );
    (*env)->ReleaseFloatArrayElements( env, value, elements, 0 );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alGetListenerfv( JNIEnv* env, jclass klass, jint param, jfloatArray values )
{
    jfloat *elements = (*env)->GetFloatArrayElements( env, values, NULL );
    alGetListenerfv( (ALenum) param, (ALfloat *) elements );
    (*env)->ReleaseFloatArrayElements( env, values, elements, 0 );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alGetListeneri( JNIEnv* env, jclass klass, jint param, jintArray value )
{
    jint *elements = (*env)->GetIntArrayElements( env, value, NULL );
    alGetListeneri( (ALenum) param, (ALint *) elements );
    (*env)->ReleaseIntArrayElements( env, value, elements, 0 );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alGetListeneriv( JNIEnv* env, jclass klass, jint param, jintArray values )
{
    jint *elements = (*env)->GetIntArrayElements( env, values, NULL );
    alGetListeneriv( (ALenum) param, (ALint *) elements );
    (*env)->ReleaseIntArrayElements( env, values, elements, 0 );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alGetSource3f( JNIEnv* env, jclass klass, jint sid, jint param, jfloatArray value1, jfloatArray value2, jfloatArray value3 )
{
    jfloat *elements1 = (*env)->GetFloatArrayElements( env, value1, NULL );
    jfloat *elements2 = (*env)->GetFloatArrayElements( env, value2, NULL );
    jfloat *elements3 = (*env)->GetFloatArrayElements( env, value3, NULL );
    alGetSource3f( (ALuint) sid, (ALenum) param, (ALfloat *) elements1, (ALfloat *) elements2, (ALfloat *) elements3 );
    (*env)->ReleaseFloatArrayElements( env, value1, elements1, 0 );
    (*env)->ReleaseFloatArrayElements( env, value2, elements2, 0 );
    (*env)->ReleaseFloatArrayElements( env, value3, elements3, 0 );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alGetSource3i( JNIEnv* env, jclass klass, jint sid, jint param, jintArray value1, jintArray value2, jintArray value3 )
{
    jint *elements1 = (*env)->GetIntArrayElements( env, value1, NULL );
    jint *elements2 = (*env)->GetIntArrayElements( env, value2, NULL );
    jint *elements3 = (*env)->GetIntArrayElements( env, value3, NULL );
    alGetSource3i( (ALuint) sid, (ALenum) param, (ALint *) elements1, (ALint *) elements2, (ALint *) elements3 );
    (*env)->ReleaseIntArrayElements( env, value1, elements1, 0 );
    (*env)->ReleaseIntArrayElements( env, value2, elements2, 0 );
    (*env)->ReleaseIntArrayElements( env, value3, elements3, 0 );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alGetSourcef( JNIEnv* env, jclass klass, jint sid, jint param, jfloatArray value )
{
    jfloat *elements = (*env)->GetFloatArrayElements( env, value, NULL );
    alGetSourcef( (ALuint) sid, (ALenum) param, (ALfloat *) elements );
    (*env)->ReleaseFloatArrayElements( env, value, elements, 0 );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alGetSourcefv( JNIEnv* env, jclass klass, jint sid, jint param, jfloatArray values )
{
    jfloat *elements = (*env)->GetFloatArrayElements( env, values, NULL );
    alGetSourcefv( (ALuint) sid, (ALenum) param, (ALfloat *) elements );
    (*env)->ReleaseFloatArrayElements( env, values, elements, 0 );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alGetSourcei( JNIEnv* env, jclass klass, jint sid, jint param, jintArray value )
{
    jint *elements = (*env)->GetIntArrayElements( env, value, NULL );
    alGetSourcei( (ALuint) sid, (ALenum) param, (ALint *) elements );
    (*env)->ReleaseIntArrayElements( env, value, elements, 0 );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alGetSourceiv( JNIEnv* env, jclass klass, jint sid, jint param, jintArray values )
{
    jint *elements = (*env)->GetIntArrayElements( env, values, NULL );
    alGetSourceiv( (ALuint) sid, (ALenum) param, (ALint *) elements );
    (*env)->ReleaseIntArrayElements( env, values, elements, 0 );
}

JNIEXPORT jstring JNICALL Java_paulscode_android_sound_ALAN_alGetString( JNIEnv* env, jclass klass, jint param )
{
	return (*env)->NewStringUTF( env, (const char *) alGetString( (ALenum) param ) );
}

JNIEXPORT jboolean JNICALL Java_paulscode_android_sound_ALAN_alIsAuxiliaryEffectSlot( JNIEnv* env, jclass klass, jint slot )
{
    return( (alIsAuxiliaryEffectSlot( (ALuint) slot ) == AL_TRUE) ? JNI_TRUE : JNI_FALSE );
}

JNIEXPORT jboolean JNICALL Java_paulscode_android_sound_ALAN_alIsBuffer( JNIEnv* env, jclass klass, jint bid )
{
    return( (alIsBuffer( (ALuint) bid ) == AL_TRUE) ? JNI_TRUE : JNI_FALSE );
}

JNIEXPORT jboolean JNICALL Java_paulscode_android_sound_ALAN_alIsEffect( JNIEnv* env, jclass klass, jint eid )
{
    return( (alIsEffect( (ALuint) eid ) == AL_TRUE) ? JNI_TRUE : JNI_FALSE );
}

JNIEXPORT jboolean JNICALL Java_paulscode_android_sound_ALAN_alIsEnabled( JNIEnv* env, jclass klass, jint capability )
{
    return( (alIsEnabled( (ALenum) capability ) == AL_TRUE) ? JNI_TRUE : JNI_FALSE );
}

JNIEXPORT jboolean JNICALL Java_paulscode_android_sound_ALAN_alIsExtensionPresent( JNIEnv* env, jclass klass, jstring extname )
{
    const char *nativeString = (*env)->GetStringUTFChars( env, extname, 0 );
    jboolean retVal = ( (alIsExtensionPresent( (const ALchar *) nativeString ) == AL_TRUE) ? JNI_TRUE : JNI_FALSE );
    (*env)->ReleaseStringUTFChars( env, extname, nativeString );
    return retVal;
}

JNIEXPORT jboolean JNICALL Java_paulscode_android_sound_ALAN_alIsFilter( JNIEnv* env, jclass klass, jint fid )
{
    return( (alIsFilter( (ALuint) fid ) == AL_TRUE) ? JNI_TRUE : JNI_FALSE );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alListener3f( JNIEnv* env, jclass klass, jint param, jfloat value1, jfloat value2, jfloat value3 )
{
    alListener3f( (ALenum) param, (ALfloat) value1, (ALfloat) value2, (ALfloat) value3 );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alListener3i( JNIEnv* env, jclass klass, jint param, jint value1, jint value2, jint value3 )
{
    alListener3i( (ALenum) param, (ALint) value1, (ALint) value2, (ALint) value3);
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alListenerf( JNIEnv* env, jclass klass, jint param, jfloat value )
{
    alListenerf( (ALenum) param, (ALfloat) value );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alListenerfv( JNIEnv* env, jclass klass, jint param, jfloatArray values )
{
    jfloat *elements = (*env)->GetFloatArrayElements( env, values, NULL );
    alListenerfv( (ALenum) param, (ALfloat *) elements );
    (*env)->ReleaseFloatArrayElements( env, values, elements, 0 );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alListeneri( JNIEnv* env, jclass klass, jint param, jint value )
{
    alListeneri( (ALenum) param, (ALint) value );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alListeneriv( JNIEnv* env, jclass klass, jint param, jintArray values )
{
    jint *elements = (*env)->GetIntArrayElements( env, values, NULL );
    alListeneriv( (ALenum) param, (ALint *) elements );
    (*env)->ReleaseIntArrayElements( env, values, elements, 0 );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alSource3f( JNIEnv* env, jclass klass, jint sid, jint param, jfloat value1, jfloat value2, jfloat value3 )
{
    alSource3f( (ALuint) sid, (ALenum) param, (ALfloat) value1, (ALfloat) value2, (ALfloat) value3 );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alSource3i( JNIEnv* env, jclass klass, jint sid, jint param, jint value1, jint value2, jint value3 )
{
    alSource3i( (ALuint) sid, (ALenum) param, (ALint) value1, (ALint) value2, (ALint) value3 );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alSourcef( JNIEnv* env, jclass klass, jint sid, jint param, jfloat value )
{
    alSourcef( (ALuint) sid, (ALenum) param, (ALfloat) value );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alSourcefv( JNIEnv* env, jclass klass, jint sid, jint param, jfloatArray values )
{
    jfloat *elements = (*env)->GetFloatArrayElements( env, values, NULL );
    alSourcefv( (ALuint) sid, (ALenum) param, (ALfloat *) elements );
    (*env)->ReleaseFloatArrayElements( env, values, elements, 0 );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alSourcei( JNIEnv* env, jclass klass, jint sid, jint param, jint value )
{
    alSourcei( (ALuint) sid, (ALenum) param, (ALint) value );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alSourceiv( JNIEnv* env, jclass klass, jint sid, jint param, jintArray values )
{
    jint *elements = (*env)->GetIntArrayElements( env, values, NULL );
    alSourceiv( (ALuint) sid, (ALenum) param, (ALint *) elements );
    (*env)->ReleaseIntArrayElements( env, values, elements, 0 );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alSourcePause( JNIEnv* env, jclass klass, jint sid )
{
    alSourcePause( (ALuint) sid );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alSourcePausev( JNIEnv* env, jclass klass, jint ns, jintArray sids )
{
    jint *elements = (*env)->GetIntArrayElements( env, sids, NULL );
    alSourcePausev( (ALsizei) ns, (const ALuint *) elements );
    (*env)->ReleaseIntArrayElements( env, sids, elements, 0 );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alSourcePlay( JNIEnv* env, jclass klass, jint sid )
{
    alSourcePlay( (ALuint) sid );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alSourcePlayv( JNIEnv* env, jclass klass, jint ns, jintArray sids )
{
    jint *elements = (*env)->GetIntArrayElements( env, sids, NULL );
    alSourcePlayv( (ALsizei) ns, (const ALuint *) elements );
    (*env)->ReleaseIntArrayElements( env, sids, elements, 0 );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alSourceQueueBuffers( JNIEnv* env, jclass klass, jint sid, jint numEntries, jintArray bids )
{
    jint *elements = (*env)->GetIntArrayElements( env, bids, NULL );
    alSourceQueueBuffers( (ALuint) sid, (ALsizei) numEntries, (const ALuint *) elements );
    (*env)->ReleaseIntArrayElements( env, bids, elements, 0 );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alSourceRewind( JNIEnv* env, jclass klass, jint sid )
{
    alSourceRewind( (ALuint) sid );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alSourceRewindv( JNIEnv* env, jclass klass, jint ns, jintArray sids )
{
    jint *elements = (*env)->GetIntArrayElements( env, sids, NULL );
    alSourceRewindv( (ALsizei) ns, (const ALuint *) elements );
    (*env)->ReleaseIntArrayElements( env, sids, elements, 0 );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alSourceStop( JNIEnv* env, jclass klass, jint sid )
{
    alSourceStop( (ALuint) sid );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alSourceStopv( JNIEnv* env, jclass klass, jint ns, jintArray sids )
{
    jint *elements = (*env)->GetIntArrayElements( env, sids, NULL );
    alSourceStopv( (ALsizei) ns, (const ALuint *) elements );
    (*env)->ReleaseIntArrayElements( env, sids, elements, 0 );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alSourceUnqueueBuffers( JNIEnv* env, jclass klass, jint sid, jint numEntries, jintArray bids )
{
    jint *elements = (*env)->GetIntArrayElements( env, bids, NULL );
    alSourceUnqueueBuffers( (ALuint) sid, (ALsizei) numEntries, (ALuint *) elements );
    (*env)->ReleaseIntArrayElements( env, bids, elements, 0 );
}

JNIEXPORT void JNICALL Java_paulscode_android_sound_ALAN_alSpeedOfSound( JNIEnv* env, jclass klass, jfloat value )
{
    alSpeedOfSound( (ALfloat) value );
}
