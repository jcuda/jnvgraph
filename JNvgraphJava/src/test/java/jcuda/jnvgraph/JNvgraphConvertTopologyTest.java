package jcuda.jnvgraph;

import static jcuda.jnvgraph.JNvgraph.nvgraphConvertTopology;
import static jcuda.jnvgraph.JNvgraph.nvgraphCreate;
import static jcuda.jnvgraph.nvgraphTopologyType.NVGRAPH_COO_32;
import static jcuda.jnvgraph.nvgraphTopologyType.NVGRAPH_CSC_32;
import static jcuda.runtime.JCuda.cudaMalloc;
import static jcuda.runtime.JCuda.cudaMemcpy;
import static jcuda.runtime.cudaMemcpyKind.cudaMemcpyDeviceToHost;
import static jcuda.runtime.cudaMemcpyKind.cudaMemcpyHostToDevice;
import static org.junit.Assert.assertArrayEquals;
import static org.junit.Assert.assertEquals;

import java.util.Arrays;

import org.junit.Test;

import jcuda.Pointer;
import jcuda.Sizeof;
import jcuda.cudaDataType;
import jcuda.runtime.JCuda;

/**
 * Basic test for the nvgraphConvertTopology method.
 */
public class JNvgraphConvertTopologyTest
{
    public static void main(String[] args)
    {
        JNvgraphConvertTopologyTest t = new JNvgraphConvertTopologyTest();
        t.testNvgraphConvertTopology();
    }
    
    @Test
    public void testNvgraphConvertTopology()
    {
        JCuda.setExceptionsEnabled(true);
        
        // Set up the values to be copied. This is the topology information
        // given in COO form. The values used here are taken from 
        // http://fareastprogramming.hatenadiary.jp/entry/2016/12/06/203405
        
        float r1 = 1.0f;
        float r2 = 1.0f / 2.0f;
        float r3 = 1.0f / 3.0f;
        int nvertices = 8;
        int nedges = 17;
        int source_indices[] = { 
            0, 0, 1, 2, 2, 3, 3, 3, 4, 4, 4, 5, 6, 6, 6, 7, 7 
        };
        int destination_indices[] = { 
            1, 2, 3, 1, 4, 1, 4, 5, 5, 6, 7, 7, 0, 4, 7, 5, 6 
        };
        float weights[] = { 
            r2, r2, r1, r2, r2, r3, r3, r3, r3, r3, r3, r1, r3, r3, r3, r2, r2 
        };

        // Set up the input topology in COO representation
        nvgraphCOOTopology32I COO_input = new nvgraphCOOTopology32I();
        COO_input.nedges = nedges;
        COO_input.nvertices = nvertices;
        COO_input.tag = nvgraphTag.NVGRAPH_UNSORTED;

        // Allocate memory for the COO representation
        cudaMalloc(COO_input.source_indices, nedges * Sizeof.FLOAT);
        cudaMalloc(COO_input.destination_indices, nedges * Sizeof.FLOAT);
        Pointer coo_weights = new Pointer();
        cudaMalloc(coo_weights, nedges * 4);
        
        // Copy the COO input data from the host to the device 
        cudaMemcpy(COO_input.source_indices, 
            Pointer.to(source_indices),
            nedges * Sizeof.FLOAT, cudaMemcpyHostToDevice);
        cudaMemcpy(
            COO_input.destination_indices, 
            Pointer.to(destination_indices), 
            nedges * Sizeof.FLOAT, cudaMemcpyHostToDevice);
        cudaMemcpy(coo_weights, 
            Pointer.to(weights), 
            nedges * Sizeof.FLOAT, cudaMemcpyHostToDevice);
        
        
        // Prepare the topology in CSC form, which will store the output
        nvgraphCSCTopology32I CSC_output = new nvgraphCSCTopology32I();
        
        // Allocate memory for the CSC representation
        cudaMalloc(CSC_output.source_indices, nedges * Sizeof.FLOAT);
        cudaMalloc(CSC_output.destination_offsets, 
            (nvertices + 1) * Sizeof.FLOAT);
        Pointer csc_weights = new Pointer();
        cudaMalloc(csc_weights, nedges * Sizeof.FLOAT);

        // Create the nvGRAPH handle
        nvgraphHandle handle = new nvgraphHandle();
        nvgraphCreate(handle);
     
        // Execute the conversion
        Pointer dataType = Pointer.to(new int[] { cudaDataType.CUDA_R_32F });
        nvgraphConvertTopology(handle, 
            NVGRAPH_COO_32, COO_input, coo_weights, dataType, 
            NVGRAPH_CSC_32, CSC_output, csc_weights);
        
        
        // Copy the CSC data from the device to the host
        int host_csc_source_indices[] = new int[nedges];
        cudaMemcpy(Pointer.to(host_csc_source_indices), 
            CSC_output.source_indices, 
            nedges * Sizeof.INT, cudaMemcpyDeviceToHost);
        
        int host_csc_destination_offsets[] = new int[nvertices + 1];
        cudaMemcpy(Pointer.to(host_csc_destination_offsets), 
            CSC_output.destination_offsets, 
            (nvertices + 1) * Sizeof.INT, cudaMemcpyDeviceToHost);
        
        float host_csc_weights[] = new float[nedges];
        cudaMemcpy(Pointer.to(host_csc_weights), 
            csc_weights, nedges * Sizeof.FLOAT, cudaMemcpyDeviceToHost);
        
        // TODO: This should not be necessary
        //System.out.println("JNvgraphConvertTopologyTest: " 
        //    + "Setting numbers of vertices and edges in output");
        //CSC_output.nvertices = COO_input.nvertices;
        //CSC_output.nedges = COO_input.nedges;
        
        boolean printResult = false;
        //printResult = true;
        if (printResult)
        {
            System.out.println("nvertices           = " + CSC_output.nvertices);
            System.out.println("nedges              = " + CSC_output.nedges);
            System.out.println("source_indices      = " + 
                Arrays.toString(host_csc_source_indices));
            System.out.println("destination_offsets = " + 
                Arrays.toString(host_csc_destination_offsets));
            System.out.println("weights             = " + 
                Arrays.toString(host_csc_weights));
        }
        
        assertEquals(8, CSC_output.nvertices);
        assertEquals(17, CSC_output.nedges);
        assertArrayEquals(new int[] {
            6, 0, 2, 3, 0, 1, 2, 3, 6, 3, 4, 7, 4, 7, 4, 5, 6
        }, host_csc_source_indices);
        assertArrayEquals(new int[] {
            0, 1, 4, 5, 6, 9, 12, 14, 17
        }, host_csc_destination_offsets);
        assertArrayEquals(new float[] {
            r3, r2, r2, r3, r2, r1, r2, r3, r3, r3, r3, r2, r3, r2, r3, r1, r3
        }, host_csc_weights, 1e-4f);
    }
}
