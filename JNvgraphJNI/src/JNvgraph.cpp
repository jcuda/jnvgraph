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

// Field IDs for the nvgraphTraversalParameter_t class
jfieldID fid_nvgraphTraversalParameter_t_pad; // size_t[128]

// Field IDs for the SpectralClusteringParameter class
jfieldID fid_SpectralClusteringParameter_n_clusters; // int
jfieldID fid_SpectralClusteringParameter_n_eig_vects; // int
jfieldID fid_SpectralClusteringParameter_algorithm; // nvgraphSpectralClusteringType_t
jfieldID fid_SpectralClusteringParameter_evs_tolerance; // float
jfieldID fid_SpectralClusteringParameter_evs_max_iter; // int
jfieldID fid_SpectralClusteringParameter_kmean_tolerance; // float
jfieldID fid_SpectralClusteringParameter_kmean_max_iter; // int
jfieldID fid_SpectralClusteringParameter_opt; // void *

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

    // Initialize the topology type classes, as global references
    if (!initGlobal(env, nvgraphCSRTopology32I_Class, "jcuda/jnvgraph/nvgraphCSRTopology32I")) return JNI_ERR;
    if (!initGlobal(env, nvgraphCSCTopology32I_Class, "jcuda/jnvgraph/nvgraphCSCTopology32I")) return JNI_ERR;
    if (!initGlobal(env, nvgraphCOOTopology32I_Class, "jcuda/jnvgraph/nvgraphCOOTopology32I")) return JNI_ERR;

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

	// Initialize the field IDs for the nvgraphTraversalParameter_t class
	if (!init(env, cls, "jcuda/jnvgraph/nvgraphTraversalParameter")) return JNI_ERR;
	if (!init(env, cls, fid_nvgraphTraversalParameter_t_pad, "pad", "[J")) return JNI_ERR;

	// Initialize the field IDs for the SpectralClusteringParameter class
	if (!init(env, cls, "jcuda/jnvgraph/SpectralClusteringParameter")) return JNI_ERR;
	if (!init(env, cls, fid_SpectralClusteringParameter_n_clusters      , "n_clusters"     , "I"              )) return JNI_ERR;
	if (!init(env, cls, fid_SpectralClusteringParameter_n_eig_vects     , "n_eig_vects"    , "I"              )) return JNI_ERR;
	if (!init(env, cls, fid_SpectralClusteringParameter_algorithm       , "algorithm"      , "I"              )) return JNI_ERR;
	if (!init(env, cls, fid_SpectralClusteringParameter_evs_tolerance   , "evs_tolerance"  , "F"              )) return JNI_ERR;
	if (!init(env, cls, fid_SpectralClusteringParameter_evs_max_iter    , "evs_max_iter"   , "I"              )) return JNI_ERR;
	if (!init(env, cls, fid_SpectralClusteringParameter_kmean_tolerance , "kmean_tolerance", "F"              )) return JNI_ERR;
	if (!init(env, cls, fid_SpectralClusteringParameter_kmean_max_iter  , "kmean_max_iter" , "I"              )) return JNI_ERR;
	if (!init(env, cls, fid_SpectralClusteringParameter_opt             , "opt"            , "Ljcuda/Pointer;")) return JNI_ERR;

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
		delete nativeTopologyData;
	}
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
		delete nativeTopologyData;
	}
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
		delete nativeTopologyData;
	}
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
    return NULL;
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



bool initNativeTraversalParameter(JNIEnv *env, jobject param, nvgraphTraversalParameter_t &param_native, bool fill)
{
    jlongArray pad = (jlongArray)env->GetObjectField(param, fid_nvgraphTraversalParameter_t_pad);
	jsize len = env->GetArrayLength(pad);
	jlong* padElements = env->GetLongArrayElements(pad, NULL);
	for (int i = 0; i < len; i++)
	{
		param_native.pad[i] = (size_t)padElements[i];
	}
	env->ReleaseLongArrayElements(pad, padElements, 0);
    return true;
}

bool releaseNativeTraversalParameter(JNIEnv *env, nvgraphTraversalParameter_t &param_native, jobject param, bool writeBack)
{
	jlongArray pad = (jlongArray)env->GetObjectField(param, fid_nvgraphTraversalParameter_t_pad);
	jsize len = env->GetArrayLength(pad);
	jlong* padElements = env->GetLongArrayElements(pad, NULL);
	for (int i = 0; i < len; i++)
	{
		padElements[i] = (jlong)param_native.pad[i];
	}
	env->ReleaseLongArrayElements(pad, padElements, 0);
	return true;
}

bool initNativeTraversalParameter(JNIEnv *env, jobject param, nvgraphTraversalParameter_t* &param_native, bool fill)
{
    if (param == NULL)
	{
		return true;
	}
	param_native = new nvgraphTraversalParameter_t();
	return initNativeTraversalParameter(env, param, *param_native, fill);
}

bool releaseNativeTraversalParameter(JNIEnv *env, nvgraphTraversalParameter_t* &param_native, jobject param, bool writeBack)
{
	if (param == NULL)
	{
		delete param_native;
		return true;
	}
	if (!releaseNativeTraversalParameter(env, *param_native, param, writeBack)) return false;
	delete param_native;
	return true;
}


