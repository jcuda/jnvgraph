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

/** nvGRAPH status type returns */
public class nvgraphStatus
{
    public static final int NVGRAPH_STATUS_SUCCESS = 0;
    public static final int NVGRAPH_STATUS_NOT_INITIALIZED = 1;
    public static final int NVGRAPH_STATUS_ALLOC_FAILED = 2;
    public static final int NVGRAPH_STATUS_INVALID_VALUE = 3;
    public static final int NVGRAPH_STATUS_ARCH_MISMATCH = 4;
    public static final int NVGRAPH_STATUS_MAPPING_ERROR = 5;
    public static final int NVGRAPH_STATUS_EXECUTION_FAILED = 6;
    public static final int NVGRAPH_STATUS_INTERNAL_ERROR = 7;
    public static final int NVGRAPH_STATUS_TYPE_NOT_SUPPORTED = 8;
    public static final int NVGRAPH_STATUS_NOT_CONVERGED = 9;
    public static final int NVGRAPH_STATUS_GRAPH_TYPE_NOT_SUPPORTED = 10;

    /** JNVgraph status returns */
    public static final int JNVGRAPH_STATUS_INTERNAL_ERROR      = 0x10000001;
    
    /**
     * Private constructor to prevent instantiation
     */
    private nvgraphStatus()
    {
        // Private constructor to prevent instantiation
    }

    /**
     * Returns a string representation of the given constant
     *
     * @return A string representation of the given constant
     */
    public static String stringFor(int n)
    {
        switch (n)
        {
            case NVGRAPH_STATUS_SUCCESS: return "NVGRAPH_STATUS_SUCCESS";
            case NVGRAPH_STATUS_NOT_INITIALIZED: return "NVGRAPH_STATUS_NOT_INITIALIZED";
            case NVGRAPH_STATUS_ALLOC_FAILED: return "NVGRAPH_STATUS_ALLOC_FAILED";
            case NVGRAPH_STATUS_INVALID_VALUE: return "NVGRAPH_STATUS_INVALID_VALUE";
            case NVGRAPH_STATUS_ARCH_MISMATCH: return "NVGRAPH_STATUS_ARCH_MISMATCH";
            case NVGRAPH_STATUS_MAPPING_ERROR: return "NVGRAPH_STATUS_MAPPING_ERROR";
            case NVGRAPH_STATUS_EXECUTION_FAILED: return "NVGRAPH_STATUS_EXECUTION_FAILED";
            case NVGRAPH_STATUS_INTERNAL_ERROR: return "NVGRAPH_STATUS_INTERNAL_ERROR";
            case NVGRAPH_STATUS_TYPE_NOT_SUPPORTED: return "NVGRAPH_STATUS_TYPE_NOT_SUPPORTED";
            case NVGRAPH_STATUS_NOT_CONVERGED: return "NVGRAPH_STATUS_NOT_CONVERGED";
            case NVGRAPH_STATUS_GRAPH_TYPE_NOT_SUPPORTED: return "NVGRAPH_STATUS_GRAPH_TYPE_NOT_SUPPORTED";
            case JNVGRAPH_STATUS_INTERNAL_ERROR: return "JNVGRAPH_STATUS_INTERNAL_ERROR";
        }
        return "INVALID nvgraphStatus: "+n;
    }
}

