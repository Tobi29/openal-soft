#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alext.h>

#include <jni.h>

#define SEA_OPENAL_PKG org_tobi29_scapes_engine_android_openal_bind

#define GEN_JNI_FUN_HELPER(pkg, static_clazz, name) Java_##pkg##_##static_clazz##_##name
#define GEN_JNI_FUN(pkg, static_clazz, name) GEN_JNI_FUN_HELPER(pkg, static_clazz, name)

#define GEN_JNI(rt, fun) JNIEXPORT rt JNICALL fun
#define GEN_JNI0(rt, fun) GEN_JNI(rt, fun)( \
    JNIEnv* env, \
    jclass clazz \
)
#define GEN_JNI1(rt, fun, p0) GEN_JNI(rt, fun)( \
    JNIEnv* env, \
    jclass clazz, \
    p0 a0 \
)
#define GEN_JNI2(rt, fun, p0, p1) GEN_JNI(rt, fun)( \
    JNIEnv* env, \
    jclass clazz, \
    p0 a0, \
    p1 a1 \
)
#define GEN_JNI3(rt, fun, p0, p1, p2) GEN_JNI(rt, fun)( \
    JNIEnv* env, \
    jclass clazz, \
    p0 a0, \
    p1 a1, \
    p2 a2 \
)
#define GEN_JNI4(rt, fun, p0, p1, p2, p3) GEN_JNI(rt, fun)( \
    JNIEnv* env, \
    jclass clazz, \
    p0 a0, \
    p1 a1, \
    p2 a2, \
    p3 a3 \
)
#define GEN_JNI5(rt, fun, p0, p1, p2, p3, p4) GEN_JNI(rt, fun)( \
    JNIEnv* env, \
    jclass clazz, \
    p0 a0, \
    p1 a1, \
    p2 a2, \
    p3 a3, \
    p4 a4 \
)

#define GEN_BIND0(pkg, static_clazz, name) \
GEN_JNI0(void, GEN_JNI_FUN(pkg, static_clazz, name)) { \
    (void) env; \
    (void) clazz; \
    name(); \
}
#define GEN_BIND0_R(pkg, static_clazz, name, rt, rc) \
GEN_JNI0(rt, GEN_JNI_FUN(pkg, static_clazz, name)) { \
    (void) env; \
    (void) clazz; \
    rc(r, r = name();); \
}
#define GEN_BIND1(pkg, static_clazz, name, p0, c0) \
GEN_JNI1(void, GEN_JNI_FUN(pkg, static_clazz, name), p0) { \
    (void) env; \
    (void) clazz; \
    c0(a0, v0, name(v0);); \
}
#define GEN_BIND1_R(pkg, static_clazz, name, rt, rc, p0, c0) \
GEN_JNI1(rt, GEN_JNI_FUN(pkg, static_clazz, name), p0) { \
    (void) env; \
    (void) clazz; \
    rc(r, c0(a0, v0, r = name(v0););); \
}
#define GEN_BIND2(pkg, static_clazz, name, p0, c0, p1, c1) \
GEN_JNI2(void, GEN_JNI_FUN(pkg, static_clazz, name), p0, p1) { \
    (void) env; \
    (void) clazz; \
    c0(a0, v0, c1(a1, v1, name(v0, v1);)); \
}
#define GEN_BIND2_R(pkg, static_clazz, name, rt, rc, p0, c0, p1, c1) \
GEN_JNI2(rt, GEN_JNI_FUN(pkg, static_clazz, name), p0, p1) { \
    (void) env; \
    (void) clazz; \
    rc(r, c0(a0, v0, c1(a1, v1, r = name(v0, v1);));); \
}
#define GEN_BIND3(pkg, static_clazz, name, p0, c0, p1, c1, p2, c2) \
GEN_JNI3(void, GEN_JNI_FUN(pkg, static_clazz, name), p0, p1, p2) { \
    (void) env; \
    (void) clazz; \
    c0(a0, v0, c1(a1, v1, c2(a2, v2, name(v0, v1, v2);))); \
}
#define GEN_BIND3_R(pkg, static_clazz, name, rt, rc, p0, c0, p1, c1, p2, c2) \
GEN_JNI3(rt, GEN_JNI_FUN(pkg, static_clazz, name), p0, p1, p2) { \
    (void) env; \
    (void) clazz; \
    rc(r, c0(a0, v0, c1(a1, v1, c2(a2, v2, r = name(v0, v1, v2);)));); \
}
#define GEN_BIND4(pkg, static_clazz, name, p0, c0, p1, c1, p2, c2, p3, c3) \
GEN_JNI4(void, GEN_JNI_FUN(pkg, static_clazz, name), p0, p1, p2, p3) { \
    (void) env; \
    (void) clazz; \
    c0(a0, v0, c1(a1, v1, c2(a2, v2, c3(a3, v3, name(v0, v1, v2, v3);)))); \
}
#define GEN_BIND4_R(pkg, static_clazz, name, rt, rc, p0, c0, p1, c1, p2, c2, p3, c3) \
GEN_JNI4(rt, GEN_JNI_FUN(pkg, static_clazz, name), p0, p1, p2, p3) { \
    (void) env; \
    (void) clazz; \
    rc(r, c0(a0, v0, c1(a1, v1, c2(a2, v2, c3(a3, v3, r = name(v0, v1, v2, v3);))));); \
}
#define GEN_BIND5(pkg, static_clazz, name, p0, c0, p1, c1, p2, c2, p3, c3, p4, c4) \
GEN_JNI5(void, GEN_JNI_FUN(pkg, static_clazz, name), p0, p1, p2, p3, p4) { \
    (void) env; \
    (void) clazz; \
    c0(a0, v0, c1(a1, v1, c2(a2, v2, c3(a3, v3, c4(a4, v4, name(v0, v1, v2, v3, v4);))))); \
}
#define GEN_BIND5_R(pkg, static_clazz, name, rt, rc, p0, c0, p1, c1, p2, c2, p3, c3, p4, c4) \
GEN_JNI5(rt, GEN_JNI_FUN(pkg, static_clazz, name), p0, p1, p2, p3, p4) { \
    (void) env; \
    (void) clazz; \
    rc(r, c0(a0, v0, c1(a1, v1, c2(a2, v2, c3(a3, v3, c4(a4, v4, r = name(v0, v1, v2, v3, v4);)))));); \
}

