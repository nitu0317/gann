using FNNLib.Core.Layers;
using FNNLib.Util;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FNNLib.Core
{
    /// <summary>
    /// Defines a network for a generalized functional neural network,.
    /// </summary>
    public class Network
    {
        public Network()
        {

            Layers.Add(new FunctionalLayer(10, 10, Interval.UnitBall));
            Layers[0].FeedForward(new FuncInterpolation(x => 10));
        }


        #region Fields

        List<ILayer> Layers;

        #endregion
    }
}
