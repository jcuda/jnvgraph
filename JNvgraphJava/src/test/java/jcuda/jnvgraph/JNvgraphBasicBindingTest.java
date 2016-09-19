/*
 * JCuda - Java bindings for CUDA
 *
 * http://www.jcuda.org
 */
package jcuda.jnvgraph;


import static org.junit.Assert.assertTrue;

import org.junit.Test;

/**
 * Basic test of the bindings of the JNvgraph class
 */
public class JNvgraphBasicBindingTest
{
    public static void main(String[] args)
    {
        BasicBindingTest.testBinding(JNvgraph.class);
    }

    @Test
    public void testJCudnn()
    {
        assertTrue(BasicBindingTest.testBinding(JNvgraph.class));
    }
    

}