#define GEN_CAST(type, a, v, c) \
type v = static_cast<type>(a); \
c;
#define GEN_CAST_REINTERPRET(type, a, v, c) \
type v = reinterpret_cast<type>(a); \
c;

#define GEN_CAST_ALENUM(a, v, c) GEN_CAST(ALenum, a, v, c)
#define GEN_CAST_ALFLOAT(a, v, c) GEN_CAST(ALfloat, a, v, c)
#define GEN_CAST_ALDOUBLE(a, v, c) GEN_CAST(ALdouble, a, v, c)
#define GEN_CAST_ALINT(a, v, c) GEN_CAST(ALint, a, v, c)
#define GEN_CAST_ALUINT(a, v, c) GEN_CAST(ALuint, a, v, c)
#define GEN_CAST_ALSIZEI(a, v, c) GEN_CAST(ALsizei, a, v, c)
#define GEN_CAST_ALBOOLEAN(a, v, c) \
type v = a ? AL_TRUE : AL_FALSE; \
c;
#define GEN_CAST_ALFLOAT_STAR(a, v, c) \
ALfloat* v = a ? env->GetFloatArrayElements(a, nullptr) : nullptr; \
c; \
if (v) env->ReleaseFloatArrayElements(a, v, 0);
#define GEN_CAST_ALDOUBLE_STAR(a, v, c) \
ALdouble* v = a ? env->GetDoubleArrayElements(a, nullptr) : nullptr; \
c; \
if (v) env->ReleaseDoubleArrayElements(a, v, 0);
#define GEN_CAST_ALINT_STAR(a, v, c) \
ALint* v = a ? env->GetIntArrayElements(a, nullptr) : nullptr; \
c; \
if (v) env->ReleaseIntArrayElements(a, v, 0);
#define GEN_CAST_ALUINT_STAR(a, v, c) \
ALuint* v = a ? reinterpret_cast<ALuint*>(env->GetIntArrayElements(a, nullptr)) : nullptr; \
c; \
if (v) env->ReleaseIntArrayElements(a, reinterpret_cast<jint*>(v), 0);
#define GEN_CAST_ALVOID_STAR(a, v, c) \
ALvoid* v = a ? static_cast<ALvoid*>(env->GetByteArrayElements(a, nullptr)) : nullptr; \
c; \
if (v) env->ReleaseByteArrayElements(a, static_cast<jbyte*>(v), 0);
#define GEN_CAST_ALBOOLEAN_STAR(a, v, c) \
ALboolean* v = a ? reinterpret_cast<ALboolean*>(env->GetBooleanArrayElements(a, nullptr)) : nullptr; \
c; \
if (v) env->ReleaseBooleanArrayElements(a, reinterpret_cast<jboolean*>(v), 0);

