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
package jcuda.jnvgraph;

import jcuda.CudaException;
import jcuda.LibUtils;
import jcuda.LogLevel;
import jcuda.Pointer;
import jcuda.runtime.JCuda;

/**
 * Java bindings for nvGRAPH, the NVIDIA CUDA graph library
 */
public class JNvgraph
{
    /**
     * The flag that indicates whether the native library has been
     * loaded
     */
    private static boolean initialized = false;

    /**
     * Whether a CudaException should be thrown if a method is about
     * to return a result code that is not
     * nvgraphStatus.NVGRAPH_STATUS_SUCCESS
     */
    private static boolean exceptionsEnabled = false;

    /* Private constructor to prevent instantiation */
    private JNvgraph()
    {
    }

    // Initialize the native library.
    static
    {
        initialize();
    }

    /**
     * Initializes the native library. Note that this method
     * does not have to be called explicitly, since it will
     * be called automatically when this class is loaded.
     */
    public static void initialize()
    {
        if (!initialized)
        {
            String libraryBaseName = "JNvgraph-" + JCuda.getJCudaVersion();
            String libraryName = 
                LibUtils.createPlatformLibraryName(libraryBaseName);
            LibUtils.loadLibrary(libraryName);
            initialized = true;
        }
    }


    /**
     * Enables or disables exceptions. By default, the methods of this class
     * only set the {@link cudnnStatus} from the native methods.
     * If exceptions are enabled, a CudaException with a detailed error
     * message will be thrown if a method is about to set a result code
     * that is not nvgraphStatus.NVGRAPH_STATUS_SUCCESS
     *
     * @param enabled Whether exceptions are enabled
     */
    public static void setExceptionsEnabled(boolean enabled)
    {
        exceptionsEnabled = enabled;
    }

    /**
     * If the given result is not nvgraphStatus.NVGRAPH_STATUS_SUCCESS
     * and exceptions have been enabled, this method will throw a
     * CudaException with an error message that corresponds to the
     * given result code. Otherwise, the given result is simply
     * returned.
     *
     * @param result The result to check
     * @return The result that was given as the parameter
     * @throws CudaException If exceptions have been enabled and
     * the given result code is not nvgraphStatus.NVGRAPH_STATUS_SUCCESS
     */
    private static int checkResult(int result)
    {
        if (exceptionsEnabled && result !=
            nvgraphStatus.NVGRAPH_STATUS_SUCCESS)
        {
            throw new CudaException(nvgraphStatus.stringFor(result));
        }
        return result;
    }

    /**
     * Set the specified log level for the JNvgraph library.<br />
     * <br />
     * Currently supported log levels:
     * <br />
     * LOG_QUIET: Never print anything <br />
     * LOG_ERROR: Print error messages <br />
     * LOG_TRACE: Print a trace of all native function calls <br />
     *
     * @param logLevel The log level to use.
     */
    public static void setLogLevel(LogLevel logLevel)
    {
        setLogLevelNative(logLevel.ordinal());
    }

    private static native void setLogLevelNative(int logLevel);
    
    
    
    
    public static String nvgraphStatusGetString(
        int status)
    {
        return nvgraphStatusGetStringNative(status);
    }
    private static native String nvgraphStatusGetStringNative(
        int status);


    /** Open the library and create the handle */
    public static int nvgraphCreate(
        nvgraphHandle handle)
    {
        return checkResult(nvgraphCreateNative(handle));
    }
    private static native int nvgraphCreateNative(
        nvgraphHandle handle);


    /**  Close the library and destroy the handle  */
    public static int nvgraphDestroy(
        nvgraphHandle handle)
    {
        return checkResult(nvgraphDestroyNative(handle));
    }
    private static native int nvgraphDestroyNative(
        nvgraphHandle handle);


    /** Create an empty graph descriptor */
    public static int nvgraphCreateGraphDescr(
        nvgraphHandle handle, 
        nvgraphGraphDescr descrG)
    {
        return checkResult(nvgraphCreateGraphDescrNative(handle, descrG));
    }
    private static native int nvgraphCreateGraphDescrNative(
        nvgraphHandle handle, 
        nvgraphGraphDescr descrG);


    /** Destroy a graph descriptor */
    public static int nvgraphDestroyGraphDescr(
        nvgraphHandle handle, 
        nvgraphGraphDescr descrG)
    {
        return checkResult(nvgraphDestroyGraphDescrNative(handle, descrG));
    }
    private static native int nvgraphDestroyGraphDescrNative(
        nvgraphHandle handle, 
        nvgraphGraphDescr descrG);


    /** Set size, topology data in the graph descriptor  */
    public static int nvgraphSetGraphStructure(
        nvgraphHandle handle, 
        nvgraphGraphDescr descrG, 
        Object topologyData, 
        int TType)
    {
        return checkResult(nvgraphSetGraphStructureNative(handle, descrG, topologyData, TType));
    }
    private static native int nvgraphSetGraphStructureNative(
        nvgraphHandle handle, 
        nvgraphGraphDescr descrG, 
        Object topologyData, 
        int TType);


