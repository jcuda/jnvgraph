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
 * Java port of a nvgraphCSRTopology32I
 */
public class nvgraphCSRTopology32I extends NativePointerObject
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
     * rowPtr
     */
    public Pointer source_offsets = new Pointer();
    
    /**
     * colInd
     */
    public Pointer destination_indices = new Pointer();

    /**
     * Creates a new, uninitialized nvgraphCSRTopology32I
     */
    public nvgraphCSRTopology32I()
    {
        // Default constructor
    }

    /**
     * Creates a new nvgraphCSRTopology32I with the given values
     *
     * @param nvertices The nvertices value
     * @param nedges The nedges value
     * @param source_offsets The source_offsets value
     * @param destination_indices The destination_indices value
     */
    public nvgraphCSRTopology32I(int nvertices, int nedges, Pointer source_offsets, Pointer destination_indices)
    {
        this.nvertices = nvertices;
        this.nedges = nedges;
        this.source_offsets = source_offsets;
        this.destination_indices = destination_indices;
    }

    @Override
    public String toString()
    {
        return "nvgraphCSRTopology32I_st["+
            "nativePointer=0x"+Long.toHexString(getNativePointer())+","+
            "nvertices="+nvertices+","+
            "nedges="+nedges+","+
            "source_offsets="+source_offsets+","+
            "destination_indices="+destination_indices+"]";
    }
}


