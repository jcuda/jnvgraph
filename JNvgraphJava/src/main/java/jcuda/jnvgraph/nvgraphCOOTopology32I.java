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

import jcuda.NativePointerObject;
import jcuda.Pointer;

/**
 * Java port of a nvgraphCOOTopology32I
 */
public class nvgraphCOOTopology32I extends NativePointerObject
{
    /**
     * n+1
     */
    public int nvertices;
    
    /**
     * nnz
     */
    public int nedges;
    
    /**
     * rowInd
     */
    public Pointer source_indices = new Pointer();
    
    /**
     * colInd
     */
    public Pointer destination_indices = new Pointer();

    /**
     * The {@link nvgraphTag}
     */
    public int tag;
    
    /**
     * Creates a new, uninitialized nvgraphCOOTopology32I
     */
    public nvgraphCOOTopology32I()
    {
        // Default constructor
    }

    /**
     * Creates a new nvgraphCOOTopology32I with the given values
     *
     * @param nvertices The nvertices value
     * @param nedges The nedges value
     * @param source_indices The source_indices value
     * @param destination_indices The source_indices value
     * @param tag The {@link nvgraphTag}
     */
    public nvgraphCOOTopology32I(int nvertices, int nedges, Pointer source_indices, Pointer destination_indices, int tag)
    {
        this.nvertices = nvertices;
        this.nedges = nedges;
        this.source_indices = source_indices;
        this.destination_indices = destination_indices;
        this.tag = tag;
    }

    @Override
    public String toString()
    {
        return "nvgraphCSCTopology32I_st["+
            "nativePointer=0x"+Long.toHexString(getNativePointer())+","+
            "nvertices="+nvertices+","+
            "nedges="+nedges+","+
            "source_indices="+source_indices+","+
            "destination_indices="+destination_indices+","+
            "tag="+nvgraphTag.stringFor(tag)+"]";
    }
    
}