    /** Query size and topology information from the graph descriptor */
    public static int nvgraphGetGraphStructure(
        nvgraphHandle handle, 
        nvgraphGraphDescr descrG, 
        Object topologyData, 
        int[] TType)
    {
        return checkResult(nvgraphGetGraphStructureNative(handle, descrG, topologyData, TType));
    }
    private static native int nvgraphGetGraphStructureNative(
        nvgraphHandle handle, 
        nvgraphGraphDescr descrG, 
        Object topologyData, 
        int[] TType);


    /** Allocate numsets vectors of size V reprensenting Vertex Data and attached them the graph.
     * settypes[i] is the type of vector #i, currently all Vertex and Edge data should have the same type */
    public static int nvgraphAllocateVertexData(
        nvgraphHandle handle, 
        nvgraphGraphDescr descrG, 
        long numsets, 
        Pointer settypes)
    {
        return checkResult(nvgraphAllocateVertexDataNative(handle, descrG, numsets, settypes));
    }
    private static native int nvgraphAllocateVertexDataNative(
        nvgraphHandle handle, 
        nvgraphGraphDescr descrG, 
        long numsets, 
        Pointer settypes);


    /** Allocate numsets vectors of size E reprensenting Edge Data and attached them the graph.
     * settypes[i] is the type of vector #i, currently all Vertex and Edge data should have the same type */
    public static int nvgraphAllocateEdgeData(
        nvgraphHandle handle, 
        nvgraphGraphDescr descrG, 
        long numsets, 
        Pointer settypes)
    {
        return checkResult(nvgraphAllocateEdgeDataNative(handle, descrG, numsets, settypes));
    }
    private static native int nvgraphAllocateEdgeDataNative(
        nvgraphHandle handle, 
        nvgraphGraphDescr descrG, 
        long numsets, 
        Pointer settypes);


    /** Update the vertex set #setnum with the data in *vertexData, sets have 0-based index
     *  Conversions are not sopported so nvgraphTopologyType_t should match the graph structure */
    public static int nvgraphSetVertexData(
        nvgraphHandle handle, 
        nvgraphGraphDescr descrG, 
        Pointer vertexData, 
        long setnum)
    {
        return checkResult(nvgraphSetVertexDataNative(handle, descrG, vertexData, setnum));
    }
    private static native int nvgraphSetVertexDataNative(
        nvgraphHandle handle, 
        nvgraphGraphDescr descrG, 
        Pointer vertexData, 
        long setnum);


    /** Copy the edge set #setnum in *edgeData, sets have 0-based index
     *  Conversions are not sopported so nvgraphTopologyType_t should match the graph structure */
    public static int nvgraphGetVertexData(
        nvgraphHandle handle, 
        nvgraphGraphDescr descrG, 
        Pointer vertexData, 
        long setnum)
    {
        return checkResult(nvgraphGetVertexDataNative(handle, descrG, vertexData, setnum));
    }
    private static native int nvgraphGetVertexDataNative(
        nvgraphHandle handle, 
        nvgraphGraphDescr descrG, 
        Pointer vertexData, 
        long setnum);


    /** Convert the edge data to another topology
     */
    public static int nvgraphConvertTopology(
        nvgraphHandle handle, 
        int srcTType, 
        Object srcTopology, 
        Pointer srcEdgeData, 
        Pointer dataType, 
        int dstTType, 
        Object dstTopology, 
        Pointer dstEdgeData)
    {
        return checkResult(nvgraphConvertTopologyNative(handle, srcTType, srcTopology, srcEdgeData, dataType, dstTType, dstTopology, dstEdgeData));
    }
    private static native int nvgraphConvertTopologyNative(
        nvgraphHandle handle, 
        int srcTType, 
        Object srcTopology, 
        Pointer srcEdgeData, 
        Pointer dataType, 
        int dstTType, 
        Object dstTopology, 
        Pointer dstEdgeData);


    /** Convert graph to another structure
     */
    public static int nvgraphConvertGraph(
        nvgraphHandle handle, 
        nvgraphGraphDescr srcDescrG, 
        nvgraphGraphDescr dstDescrG, 
        int dstTType)
    {
        return checkResult(nvgraphConvertGraphNative(handle, srcDescrG, dstDescrG, dstTType));
    }
    private static native int nvgraphConvertGraphNative(
        nvgraphHandle handle, 
        nvgraphGraphDescr srcDescrG, 
        nvgraphGraphDescr dstDescrG, 
        int dstTType);


    /** Update the edge set #setnum with the data in *edgeData, sets have 0-based index
     *  Conversions are not sopported so nvgraphTopologyType_t should match the graph structure */
    public static int nvgraphSetEdgeData(
        nvgraphHandle handle, 
        nvgraphGraphDescr descrG, 
        Pointer edgeData, 
        long setnum)
    {
        return checkResult(nvgraphSetEdgeDataNative(handle, descrG, edgeData, setnum));
    }
    private static native int nvgraphSetEdgeDataNative(
        nvgraphHandle handle, 
        nvgraphGraphDescr descrG, 
        Pointer edgeData, 
        long setnum);


