/*
 * JNvgraph - Java bindings for nvGRAPH, the NVIDIA CUDA graph library,
 * to be used with JCuda
 *
 * Copyright (c) 2016-2016 Marco Hutter - http://www.jcuda.org
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include "JNvgraph.hpp"
#include "JNvgraph_common.hpp"
#include <iostream>
#include <string>
#include <map>

jclass nvgraphCSRTopology32I_Class;
jclass nvgraphCSCTopology32I_Class;
jclass nvgraphCOOTopology32I_Class;

// Field IDs for the nvgraphCSRTopology32I_st class
jfieldID fid_nvgraphCSRTopology32I_st_nvertices; // int
jfieldID fid_nvgraphCSRTopology32I_st_nedges; // int
jfieldID fid_nvgraphCSRTopology32I_st_source_offsets; // int *
jfieldID fid_nvgraphCSRTopology32I_st_destination_indices; // int *

// Field IDs for the nvgraphCSCTopology32I_st class
jfieldID fid_nvgraphCSCTopology32I_st_nvertices; // int
jfieldID fid_nvgraphCSCTopology32I_st_nedges; // int
jfieldID fid_nvgraphCSCTopology32I_st_destination_offsets; // int *
jfieldID fid_nvgraphCSCTopology32I_st_source_indices; // int *

// Field IDs for the nvgraphCOOTopology32I_st class
jfieldID fid_nvgraphCOOTopology32I_st_nvertices; // int
jfieldID fid_nvgraphCOOTopology32I_st_nedges; // int
jfieldID fid_nvgraphCOOTopology32I_st_source_indices; // int *
jfieldID fid_nvgraphCOOTopology32I_st_destination_indices; // int *
jfieldID fid_nvgraphCOOTopology32I_st_tag; // int


/**
 * Called when the library is loaded. Will initialize all
 * required field and method IDs
 */
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *jvm, void *reserved)
{
    JNIEnv *env = NULL;
    if (jvm->GetEnv((void **)&env, JNI_VERSION_1_4))
    {
        return JNI_ERR;
    }

    Logger::log(LOG_TRACE, "Initializing JNvgraph\n");


    // Initialize the JNIUtils and PointerUtils
    if (initJNIUtils(env) == JNI_ERR) return JNI_ERR;
    if (initPointerUtils(env) == JNI_ERR) return JNI_ERR;

    // Initialize the topology type classes
    if (!init(env, nvgraphCSRTopology32I_Class, "jcuda/jnvgraph/nvgraphCSRTopology32I")) return JNI_ERR;
    if (!init(env, nvgraphCSCTopology32I_Class, "jcuda/jnvgraph/nvgraphCSCTopology32I")) return JNI_ERR;
    if (!init(env, nvgraphCOOTopology32I_Class, "jcuda/jnvgraph/nvgraphCOOTopology32I")) return JNI_ERR;

    jclass cls = NULL;

    // Initialize the field IDs for the nvgraphCSRTopology32I_st class
    if (!init(env, cls, "jcuda/jnvgraph/nvgraphCSRTopology32I")) return JNI_ERR;
    if (!init(env, cls, fid_nvgraphCSRTopology32I_st_nvertices           , "nvertices"          , "I"              )) return JNI_ERR;
    if (!init(env, cls, fid_nvgraphCSRTopology32I_st_nedges              , "nedges"             , "I"              )) return JNI_ERR;
    if (!init(env, cls, fid_nvgraphCSRTopology32I_st_source_offsets      , "source_offsets"     , "Ljcuda/Pointer;")) return JNI_ERR;
    if (!init(env, cls, fid_nvgraphCSRTopology32I_st_destination_indices , "destination_indices", "Ljcuda/Pointer;")) return JNI_ERR;

    // Initialize the field IDs for the nvgraphCSCTopology32I_st class
    if (!init(env, cls, "jcuda/jnvgraph/nvgraphCSCTopology32I")) return JNI_ERR;
    if (!init(env, cls, fid_nvgraphCSCTopology32I_st_nvertices           , "nvertices"          , "I"              )) return JNI_ERR;
    if (!init(env, cls, fid_nvgraphCSCTopology32I_st_nedges              , "nedges"             , "I"              )) return JNI_ERR;
    if (!init(env, cls, fid_nvgraphCSCTopology32I_st_destination_offsets , "destination_offsets", "Ljcuda/Pointer;")) return JNI_ERR;
    if (!init(env, cls, fid_nvgraphCSCTopology32I_st_source_indices      , "source_indices"     , "Ljcuda/Pointer;")) return JNI_ERR;

    // Initialize the field IDs for the nvgraphCOOTopology32I_st class
    if (!init(env, cls, "jcuda/jnvgraph/nvgraphCOOTopology32I")) return JNI_ERR;
    if (!init(env, cls, fid_nvgraphCOOTopology32I_st_nvertices          , "nvertices"          , "I"))               return JNI_ERR;
    if (!init(env, cls, fid_nvgraphCOOTopology32I_st_nedges             , "nedges"             , "I"))               return JNI_ERR;
    if (!init(env, cls, fid_nvgraphCOOTopology32I_st_source_indices     , "source_indices"     , "Ljcuda/Pointer;")) return JNI_ERR;
    if (!init(env, cls, fid_nvgraphCOOTopology32I_st_destination_indices, "destination_indices", "Ljcuda/Pointer;")) return JNI_ERR;
    if (!init(env, cls, fid_nvgraphCOOTopology32I_st_tag                , "tag"                , "I"))               return JNI_ERR;


    return JNI_VERSION_1_4;
}


/**
* A structure containing all information necessary for maintaining
* the nvgraphCSCTopology32I or nvgraphCSRTopology32I parameters
*/
typedef struct nvgraphTopologyData
{
    /** The native nvgraph*Topology object */
    void *nativeTopologyData;

    /** The data for the source object (source_indices or source_offsets) */
    PointerData *source_PointerData;

    /** The data for the destination object (destination_offsets or destination_indices) */
    PointerData *destination_PointerData;

} Memcpy3DData;



/**
* Create a nvgraphToplogyData object from the given input.
* Returns NULL if the given object is NULL, or if any
* error occurs.
*/
nvgraphTopologyData* initNativeTopologyDataCSC32I(JNIEnv *env, jobject &input)
{
    if (input == NULL)
    {
        return NULL;
    }
    nvgraphTopologyData* result = new nvgraphTopologyData();

    nvgraphCSCTopology32I_st* nativeResult = new nvgraphCSCTopology32I_st();
    result->nativeTopologyData = nativeResult;

    nativeResult->nedges = (int)env->GetIntField(input, fid_nvgraphCSCTopology32I_st_nedges);
    nativeResult->nvertices = (int)env->GetIntField(input, fid_nvgraphCSCTopology32I_st_nvertices);

    jobject source = env->GetObjectField(input, fid_nvgraphCSCTopology32I_st_source_indices);
    result->source_PointerData = initPointerData(env, source);
    if (result->source_PointerData == NULL)
    {
        return NULL;
    }
    nativeResult->source_indices = (int*)result->source_PointerData->getPointer(env);

    jobject destination = env->GetObjectField(input, fid_nvgraphCSCTopology32I_st_destination_offsets);
    result->destination_PointerData = initPointerData(env, destination);
    if (result->destination_PointerData == NULL)
    {
        return NULL;
    }
    nativeResult->destination_offsets = (int*)result->destination_PointerData->getPointer(env);

    return result;
}

