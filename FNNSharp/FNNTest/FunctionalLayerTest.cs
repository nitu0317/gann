using FNNLib.Core.Layers;
using FNNLib.Util;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace FNNTest
{
    /// <summary>
    /// Tests an F functional layer
    /// </summary>
    [TestClass]
    public class FunctionalLayerTest
    {
        /// <summary>
        /// Initializes the testing sweet.
        /// </summary>
        [TestInitialize]
        public void Initialize()
        {
            f = new FunctionalLayer(10, 10, Interval.AbsoluteUnitBall);
        }

        /// <summary>
        /// Tests the feedforward propagation algorithm,
        /// </summary>
        [TestMethod]
        public void FeedForwardTest()
        {
            f.FeedForward(new FuncInterpolation((x) => x));
        }

        private FunctionalLayer f;
    }
}