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
 * Java port of a nvgraphCSCTopology32I
 */
public class nvgraphCSCTopology32I extends NativePointerObject
{
    public int nvertices;
    public int nedges;
    public Pointer destination_offsets = new Pointer();
    public Pointer source_indices = new Pointer();

    /**
     * Creates a new, uninitialized nvgraphCSCTopology32I
     */
    public nvgraphCSCTopology32I()
    {
        // Default constructor
    }

    /**
     * Creates a new nvgraphCSCTopology32I_st with the given values
     *
     * @param nvertices The nvertices value
     * @param nedges The nedges value
     * @param destination_offsets The destination_offsets value
     * @param source_indices The source_indices value
     */
    public nvgraphCSCTopology32I(int nvertices, int nedges, Pointer destination_offsets, Pointer source_indices)
    {
        this.nvertices = nvertices;
        this.nedges = nedges;
        this.destination_offsets = destination_offsets;
        this.source_indices = source_indices;
    }

    @Override
    public String toString()
    {
        return "nvgraphCSCTopology32I_st["+
            "nativePointer=0x"+Long.toHexString(getNativePointer())+","+
            "nvertices="+nvertices+","+
            "nedges="+nedges+","+
            "destination_offsets="+destination_offsets+","+
            "source_indices="+source_indices+"]";
    }
    
}


