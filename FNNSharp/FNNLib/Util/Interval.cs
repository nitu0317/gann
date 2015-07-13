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
    public struct Interval
    {

        /// <summary>
        /// Defines the interval with a left and right hand.
        /// </summary>
        /// <param name="a">The left hand.</param>
        /// <param name="b">The right hand.</param>
        public Interval(double a, double b)
            : this()
        {
            A = a > b ? b : a;
            B = a > b ? a : b;
        }

        public double A { get; private set; }
        public double B { get; private set; }

        #region Operators

        /// <summary>
        /// The scaling operator for real intervals.
        /// </summary>
        /// <param name="a"></param>
        /// <param name="I"></param>
        /// <returns></returns>
        public static Interval operator*(double a, Interval I){
            return new Interval(I.A*a, I.B*a);
        }

        /// <summary>
        /// The lexically inverted scale operator.
        /// </summary>
        /// <param name="I"></param>
        /// <param name="a"></param>
        /// <returns></returns>
        public static Interval operator*(Interval I, double a){
            return a*I;
        }
        #endregion

        #region Predefined Intervals
        public static Interval UnitBall = new Interval(-1, 1);
        public static Interval AbsoluteUnitBall = new Interval(0, 1);
        #endregion
    }
}
