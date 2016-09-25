using MathNet.Numerics;
using MathNet.Numerics.Interpolation;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FNNLib.Util.Helpers
{
    /// <summary>
    /// A helper class for integration.
    /// </summary>
    public static class IntegrateHelper
    {
        /// <summary>
        /// Integrates an Ienumerable of funcs.
        /// </summary>
        /// <param name="funcs"></param>
        /// <param name="intervalBegin"></param>
        /// <param name="intervalEnd"></param>
        /// <param name="targetError"></param>
        /// <returns></returns>
        public static IEnumerable<double> OnClosedInterval(IEnumerable<IInterpolation> funcs,
            double intervalBegin, double intervalEnd, double targetError)
        {
            return funcs.Select(
                f => Integrate.OnClosedInterval(x => f.Interpolate(x), intervalBegin, intervalEnd, targetError)
            );
        }

        /// <summary>
        /// Intefgrates an IEnumerable of funcs
        /// </summary>
        /// <param name="funcs"></param>
        /// <param name="intervalBegin"></param>
        /// <param name="intervalEnd"></param>
        /// <param name="targetError"></param>
        /// <returns></returns>
        public static IEnumerable<double> OnClosedInterval(IEnumerable<Func<double,double>> funcs,
                    double intervalBegin, double intervalEnd, double targetError)
        {
            return funcs.Select(
                f => Integrate.OnClosedInterval(f, intervalBegin, intervalEnd, targetError)
            );
        }


    }
}
