#include <jni.h>
#include <string>
#include "fastmath.hpp"

jobject createJavaMatrix(JNIEnv* env, const Matrix* nativeMatrix, jclass matrixClass);

extern "C" JNIEXPORT jstring JNICALL
Java_org_example_NativeAPI_helloFromCPP(JNIEnv* env, jclass clazz) {
    return env->NewStringUTF("Hello from C++!");
}

extern "C" JNIEXPORT jobject JNICALL
Java_org_example_NativeAPI_multiplyMatrices(JNIEnv* env, jclass clazz, jobject matA, jobject matB) {
    jclass matrixClass = env->FindClass("org/example/Matrix");
    jfieldID rowField = env->GetFieldID(matrixClass, "row", "I");
    jfieldID colField = env->GetFieldID(matrixClass, "col", "I");
    jfieldID valuesField = env->GetFieldID(matrixClass, "values", "[[D");

    jint rowA = env->GetIntField(matA, rowField);
    jint colA = env->GetIntField(matA, colField);
    jobjectArray valuesA = (jobjectArray)env->GetObjectField(matA, valuesField);

    Matrix matrixA;
    matrixA.row = rowA;
    matrixA.col = colA;
    Matrix_alloc(&matrixA);
    for (int i = 0; i < rowA; ++i) {
        jdoubleArray row = (jdoubleArray)env->GetObjectArrayElement(valuesA, i);
        jdouble* rowElements = env->GetDoubleArrayElements(row, nullptr);
        for (int j = 0; j < colA; ++j) {
            matrixA.n[i][j] = rowElements[j];
        }
        env->ReleaseDoubleArrayElements(row, rowElements, 0);
    }

    jint rowB = env->GetIntField(matB, rowField);
    jint colB = env->GetIntField(matB, colField);
    jobjectArray valuesB = (jobjectArray)env->GetObjectField(matB, valuesField);

    Matrix matrixB;
    matrixB.row = rowB;
    matrixB.col = colB;
    Matrix_alloc(&matrixB);
    for (int i = 0; i < rowB; ++i) {
        jdoubleArray row = (jdoubleArray)env->GetObjectArrayElement(valuesB, i);
        jdouble* rowElements = env->GetDoubleArrayElements(row, nullptr);
        for (int j = 0; j < colB; ++j) {
            matrixB.n[i][j] = rowElements[j];
        }
        env->ReleaseDoubleArrayElements(row, rowElements, 0);
    }

    Matrix* result = multiplyMatrices(&matrixA, &matrixB);

    jobject resultMatrix = createJavaMatrix(env, result, matrixClass);

    Matrix_free(&matrixA);
    Matrix_free(&matrixB);
    Matrix_free(result);
    delete result;

    return resultMatrix;
}

jobject createJavaMatrix(JNIEnv* env, const Matrix* nativeMatrix, jclass matrixClass) {
    jmethodID matrixConstructor = env->GetMethodID(matrixClass, "<init>", "(II[[D)V");

    jobjectArray javaValues = env->NewObjectArray(nativeMatrix->row, env->FindClass("[D"), nullptr);
    for (int i = 0; i < nativeMatrix->row; ++i) {
        jdoubleArray row = env->NewDoubleArray(nativeMatrix->col);
        env->SetDoubleArrayRegion(row, 0, nativeMatrix->col, nativeMatrix->n[i]);
        env->SetObjectArrayElement(javaValues, i, row);
    }

    return env->NewObject(matrixClass, matrixConstructor, nativeMatrix->row, nativeMatrix->col, javaValues);
}