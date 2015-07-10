using FNNLib.Util;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FNNLib.Core
{
    /// <summary>
    /// Describes the general class of layers, \Sigma_l: A -> B.
    /// Subclasses include n,n1,n2, and f, all of which are described in the white paper.
    /// </summary>
    /// <typeparam name="A">The set from which the layer maps.</typeparam>
    /// <typeparam name="B">The set to which the layer maps.</typeparam>
    class Layer<A,B>
    {

        public Layer(int Z_X, int Z_Y, Interval R)
        {
            this.Z_X = Z_X;
            this.Z_Y = Z_Y;
            this.R = R;
        }

        /// <summary>
        /// Feeds the algorithm forward, yielding an output.
        /// We do not wish to contain anterior layers, and let the network handle propagation
        /// in an interative fashion.
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns>
        public abstract B FeedForward(A input);


        public int Z_X { get; set; }

        public int Z_Y { get; set; }

        public Interval R { get; set; }
    }
}