/**
 * Release the given nvgraphTopologyData. The source- and destination pointer data
 * will be released, and the information about the number of vertices and edges
 * will be written back into the given Java Object
 */
bool releaseNativeTopologyDataCSC32I(JNIEnv *env, nvgraphTopologyData* &nativeObject, jobject &javaObject)
{
    if (!releasePointerData(env, nativeObject->source_PointerData)) return false;
    if (!releasePointerData(env, nativeObject->destination_PointerData)) return false;
    if (javaObject != NULL)
    {
        nvgraphCSCTopology32I_st* nativeTopologyData = (nvgraphCSCTopology32I_st*)nativeObject->nativeTopologyData;
        env->SetIntField(javaObject, fid_nvgraphCSCTopology32I_st_nvertices, nativeTopologyData->nvertices);
        env->SetIntField(javaObject, fid_nvgraphCSCTopology32I_st_nedges, nativeTopologyData->nedges);
    }
    delete nativeObject->nativeTopologyData;
    delete nativeObject;
    nativeObject = NULL;
    return true;
}



/**
* Create a nvgraphToplogyData object from the given input.
* Returns NULL if the given object is NULL, or if any
* error occurs.
*/
nvgraphTopologyData* initNativeTopologyDataCSR32I(JNIEnv *env, jobject &javaObject)
{
    if (javaObject == NULL)
    {
        return NULL;
    }
    nvgraphTopologyData* result = new nvgraphTopologyData();

    nvgraphCSRTopology32I_st* nativeResult = new nvgraphCSRTopology32I_st();
    result->nativeTopologyData = nativeResult;

    nativeResult->nedges = (int)env->GetIntField(javaObject, fid_nvgraphCSRTopology32I_st_nedges);
    nativeResult->nvertices = (int)env->GetIntField(javaObject, fid_nvgraphCSRTopology32I_st_nvertices);

    jobject source = env->GetObjectField(javaObject, fid_nvgraphCSRTopology32I_st_source_offsets);
    result->source_PointerData = initPointerData(env, source);
    if (result->source_PointerData == NULL)
    {
        return NULL;
    }
    nativeResult->source_offsets = (int*)result->source_PointerData->getPointer(env);

    jobject destination = env->GetObjectField(javaObject, fid_nvgraphCSRTopology32I_st_destination_indices);
    result->destination_PointerData = initPointerData(env, destination);
    if (result->destination_PointerData == NULL)
    {
        return NULL;
    }
    nativeResult->destination_indices = (int*)result->destination_PointerData->getPointer(env);

    return result;
}

/**
* Release the given nvgraphTopologyData. The source- and destination pointer data
* will be released, and the information about the number of vertices and edges
* will be written back into the given Java Object
*/
bool releaseNativeTopologyDataCSR32I(JNIEnv *env, nvgraphTopologyData* &nativeObject, jobject &javaObject)
{
    if (!releasePointerData(env, nativeObject->source_PointerData)) return false;
    if (!releasePointerData(env, nativeObject->destination_PointerData)) return false;
    if (javaObject != NULL)
    {
        nvgraphCSRTopology32I_st* nativeTopologyData = (nvgraphCSRTopology32I_st*)nativeObject->nativeTopologyData;
        env->SetIntField(javaObject, fid_nvgraphCSRTopology32I_st_nvertices, nativeTopologyData->nvertices);
        env->SetIntField(javaObject, fid_nvgraphCSRTopology32I_st_nedges, nativeTopologyData->nedges);
    }
    delete nativeObject->nativeTopologyData;
    delete nativeObject;
    nativeObject = NULL;
    return true;
}

/**
* Create a nvgraphToplogyData object from the given input.
* Returns NULL if the given object is NULL, or if any
* error occurs.
*/
nvgraphTopologyData* initNativeTopologyDataCOO32I(JNIEnv *env, jobject &input)
{
    if (input == NULL)
    {
        return NULL;
    }
    nvgraphTopologyData* result = new nvgraphTopologyData();

    nvgraphCOOTopology32I_st* nativeResult = new nvgraphCOOTopology32I_st();
    result->nativeTopologyData = nativeResult;

    nativeResult->nedges = (int)env->GetIntField(input, fid_nvgraphCOOTopology32I_st_nedges);
    nativeResult->nvertices = (int)env->GetIntField(input, fid_nvgraphCOOTopology32I_st_nvertices);

    jobject source = env->GetObjectField(input, fid_nvgraphCOOTopology32I_st_source_indices);
    result->source_PointerData = initPointerData(env, source);
    if (result->source_PointerData == NULL)
    {
        return NULL;
    }
    nativeResult->source_indices = (int*)result->source_PointerData->getPointer(env);

    jobject destination = env->GetObjectField(input, fid_nvgraphCOOTopology32I_st_destination_indices);
    result->destination_PointerData = initPointerData(env, destination);
    if (result->destination_PointerData == NULL)
    {
        return NULL;
    }
    nativeResult->destination_indices = (int*)result->destination_PointerData->getPointer(env);

    nativeResult->tag = (nvgraphTag_t)env->GetIntField(input, fid_nvgraphCOOTopology32I_st_tag);

    return result;
}

/**
* Release the given nvgraphTopologyData. The source- and destination pointer data
* will be released, and the information about the number of vertices and edges
* will be written back into the given Java Object
*/
bool releaseNativeTopologyDataCOO32I(JNIEnv *env, nvgraphTopologyData* &nativeObject, jobject &javaObject)
{
    if (!releasePointerData(env, nativeObject->source_PointerData)) return false;
    if (!releasePointerData(env, nativeObject->destination_PointerData)) return false;
    if (javaObject != NULL)
    {
        nvgraphCOOTopology32I_st* nativeTopologyData = (nvgraphCOOTopology32I_st*)nativeObject->nativeTopologyData;
        env->SetIntField(javaObject, fid_nvgraphCOOTopology32I_st_nvertices, nativeTopologyData->nvertices);
        env->SetIntField(javaObject, fid_nvgraphCOOTopology32I_st_nedges, nativeTopologyData->nedges);
    }
    delete nativeObject->nativeTopologyData;
    delete nativeObject;
    nativeObject = NULL;
    return true;
}


/**
 * Create the nvgraphTopologyData object from the given 
 * Java nvgraphCSCTopology32I or nvgraphCSRTopology32I object.
 * Returns NULL if the given object is NULL, or if any
 * error occurs.
 * Throws an IllegalArgumentException is the given input
 * object does not have a known nvGRAPH topology type
 */
nvgraphTopologyData* initNativeTopologyData(JNIEnv *env, jobject &javaObject)
{
    if (javaObject == NULL)
    {
        return NULL;
    }
    if (env->IsInstanceOf(javaObject, nvgraphCSCTopology32I_Class))
    {
        return initNativeTopologyDataCSC32I(env, javaObject);
    }
    else if (env->IsInstanceOf(javaObject, nvgraphCSRTopology32I_Class))
    {
        return initNativeTopologyDataCSR32I(env, javaObject);
    }
    else if (env->IsInstanceOf(javaObject, nvgraphCOOTopology32I_Class))
    {
        return initNativeTopologyDataCOO32I(env, javaObject);
    }
    ThrowByName(env, "java/lang/IllegalArgumentException",
        "Topology data parameter does not have a valid type");
    return false;
}

/**
 * Release the given nvgraphTopologyData 
 */
