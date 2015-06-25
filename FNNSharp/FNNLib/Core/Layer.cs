using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FNNLib.Core
{
    /// <summary>
    /// Describes the general class of layers, \Sigma_l: A -> B.
    /// Subclasses include n1,n2, and f, all of which are described in the white paper.
    /// </summary>
    /// <typeparam name="A">The set from which the layer maps.</typeparam>
    /// <typeparam name="B">The set to which the layer maps.</typeparam>
    class Layer<A,B>
    {
        public Layer(int Z_X, int Z_Y)
        {
            this.Z_X = Z_X;
            this.Z_Y = Z_Y;
        }



        public int Z_X { get; set; }

        public int Z_Y { get; set; }
    }
}
