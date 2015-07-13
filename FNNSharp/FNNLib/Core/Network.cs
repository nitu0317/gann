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
    /// Defines a network for a generalized artificial neural network,.
    /// </summary>
    public class Network
    {
        public Network()
        {
            layers = new List<ILayer>();
        }


        /// <summary>
        /// Feeds the network forward with some input
        /// </summary>
        /// <param name="input">The input of the network : A</param>
        /// <returns>The output of the network : B</returns>
        public object FeedForward(object input)
        {
            if (layers.Count() == 0)
                return input;


            if (AType.IsInstanceOfType(input))
            {
                if (layers.Count() == 0)
                    return input;
                else
                    layers[0].FeedForward(input);
                
                for (int i = 1; i < layers.Count(); i++)
                {
                    layers[i].FeedForward(layers[i - 1].Output);
                }

                return layers.Last().Output;
            }
            else
                throw new InvalidOperationException("Tried to apply the network to input of incorrect codomain.");
        }




        /// <summary>
        /// Adds a layer to the generalized artificial neural network.
        /// The layer must have B equal to the previously added layer.
        /// </summary>
        /// <param name="layer"></param>
        public void AddLayer(ILayer layer){
            //We need to verify type congruence.
            if (layers.Count() != 0) 
            {
                if (!layers.Last().BType.Equals(layer.AType))
                    throw new ArrayTypeMismatchException(
                        "Tried to add a layer to the network whose domain is not equivalent tohe last layers codomain.");
                else
                    this.layers.Add(layer);
                    
            }
            else
            {
                layers.Add(layer);
                this.AType = layer.AType;
            }

            this.BType = layer.AType;
        }

        #region Properties

        /// <summary>
        /// The input type of the neural network
        /// </summary>
        public Type AType{ get; protected set;}

        /// <summary>
        /// The output type of the nerual network.
        /// </summary>
        public Type BType {get; protected set;}
        #endregion


        #region Fields

        List<ILayer> layers;

        #endregion
    }
}