bool releaseNativeTopologyData(JNIEnv *env, nvgraphTopologyData* &nativeObject, jobject &javaObject)
{
    if (nativeObject == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException",
            "Native topology data is NULL");
        return false;
    }
    if (javaObject == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException",
            "Java topology data is NULL");
        return false;
    }
    if (env->IsInstanceOf(javaObject, nvgraphCSCTopology32I_Class))
    {
        return releaseNativeTopologyDataCSC32I(env, nativeObject, javaObject);
    }
    else if (env->IsInstanceOf(javaObject, nvgraphCSRTopology32I_Class))
    {
        return releaseNativeTopologyDataCSR32I(env, nativeObject, javaObject);
    }
    else if (env->IsInstanceOf(javaObject, nvgraphCOOTopology32I_Class))
    {
        return releaseNativeTopologyDataCOO32I(env, nativeObject, javaObject);
    }
    ThrowByName(env, "java/lang/IllegalArgumentException",
        "Topology data parameter does not have a valid type");
    return false;
}


/*
* Set the log level
*
* Class:     jcuda_jnvgraph_JNvgraph
* Method:    setLogLevelNative
* Signature: (I)V
*/
JNIEXPORT void JNICALL Java_jcuda_jnvgraph_JNvgraph_setLogLevelNative
(JNIEnv *env, jclass cla, jint logLevel)
{
    Logger::setLogLevel((LogLevel)logLevel);
}



JNIEXPORT jstring JNICALL Java_jcuda_jnvgraph_JNvgraph_nvgraphStatusGetStringNative(JNIEnv *env, jclass cls, jint status)
{
    // Null-checks for non-primitive arguments
    // status is primitive

    // Log message
    Logger::log(LOG_TRACE, "Executing nvgraphStatusGetString(status=%d)\n",
        status);

    // Native variable declarations
    nvgraphStatus_t status_native = NVGRAPH_STATUS_SUCCESS;

    // Obtain native variable values
    status_native = (nvgraphStatus_t)status;

    // Native function call
    char const * jniResult_native = nvgraphStatusGetString(status_native);

    // Write back native variable values
    // status is primitive

    // Return the result
    return env->NewStringUTF(jniResult_native);
}

/** Open the library and create the handle */
JNIEXPORT jint JNICALL Java_jcuda_jnvgraph_JNvgraph_nvgraphCreateNative(JNIEnv *env, jclass cls, jobject handle)
{
    // Null-checks for non-primitive arguments
    if (handle == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'handle' is null for nvgraphCreate");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }

    // Log message
    Logger::log(LOG_TRACE, "Executing nvgraphCreate(handle=%p)\n",
        handle);

    // Native variable declarations
    nvgraphHandle_t handle_native;

    // Obtain native variable values
    // handle is write-only

    // Native function call
    nvgraphStatus_t jniResult_native = nvgraphCreate(&handle_native);

    // Write back native variable values
    setNativePointerValue(env, handle, (jlong)handle_native);

    // Return the result
    jint jniResult = (jint)jniResult_native;
    return jniResult;
}

/**  Close the library and destroy the handle  */
JNIEXPORT jint JNICALL Java_jcuda_jnvgraph_JNvgraph_nvgraphDestroyNative(JNIEnv *env, jclass cls, jobject handle)
{
    // Null-checks for non-primitive arguments
    if (handle == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'handle' is null for nvgraphDestroy");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }

    // Log message
    Logger::log(LOG_TRACE, "Executing nvgraphDestroy(handle=%p)\n",
        handle);

    // Native variable declarations
    nvgraphHandle_t handle_native;

    // Obtain native variable values
    handle_native = (nvgraphHandle_t)getNativePointerValue(env, handle);

    // Native function call
    nvgraphStatus_t jniResult_native = nvgraphDestroy(handle_native);

    // Write back native variable values
    // handle is read-only

    // Return the result
    jint jniResult = (jint)jniResult_native;
    return jniResult;
}

/** Create an empty graph descriptor */
JNIEXPORT jint JNICALL Java_jcuda_jnvgraph_JNvgraph_nvgraphCreateGraphDescrNative(JNIEnv *env, jclass cls, jobject handle, jobject descrG)
{
    // Null-checks for non-primitive arguments
    if (handle == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'handle' is null for nvgraphCreateGraphDescr");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    if (descrG == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'descrG' is null for nvgraphCreateGraphDescr");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }

    // Log message
    Logger::log(LOG_TRACE, "Executing nvgraphCreateGraphDescr(handle=%p, descrG=%p)\n",
        handle, descrG);

    // Native variable declarations
    nvgraphHandle_t handle_native;
    nvgraphGraphDescr_t descrG_native;

    // Obtain native variable values
    handle_native = (nvgraphHandle_t)getNativePointerValue(env, handle);
    // descrG is write-only

    // Native function call
    nvgraphStatus_t jniResult_native = nvgraphCreateGraphDescr(handle_native, &descrG_native);

    // Write back native variable values
    // handle is read-only
    setNativePointerValue(env, descrG, (jlong)descrG_native);

    // Return the result
    jint jniResult = (jint)jniResult_native;
    return jniResult;
}

/** Destroy a graph descriptor */
JNIEXPORT jint JNICALL Java_jcuda_jnvgraph_JNvgraph_nvgraphDestroyGraphDescrNative(JNIEnv *env, jclass cls, jobject handle, jobject descrG)
{
    // Null-checks for non-primitive arguments
    if (handle == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'handle' is null for nvgraphDestroyGraphDescr");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    if (descrG == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'descrG' is null for nvgraphDestroyGraphDescr");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }

    // Log message
    Logger::log(LOG_TRACE, "Executing nvgraphDestroyGraphDescr(handle=%p, descrG=%p)\n",
        handle, descrG);

    // Native variable declarations
    nvgraphHandle_t handle_native;
    nvgraphGraphDescr_t descrG_native;

    // Obtain native variable values
    handle_native = (nvgraphHandle_t)getNativePointerValue(env, handle);
    descrG_native = (nvgraphGraphDescr_t)getNativePointerValue(env, descrG);

    // Native function call
    nvgraphStatus_t jniResult_native = nvgraphDestroyGraphDescr(handle_native, descrG_native);

    // Write back native variable values
    // handle is read-only
    // descrG is read-only

    // Return the result
    jint jniResult = (jint)jniResult_native;
    return jniResult;
}