bool initNativeSpectralClusteringParameter(JNIEnv *env, jobject param, SpectralClusteringParameter* &param_native, bool fill)
{
	if (param == NULL)
	{
		return true;
	}
	param_native = new SpectralClusteringParameter();
	param_native->n_clusters = (int)env->GetIntField(param, fid_SpectralClusteringParameter_n_clusters);
	param_native->n_eig_vects = (int)env->GetIntField(param, fid_SpectralClusteringParameter_n_eig_vects);
	param_native->algorithm = (nvgraphSpectralClusteringType_t)env->GetIntField(param, fid_SpectralClusteringParameter_algorithm);
	param_native->evs_tolerance = env->GetFloatField(param, fid_SpectralClusteringParameter_evs_tolerance);
	param_native->evs_max_iter = (int)env->GetIntField(param, fid_SpectralClusteringParameter_evs_max_iter);
	param_native->kmean_tolerance = env->GetFloatField(param, fid_SpectralClusteringParameter_kmean_tolerance);
	param_native->kmean_max_iter = (int)env->GetIntField(param, fid_SpectralClusteringParameter_kmean_max_iter);
	jobject opt = env->GetObjectField(param, fid_SpectralClusteringParameter_opt);

	// TODO: As of CUDA 9.0.176, the optional parameters are not supported yet.
	// Print a warning if they are not NULL.
	if (opt != NULL) {
		Logger::log(LOG_WARNING, "Optional spectral clustering parameters are not supported");
	}
	param_native->opt = NULL;
	return true;
}

