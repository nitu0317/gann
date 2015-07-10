using MathNet.Numerics.Interpolation;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FNNLib.Util
{
    public class FuncInterpolation :IInterpolation
    {
        #region Fields
        private Func<double, double> proc;
        private Func<double, double> deriv = null;
        private Func<double, double> integ = null;
        #endregion

        /// <summary>
        /// Defines a functional interepolation with only a procedure ]
        /// and no integratrion/differentiation capabilities.
        /// </summary>
        /// <param name="proc">The function representing the interpolation</param>
        public FuncInterpolation(Func<double, double> proc)
        {
            this.proc = proc;
        }


        /// <summary>
        /// Checks to see if a derivative is specified and returns its evaluation at t.
        /// </summary>
        /// <param name="t">The value at which to evaluate the derivative.</param>
        /// <returns>The derivative evaluated at t.</returns>
        public double Differentiate(double t)
        {
            if (deriv != null)
                return deriv(t);
            else
                throw new NotImplementedException();
        }

        /// <summary>
        /// We do not implement second order differentiation explicitly.
        /// </summary>
        /// <param name="t">NA</param>
        /// <returns>NA</returns>
        public double Differentiate2(double t)
        {
            throw new NotImplementedException();
        }

        /// <summary>
        /// Returns the evaluation of integration at a certain interval.
        /// </summary>
        /// <param name="a">The left end point.</param>
        /// <param name="b">The right end point.</param>
        /// <returns></returns>
        public double Integrate(double a, double b)
        {
            if (integ != null)
                return integ(b) - integ(a);
            else
                throw new NotImplementedException();
        }

        /// <summary>
        /// Integrates the procedure from 0 to t.
        /// </summary>
        /// <param name="t">The value at which to end the integration.</param>
        /// <returns></returns>
        public double Integrate(double t)
        {
            if (integ != null)
                return integ(t);
            else
                throw new NotImplementedException();
        }
        
        /// <summary>
        /// Returns the value of the procedure at some value t.
        /// </summary>
        /// <param name="t"></param>
        /// <returns></returns>
        public double Interpolate(double t)
        {
            return proc(t);
        }

        /// <summary>
        /// Returns whether or not differentiation is supported.
        /// </summary>
        public bool SupportsDifferentiation
        {
            get { return deriv == null; }
        }

        /// <summary>
        /// Returns whether or not integration is supported.
        /// </summary>
        public bool SupportsIntegration
        {
            get { return integ == null; }
        }
    }
}
