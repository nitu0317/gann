using FNNLib.Core;
using FNNLib.Core.Layers;
using FNNLib.Util;
using MathNet.Numerics.LinearAlgebra;
using System;
using System.Threading;
using System.Windows.Forms;

namespace FNNSharp
{
    internal class Program
    {
        [STAThread]
        private static void Main(string[] args)
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

            Network fnn = new Network();
            fnn.AddLayer(new FunctionalLayer(10, 10, Interval.UnitBall));

            fnn.AddLayer(new FunctionalLayer(10, 10, Interval.UnitBall));


            ShowPlot fPlot = new ShowPlot(
                (FuncInterpolation)fnn.FeedForward(
                new FuncInterpolation(x => x)), "f functional test");

            Thread t = new Thread(
                () => Application.Run(fPlot));

            t.Start();

            //Train a functional neural network
            while (true)
            {

               // Console.ReadKey();
                double error  = fnn.Train(new FuncInterpolation(x => x),
                    new FuncInterpolation(x => Math.Sin(2*x)), 0.5);
                Console.WriteLine(error);
                fPlot.Replot((FuncInterpolation)fnn.Output, error.ToString());

            }

            ///Build arbitrary discrete neural network.
            //while (true)
            //{
            //    Network nn = new Network();
            //    nn.AddLayer(new FunctionalLayer(10, 10, Interval.UnitBall));

                
            //    Console.ReadKey();
            //}

            Console.ReadKey();
        }
    }
}