bool releaseNativeSpectralClusteringParameter(JNIEnv *env, SpectralClusteringParameter* &param_native, jobject param, bool writeBack)
{
	if (param == NULL)
	{
		delete param_native;
		return true;
	}
	delete param_native;
	return true;
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

/** Return properties values for the nvGraph library, such as library version */
JNIEXPORT jint JNICALL Java_jcuda_jnvgraph_JNvgraph_nvgraphGetPropertyNative(JNIEnv *env, jclass cls, jint type, jintArray value)
{
    // Null-checks for non-primitive arguments
    // type is primitive
    if (value == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'value' is null for nvgraphGetProperty");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }

    // Log message
    Logger::log(LOG_TRACE, "Executing nvgraphGetProperty(type=%d, value=%p)\n",
        type, value);

    // Native variable declarations
    libraryPropertyType type_native;
    int value_native;

    // Obtain native variable values
    type_native = (libraryPropertyType)type;
    // value is write-only

    // Native function call
    nvgraphStatus_t jniResult_native = nvgraphGetProperty(type_native, &value_native);

    // Write back native variable values
    // type is primitive
    if (!set(env, value, 0, (jint)value_native)) return JNVGRAPH_STATUS_INTERNAL_ERROR;

    // Return the result
    jint jniResult = (jint)jniResult_native;
    return jniResult;
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
*/
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
*/
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

JNIEXPORT jint JNICALL Java_jcuda_jnvgraph_JNvgraph_nvgraphTraversalParameterInitNative(JNIEnv *env, jclass cls, jobject param)
{
    // Null-checks for non-primitive arguments
    if (param == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'param' is null for nvgraphTraversalParameterInit");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }

    // Log message
    Logger::log(LOG_TRACE, "Executing nvgraphTraversalParameterInit(param=%p)\n",
        param);

    // Native variable declarations
    nvgraphTraversalParameter_t * param_native = NULL;

    // Obtain native variable values
    if (!initNativeTraversalParameter(env, param, param_native, true)) return JNVGRAPH_STATUS_INTERNAL_ERROR;

    // Native function call
    nvgraphStatus_t jniResult_native = nvgraphTraversalParameterInit(param_native);

    // Write back native variable values
    if (!releaseNativeTraversalParameter(env, param_native, param, true)) return JNVGRAPH_STATUS_INTERNAL_ERROR;

    // Return the result
    jint jniResult = (jint)jniResult_native;
    return jniResult;
}

JNIEXPORT jint JNICALL Java_jcuda_jnvgraph_JNvgraph_nvgraphTraversalSetDistancesIndexNative(JNIEnv *env, jclass cls, jobject param, jlong value)
{
    // Null-checks for non-primitive arguments
    if (param == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'param' is null for nvgraphTraversalSetDistancesIndex");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    // value is primitive

    // Log message
    Logger::log(LOG_TRACE, "Executing nvgraphTraversalSetDistancesIndex(param=%p, value=%ld)\n",
        param, value);

    // Native variable declarations
    nvgraphTraversalParameter_t * param_native = NULL;
    size_t value_native = 0;

    // Obtain native variable values
    if (!initNativeTraversalParameter(env, param, param_native, true)) return JNVGRAPH_STATUS_INTERNAL_ERROR;
    value_native = (size_t)value;

    // Native function call
    nvgraphStatus_t jniResult_native = nvgraphTraversalSetDistancesIndex(param_native, value_native);

    // Write back native variable values
    if (!releaseNativeTraversalParameter(env, param_native, param, true)) return JNVGRAPH_STATUS_INTERNAL_ERROR;
    // value is primitive

    // Return the result
    jint jniResult = (jint)jniResult_native;
    return jniResult;
}

JNIEXPORT jint JNICALL Java_jcuda_jnvgraph_JNvgraph_nvgraphTraversalGetDistancesIndexNative(JNIEnv *env, jclass cls, jobject param, jlongArray value)
{
    // Null-checks for non-primitive arguments
    if (param == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'param' is null for nvgraphTraversalGetDistancesIndex");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    if (value == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'value' is null for nvgraphTraversalGetDistancesIndex");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }

    // Log message
    Logger::log(LOG_TRACE, "Executing nvgraphTraversalGetDistancesIndex(param=%p, value=%p)\n",
        param, value);

    // Native variable declarations
	nvgraphTraversalParameter_t param_native = { 0 };
    size_t value_native;

    // Obtain native variable values
    if (!initNativeTraversalParameter(env, param, param_native, true)) return JNVGRAPH_STATUS_INTERNAL_ERROR;
    // value is write-only

    // Native function call
    nvgraphStatus_t jniResult_native = nvgraphTraversalGetDistancesIndex(param_native, &value_native);

    // Write back native variable values
    if (!releaseNativeTraversalParameter(env, param_native, param, true)) return JNVGRAPH_STATUS_INTERNAL_ERROR;
    if (!set(env, value, 0, (jlong)value_native)) return JNVGRAPH_STATUS_INTERNAL_ERROR;

    // Return the result
    jint jniResult = (jint)jniResult_native;
    return jniResult;
}

JNIEXPORT jint JNICALL Java_jcuda_jnvgraph_JNvgraph_nvgraphTraversalSetPredecessorsIndexNative(JNIEnv *env, jclass cls, jobject param, jlong value)
{
    // Null-checks for non-primitive arguments
    if (param == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'param' is null for nvgraphTraversalSetPredecessorsIndex");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    // value is primitive

    // Log message
    Logger::log(LOG_TRACE, "Executing nvgraphTraversalSetPredecessorsIndex(param=%p, value=%ld)\n",
        param, value);

    // Native variable declarations
    nvgraphTraversalParameter_t * param_native = NULL;
    size_t value_native = 0;

    // Obtain native variable values
    if (!initNativeTraversalParameter(env, param, param_native, true)) return JNVGRAPH_STATUS_INTERNAL_ERROR;
    value_native = (size_t)value;

    // Native function call
    nvgraphStatus_t jniResult_native = nvgraphTraversalSetPredecessorsIndex(param_native, value_native);

    // Write back native variable values
    if (!releaseNativeTraversalParameter(env, param_native, param, true)) return JNVGRAPH_STATUS_INTERNAL_ERROR;
    // value is primitive

    // Return the result
    jint jniResult = (jint)jniResult_native;
    return jniResult;
}

JNIEXPORT jint JNICALL Java_jcuda_jnvgraph_JNvgraph_nvgraphTraversalGetPredecessorsIndexNative(JNIEnv *env, jclass cls, jobject param, jlongArray value)
{
    // Null-checks for non-primitive arguments
    if (param == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'param' is null for nvgraphTraversalGetPredecessorsIndex");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    if (value == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'value' is null for nvgraphTraversalGetPredecessorsIndex");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }

    // Log message
    Logger::log(LOG_TRACE, "Executing nvgraphTraversalGetPredecessorsIndex(param=%p, value=%p)\n",
        param, value);

    // Native variable declarations
    nvgraphTraversalParameter_t param_native = { 0 };
    size_t value_native;

    // Obtain native variable values
    if (!initNativeTraversalParameter(env, param, param_native, true)) return JNVGRAPH_STATUS_INTERNAL_ERROR;
    // value is write-only

    // Native function call
    nvgraphStatus_t jniResult_native = nvgraphTraversalGetPredecessorsIndex(param_native, &value_native);

    // Write back native variable values
    if (!releaseNativeTraversalParameter(env, param_native, param, true)) return JNVGRAPH_STATUS_INTERNAL_ERROR;
    if (!set(env, value, 0, (jlong)value_native)) return JNVGRAPH_STATUS_INTERNAL_ERROR;

    // Return the result
    jint jniResult = (jint)jniResult_native;
    return jniResult;
}

JNIEXPORT jint JNICALL Java_jcuda_jnvgraph_JNvgraph_nvgraphTraversalSetEdgeMaskIndexNative(JNIEnv *env, jclass cls, jobject param, jlong value)
{
    // Null-checks for non-primitive arguments
    if (param == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'param' is null for nvgraphTraversalSetEdgeMaskIndex");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    // value is primitive

    // Log message
    Logger::log(LOG_TRACE, "Executing nvgraphTraversalSetEdgeMaskIndex(param=%p, value=%ld)\n",
        param, value);

    // Native variable declarations
    nvgraphTraversalParameter_t * param_native = NULL;
    size_t value_native = 0;

    // Obtain native variable values
    if (!initNativeTraversalParameter(env, param, param_native, true)) return JNVGRAPH_STATUS_INTERNAL_ERROR;
    value_native = (size_t)value;

    // Native function call
    nvgraphStatus_t jniResult_native = nvgraphTraversalSetEdgeMaskIndex(param_native, value_native);

    // Write back native variable values
    if (!releaseNativeTraversalParameter(env, param_native, param, true)) return JNVGRAPH_STATUS_INTERNAL_ERROR;
    // value is primitive

    // Return the result
    jint jniResult = (jint)jniResult_native;
    return jniResult;
}

JNIEXPORT jint JNICALL Java_jcuda_jnvgraph_JNvgraph_nvgraphTraversalGetEdgeMaskIndexNative(JNIEnv *env, jclass cls, jobject param, jlongArray value)
{
    // Null-checks for non-primitive arguments
    if (param == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'param' is null for nvgraphTraversalGetEdgeMaskIndex");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    if (value == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'value' is null for nvgraphTraversalGetEdgeMaskIndex");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }

    // Log message
    Logger::log(LOG_TRACE, "Executing nvgraphTraversalGetEdgeMaskIndex(param=%p, value=%p)\n",
        param, value);

    // Native variable declarations
	nvgraphTraversalParameter_t param_native = { 0 };
    size_t value_native;

    // Obtain native variable values
    if (!initNativeTraversalParameter(env, param, param_native, true)) return JNVGRAPH_STATUS_INTERNAL_ERROR;
    // value is write-only

    // Native function call
    nvgraphStatus_t jniResult_native = nvgraphTraversalGetEdgeMaskIndex(param_native, &value_native);

    // Write back native variable values
    if (!releaseNativeTraversalParameter(env, param_native, param, true)) return JNVGRAPH_STATUS_INTERNAL_ERROR;
    if (!set(env, value, 0, (jlong)value_native)) return JNVGRAPH_STATUS_INTERNAL_ERROR;

    // Return the result
    jint jniResult = (jint)jniResult_native;
    return jniResult;
}

JNIEXPORT jint JNICALL Java_jcuda_jnvgraph_JNvgraph_nvgraphTraversalSetUndirectedFlagNative(JNIEnv *env, jclass cls, jobject param, jlong value)
{
    // Null-checks for non-primitive arguments
    if (param == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'param' is null for nvgraphTraversalSetUndirectedFlag");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    // value is primitive

    // Log message
    Logger::log(LOG_TRACE, "Executing nvgraphTraversalSetUndirectedFlag(param=%p, value=%ld)\n",
        param, value);

    // Native variable declarations
    nvgraphTraversalParameter_t * param_native = NULL;
    size_t value_native = 0;

    // Obtain native variable values
    if (!initNativeTraversalParameter(env, param, param_native, true)) return JNVGRAPH_STATUS_INTERNAL_ERROR;
    value_native = (size_t)value;

    // Native function call
    nvgraphStatus_t jniResult_native = nvgraphTraversalSetUndirectedFlag(param_native, value_native);

    // Write back native variable values
    if (!releaseNativeTraversalParameter(env, param_native, param, true)) return JNVGRAPH_STATUS_INTERNAL_ERROR;
    // value is primitive

    // Return the result
    jint jniResult = (jint)jniResult_native;
    return jniResult;
}

JNIEXPORT jint JNICALL Java_jcuda_jnvgraph_JNvgraph_nvgraphTraversalGetUndirectedFlagNative(JNIEnv *env, jclass cls, jobject param, jlongArray value)
{
    // Null-checks for non-primitive arguments
    if (param == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'param' is null for nvgraphTraversalGetUndirectedFlag");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    if (value == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'value' is null for nvgraphTraversalGetUndirectedFlag");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }

    // Log message
    Logger::log(LOG_TRACE, "Executing nvgraphTraversalGetUndirectedFlag(param=%p, value=%p)\n",
        param, value);

    // Native variable declarations
    nvgraphTraversalParameter_t param_native = { 0 };
    size_t value_native;

    // Obtain native variable values
    if (!initNativeTraversalParameter(env, param, param_native, true)) return JNVGRAPH_STATUS_INTERNAL_ERROR;
    // value is write-only

    // Native function call
    nvgraphStatus_t jniResult_native = nvgraphTraversalGetUndirectedFlag(param_native, &value_native);

    // Write back native variable values
    if (!releaseNativeTraversalParameter(env, param_native, param, true)) return JNVGRAPH_STATUS_INTERNAL_ERROR;
    if (!set(env, value, 0, (jlong)value_native)) return JNVGRAPH_STATUS_INTERNAL_ERROR;

    // Return the result
    jint jniResult = (jint)jniResult_native;
    return jniResult;
}

JNIEXPORT jint JNICALL Java_jcuda_jnvgraph_JNvgraph_nvgraphTraversalSetAlphaNative(JNIEnv *env, jclass cls, jobject param, jlong value)
{
	ThrowByName(env, "java/lang/UnsupportedOperationException", "This function is not implemented in CUDA 9.0.176");
	return JNVGRAPH_STATUS_INTERNAL_ERROR;
	/*
    // Null-checks for non-primitive arguments
    if (param == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'param' is null for nvgraphTraversalSetAlpha");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    // value is primitive

    // Log message
    Logger::log(LOG_TRACE, "Executing nvgraphTraversalSetAlpha(param=%p, value=%ld)\n",
        param, value);

    // Native variable declarations
    nvgraphTraversalParameter_t * param_native = NULL;
    size_t value_native = 0;

    // Obtain native variable values
    if (!initNativeTraversalParameter(env, param, param_native, true)) return JNVGRAPH_STATUS_INTERNAL_ERROR;
    value_native = (size_t)value;

    // Native function call
    nvgraphStatus_t jniResult_native = nvgraphTraversalSetAlpha(param_native, value_native);

    // Write back native variable values
    if (!releaseNativeTraversalParameter(env, param_native, param, true)) return JNVGRAPH_STATUS_INTERNAL_ERROR;
    // value is primitive

    // Return the result
    jint jniResult = (jint)jniResult_native;
    return jniResult;
	*/
}

JNIEXPORT jint JNICALL Java_jcuda_jnvgraph_JNvgraph_nvgraphTraversalGetAlphaNative(JNIEnv *env, jclass cls, jobject param, jlongArray value)
{
	ThrowByName(env, "java/lang/UnsupportedOperationException", "This function is not implemented in CUDA 9.0.176");
	return JNVGRAPH_STATUS_INTERNAL_ERROR;
	/*
	// Null-checks for non-primitive arguments
    if (param == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'param' is null for nvgraphTraversalGetAlpha");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    if (value == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'value' is null for nvgraphTraversalGetAlpha");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }

    // Log message
    Logger::log(LOG_TRACE, "Executing nvgraphTraversalGetAlpha(param=%p, value=%p)\n",
        param, value);

    // Native variable declarations
    nvgraphTraversalParameter_t param_native = { 0 };
    size_t value_native;

    // Obtain native variable values
    if (!initNativeTraversalParameter(env, param, param_native, true)) return JNVGRAPH_STATUS_INTERNAL_ERROR;
    // value is write-only

    // Native function call
    nvgraphStatus_t jniResult_native = nvgraphTraversalGetAlpha(param_native, &value_native);

    // Write back native variable values
    if (!releaseNativeTraversalParameter(env, param_native, param, true)) return JNVGRAPH_STATUS_INTERNAL_ERROR;
    if (!set(env, value, 0, (jlong)value_native)) return JNVGRAPH_STATUS_INTERNAL_ERROR;

    // Return the result
    jint jniResult = (jint)jniResult_native;
    return jniResult;
	*/
}

JNIEXPORT jint JNICALL Java_jcuda_jnvgraph_JNvgraph_nvgraphTraversalSetBetaNative(JNIEnv *env, jclass cls, jobject param, jlong value)
{
	ThrowByName(env, "java/lang/UnsupportedOperationException", "This function is not implemented in CUDA 9.0.176");
	return JNVGRAPH_STATUS_INTERNAL_ERROR;
	/*/
	// Null-checks for non-primitive arguments
    if (param == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'param' is null for nvgraphTraversalSetBeta");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    // value is primitive

    // Log message
    Logger::log(LOG_TRACE, "Executing nvgraphTraversalSetBeta(param=%p, value=%ld)\n",
        param, value);

    // Native variable declarations
    nvgraphTraversalParameter_t * param_native = NULL;
    size_t value_native = 0;

    // Obtain native variable values
    if (!initNativeTraversalParameter(env, param, param_native, true)) return JNVGRAPH_STATUS_INTERNAL_ERROR;
    value_native = (size_t)value;

    // Native function call
    nvgraphStatus_t jniResult_native = nvgraphTraversalSetBeta(param_native, value_native);

    // Write back native variable values
    if (!releaseNativeTraversalParameter(env, param_native, param, true)) return JNVGRAPH_STATUS_INTERNAL_ERROR;
    // value is primitive

    // Return the result
    jint jniResult = (jint)jniResult_native;
    return jniResult;
	*/
}

JNIEXPORT jint JNICALL Java_jcuda_jnvgraph_JNvgraph_nvgraphTraversalGetBetaNative(JNIEnv *env, jclass cls, jobject param, jlongArray value)
{
	ThrowByName(env, "java/lang/UnsupportedOperationException", "This function is not implemented in CUDA 9.0.176");
	return JNVGRAPH_STATUS_INTERNAL_ERROR;
	/*
	// Null-checks for non-primitive arguments
    if (param == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'param' is null for nvgraphTraversalGetBeta");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    if (value == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'value' is null for nvgraphTraversalGetBeta");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }

    // Log message
    Logger::log(LOG_TRACE, "Executing nvgraphTraversalGetBeta(param=%p, value=%p)\n",
        param, value);

    // Native variable declarations
    nvgraphTraversalParameter_t param_native = { 0 };
    size_t value_native;

    // Obtain native variable values
    if (!initNativeTraversalParameter(env, param, param_native, true)) return JNVGRAPH_STATUS_INTERNAL_ERROR;
    // value is write-only

    // Native function call
    nvgraphStatus_t jniResult_native = nvgraphTraversalGetBeta(param_native, &value_native);

    // Write back native variable values
    if (!releaseNativeTraversalParameter(env, param_native, param, true)) return JNVGRAPH_STATUS_INTERNAL_ERROR;
    if (!set(env, value, 0, (jlong)value_native)) return JNVGRAPH_STATUS_INTERNAL_ERROR;

    // Return the result
    jint jniResult = (jint)jniResult_native;
    return jniResult;
	*/
}

JNIEXPORT jint JNICALL Java_jcuda_jnvgraph_JNvgraph_nvgraphTraversalNative(JNIEnv *env, jclass cls, jobject handle, jobject descrG, jint traversalT, jobject source_vert, jobject params)
{
    // Null-checks for non-primitive arguments
    if (handle == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'handle' is null for nvgraphTraversal");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    if (descrG == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'descrG' is null for nvgraphTraversal");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    // traversalT is primitive
    if (source_vert == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'source_vert' is null for nvgraphTraversal");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    if (params == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'params' is null for nvgraphTraversal");
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }

    // Log message
    Logger::log(LOG_TRACE, "Executing nvgraphTraversal(handle=%p, descrG=%p, traversalT=%d, source_vert=%p, params=%p)\n",
        handle, descrG, traversalT, source_vert, params);

    // Native variable declarations
    nvgraphHandle_t handle_native;
    nvgraphGraphDescr_t descrG_native;
    nvgraphTraversal_t traversalT_native;
    int * source_vert_native = NULL;
    nvgraphTraversalParameter_t params_native = { 0 };

    // Obtain native variable values
    handle_native = (nvgraphHandle_t)getNativePointerValue(env, handle);
    descrG_native = (nvgraphGraphDescr_t)getNativePointerValue(env, descrG);
    traversalT_native = (nvgraphTraversal_t)traversalT;
    PointerData *source_vert_pointerData = initPointerData(env, source_vert);
    if (source_vert_pointerData == NULL)
    {
        return JNVGRAPH_STATUS_INTERNAL_ERROR;
    }
    source_vert_native = (int *)source_vert_pointerData->getPointer(env);
    if (!initNativeTraversalParameter(env, params, params_native, true)) return JNVGRAPH_STATUS_INTERNAL_ERROR;

    // Native function call
    nvgraphStatus_t jniResult_native = nvgraphTraversal(handle_native, descrG_native, traversalT_native, source_vert_native, params_native);

    // Write back native variable values
    // handle is read-only
    // descrG is read-only
    // traversalT is primitive
    if (!releasePointerData(env, source_vert_pointerData, JNI_ABORT)) return JNVGRAPH_STATUS_INTERNAL_ERROR;
    if (!releaseNativeTraversalParameter(env, params_native, params, true)) return JNVGRAPH_STATUS_INTERNAL_ERROR;

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

/**
* <pre>
* nvGRAPH contraction
* given array of agregates contract graph with
* given (Combine, Reduce) operators for Vertex Set
* and Edge Set;
* </pre>
*/
JNIEXPORT jint JNICALL Java_jcuda_jnvgraph_JNvgraph_nvgraphContractGraphNative(JNIEnv *env, jclass cls, jobject handle, jobject descrG, jobject contrdescrG, jobject aggregates, jlong numaggregates, jint VertexCombineOp, jint VertexReduceOp, jint EdgeCombineOp, jint EdgeReduceOp, jint flag)
{
	// Null-checks for non-primitive arguments
	if (handle == NULL)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'handle' is null for nvgraphContractGraph");
		return JNVGRAPH_STATUS_INTERNAL_ERROR;
	}
	if (descrG == NULL)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'descrG' is null for nvgraphContractGraph");
		return JNVGRAPH_STATUS_INTERNAL_ERROR;
	}
	if (contrdescrG == NULL)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'contrdescrG' is null for nvgraphContractGraph");
		return JNVGRAPH_STATUS_INTERNAL_ERROR;
	}
	if (aggregates == NULL)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'aggregates' is null for nvgraphContractGraph");
		return JNVGRAPH_STATUS_INTERNAL_ERROR;
	}
	// numaggregates is primitive
	// VertexCombineOp is primitive
	// VertexReduceOp is primitive
	// EdgeCombineOp is primitive
	// EdgeReduceOp is primitive
	// flag is primitive

	// Log message
	Logger::log(LOG_TRACE, "Executing nvgraphContractGraph(handle=%p, descrG=%p, contrdescrG=%p, aggregates=%p, numaggregates=%ld, VertexCombineOp=%d, VertexReduceOp=%d, EdgeCombineOp=%d, EdgeReduceOp=%d, flag=%d)\n",
		handle, descrG, contrdescrG, aggregates, numaggregates, VertexCombineOp, VertexReduceOp, EdgeCombineOp, EdgeReduceOp, flag);

	// Native variable declarations
	nvgraphHandle_t handle_native;
	nvgraphGraphDescr_t descrG_native;
	nvgraphGraphDescr_t contrdescrG_native;
	int * aggregates_native = NULL;
	size_t numaggregates_native = 0;
	nvgraphSemiringOps_t VertexCombineOp_native;
	nvgraphSemiringOps_t VertexReduceOp_native;
	nvgraphSemiringOps_t EdgeCombineOp_native;
	nvgraphSemiringOps_t EdgeReduceOp_native;
	int flag_native = 0;

	// Obtain native variable values
	handle_native = (nvgraphHandle_t)getNativePointerValue(env, handle);
	descrG_native = (nvgraphGraphDescr_t)getNativePointerValue(env, descrG);
	contrdescrG_native = (nvgraphGraphDescr_t)getNativePointerValue(env, contrdescrG);
	PointerData *aggregates_pointerData = initPointerData(env, aggregates);
	if (aggregates_pointerData == NULL)
	{
		return JNVGRAPH_STATUS_INTERNAL_ERROR;
	}
	aggregates_native = (int *)aggregates_pointerData->getPointer(env);
	numaggregates_native = (size_t)numaggregates;
	VertexCombineOp_native = (nvgraphSemiringOps_t)VertexCombineOp;
	VertexReduceOp_native = (nvgraphSemiringOps_t)VertexReduceOp;
	EdgeCombineOp_native = (nvgraphSemiringOps_t)EdgeCombineOp;
	EdgeReduceOp_native = (nvgraphSemiringOps_t)EdgeReduceOp;
	flag_native = (int)flag;

	// Native function call
	nvgraphStatus_t jniResult_native = nvgraphContractGraph(handle_native, descrG_native, contrdescrG_native, aggregates_native, numaggregates_native, VertexCombineOp_native, VertexReduceOp_native, EdgeCombineOp_native, EdgeReduceOp_native, flag_native);

	// Write back native variable values
	// handle is read-only
	// descrG is read-only
	// contrdescrG is read-only
	// If the PointerData is not backed by native memory, then this call has to block
	if (!isPointerBackedByNativeMemory(env, aggregates))
	{
		cudaDeviceSynchronize();
	}
	if (!releasePointerData(env, aggregates_pointerData, 0)) return JNVGRAPH_STATUS_INTERNAL_ERROR;
	// numaggregates is primitive
	// VertexCombineOp is primitive
	// VertexReduceOp is primitive
	// EdgeCombineOp is primitive
	// EdgeReduceOp is primitive
	// flag is primitive

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

/**
* <pre>
* nvGRAPH spectral clustering
* given a graph and solver parameters of struct SpectralClusteringParameter,
* assign vertices to groups such as
* intra-group connections are strong and/or inter-groups connections are weak
* using spectral technique.
* </pre>
*/
JNIEXPORT jint JNICALL Java_jcuda_jnvgraph_JNvgraph_nvgraphSpectralClusteringNative(JNIEnv *env, jclass cls, jobject handle, jobject graph_descr, jlong weight_index, jobject params, jobject clustering, jobject eig_vals, jobject eig_vects)
{
	// Null-checks for non-primitive arguments
	if (handle == NULL)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'handle' is null for nvgraphSpectralClustering");
		return JNVGRAPH_STATUS_INTERNAL_ERROR;
	}
	if (graph_descr == NULL)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'graph_descr' is null for nvgraphSpectralClustering");
		return JNVGRAPH_STATUS_INTERNAL_ERROR;
	}
	// weight_index is primitive
	if (params == NULL)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'params' is null for nvgraphSpectralClustering");
		return JNVGRAPH_STATUS_INTERNAL_ERROR;
	}
	if (clustering == NULL)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'clustering' is null for nvgraphSpectralClustering");
		return JNVGRAPH_STATUS_INTERNAL_ERROR;
	}
	if (eig_vals == NULL)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'eig_vals' is null for nvgraphSpectralClustering");
		return JNVGRAPH_STATUS_INTERNAL_ERROR;
	}
	if (eig_vects == NULL)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'eig_vects' is null for nvgraphSpectralClustering");
		return JNVGRAPH_STATUS_INTERNAL_ERROR;
	}

	// Log message
	Logger::log(LOG_TRACE, "Executing nvgraphSpectralClustering(handle=%p, graph_descr=%p, weight_index=%ld, params=%p, clustering=%p, eig_vals=%p, eig_vects=%p)\n",
		handle, graph_descr, weight_index, params, clustering, eig_vals, eig_vects);

	// Native variable declarations
	nvgraphHandle_t handle_native;
	nvgraphGraphDescr_t graph_descr_native;
	size_t weight_index_native = 0;
	SpectralClusteringParameter * params_native = NULL;
	int * clustering_native = NULL;
	void * eig_vals_native = NULL;
	void * eig_vects_native = NULL;

	// Obtain native variable values
	handle_native = (nvgraphHandle_t)getNativePointerValue(env, handle);
	graph_descr_native = (nvgraphGraphDescr_t)getNativePointerValue(env, graph_descr);
	weight_index_native = (size_t)weight_index;
	if (!initNativeSpectralClusteringParameter(env, params, params_native, true)) return JNVGRAPH_STATUS_INTERNAL_ERROR;
	PointerData *clustering_pointerData = initPointerData(env, clustering);
	if (clustering_pointerData == NULL)
	{
		return JNVGRAPH_STATUS_INTERNAL_ERROR;
	}
	clustering_native = (int *)clustering_pointerData->getPointer(env);
	PointerData *eig_vals_pointerData = initPointerData(env, eig_vals);
	if (eig_vals_pointerData == NULL)
	{
		return JNVGRAPH_STATUS_INTERNAL_ERROR;
	}
	eig_vals_native = (void *)eig_vals_pointerData->getPointer(env);
	PointerData *eig_vects_pointerData = initPointerData(env, eig_vects);
	if (eig_vects_pointerData == NULL)
	{
		return JNVGRAPH_STATUS_INTERNAL_ERROR;
	}
	eig_vects_native = (void *)eig_vects_pointerData->getPointer(env);

	// Native function call
	nvgraphStatus_t jniResult_native = nvgraphSpectralClustering(handle_native, graph_descr_native, weight_index_native, params_native, clustering_native, eig_vals_native, eig_vects_native);

	// Write back native variable values
	// handle is read-only
	// graph_descr is read-only
	// weight_index is primitive
	if (!releaseNativeSpectralClusteringParameter(env, params_native, params, true)) return JNVGRAPH_STATUS_INTERNAL_ERROR;
	// If the PointerData is not backed by native memory, then this call has to block
	if (!isPointerBackedByNativeMemory(env, clustering))
	{
		cudaDeviceSynchronize();
	}
	if (!releasePointerData(env, clustering_pointerData, 0)) return JNVGRAPH_STATUS_INTERNAL_ERROR;
	// If the PointerData is not backed by native memory, then this call has to block
	if (!isPointerBackedByNativeMemory(env, eig_vals))
	{
		cudaDeviceSynchronize();
	}
	if (!releasePointerData(env, eig_vals_pointerData, 0)) return JNVGRAPH_STATUS_INTERNAL_ERROR;
	// If the PointerData is not backed by native memory, then this call has to block
	if (!isPointerBackedByNativeMemory(env, eig_vects))
	{
		cudaDeviceSynchronize();
	}
	if (!releasePointerData(env, eig_vects_pointerData, 0)) return JNVGRAPH_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