#define GEN_RCAST(type, type_org, r, c) \
type_org r; \
c; \
return (type) r;
#define GEN_RCAST_REINTERPRET(type, type_org, r, c) \
type_org r; \
c; \
return (type) r;

#define GEN_RCAST_ALENUM(r, c) GEN_RCAST(jint, ALenum, r, c)
#define GEN_RCAST_ALFLOAT(r, c) GEN_RCAST(jfloat, ALfloat, r, c)
#define GEN_RCAST_ALDOUBLE(r, c) GEN_RCAST(jdouble, ALdouble, r, c)
#define GEN_RCAST_ALINT(r, c) GEN_RCAST(jint, ALint, r, c)
#define GEN_RCAST_ALUINT(r, c) GEN_RCAST(jint, ALuint, r, c)
#define GEN_RCAST_ALBOOLEAN(r, c) \
ALboolean r; \
c; \
return r ? JNI_TRUE : JNI_FALSE;
#define GEN_RCAST_CONST_ALCHAR_STAR(r, c) \
const ALchar* r; \
c; \
return env->NewStringUTF(r);

#define GEN_CAST_ALCENUM(a, v, c) GEN_CAST(ALCenum, a, v, c)
#define GEN_CAST_ALCUINT(a, v, c) GEN_CAST(ALCuint, a, v, c)
#define GEN_CAST_ALCSIZEI(a, v, c) GEN_CAST(ALCsizei, a, v, c)
#define GEN_CAST_ALCCONTEXT_STAR(a, v, c) GEN_CAST_REINTERPRET(ALCcontext*, a, v, c)
#define GEN_CAST_ALCDEVICE_STAR(a, v, c) GEN_CAST_REINTERPRET(ALCdevice*, a, v, c)
#define GEN_CAST_ALCINT_STAR(a, v, c) \
ALCint* v = a ? env->GetIntArrayElements(a, nullptr) : nullptr; \
c; \
if (v) env->ReleaseIntArrayElements(a, v, 0);
#define GEN_CAST_ALCVOID_STAR(a, v, c) \
ALCvoid* v = a ? static_cast<ALCvoid*>(env->GetByteArrayElements(a, nullptr)) : nullptr; \
c; \
if (v) env->ReleaseByteArrayElements(a, static_cast<jbyte*>(v), 0);
#define GEN_CAST_CONST_ALCCHAR_STAR(a, v, c) \
const ALCchar* v = a ? env->GetStringUTFChars(a, nullptr) : nullptr; \
c; \
if (v) env->ReleaseStringUTFChars(a, v);

#define GEN_RCAST_ALCENUM(r, c) GEN_RCAST(jint, ALCenum, r, c)
#define GEN_RCAST_ALCCONTEXT_STAR(r, c) GEN_RCAST_REINTERPRET(jlong, ALCcontext*, r, c)
#define GEN_RCAST_ALCDEVICE_STAR(r, c) GEN_RCAST_REINTERPRET(jlong, ALCdevice*, r, c)
#define GEN_RCAST_ALCBOOLEAN(r, c) \
ALCboolean r; \
c; \
return r ? JNI_TRUE : JNI_FALSE;
#define GEN_RCAST_CONST_ALCCHAR_STAR(r, c) \
const ALCchar* r; \
c; \
return env->NewStringUTF(r);

