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

public class nvgraphSpectralClusteringType
{
    /**
     * maximize modularity with Lanczos solver
     */
    public static final int NVGRAPH_MODULARITY_MAXIMIZATION = 0;
    /**
     * minimize balanced cut with Lanczos solver
     */
    public static final int NVGRAPH_BALANCED_CUT_LANCZOS = 1;
    /**
     * minimize balanced cut with LOPCG solver
     */
    public static final int NVGRAPH_BALANCED_CUT_LOBPCG = 2;

    /**
     * Private constructor to prevent instantiation
     */
    private nvgraphSpectralClusteringType()
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
            case NVGRAPH_MODULARITY_MAXIMIZATION: return "NVGRAPH_MODULARITY_MAXIMIZATION";
            case NVGRAPH_BALANCED_CUT_LANCZOS: return "NVGRAPH_BALANCED_CUT_LANCZOS";
            case NVGRAPH_BALANCED_CUT_LOBPCG: return "NVGRAPH_BALANCED_CUT_LOBPCG";
        }
        return "INVALID nvgraphSpectralClusteringType: "+n;
    }
}