/**
* <pre>
* nvGRAPH analyze clustering
* Given a graph, a clustering, and a metric
* compute the score that measures the clustering quality according to the metric.
* </pre>
*/
JNIEXPORT jint JNICALL Java_jcuda_jnvgraph_JNvgraph_nvgraphAnalyzeClusteringNative(JNIEnv *env, jclass cls, jobject handle, jobject graph_descr, jlong weight_index, jint n_clusters, jobject clustering, jint metric, jobject score)
{
	// Null-checks for non-primitive arguments
	if (handle == NULL)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'handle' is null for nvgraphAnalyzeClustering");
		return JNVGRAPH_STATUS_INTERNAL_ERROR;
	}
	if (graph_descr == NULL)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'graph_descr' is null for nvgraphAnalyzeClustering");
		return JNVGRAPH_STATUS_INTERNAL_ERROR;
	}
	// weight_index is primitive
	// n_clusters is primitive
	if (clustering == NULL)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'clustering' is null for nvgraphAnalyzeClustering");
		return JNVGRAPH_STATUS_INTERNAL_ERROR;
	}
	// metric is primitive
	if (score == NULL)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'score' is null for nvgraphAnalyzeClustering");
		return JNVGRAPH_STATUS_INTERNAL_ERROR;
	}

	// Log message
	Logger::log(LOG_TRACE, "Executing nvgraphAnalyzeClustering(handle=%p, graph_descr=%p, weight_index=%ld, n_clusters=%d, clustering=%p, metric=%d, score=%p)\n",
		handle, graph_descr, weight_index, n_clusters, clustering, metric, score);

	// Native variable declarations
	nvgraphHandle_t handle_native;
	nvgraphGraphDescr_t graph_descr_native;
	size_t weight_index_native = 0;
	int n_clusters_native = 0;
	int * clustering_native = NULL;
	nvgraphClusteringMetric_t metric_native;
	float * score_native = NULL;

	// Obtain native variable values
	handle_native = (nvgraphHandle_t)getNativePointerValue(env, handle);
	graph_descr_native = (nvgraphGraphDescr_t)getNativePointerValue(env, graph_descr);
	weight_index_native = (size_t)weight_index;
	n_clusters_native = (int)n_clusters;
	PointerData *clustering_pointerData = initPointerData(env, clustering);
	if (clustering_pointerData == NULL)
	{
		return JNVGRAPH_STATUS_INTERNAL_ERROR;
	}
	clustering_native = (int *)clustering_pointerData->getPointer(env);
	metric_native = (nvgraphClusteringMetric_t)metric;
	PointerData *score_pointerData = initPointerData(env, score);
	if (score_pointerData == NULL)
	{
		return JNVGRAPH_STATUS_INTERNAL_ERROR;
	}
	score_native = (float *)score_pointerData->getPointer(env);

	// Native function call
	nvgraphStatus_t jniResult_native = nvgraphAnalyzeClustering(handle_native, graph_descr_native, weight_index_native, n_clusters_native, clustering_native, metric_native, score_native);

	// Write back native variable values
	// handle is read-only
	// graph_descr is read-only
	// weight_index is primitive
	// n_clusters is primitive
	// If the PointerData is not backed by native memory, then this call has to block
	if (!isPointerBackedByNativeMemory(env, clustering))
	{
		cudaDeviceSynchronize();
	}
	if (!releasePointerData(env, clustering_pointerData, 0)) return JNVGRAPH_STATUS_INTERNAL_ERROR;
	// metric is primitive
	// If the PointerData is not backed by native memory, then this call has to block
	if (!isPointerBackedByNativeMemory(env, score))
	{
		cudaDeviceSynchronize();
	}
	if (!releasePointerData(env, score_pointerData, 0)) return JNVGRAPH_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}