#define GEN_PROPERTY_FUNS1(pkg, static_clazz, prefix, name, p0, c0) \
GEN_BIND2(pkg, static_clazz, prefix##name##f, p0, c0, jfloat, GEN_CAST_ALFLOAT) \
GEN_BIND4(pkg, static_clazz, prefix##name##3f, p0, c0, jfloat, GEN_CAST_ALFLOAT, jfloat, GEN_CAST_ALFLOAT, jfloat, GEN_CAST_ALFLOAT) \
GEN_BIND2(pkg, static_clazz, prefix##name##fv, p0, c0, jfloatArray, GEN_CAST_ALFLOAT_STAR) \
GEN_BIND2(pkg, static_clazz, prefix##name##i, p0, c0, jint, GEN_CAST_ALINT) \
GEN_BIND4(pkg, static_clazz, prefix##name##3i, p0, c0, jint, GEN_CAST_ALINT, jint, GEN_CAST_ALINT, jint, GEN_CAST_ALINT) \
GEN_BIND2(pkg, static_clazz, prefix##name##iv, p0, c0, jintArray, GEN_CAST_ALINT_STAR) \
GEN_BIND2(pkg, static_clazz, prefix##Get##name##f, p0, c0, jfloatArray, GEN_CAST_ALFLOAT_STAR) \
GEN_BIND4(pkg, static_clazz, prefix##Get##name##3f, p0, c0, jfloatArray, GEN_CAST_ALFLOAT_STAR, jfloatArray, GEN_CAST_ALFLOAT_STAR, jfloatArray, GEN_CAST_ALFLOAT_STAR) \
GEN_BIND2(pkg, static_clazz, prefix##Get##name##fv, p0, c0, jfloatArray, GEN_CAST_ALFLOAT_STAR) \
GEN_BIND2(pkg, static_clazz, prefix##Get##name##i, p0, c0, jintArray, GEN_CAST_ALINT_STAR) \
GEN_BIND4(pkg, static_clazz, prefix##Get##name##3i, p0, c0, jintArray, GEN_CAST_ALINT_STAR, jintArray, GEN_CAST_ALINT_STAR, jintArray, GEN_CAST_ALINT_STAR) \
GEN_BIND2(pkg, static_clazz, prefix##Get##name##iv, p0, c0, jintArray, GEN_CAST_ALINT_STAR)
#define GEN_PROPERTY_FUNS2(pkg, static_clazz, prefix, name, p0, c0, p1, c1) \
GEN_BIND3(pkg, static_clazz, prefix##name##f, p0, c0, p1, c1, jfloat, GEN_CAST_ALFLOAT) \
GEN_BIND5(pkg, static_clazz, prefix##name##3f, p0, c0, p1, c1, jfloat, GEN_CAST_ALFLOAT, jfloat, GEN_CAST_ALFLOAT, jfloat, GEN_CAST_ALFLOAT) \
GEN_BIND3(pkg, static_clazz, prefix##name##fv, p0, c0, p1, c1, jfloatArray, GEN_CAST_ALFLOAT_STAR) \
GEN_BIND3(pkg, static_clazz, prefix##name##i, p0, c0, p1, c1, jint, GEN_CAST_ALINT) \
GEN_BIND5(pkg, static_clazz, prefix##name##3i, p0, c0, p1, c1, jint, GEN_CAST_ALINT, jint, GEN_CAST_ALINT, jint, GEN_CAST_ALINT) \
GEN_BIND3(pkg, static_clazz, prefix##name##iv, p0, c0, p1, c1, jintArray, GEN_CAST_ALINT_STAR) \
GEN_BIND3(pkg, static_clazz, prefix##Get##name##f, p0, c0, p1, c1, jfloatArray, GEN_CAST_ALFLOAT_STAR) \
GEN_BIND5(pkg, static_clazz, prefix##Get##name##3f, p0, c0, p1, c1, jfloatArray, GEN_CAST_ALFLOAT_STAR, jfloatArray, GEN_CAST_ALFLOAT_STAR, jfloatArray, GEN_CAST_ALFLOAT_STAR) \
GEN_BIND3(pkg, static_clazz, prefix##Get##name##fv, p0, c0, p1, c1, jfloatArray, GEN_CAST_ALFLOAT_STAR) \
GEN_BIND3(pkg, static_clazz, prefix##Get##name##i, p0, c0, p1, c1, jintArray, GEN_CAST_ALINT_STAR) \
GEN_BIND5(pkg, static_clazz, prefix##Get##name##3i, p0, c0, p1, c1, jintArray, GEN_CAST_ALINT_STAR, jintArray, GEN_CAST_ALINT_STAR, jintArray, GEN_CAST_ALINT_STAR) \
GEN_BIND3(pkg, static_clazz, prefix##Get##name##iv, p0, c0, p1, c1, jintArray, GEN_CAST_ALINT_STAR)

GEN_BIND0_R(SEA_OPENAL_PKG, AL, alGetError,
            jint, GEN_RCAST_ALENUM)

GEN_BIND1(SEA_OPENAL_PKG, AL, alEnable,
          jint, GEN_CAST_ALENUM)

GEN_BIND1(SEA_OPENAL_PKG, AL, alDisable,
          jint, GEN_CAST_ALENUM)

GEN_BIND1_R(SEA_OPENAL_PKG, AL, alIsEnabled,
            jboolean, GEN_RCAST_ALBOOLEAN,
            jint, GEN_CAST_ALENUM)

GEN_BIND1_R(SEA_OPENAL_PKG, AL, alGetBoolean,
            jboolean, GEN_RCAST_ALBOOLEAN,
            jint, GEN_CAST_ALENUM)

GEN_BIND1_R(SEA_OPENAL_PKG, AL, alGetInteger,
            jint, GEN_RCAST_ALINT,
            jint, GEN_CAST_ALENUM)

GEN_BIND1_R(SEA_OPENAL_PKG, AL, alGetFloat,
            jfloat, GEN_RCAST_ALFLOAT,
            jint, GEN_CAST_ALENUM)

GEN_BIND1_R(SEA_OPENAL_PKG, AL, alGetDouble,
            jdouble, GEN_RCAST_ALDOUBLE,
            jint, GEN_CAST_ALENUM)

GEN_BIND2(SEA_OPENAL_PKG, AL, alGetBooleanv,
          jint, GEN_CAST_ALENUM,
          jbooleanArray, GEN_CAST_ALBOOLEAN_STAR)

GEN_BIND2(SEA_OPENAL_PKG, AL, alGetIntegerv,
          jint, GEN_CAST_ALENUM,
          jintArray, GEN_CAST_ALINT_STAR)

GEN_BIND2(SEA_OPENAL_PKG, AL, alGetFloatv,
          jint, GEN_CAST_ALENUM,
          jfloatArray, GEN_CAST_ALFLOAT_STAR)

GEN_BIND2(SEA_OPENAL_PKG, AL, alGetDoublev,
          jint, GEN_CAST_ALENUM,
          jdoubleArray, GEN_CAST_ALDOUBLE_STAR)

GEN_BIND1_R(SEA_OPENAL_PKG, AL, alGetString,
            jstring, GEN_RCAST_CONST_ALCHAR_STAR,
            jint, GEN_CAST_ALENUM)

GEN_BIND1(SEA_OPENAL_PKG, AL, alDopplerFactor,
          jfloat, GEN_CAST_ALFLOAT)

GEN_BIND1(SEA_OPENAL_PKG, AL, alDopplerVelocity,
          jfloat, GEN_CAST_ALFLOAT)

GEN_BIND1(SEA_OPENAL_PKG, AL, alSpeedOfSound,
          jfloat, GEN_CAST_ALFLOAT)

GEN_BIND1(SEA_OPENAL_PKG, AL, alDistanceModel,
          jint, GEN_CAST_ALINT)

GEN_PROPERTY_FUNS1(SEA_OPENAL_PKG, AL, al, Listener,
                   jint, GEN_CAST_ALENUM)

GEN_BIND2(SEA_OPENAL_PKG, AL, alGenSources,
          jint, GEN_CAST_ALSIZEI,
          jintArray, GEN_CAST_ALUINT_STAR)

GEN_BIND2(SEA_OPENAL_PKG, AL, alDeleteSources,
          jint, GEN_CAST_ALSIZEI,
          jintArray, GEN_CAST_ALUINT_STAR)

GEN_BIND1_R(SEA_OPENAL_PKG, AL, alIsSource,
            jboolean, GEN_RCAST_ALBOOLEAN,
            jint, GEN_CAST_ALUINT)

GEN_PROPERTY_FUNS2(SEA_OPENAL_PKG, AL, al, Source,
                   jint, GEN_CAST_ALUINT,
                   jint, GEN_CAST_ALENUM)

GEN_BIND3(SEA_OPENAL_PKG, AL, alSourceQueueBuffers,
          jint, GEN_CAST_ALUINT,
          jint, GEN_CAST_ALSIZEI,
          jintArray, GEN_CAST_ALUINT_STAR)

GEN_BIND3(SEA_OPENAL_PKG, AL, alSourceUnqueueBuffers,
          jint, GEN_CAST_ALUINT,
          jint, GEN_CAST_ALSIZEI,
          jintArray, GEN_CAST_ALUINT_STAR)

GEN_BIND1(SEA_OPENAL_PKG, AL, alSourcePlay,
          jint, GEN_CAST_ALUINT)

GEN_BIND1(SEA_OPENAL_PKG, AL, alSourcePause,
          jint, GEN_CAST_ALUINT)

GEN_BIND1(SEA_OPENAL_PKG, AL, alSourceStop,
          jint, GEN_CAST_ALUINT)

GEN_BIND1(SEA_OPENAL_PKG, AL, alSourceRewind,
          jint, GEN_CAST_ALUINT)

GEN_BIND2(SEA_OPENAL_PKG, AL, alSourcePlayv,
          jint, GEN_CAST_ALSIZEI,
          jintArray, GEN_CAST_ALUINT_STAR)

GEN_BIND2(SEA_OPENAL_PKG, AL, alSourcePausev,
          jint, GEN_CAST_ALSIZEI,
          jintArray, GEN_CAST_ALUINT_STAR)

GEN_BIND2(SEA_OPENAL_PKG, AL, alSourceStopv,
          jint, GEN_CAST_ALSIZEI,
          jintArray, GEN_CAST_ALUINT_STAR)

GEN_BIND2(SEA_OPENAL_PKG, AL, alSourceRewindv,
          jint, GEN_CAST_ALSIZEI,
          jintArray, GEN_CAST_ALUINT_STAR)

GEN_BIND2(SEA_OPENAL_PKG, AL, alGenBuffers,
          jint, GEN_CAST_ALSIZEI,
          jintArray, GEN_CAST_ALUINT_STAR)

GEN_BIND2(SEA_OPENAL_PKG, AL, alDeleteBuffers,
          jint, GEN_CAST_ALSIZEI,
          jintArray, GEN_CAST_ALUINT_STAR)

GEN_BIND1_R(SEA_OPENAL_PKG, AL, alIsBuffer,
            jboolean, GEN_RCAST_ALBOOLEAN,
            jint, GEN_CAST_ALUINT)

GEN_PROPERTY_FUNS2(SEA_OPENAL_PKG, AL, al, Buffer,
                   jint, GEN_CAST_ALUINT,
                   jint, GEN_CAST_ALENUM)

GEN_BIND5(SEA_OPENAL_PKG, AL, alBufferData,
          jint, GEN_CAST_ALUINT,
          jint, GEN_CAST_ALENUM,
          jbyteArray, GEN_CAST_ALVOID_STAR,
          jint, GEN_CAST_ALSIZEI,
          jint, GEN_CAST_ALSIZEI)

GEN_BIND2_R(SEA_OPENAL_PKG, ALC, alcCreateContext,
            jlong, GEN_RCAST_ALCCONTEXT_STAR,
            jlong, GEN_CAST_ALCDEVICE_STAR,
            jintArray, GEN_CAST_ALCINT_STAR)

GEN_BIND1_R(SEA_OPENAL_PKG, ALC, alcMakeContextCurrent,
            jboolean, GEN_RCAST_ALCBOOLEAN,
            jlong, GEN_CAST_ALCCONTEXT_STAR)

GEN_BIND1(SEA_OPENAL_PKG, ALC, alcProcessContext,
          jlong, GEN_CAST_ALCCONTEXT_STAR)

GEN_BIND1(SEA_OPENAL_PKG, ALC, alcSuspendContext,
          jlong, GEN_CAST_ALCCONTEXT_STAR)

GEN_BIND1(SEA_OPENAL_PKG, ALC, alcDestroyContext,
          jlong, GEN_CAST_ALCCONTEXT_STAR)

GEN_BIND0_R(SEA_OPENAL_PKG, ALC, alcGetCurrentContext,
            jlong, GEN_RCAST_ALCCONTEXT_STAR)

GEN_BIND1_R(SEA_OPENAL_PKG, ALC, alcGetContextsDevice,
            jlong, GEN_RCAST_ALCDEVICE_STAR,
            jlong, GEN_CAST_ALCCONTEXT_STAR)

GEN_BIND1_R(SEA_OPENAL_PKG, ALC, alcOpenDevice,
            jlong, GEN_RCAST_ALCDEVICE_STAR,
            jstring, GEN_CAST_CONST_ALCCHAR_STAR)

GEN_BIND1_R(SEA_OPENAL_PKG, ALC, alcCloseDevice,
            jboolean, GEN_RCAST_ALCBOOLEAN,
            jlong, GEN_CAST_ALCDEVICE_STAR)

GEN_BIND1_R(SEA_OPENAL_PKG, ALC, alcGetError,
            jint, GEN_RCAST_ALCENUM,
            jlong, GEN_CAST_ALCDEVICE_STAR)

GEN_BIND2_R(SEA_OPENAL_PKG, ALC, alcIsExtensionPresent,
            jboolean, GEN_RCAST_ALCBOOLEAN,
            jlong, GEN_CAST_ALCDEVICE_STAR,
            jstring, GEN_CAST_CONST_ALCCHAR_STAR)

GEN_BIND2_R(SEA_OPENAL_PKG, ALC, alcGetEnumValue,
            jint, GEN_RCAST_ALCENUM,
            jlong, GEN_CAST_ALCDEVICE_STAR,
            jstring, GEN_CAST_CONST_ALCCHAR_STAR)

GEN_BIND2_R(SEA_OPENAL_PKG, ALC, alcGetString,
            jstring, GEN_RCAST_CONST_ALCCHAR_STAR,
            jlong, GEN_CAST_ALCDEVICE_STAR,
            jint, GEN_CAST_ALCENUM)

GEN_BIND4(SEA_OPENAL_PKG, ALC, alcGetIntegerv,
          jlong, GEN_CAST_ALCDEVICE_STAR,
          jint, GEN_CAST_ALCENUM,
          jint, GEN_CAST_ALCSIZEI,
          jintArray, GEN_CAST_ALINT_STAR)

GEN_BIND4_R(SEA_OPENAL_PKG, ALC, alcCaptureOpenDevice,
            jlong, GEN_RCAST_ALCDEVICE_STAR,
            jstring, GEN_CAST_CONST_ALCCHAR_STAR,
            jint, GEN_CAST_ALCUINT,
            jint, GEN_CAST_ALCENUM,
            jint, GEN_CAST_ALCSIZEI)

GEN_BIND1_R(SEA_OPENAL_PKG, ALC, alcCaptureCloseDevice,
            jboolean, GEN_RCAST_ALCBOOLEAN,
            jlong, GEN_CAST_ALCDEVICE_STAR)

GEN_BIND1(SEA_OPENAL_PKG, ALC, alcCaptureStart,
          jlong, GEN_CAST_ALCDEVICE_STAR)

GEN_BIND1(SEA_OPENAL_PKG, ALC, alcCaptureStop,
          jlong, GEN_CAST_ALCDEVICE_STAR)

GEN_BIND3(SEA_OPENAL_PKG, ALC, alcCaptureSamples,
          jlong, GEN_CAST_ALCDEVICE_STAR,
          jbyteArray, GEN_CAST_ALCVOID_STAR,
          jint, GEN_CAST_ALCSIZEI)

GEN_BIND1(SEA_OPENAL_PKG, SOFTPauseDevice, alcDeviceResumeSOFT,
          jlong, GEN_CAST_ALCDEVICE_STAR)

GEN_BIND1(SEA_OPENAL_PKG, SOFTPauseDevice, alcDevicePauseSOFT,
          jlong, GEN_CAST_ALCDEVICE_STAR)
