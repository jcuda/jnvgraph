/*
 * JNvgraph - Java bindings for nvGRAPH, the NVIDIA CUDA graph library,
 * to be used with JCuda
 *
 * Copyright (c) 2016-2017 Marco Hutter - http://www.jcuda.org
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

public class nvgraphClusteringMetric
{
    /**
     * clustering score telling how good the clustering is compared to random assignment.
     */
    public static final int NVGRAPH_MODULARITY = 0;
    /**
     * total number of edges between clusters.
     */
    public static final int NVGRAPH_EDGE_CUT = 1;
    /**
     * sum for all clusters of the number of edges going outside of the cluster divided by the number of vertex inside the cluster
     */
    public static final int NVGRAPH_RATIO_CUT = 2;

    /**
     * Private constructor to prevent instantiation
     */
    private nvgraphClusteringMetric()
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
            case NVGRAPH_MODULARITY: return "NVGRAPH_MODULARITY";
            case NVGRAPH_EDGE_CUT: return "NVGRAPH_EDGE_CUT";
            case NVGRAPH_RATIO_CUT: return "NVGRAPH_RATIO_CUT";
        }
        return "INVALID nvgraphClusteringMetric: "+n;
    }
}