/** nvGRAPH Triangles counting
* count number of triangles (cycles of size 3) formed by graph edges
*/
JNIEXPORT jint JNICALL Java_jcuda_jnvgraph_JNvgraph_nvgraphTriangleCountNative(JNIEnv *env, jclass cls, jobject handle, jobject graph_descr, jlongArray result)
{
	// Null-checks for non-primitive arguments
	if (handle == NULL)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'handle' is null for nvgraphTriangleCount");
		return JNVGRAPH_STATUS_INTERNAL_ERROR;
	}
	if (graph_descr == NULL)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'graph_descr' is null for nvgraphTriangleCount");
		return JNVGRAPH_STATUS_INTERNAL_ERROR;
	}
	if (result == NULL)
	{
		ThrowByName(env, "java/lang/NullPointerException", "Parameter 'result' is null for nvgraphTriangleCount");
		return JNVGRAPH_STATUS_INTERNAL_ERROR;
	}

	// Log message
	Logger::log(LOG_TRACE, "Executing nvgraphTriangleCount(handle=%p, graph_descr=%p, result=%p)\n",
		handle, graph_descr, result);

	// Native variable declarations
	nvgraphHandle_t handle_native;
	nvgraphGraphDescr_t graph_descr_native;
	uint64_t result_native;

	// Obtain native variable values
	handle_native = (nvgraphHandle_t)getNativePointerValue(env, handle);
	graph_descr_native = (nvgraphGraphDescr_t)getNativePointerValue(env, graph_descr);
	// result is write-only

	// Native function call
	nvgraphStatus_t jniResult_native = nvgraphTriangleCount(handle_native, graph_descr_native, &result_native);

	// Write back native variable values
	// handle is read-only
	// graph_descr is read-only
	if (!set(env, result, 0, (jlong)result_native)) return JNVGRAPH_STATUS_INTERNAL_ERROR;

	// Return the result
	jint jniResult = (jint)jniResult_native;
	return jniResult;
}


