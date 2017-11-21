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

import jcuda.Pointer;

/**
 * Java port of a SpectralClusteringParameter
 */
public class SpectralClusteringParameter
{
    /**
     * number of clusters
     */
    public int n_clusters;
    /**
     * number of eigenvectors
     */
    public int n_eig_vects;
    /**
     * algorithm to use
     */
    public int algorithm;
    /**
     * tolerance of the eigensolver
     */
    public float evs_tolerance;
    /**
     * maximum number of iterations of the eigensolver
     */
    public int evs_max_iter;
    /**
     * tolerance of kmeans
     */
    public float kmean_tolerance;
    /**
     * maximum number of iterations of kemeans
     */
    public int kmean_max_iter;
    /**
     * optional parameter that can be used for preconditioning in the future
     */
    public Pointer opt;

    /**
     * Creates a new, uninitialized SpectralClusteringParameter
     */
    public SpectralClusteringParameter()
    {
        // Default constructor
    }

    /**
     * Creates a new SpectralClusteringParameter with the given values
     *
     * @param n_clusters The n_clusters value
     * @param n_eig_vects The n_eig_vects value
     * @param algorithm The algorithm value
     * @param evs_tolerance The evs_tolerance value
     * @param evs_max_iter The evs_max_iter value
     * @param kmean_tolerance The kmean_tolerance value
     * @param kmean_max_iter The kmean_max_iter value
     * @param opt The opt value
     */
    public SpectralClusteringParameter(int n_clusters, int n_eig_vects, int algorithm, float evs_tolerance, int evs_max_iter, float kmean_tolerance, int kmean_max_iter, Pointer opt)
    {
        this.n_clusters = n_clusters;
        this.n_eig_vects = n_eig_vects;
        this.algorithm = algorithm;
        this.evs_tolerance = evs_tolerance;
        this.evs_max_iter = evs_max_iter;
        this.kmean_tolerance = kmean_tolerance;
        this.kmean_max_iter = kmean_max_iter;
        this.opt = opt;
    }

    @Override
    public String toString()
    {
        return "SpectralClusteringParameter["+
            "n_clusters="+n_clusters+","+
            "n_eig_vects="+n_eig_vects+","+
            "algorithm="+algorithm+","+
            "evs_tolerance="+evs_tolerance+","+
            "evs_max_iter="+evs_max_iter+","+
            "kmean_tolerance="+kmean_tolerance+","+
            "kmean_max_iter="+kmean_max_iter+","+
            "opt="+opt+"]";
    }
}


