package jcuda.jnvgraph;

import static jcuda.cudaDataType.CUDA_R_32F;
import static jcuda.jnvgraph.JNvgraph.nvgraphAllocateEdgeData;
import static jcuda.jnvgraph.JNvgraph.nvgraphAllocateVertexData;
import static jcuda.jnvgraph.JNvgraph.nvgraphCreate;
import static jcuda.jnvgraph.JNvgraph.nvgraphCreateGraphDescr;
import static jcuda.jnvgraph.JNvgraph.nvgraphDestroy;
import static jcuda.jnvgraph.JNvgraph.nvgraphDestroyGraphDescr;
import static jcuda.jnvgraph.JNvgraph.nvgraphGetVertexData;
import static jcuda.jnvgraph.JNvgraph.nvgraphPagerank;
import static jcuda.jnvgraph.JNvgraph.nvgraphSetEdgeData;
import static jcuda.jnvgraph.JNvgraph.nvgraphSetGraphStructure;
import static jcuda.jnvgraph.JNvgraph.nvgraphSetVertexData;
import static jcuda.jnvgraph.nvgraphTopologyType.NVGRAPH_CSC_32;

import jcuda.Pointer;

public class JNvgraphSetGraphStructureTest
{
    public static void main(String[] args)
    {
        JNvgraph.setExceptionsEnabled(true);

        int n = 6, nnz = 10, vertex_numsets = 3, edge_numsets = 1;
        float alpha1 = 0.85f, alpha2 = 0.90f;
        Pointer alpha1_p = Pointer.to(new float[]{ alpha1 });
        Pointer alpha2_p = Pointer.to(new float[]{ alpha2 });
        int i, destination_offsets_h[], source_indices_h[];
        float weights_h[], bookmark_h[], pr_1[], pr_2[];
        Pointer vertex_dim[];

        // nvgraph variables
        nvgraphHandle handle = new nvgraphHandle();
        nvgraphGraphDescr graph = new nvgraphGraphDescr();
        nvgraphCSCTopology32I CSC_input;
        int edge_dimT[] = new int[]{ CUDA_R_32F };
        int vertex_dimT[];

        // Allocate host data
        destination_offsets_h = new int[n + 1];
        source_indices_h = new int[nnz];
        weights_h = new float[nnz];
        bookmark_h = new float[n];
        pr_1 = new float[n];
        pr_2 = new float[n];
        vertex_dim = new Pointer[vertex_numsets];
        vertex_dimT = new int[3];
        CSC_input = new nvgraphCSCTopology32I();

        // Initialize host data
        vertex_dim[0] = Pointer.to(bookmark_h);
        vertex_dim[1] = Pointer.to(pr_1);
        vertex_dim[2] = Pointer.to(pr_2);
        vertex_dimT[0] = CUDA_R_32F;
        vertex_dimT[1] = CUDA_R_32F;
        vertex_dimT[2] = CUDA_R_32F;

        weights_h[0] = 0.333333f;
        weights_h[1] = 0.500000f;
        weights_h[2] = 0.333333f;
        weights_h[3] = 0.500000f;
        weights_h[4] = 0.500000f;
        weights_h[5] = 1.000000f;
        weights_h[6] = 0.333333f;
        weights_h[7] = 0.500000f;
        weights_h[8] = 0.500000f;
        weights_h[9] = 0.500000f;

        destination_offsets_h[0] = 0;
        destination_offsets_h[1] = 1;
        destination_offsets_h[2] = 3;
        destination_offsets_h[3] = 4;
        destination_offsets_h[4] = 6;
        destination_offsets_h[5] = 8;
        destination_offsets_h[6] = 10;

        source_indices_h[0] = 2;
        source_indices_h[1] = 0;
        source_indices_h[2] = 2;
        source_indices_h[3] = 0;
        source_indices_h[4] = 4;
        source_indices_h[5] = 5;
        source_indices_h[6] = 2;
        source_indices_h[7] = 3;
        source_indices_h[8] = 3;
        source_indices_h[9] = 4;

        bookmark_h[0] = 0.0f;
        bookmark_h[1] = 1.0f;
        bookmark_h[2] = 0.0f;
        bookmark_h[3] = 0.0f;
        bookmark_h[4] = 0.0f;
        bookmark_h[5] = 0.0f;

        // Starting nvgraph
        nvgraphCreate(handle);
        nvgraphCreateGraphDescr(handle, graph);

        CSC_input.nvertices = n;
        CSC_input.nedges = nnz;
        CSC_input.destination_offsets = Pointer.to(destination_offsets_h);
        CSC_input.source_indices = Pointer.to(source_indices_h);

        // Set graph connectivity and properties (transfers)
        nvgraphSetGraphStructure(handle, graph, CSC_input, NVGRAPH_CSC_32);
        
        nvgraphAllocateVertexData(handle, graph, vertex_numsets,
            Pointer.to(vertex_dimT));
        nvgraphAllocateEdgeData(handle, graph, edge_numsets,
            Pointer.to(edge_dimT));
        for (i = 0; i < 2; ++i)
            nvgraphSetVertexData(handle, graph, vertex_dim[i], i);
        nvgraphSetEdgeData(handle, graph, Pointer.to(weights_h), 0);

        // First run with default values
        nvgraphPagerank(handle, graph, 0, alpha1_p, 0, 0, 1, 0.0f, 0);

        // Get and print result
        nvgraphGetVertexData(handle, graph, vertex_dim[1], 1);
        System.out.printf("pr_1, alpha = 0.85\n");
        for (i = 0; i < n; i++)
            System.out.printf("%f\n", pr_1[i]);
        System.out.printf("\n");

        // Second run with different damping factor and an initial guess
        for (i = 0; i < n; i++)
            pr_2[i] = pr_1[i];

        nvgraphSetVertexData(handle, graph, vertex_dim[2], 2);
        nvgraphPagerank(handle, graph, 0, alpha2_p, 0, 1, 2, 0.0f, 0);

        // Get and print result
        nvgraphGetVertexData(handle, graph, vertex_dim[2], 2);
        System.out.printf("pr_2, alpha = 0.90\n");
        for (i = 0; i < n; i++)
            System.out.printf("%f\n", pr_2[i]);
        System.out.printf("\n");

        // Clean
        nvgraphDestroyGraphDescr(handle, graph);
        nvgraphDestroy(handle);

        System.out.printf("\nDone!\n");
    }
}