    /** Copy the edge set #setnum in *edgeData, sets have 0-based index
     * Conversions are not sopported so nvgraphTopologyType_t should match the graph structure */
    public static int nvgraphGetEdgeData(
        nvgraphHandle handle, 
        nvgraphGraphDescr descrG, 
        Pointer edgeData, 
        long setnum)
    {
        return checkResult(nvgraphGetEdgeDataNative(handle, descrG, edgeData, setnum));
    }
    private static native int nvgraphGetEdgeDataNative(
        nvgraphHandle handle, 
        nvgraphGraphDescr descrG, 
        Pointer edgeData, 
        long setnum);


    /** create a new graph by extracting a subgraph given a list of vertices
     */
    public static int nvgraphExtractSubgraphByVertex(
        nvgraphHandle handle, 
        nvgraphGraphDescr descrG, 
        nvgraphGraphDescr subdescrG, 
        Pointer subvertices, 
        long numvertices)
    {
        return checkResult(nvgraphExtractSubgraphByVertexNative(handle, descrG, subdescrG, subvertices, numvertices));
    }
    private static native int nvgraphExtractSubgraphByVertexNative(
        nvgraphHandle handle, 
        nvgraphGraphDescr descrG, 
        nvgraphGraphDescr subdescrG, 
        Pointer subvertices, 
        long numvertices);


    /** create a new graph by extracting a subgraph given a list of edges
     */
    public static int nvgraphExtractSubgraphByEdge(
        nvgraphHandle handle, 
        nvgraphGraphDescr descrG, 
        nvgraphGraphDescr subdescrG, 
        Pointer subedges, 
        long numedges)
    {
        return checkResult(nvgraphExtractSubgraphByEdgeNative(handle, descrG, subdescrG, subedges, numedges));
    }
    private static native int nvgraphExtractSubgraphByEdgeNative(
        nvgraphHandle handle, 
        nvgraphGraphDescr descrG, 
        nvgraphGraphDescr subdescrG, 
        Pointer subedges, 
        long numedges);


    /** nvGRAPH Semi-ring sparse matrix vector multiplication
     */
    public static int nvgraphSrSpmv(
        nvgraphHandle handle, 
        nvgraphGraphDescr descrG, 
        long weight_index, 
        Pointer alpha, 
        long x_index, 
        Pointer beta, 
        long y_index, 
        int SR)
    {
        return checkResult(nvgraphSrSpmvNative(handle, descrG, weight_index, alpha, x_index, beta, y_index, SR));
    }
    private static native int nvgraphSrSpmvNative(
        nvgraphHandle handle, 
        nvgraphGraphDescr descrG, 
        long weight_index, 
        Pointer alpha, 
        long x_index, 
        Pointer beta, 
        long y_index, 
        int SR);


    /** nvGRAPH Single Source Shortest Path (SSSP)
     * Calculate the shortest path distance from a single vertex in the graph to all other vertices.
     */
    public static int nvgraphSssp(
        nvgraphHandle handle, 
        nvgraphGraphDescr descrG, 
        long weight_index, 
        Pointer source_vert, 
        long sssp_index)
    {
        return checkResult(nvgraphSsspNative(handle, descrG, weight_index, source_vert, sssp_index));
    }
    private static native int nvgraphSsspNative(
        nvgraphHandle handle, 
        nvgraphGraphDescr descrG, 
        long weight_index, 
        Pointer source_vert, 
        long sssp_index);


    /** nvGRAPH WidestPath
     * Find widest path potential from source_index to every other vertices.
     */
    public static int nvgraphWidestPath(
        nvgraphHandle handle, 
        nvgraphGraphDescr descrG, 
        long weight_index, 
        Pointer source_vert, 
        long widest_path_index)
    {
        return checkResult(nvgraphWidestPathNative(handle, descrG, weight_index, source_vert, widest_path_index));
    }
    private static native int nvgraphWidestPathNative(
        nvgraphHandle handle, 
        nvgraphGraphDescr descrG, 
        long weight_index, 
        Pointer source_vert, 
        long widest_path_index);


    /** nvGRAPH PageRank
     * Find PageRank for each vertex of a graph with a given transition probabilities, a bookmark vector of dangling vertices, and the damping factor.
     */
    public static int nvgraphPagerank(
        nvgraphHandle handle, 
        nvgraphGraphDescr descrG, 
        long weight_index, 
        Pointer alpha, 
        long bookmark_index, 
        int has_guess, 
        long pagerank_index, 
        float tolerance, 
        int max_iter)
    {
        return checkResult(nvgraphPagerankNative(handle, descrG, weight_index, alpha, bookmark_index, has_guess, pagerank_index, tolerance, max_iter));
    }
    private static native int nvgraphPagerankNative(
        nvgraphHandle handle, 
        nvgraphGraphDescr descrG, 
        long weight_index, 
        Pointer alpha, 
        long bookmark_index, 
        int has_guess, 
        long pagerank_index, 
        float tolerance, 
        int max_iter);

}

