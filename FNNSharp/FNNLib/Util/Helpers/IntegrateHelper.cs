using MathNet.Numerics;
using MathNet.Numerics.LinearAlgebra;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FNNLib.Util
{
    public static class IntegrateHelper
    {

    //    #region Integrate
    //    #region Matrix Integration
    //    /// <summary>
    //    /// Approximation of the definite integral of an analytic smooth function valued matrix on a closed interval.
    //    /// </summary>
    //    /// <param name="F">The analytic smooth functional matrix to integrate.</param>
    //    /// <param name="intervalBegin">Where the interval starts, inclusive and finite.</param>
    //    /// <param name="intervalEnd">Where the interval stops, inclusive and finite.</param>
    //    /// <param name="targetAbsoluteError">The expected relative accuracy of the approximation.</param>
    //    /// <returns>Approximation of the finite integral in the given interval.</returns>
    //    public static Matrix<double> OnClosedInterval(
    //        Matrix<Func<double, double>> F, double intervalBegin, double intervalEnd, double absoluteTargetError)
    //    {
    //        return F.Map(
    //            f => Integrate.OnClosedInterval(f, intervalBegin, intervalEnd, absoluteTargetError)
    //        );
    //    }

    //    /// <summary>
    //    /// Approximation of the definite integral of an analytic smooth function valued matrix on a closed interval.
    //    /// </summary>
    //    /// <param name="F">The analytic smooth functional matrix to integrate.</param>
    //    /// <param name="intervalBegin">Where the interval starts, inclusive and finite.</param>
    //    /// <param name="intervalEnd">Where the interval stops, inclusive and finite.</param>
    //    /// <returns>Approximation of the finite integral in the given interval.</returns>
    //    public static Matrix<double> OnClosedInterval(
    //        Matrix<Func<double, double>> F, double intervalBegin, double intervalEnd)
    //    {
    //        return OnClosedInterval(F, intervalBegin, intervalEnd, 1e-8);
    //    }

    //    #endregion Matrix Integration


    //    #region Vector Integration

    //    /// <summary>
    //    /// Approximation of the definite integral of an analytic smooth function valued vector on a closed interval.
    //    /// </summary>
    //    /// <param name="F">The analytic smooth functional vector to integrate.</param>
    //    /// <param name="intervalBegin">Where the interval starts, inclusive and finite.</param>
    //    /// <param name="intervalEnd">Where the interval stops, inclusive and finite.</param>
    //    /// <param name="targetAbsoluteError">The expected relative accuracy of the approximation.</param>
    //    /// <returns>Approximation of the finite integral in the given interval.</returns>
    //    public static Vector<double> OnClosedInterval(
    //        Vector<Func<double, double>> F, double intervalBegin, double intervalEnd, double absoluteTargetError)
    //    {
    //        return F.Map(
    //            f => Integrate.OnClosedInterval(f, intervalBegin, intervalEnd, absoluteTargetError)
    //        );
    //    }

    //    /// <summary>
    //    /// Approximation of the definite integral of an analytic smooth function valued vector on a closed interval.
    //    /// </summary>
    //    /// <param name="F">The analytic smooth functional vector to integrate.</param>
    //    /// <param name="intervalBegin">Where the interval starts, inclusive and finite.</param>
    //    /// <param name="intervalEnd">Where the interval stops, inclusive and finite.</param>
    //    /// <returns>Approximation of the finite integral in the given interval.</returns>
    //    public static Vector<double> OnClosedInterval(
    //        Vector<Func<double, double>> F, double intervalBegin, double intervalEnd)
    //    {
    //        return OnClosedInterval(F, intervalBegin, intervalEnd, 1e-8);
    //    }

    //    #endregion Vector Integration

    //    #endregion
    }
}
