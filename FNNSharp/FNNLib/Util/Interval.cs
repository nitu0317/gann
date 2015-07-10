using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FNNLib.Util
{
    /// <summary>
    /// Represents a real closed interval. 
    /// </summary>
    public class Interval
    {
        /// <summary>
        /// Defines the interval with a left and right hand.
        /// </summary>
        /// <param name="a">The left hand.</param>
        /// <param name="b">The right hand.</param>
        public Interval(double a, double b)
        {
            this.A = a > b ? b : a;
            this.B = a > b ? a : b;
        }

        public double A { get; set; }
        public double B { get; set; }
    }
}