/** Set size, topology data in the graph descriptor  */
JNIEXPORT jint JNICALL Java_jcuda_jnvgraph_JNvgraph_nvgraphSetGraphStructureNative(JNIEnv *env, jclass cls, jobject handle, jobject descrG, jobject topologyData, jint TType)
{
    // Null-checks for non-primitive arguments
    if (handle == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'handle' is null for nvgraphSetGraphStructure");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    if (descrG == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'descrG' is null for nvgraphSetGraphStructure");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    if (topologyData == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'topologyData' is null for nvgraphSetGraphStructure");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    // TType is primitive

    // Log message
    Logger::log(LOG_TRACE, "Executing nvgraphSetGraphStructure(handle=%p, descrG=%p, topologyData=%p, TType=%d)\n",
        handle, descrG, topologyData, TType);

    // Native variable declarations
    nvgraphHandle_t handle_native;
    nvgraphGraphDescr_t descrG_native;
    void * topologyData_native;
    nvgraphTopologyType_t TType_native;

    // Obtain native variable values
    handle_native = (nvgraphHandle_t)getNativePointerValue(env, handle);
    descrG_native = (nvgraphGraphDescr_t)getNativePointerValue(env, descrG);
    nvgraphTopologyData* topologyData_Data = initNativeTopologyData(env, topologyData);
    if (topologyData_Data == NULL)
    {
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    topologyData_native = topologyData_Data->nativeTopologyData;
    TType_native = (nvgraphTopologyType_t)TType;

    // Native function call
    nvgraphStatus_t jniResult_native = nvgraphSetGraphStructure(handle_native, descrG_native, topologyData_native, TType_native);

    // Write back native variable values
    // handle is read-only
    // descrG is read-only
    if (!releaseNativeTopologyData(env, topologyData_Data, topologyData)) return JNVGRAPH_STATUS_INTERNAL_ERROR;
    // TType is primitive

    // Return the result
    jint jniResult = (jint)jniResult_native;
    return jniResult;
}

/** Query size and topology information from the graph descriptor */
JNIEXPORT jint JNICALL Java_jcuda_jnvgraph_JNvgraph_nvgraphGetGraphStructureNative(JNIEnv *env, jclass cls, jobject handle, jobject descrG, jobject topologyData, jintArray TType)
{
    // Null-checks for non-primitive arguments
    if (handle == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'handle' is null for nvgraphGetGraphStructure");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    if (descrG == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'descrG' is null for nvgraphGetGraphStructure");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    if (topologyData == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'topologyData' is null for nvgraphGetGraphStructure");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    if (TType == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'TType' is null for nvgraphGetGraphStructure");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }

    // Log message
    Logger::log(LOG_TRACE, "Executing nvgraphGetGraphStructure(handle=%p, descrG=%p, topologyData=%p, TType=%p)\n",
        handle, descrG, topologyData, TType);

    // Native variable declarations
    nvgraphHandle_t handle_native;
    nvgraphGraphDescr_t descrG_native;
    void * topologyData_native;
    nvgraphTopologyType_t TType_native;

    // Obtain native variable values
    handle_native = (nvgraphHandle_t)getNativePointerValue(env, handle);
    descrG_native = (nvgraphGraphDescr_t)getNativePointerValue(env, descrG);
    nvgraphTopologyData* topologyData_Data = initNativeTopologyData(env, topologyData);
    if (topologyData_Data == NULL)
    {
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    topologyData_native = topologyData_Data->nativeTopologyData;

    // Native function call
    nvgraphStatus_t jniResult_native = nvgraphGetGraphStructure(handle_native, descrG_native, topologyData_native, &TType_native);

    // Write back native variable values
    // handle is read-only
    // descrG is read-only
    if (!releaseNativeTopologyData(env, topologyData_Data, topologyData)) return JNVGRAPH_STATUS_INTERNAL_ERROR;
    if (!set(env, TType, 0, (jint)TType_native)) return JNVGRAPH_STATUS_INTERNAL_ERROR;

    // Return the result
    jint jniResult = (jint)jniResult_native;
    return jniResult;
}

/** Allocate numsets vectors of size V reprensenting Vertex Data and attached them the graph.
* settypes[i] is the type of vector #i, currently all Vertex and Edge data should have the same type */
JNIEXPORT jint JNICALL Java_jcuda_jnvgraph_JNvgraph_nvgraphAllocateVertexDataNative(JNIEnv *env, jclass cls, jobject handle, jobject descrG, jlong numsets, jobject settypes)
{
    // Null-checks for non-primitive arguments
    if (handle == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'handle' is null for nvgraphAllocateVertexData");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    if (descrG == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'descrG' is null for nvgraphAllocateVertexData");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    // numsets is primitive
    if (settypes == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'settypes' is null for nvgraphAllocateVertexData");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }

    // Log message
    Logger::log(LOG_TRACE, "Executing nvgraphAllocateVertexData(handle=%p, descrG=%p, numsets=%ld, settypes=%p)\n",
        handle, descrG, numsets, settypes);

    // Native variable declarations
    nvgraphHandle_t handle_native;
    nvgraphGraphDescr_t descrG_native;
    size_t numsets_native = 0;
    cudaDataType_t * settypes_native = NULL;

    // Obtain native variable values
    handle_native = (nvgraphHandle_t)getNativePointerValue(env, handle);
    descrG_native = (nvgraphGraphDescr_t)getNativePointerValue(env, descrG);
    numsets_native = (size_t)numsets;
    PointerData *settypes_pointerData = initPointerData(env, settypes);
    if (settypes_pointerData == NULL)
    {
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    settypes_native = (cudaDataType_t *)settypes_pointerData->getPointer(env);

    // Native function call
    nvgraphStatus_t jniResult_native = nvgraphAllocateVertexData(handle_native, descrG_native, numsets_native, settypes_native);

    // Write back native variable values
    // handle is read-only
    // descrG is read-only
    // numsets is primitive
    if (!releasePointerData(env, settypes_pointerData, JNI_ABORT)) return JNVGRAPH_STATUS_INTERNAL_ERROR;

    // Return the result
    jint jniResult = (jint)jniResult_native;
    return jniResult;
}

/** Allocate numsets vectors of size E reprensenting Edge Data and attached them the graph.
* settypes[i] is the type of vector #i, currently all Vertex and Edge data should have the same type */
JNIEXPORT jint JNICALL Java_jcuda_jnvgraph_JNvgraph_nvgraphAllocateEdgeDataNative(JNIEnv *env, jclass cls, jobject handle, jobject descrG, jlong numsets, jobject settypes)
{
    // Null-checks for non-primitive arguments
    if (handle == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'handle' is null for nvgraphAllocateEdgeData");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    if (descrG == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'descrG' is null for nvgraphAllocateEdgeData");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    // numsets is primitive
    if (settypes == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'settypes' is null for nvgraphAllocateEdgeData");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }

    // Log message
    Logger::log(LOG_TRACE, "Executing nvgraphAllocateEdgeData(handle=%p, descrG=%p, numsets=%ld, settypes=%p)\n",
        handle, descrG, numsets, settypes);

    // Native variable declarations
    nvgraphHandle_t handle_native;
    nvgraphGraphDescr_t descrG_native;
    size_t numsets_native = 0;
    cudaDataType_t * settypes_native = NULL;

    // Obtain native variable values
    handle_native = (nvgraphHandle_t)getNativePointerValue(env, handle);
    descrG_native = (nvgraphGraphDescr_t)getNativePointerValue(env, descrG);
    numsets_native = (size_t)numsets;
    PointerData *settypes_pointerData = initPointerData(env, settypes);
    if (settypes_pointerData == NULL)
    {
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    settypes_native = (cudaDataType_t *)settypes_pointerData->getPointer(env);

    // Native function call
    nvgraphStatus_t jniResult_native = nvgraphAllocateEdgeData(handle_native, descrG_native, numsets_native, settypes_native);

    // Write back native variable values
    // handle is read-only
    // descrG is read-only
    // numsets is primitive
    if (!releasePointerData(env, settypes_pointerData, JNI_ABORT)) return JNVGRAPH_STATUS_INTERNAL_ERROR;

    // Return the result
    jint jniResult = (jint)jniResult_native;
    return jniResult;
}

/** Update the vertex set #setnum with the data in *vertexData, sets have 0-based index
*  Conversions are not sopported so nvgraphTopologyType_t should match the graph structure */
JNIEXPORT jint JNICALL Java_jcuda_jnvgraph_JNvgraph_nvgraphSetVertexDataNative(JNIEnv *env, jclass cls, jobject handle, jobject descrG, jobject vertexData, jlong setnum)
{
    // Null-checks for non-primitive arguments
    if (handle == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'handle' is null for nvgraphSetVertexData");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    if (descrG == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'descrG' is null for nvgraphSetVertexData");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    if (vertexData == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'vertexData' is null for nvgraphSetVertexData");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    // setnum is primitive

    // Log message
    Logger::log(LOG_TRACE, "Executing nvgraphSetVertexData(handle=%p, descrG=%p, vertexData=%p, setnum=%ld)\n",
        handle, descrG, vertexData, setnum);

    // Native variable declarations
    nvgraphHandle_t handle_native;
    nvgraphGraphDescr_t descrG_native;
    void * vertexData_native = NULL;
    size_t setnum_native = 0;

    // Obtain native variable values
    handle_native = (nvgraphHandle_t)getNativePointerValue(env, handle);
    descrG_native = (nvgraphGraphDescr_t)getNativePointerValue(env, descrG);
    PointerData *vertexData_pointerData = initPointerData(env, vertexData);
    if (vertexData_pointerData == NULL)
    {
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    vertexData_native = (void *)vertexData_pointerData->getPointer(env);
    setnum_native = (size_t)setnum;

    // Native function call
    nvgraphStatus_t jniResult_native = nvgraphSetVertexData(handle_native, descrG_native, vertexData_native, setnum_native);

    // Write back native variable values
    // handle is read-only
    // descrG is read-only
    if (!releasePointerData(env, vertexData_pointerData, JNI_ABORT)) return JNVGRAPH_STATUS_INTERNAL_ERROR;
    // setnum is primitive

    // Return the result
    jint jniResult = (jint)jniResult_native;
    return jniResult;
}

/** Copy the edge set #setnum in *edgeData, sets have 0-based index
*  Conversions are not sopported so nvgraphTopologyType_t should match the graph structure */
JNIEXPORT jint JNICALL Java_jcuda_jnvgraph_JNvgraph_nvgraphGetVertexDataNative(JNIEnv *env, jclass cls, jobject handle, jobject descrG, jobject vertexData, jlong setnum)
{
    // Null-checks for non-primitive arguments
    if (handle == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'handle' is null for nvgraphGetVertexData");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    if (descrG == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'descrG' is null for nvgraphGetVertexData");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    if (vertexData == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'vertexData' is null for nvgraphGetVertexData");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    // setnum is primitive

    // Log message
    Logger::log(LOG_TRACE, "Executing nvgraphGetVertexData(handle=%p, descrG=%p, vertexData=%p, setnum=%ld)\n",
        handle, descrG, vertexData, setnum);

    // Native variable declarations
    nvgraphHandle_t handle_native;
    nvgraphGraphDescr_t descrG_native;
    void * vertexData_native = NULL;
    size_t setnum_native = 0;

    // Obtain native variable values
    handle_native = (nvgraphHandle_t)getNativePointerValue(env, handle);
    descrG_native = (nvgraphGraphDescr_t)getNativePointerValue(env, descrG);
    PointerData *vertexData_pointerData = initPointerData(env, vertexData);
    if (vertexData_pointerData == NULL)
    {
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    vertexData_native = (void *)vertexData_pointerData->getPointer(env);
    setnum_native = (size_t)setnum;

    // Native function call
    nvgraphStatus_t jniResult_native = nvgraphGetVertexData(handle_native, descrG_native, vertexData_native, setnum_native);

    // Write back native variable values
    // handle is read-only
    // descrG is read-only
    // If the PointerData is not backed by native memory, then this call has to block
    if (!isPointerBackedByNativeMemory(env, vertexData))
    {
        cudaDeviceSynchronize();
    }
    if (!releasePointerData(env, vertexData_pointerData, 0)) return JNVGRAPH_STATUS_INTERNAL_ERROR;
    // setnum is primitive

    // Return the result
    jint jniResult = (jint)jniResult_native;
    return jniResult;
}

/** Convert the edge data to another topology
*/
JNIEXPORT jint JNICALL Java_jcuda_jnvgraph_JNvgraph_nvgraphConvertTopologyNative(JNIEnv *env, jclass cls, jobject handle, jint srcTType, jobject srcTopology, jobject srcEdgeData, jobject dataType, jint dstTType, jobject dstTopology, jobject dstEdgeData)
{
    // Null-checks for non-primitive arguments
    if (handle == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'handle' is null for nvgraphConvertTopology");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    // srcTType is primitive
    if (srcTopology == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'srcTopology' is null for nvgraphConvertTopology");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    if (srcEdgeData == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'srcEdgeData' is null for nvgraphConvertTopology");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    if (dataType == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'dataType' is null for nvgraphConvertTopology");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    // dstTType is primitive
    if (dstTopology == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'dstTopology' is null for nvgraphConvertTopology");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    if (dstEdgeData == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'dstEdgeData' is null for nvgraphConvertTopology");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }

    // Log message
    Logger::log(LOG_TRACE, "Executing nvgraphConvertTopology(handle=%p, srcTType=%d, srcTopology=%p, srcEdgeData=%p, dataType=%p, dstTType=%d, dstTopology=%p, dstEdgeData=%p)\n",
        handle, srcTType, srcTopology, srcEdgeData, dataType, dstTType, dstTopology, dstEdgeData);

    // Native variable declarations
    nvgraphHandle_t handle_native;
    nvgraphTopologyType_t srcTType_native;
    void * srcTopology_native = NULL;
    void * srcEdgeData_native = NULL;
    cudaDataType_t * dataType_native = NULL;
    nvgraphTopologyType_t dstTType_native;
    void * dstTopology_native = NULL;
    void * dstEdgeData_native = NULL;

    // Obtain native variable values
    handle_native = (nvgraphHandle_t)getNativePointerValue(env, handle);
    srcTType_native = (nvgraphTopologyType_t)srcTType;
    nvgraphTopologyData* srcTopology_Data = initNativeTopologyData(env, srcTopology);
    if (srcTopology_Data == NULL)
    {
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    srcTopology_native = srcTopology_Data->nativeTopologyData;
    PointerData *srcEdgeData_pointerData = initPointerData(env, srcEdgeData);
    if (srcEdgeData_pointerData == NULL)
    {
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    srcEdgeData_native = srcEdgeData_pointerData->getPointer(env);
    PointerData *dataType_pointerData = initPointerData(env, dataType);
    if (dataType_pointerData == NULL)
    {
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    dataType_native = (cudaDataType_t *)dataType_pointerData->getPointer(env);
    dstTType_native = (nvgraphTopologyType_t)dstTType;
    nvgraphTopologyData* dstTopology_Data = initNativeTopologyData(env, dstTopology);
    if (dstTopology_Data == NULL)
    {
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    dstTopology_native = dstTopology_Data->nativeTopologyData;
    PointerData *dstEdgeData_pointerData = initPointerData(env, dstEdgeData);
    if (dstEdgeData_pointerData == NULL)
    {
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    dstEdgeData_native = dstEdgeData_pointerData->getPointer(env);

    // Native function call
    nvgraphStatus_t jniResult_native = nvgraphConvertTopology(handle_native, srcTType_native, srcTopology_native, srcEdgeData_native, dataType_native, dstTType_native, dstTopology_native, dstEdgeData_native);

    // Write back native variable values
    // handle is read-only
    // srcTType is primitive
    if (!releaseNativeTopologyData(env, srcTopology_Data, srcTopology)) return JNVGRAPH_STATUS_INTERNAL_ERROR;
    if (!releasePointerData(env, srcEdgeData_pointerData, 0)) return JNVGRAPH_STATUS_INTERNAL_ERROR;
    if (!releasePointerData(env, dataType_pointerData, JNI_ABORT)) return JNVGRAPH_STATUS_INTERNAL_ERROR;
    // dstTType is primitive
    if (!releaseNativeTopologyData(env, dstTopology_Data, dstTopology)) return JNVGRAPH_STATUS_INTERNAL_ERROR;
    if (!releasePointerData(env, dstEdgeData_pointerData, 0)) return JNVGRAPH_STATUS_INTERNAL_ERROR;

    // Return the result
    jint jniResult = (jint)jniResult_native;
    return jniResult;
}

/** Convert graph to another structure
*/
JNIEXPORT jint JNICALL Java_jcuda_jnvgraph_JNvgraph_nvgraphConvertGraphNative(JNIEnv *env, jclass cls, jobject handle, jobject srcDescrG, jobject dstDescrG, jint dstTType)
{
    // Null-checks for non-primitive arguments
    if (handle == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'handle' is null for nvgraphConvertGraph");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    if (srcDescrG == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'srcDescrG' is null for nvgraphConvertGraph");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    if (dstDescrG == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'dstDescrG' is null for nvgraphConvertGraph");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    // dstTType is primitive

    // Log message
    Logger::log(LOG_TRACE, "Executing nvgraphConvertGraph(handle=%p, srcDescrG=%p, dstDescrG=%p, dstTType=%d)\n",
        handle, srcDescrG, dstDescrG, dstTType);

    // Native variable declarations
    nvgraphHandle_t handle_native;
    nvgraphGraphDescr_t srcDescrG_native;
    nvgraphGraphDescr_t dstDescrG_native;
    nvgraphTopologyType_t dstTType_native;

    // Obtain native variable values
    handle_native = (nvgraphHandle_t)getNativePointerValue(env, handle);
    srcDescrG_native = (nvgraphGraphDescr_t)getNativePointerValue(env, srcDescrG);
    dstDescrG_native = (nvgraphGraphDescr_t)getNativePointerValue(env, dstDescrG);
    dstTType_native = (nvgraphTopologyType_t)dstTType;

    // Native function call
    nvgraphStatus_t jniResult_native = nvgraphConvertGraph(handle_native, srcDescrG_native, dstDescrG_native, dstTType_native);

    // Write back native variable values
    // handle is read-only
    // srcDescrG is read-only
    // dstDescrG is read-only
    // dstTType is primitive

    // Return the result
    jint jniResult = (jint)jniResult_native;
    return jniResult;
}

/** Update the edge set #setnum with the data in *edgeData, sets have 0-based index
*  Conversions are not sopported so nvgraphTopologyType_t should match the graph structure */
JNIEXPORT jint JNICALL Java_jcuda_jnvgraph_JNvgraph_nvgraphSetEdgeDataNative(JNIEnv *env, jclass cls, jobject handle, jobject descrG, jobject edgeData, jlong setnum)
{
    // Null-checks for non-primitive arguments
    if (handle == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'handle' is null for nvgraphSetEdgeData");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    if (descrG == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'descrG' is null for nvgraphSetEdgeData");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    if (edgeData == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'edgeData' is null for nvgraphSetEdgeData");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    // setnum is primitive

    // Log message
    Logger::log(LOG_TRACE, "Executing nvgraphSetEdgeData(handle=%p, descrG=%p, edgeData=%p, setnum=%ld)\n",
        handle, descrG, edgeData, setnum);

    // Native variable declarations
    nvgraphHandle_t handle_native;
    nvgraphGraphDescr_t descrG_native;
    void * edgeData_native = NULL;
    size_t setnum_native = 0;

    // Obtain native variable values
    handle_native = (nvgraphHandle_t)getNativePointerValue(env, handle);
    descrG_native = (nvgraphGraphDescr_t)getNativePointerValue(env, descrG);
    PointerData *edgeData_pointerData = initPointerData(env, edgeData);
    if (edgeData_pointerData == NULL)
    {
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    edgeData_native = (void *)edgeData_pointerData->getPointer(env);
    setnum_native = (size_t)setnum;

    // Native function call
    nvgraphStatus_t jniResult_native = nvgraphSetEdgeData(handle_native, descrG_native, edgeData_native, setnum_native);

    // Write back native variable values
    // handle is read-only
    // descrG is read-only
    if (!releasePointerData(env, edgeData_pointerData, JNI_ABORT)) return JNVGRAPH_STATUS_INTERNAL_ERROR;
    // setnum is primitive

    // Return the result
    jint jniResult = (jint)jniResult_native;
    return jniResult;
}

/** Copy the edge set #setnum in *edgeData, sets have 0-based index
* Conversions are not sopported so nvgraphTopologyType_t should match the graph structure */
JNIEXPORT jint JNICALL Java_jcuda_jnvgraph_JNvgraph_nvgraphGetEdgeDataNative(JNIEnv *env, jclass cls, jobject handle, jobject descrG, jobject edgeData, jlong setnum)
{
    // Null-checks for non-primitive arguments
    if (handle == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'handle' is null for nvgraphGetEdgeData");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    if (descrG == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'descrG' is null for nvgraphGetEdgeData");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    if (edgeData == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'edgeData' is null for nvgraphGetEdgeData");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    // setnum is primitive

    // Log message
    Logger::log(LOG_TRACE, "Executing nvgraphGetEdgeData(handle=%p, descrG=%p, edgeData=%p, setnum=%ld)\n",
        handle, descrG, edgeData, setnum);

    // Native variable declarations
    nvgraphHandle_t handle_native;
    nvgraphGraphDescr_t descrG_native;
    void * edgeData_native = NULL;
    size_t setnum_native = 0;

    // Obtain native variable values
    handle_native = (nvgraphHandle_t)getNativePointerValue(env, handle);
    descrG_native = (nvgraphGraphDescr_t)getNativePointerValue(env, descrG);
    PointerData *edgeData_pointerData = initPointerData(env, edgeData);
    if (edgeData_pointerData == NULL)
    {
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    edgeData_native = (void *)edgeData_pointerData->getPointer(env);
    setnum_native = (size_t)setnum;

    // Native function call
    nvgraphStatus_t jniResult_native = nvgraphGetEdgeData(handle_native, descrG_native, edgeData_native, setnum_native);

    // Write back native variable values
    // handle is read-only
    // descrG is read-only
    // If the PointerData is not backed by native memory, then this call has to block
    if (!isPointerBackedByNativeMemory(env, edgeData))
    {
        cudaDeviceSynchronize();
    }
    if (!releasePointerData(env, edgeData_pointerData, 0)) return JNVGRAPH_STATUS_INTERNAL_ERROR;
    // setnum is primitive

    // Return the result
    jint jniResult = (jint)jniResult_native;
    return jniResult;
}

/** create a new graph by extracting a subgraph given a list of vertices
*/
JNIEXPORT jint JNICALL Java_jcuda_jnvgraph_JNvgraph_nvgraphExtractSubgraphByVertexNative(JNIEnv *env, jclass cls, jobject handle, jobject descrG, jobject subdescrG, jobject subvertices, jlong numvertices)
{
    // Null-checks for non-primitive arguments
    if (handle == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'handle' is null for nvgraphExtractSubgraphByVertex");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    if (descrG == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'descrG' is null for nvgraphExtractSubgraphByVertex");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    if (subdescrG == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'subdescrG' is null for nvgraphExtractSubgraphByVertex");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    if (subvertices == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'subvertices' is null for nvgraphExtractSubgraphByVertex");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    // numvertices is primitive

    // Log message
    Logger::log(LOG_TRACE, "Executing nvgraphExtractSubgraphByVertex(handle=%p, descrG=%p, subdescrG=%p, subvertices=%p, numvertices=%ld)\n",
        handle, descrG, subdescrG, subvertices, numvertices);

    // Native variable declarations
    nvgraphHandle_t handle_native;
    nvgraphGraphDescr_t descrG_native;
    nvgraphGraphDescr_t subdescrG_native;
    int * subvertices_native = NULL;
    size_t numvertices_native = 0;

    // Obtain native variable values
    handle_native = (nvgraphHandle_t)getNativePointerValue(env, handle);
    descrG_native = (nvgraphGraphDescr_t)getNativePointerValue(env, descrG);
    subdescrG_native = (nvgraphGraphDescr_t)getNativePointerValue(env, subdescrG);
    PointerData *subvertices_pointerData = initPointerData(env, subvertices);
    if (subvertices_pointerData == NULL)
    {
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    subvertices_native = (int *)subvertices_pointerData->getPointer(env);
    numvertices_native = (size_t)numvertices;

    // Native function call
    nvgraphStatus_t jniResult_native = nvgraphExtractSubgraphByVertex(handle_native, descrG_native, subdescrG_native, subvertices_native, numvertices_native);

    // Write back native variable values
    // handle is read-only
    // descrG is read-only
    // subdescrG is read-only
    if (!releasePointerData(env, subvertices_pointerData, JNI_ABORT)) return JNVGRAPH_STATUS_INTERNAL_ERROR;
    // numvertices is primitive

    // Return the result
    jint jniResult = (jint)jniResult_native;
    return jniResult;
}

/** create a new graph by extracting a subgraph given a list of edges
*/
JNIEXPORT jint JNICALL Java_jcuda_jnvgraph_JNvgraph_nvgraphExtractSubgraphByEdgeNative(JNIEnv *env, jclass cls, jobject handle, jobject descrG, jobject subdescrG, jobject subedges, jlong numedges)
{
    // Null-checks for non-primitive arguments
    if (handle == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'handle' is null for nvgraphExtractSubgraphByEdge");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    if (descrG == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'descrG' is null for nvgraphExtractSubgraphByEdge");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    if (subdescrG == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'subdescrG' is null for nvgraphExtractSubgraphByEdge");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    if (subedges == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'subedges' is null for nvgraphExtractSubgraphByEdge");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    // numedges is primitive

    // Log message
    Logger::log(LOG_TRACE, "Executing nvgraphExtractSubgraphByEdge(handle=%p, descrG=%p, subdescrG=%p, subedges=%p, numedges=%ld)\n",
        handle, descrG, subdescrG, subedges, numedges);

    // Native variable declarations
    nvgraphHandle_t handle_native;
    nvgraphGraphDescr_t descrG_native;
    nvgraphGraphDescr_t subdescrG_native;
    int * subedges_native = NULL;
    size_t numedges_native = 0;

    // Obtain native variable values
    handle_native = (nvgraphHandle_t)getNativePointerValue(env, handle);
    descrG_native = (nvgraphGraphDescr_t)getNativePointerValue(env, descrG);
    subdescrG_native = (nvgraphGraphDescr_t)getNativePointerValue(env, subdescrG);
    PointerData *subedges_pointerData = initPointerData(env, subedges);
    if (subedges_pointerData == NULL)
    {
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    subedges_native = (int *)subedges_pointerData->getPointer(env);
    numedges_native = (size_t)numedges;

    // Native function call
    nvgraphStatus_t jniResult_native = nvgraphExtractSubgraphByEdge(handle_native, descrG_native, subdescrG_native, subedges_native, numedges_native);

    // Write back native variable values
    // handle is read-only
    // descrG is read-only
    // subdescrG is read-only
    if (!releasePointerData(env, subedges_pointerData, JNI_ABORT)) return JNVGRAPH_STATUS_INTERNAL_ERROR;
    // numedges is primitive

    // Return the result
    jint jniResult = (jint)jniResult_native;
    return jniResult;
}

/** nvGRAPH Semi-ring sparse matrix vector multiplication
*/
JNIEXPORT jint JNICALL Java_jcuda_jnvgraph_JNvgraph_nvgraphSrSpmvNative(JNIEnv *env, jclass cls, jobject handle, jobject descrG, jlong weight_index, jobject alpha, jlong x_index, jobject beta, jlong y_index, jint SR)
{
    // Null-checks for non-primitive arguments
    if (handle == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'handle' is null for nvgraphSrSpmv");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    if (descrG == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'descrG' is null for nvgraphSrSpmv");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    // weight_index is primitive
    if (alpha == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'alpha' is null for nvgraphSrSpmv");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    // x_index is primitive
    if (beta == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'beta' is null for nvgraphSrSpmv");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    // y_index is primitive
    // SR is primitive

    // Log message
    Logger::log(LOG_TRACE, "Executing nvgraphSrSpmv(handle=%p, descrG=%p, weight_index=%ld, alpha=%p, x_index=%ld, beta=%p, y_index=%ld, SR=%d)\n",
        handle, descrG, weight_index, alpha, x_index, beta, y_index, SR);

    // Native variable declarations
    nvgraphHandle_t handle_native;
    nvgraphGraphDescr_t descrG_native;
    size_t weight_index_native = 0;
    void * alpha_native = NULL;
    size_t x_index_native = 0;
    void * beta_native = NULL;
    size_t y_index_native = 0;
    nvgraphSemiring_t SR_native;

    // Obtain native variable values
    handle_native = (nvgraphHandle_t)getNativePointerValue(env, handle);
    descrG_native = (nvgraphGraphDescr_t)getNativePointerValue(env, descrG);
    weight_index_native = (size_t)weight_index;
    PointerData *alpha_pointerData = initPointerData(env, alpha);
    if (alpha_pointerData == NULL)
    {
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    alpha_native = (void *)alpha_pointerData->getPointer(env);
    x_index_native = (size_t)x_index;
    PointerData *beta_pointerData = initPointerData(env, beta);
    if (beta_pointerData == NULL)
    {
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    beta_native = (void *)beta_pointerData->getPointer(env);
    y_index_native = (size_t)y_index;
    SR_native = (nvgraphSemiring_t)SR;

    // Native function call
    nvgraphStatus_t jniResult_native = nvgraphSrSpmv(handle_native, descrG_native, weight_index_native, alpha_native, x_index_native, beta_native, y_index_native, SR_native);

    // Write back native variable values
    // handle is read-only
    // descrG is read-only
    // weight_index is primitive
    if (!releasePointerData(env, alpha_pointerData, JNI_ABORT)) return JNVGRAPH_STATUS_INTERNAL_ERROR;
    // x_index is primitive
    if (!releasePointerData(env, beta_pointerData, JNI_ABORT)) return JNVGRAPH_STATUS_INTERNAL_ERROR;
    // y_index is primitive
    // SR is primitive

    // Return the result
    jint jniResult = (jint)jniResult_native;
    return jniResult;
}

/** nvGRAPH Single Source Shortest Path (SSSP)
* Calculate the shortest path distance from a single vertex in the graph to all other vertices.
*/
JNIEXPORT jint JNICALL Java_jcuda_jnvgraph_JNvgraph_nvgraphSsspNative(JNIEnv *env, jclass cls, jobject handle, jobject descrG, jlong weight_index, jobject source_vert, jlong sssp_index)
{
    // Null-checks for non-primitive arguments
    if (handle == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'handle' is null for nvgraphSssp");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    if (descrG == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'descrG' is null for nvgraphSssp");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    // weight_index is primitive
    if (source_vert == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'source_vert' is null for nvgraphSssp");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    // sssp_index is primitive

    // Log message
    Logger::log(LOG_TRACE, "Executing nvgraphSssp(handle=%p, descrG=%p, weight_index=%ld, source_vert=%p, sssp_index=%ld)\n",
        handle, descrG, weight_index, source_vert, sssp_index);

    // Native variable declarations
    nvgraphHandle_t handle_native;
    nvgraphGraphDescr_t descrG_native;
    size_t weight_index_native = 0;
    int * source_vert_native = NULL;
    size_t sssp_index_native = 0;

    // Obtain native variable values
    handle_native = (nvgraphHandle_t)getNativePointerValue(env, handle);
    descrG_native = (nvgraphGraphDescr_t)getNativePointerValue(env, descrG);
    weight_index_native = (size_t)weight_index;
    PointerData *source_vert_pointerData = initPointerData(env, source_vert);
    if (source_vert_pointerData == NULL)
    {
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    source_vert_native = (int *)source_vert_pointerData->getPointer(env);
    sssp_index_native = (size_t)sssp_index;

    // Native function call
    nvgraphStatus_t jniResult_native = nvgraphSssp(handle_native, descrG_native, weight_index_native, source_vert_native, sssp_index_native);

    // Write back native variable values
    // handle is read-only
    // descrG is read-only
    // weight_index is primitive
    if (!releasePointerData(env, source_vert_pointerData, JNI_ABORT)) return JNVGRAPH_STATUS_INTERNAL_ERROR;
    // sssp_index is primitive

    // Return the result
    jint jniResult = (jint)jniResult_native;
    return jniResult;
}

/** nvGRAPH WidestPath
* Find widest path potential from source_index to every other vertices.
*/
JNIEXPORT jint JNICALL Java_jcuda_jnvgraph_JNvgraph_nvgraphWidestPathNative(JNIEnv *env, jclass cls, jobject handle, jobject descrG, jlong weight_index, jobject source_vert, jlong widest_path_index)
{
    // Null-checks for non-primitive arguments
    if (handle == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'handle' is null for nvgraphWidestPath");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    if (descrG == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'descrG' is null for nvgraphWidestPath");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    // weight_index is primitive
    if (source_vert == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'source_vert' is null for nvgraphWidestPath");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    // widest_path_index is primitive

    // Log message
    Logger::log(LOG_TRACE, "Executing nvgraphWidestPath(handle=%p, descrG=%p, weight_index=%ld, source_vert=%p, widest_path_index=%ld)\n",
        handle, descrG, weight_index, source_vert, widest_path_index);

    // Native variable declarations
    nvgraphHandle_t handle_native;
    nvgraphGraphDescr_t descrG_native;
    size_t weight_index_native = 0;
    int * source_vert_native = NULL;
    size_t widest_path_index_native = 0;

    // Obtain native variable values
    handle_native = (nvgraphHandle_t)getNativePointerValue(env, handle);
    descrG_native = (nvgraphGraphDescr_t)getNativePointerValue(env, descrG);
    weight_index_native = (size_t)weight_index;
    PointerData *source_vert_pointerData = initPointerData(env, source_vert);
    if (source_vert_pointerData == NULL)
    {
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    source_vert_native = (int *)source_vert_pointerData->getPointer(env);
    widest_path_index_native = (size_t)widest_path_index;

    // Native function call
    nvgraphStatus_t jniResult_native = nvgraphWidestPath(handle_native, descrG_native, weight_index_native, source_vert_native, widest_path_index_native);

    // Write back native variable values
    // handle is read-only
    // descrG is read-only
    // weight_index is primitive
    if (!releasePointerData(env, source_vert_pointerData, JNI_ABORT)) return JNVGRAPH_STATUS_INTERNAL_ERROR;
    // widest_path_index is primitive

    // Return the result
    jint jniResult = (jint)jniResult_native;
    return jniResult;
}

/** nvGRAPH PageRank
* Find PageRank for each vertex of a graph with a given transition probabilities, a bookmark vector of dangling vertices, and the damping factor.
*/
JNIEXPORT jint JNICALL Java_jcuda_jnvgraph_JNvgraph_nvgraphPagerankNative(JNIEnv *env, jclass cls, jobject handle, jobject descrG, jlong weight_index, jobject alpha, jlong bookmark_index, jint has_guess, jlong pagerank_index, jfloat tolerance, jint max_iter)
{
    // Null-checks for non-primitive arguments
    if (handle == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'handle' is null for nvgraphPagerank");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    if (descrG == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'descrG' is null for nvgraphPagerank");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    // weight_index is primitive
    if (alpha == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'alpha' is null for nvgraphPagerank");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    // bookmark_index is primitive
    // has_guess is primitive
    // pagerank_index is primitive
    // tolerance is primitive
    // max_iter is primitive

    // Log message
    Logger::log(LOG_TRACE, "Executing nvgraphPagerank(handle=%p, descrG=%p, weight_index=%ld, alpha=%p, bookmark_index=%ld, has_guess=%d, pagerank_index=%ld, tolerance=%f, max_iter=%d)\n",
        handle, descrG, weight_index, alpha, bookmark_index, has_guess, pagerank_index, tolerance, max_iter);

    // Native variable declarations
    nvgraphHandle_t handle_native;
    nvgraphGraphDescr_t descrG_native;
    size_t weight_index_native = 0;
    void * alpha_native = NULL;
    size_t bookmark_index_native = 0;
    int has_guess_native = 0;
    size_t pagerank_index_native = 0;
    float tolerance_native = 0.0f;
    int max_iter_native = 0;

    // Obtain native variable values
    handle_native = (nvgraphHandle_t)getNativePointerValue(env, handle);
    descrG_native = (nvgraphGraphDescr_t)getNativePointerValue(env, descrG);
    weight_index_native = (size_t)weight_index;
    PointerData *alpha_pointerData = initPointerData(env, alpha);
    if (alpha_pointerData == NULL)
    {
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    alpha_native = (void *)alpha_pointerData->getPointer(env);
    bookmark_index_native = (size_t)bookmark_index;
    has_guess_native = (int)has_guess;
    pagerank_index_native = (size_t)pagerank_index;
    tolerance_native = (float)tolerance;
    max_iter_native = (int)max_iter;

    // Native function call
    nvgraphStatus_t jniResult_native = nvgraphPagerank(handle_native, descrG_native, weight_index_native, alpha_native, bookmark_index_native, has_guess_native, pagerank_index_native, tolerance_native, max_iter_native);

    // Write back native variable values
    // handle is read-only
    // descrG is read-only
    // weight_index is primitive
    if (!releasePointerData(env, alpha_pointerData, JNI_ABORT)) return JNVGRAPH_STATUS_INTERNAL_ERROR;
    // bookmark_index is primitive
    // has_guess is primitive
    // pagerank_index is primitive
    // tolerance is primitive
    // max_iter is primitive

    // Return the result
    jint jniResult = (jint)jniResult_native;
    return jniResult;
}



