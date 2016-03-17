using FNNLib.Core;
using FNNLib.Core.Layers;
using FNNLib.Core.NeuralLibrary.NeuralNetwork;
using FNNLib.Experimentation;
using FNNLib.Util;
using MathNet.Numerics.IntegralTransforms;
using MathNet.Numerics.LinearAlgebra;
using System;
using System.Linq;
using System.Threading;
using System.Windows.Forms;

namespace FNNSharp
{
    internal class Program
    {
        [STAThread]
        private static void Main(string[] args)
        {

            Network gann = new Network();

            double lr = 1;
            int hidden = 1000, outp = 1, inp = 1;

            double error;
            int epoch;


            #region Saturation Test

            var hidOut = new N2TransitionalLayer(2, outp, Interval.UnitBall,
                new MathNet.Numerics.Distributions.Normal(0, 10),Sigmoid.Linear);
            var inHid = new N1TransitionalLayer(hidden, 2, Interval.UnitBall,
                new MathNet.Numerics.Distributions.Normal(0, 10), Sigmoid.HyperbolicTangent);


            gann.AddLayer(inHid);
            gann.AddLayer(hidOut);

            var fPLot = new ShowPlot(new FuncInterpolation(
                x =>
                    ((Vector<double>)gann.FeedForward(Vector<double>.Build.Dense(1,x)))[0]
                ), "cont neural net test");


            Application.Run(fPLot);


            #endregion

            //Copy K for comparison
            //Matrix<double> K = Matrix<double>.Build.Dense(hidden, outp);

            //hidOut.K.CopyTo(K);

            #region C(x) to R^n Test

            
            //gann.AddLayer(transLayer);

            //error = 10000;

           
            //for (epoch = 0; error > 0.01; epoch++ )
            //{
            //    error =
            //        gann.Train(FuncInterpolation.Mononomial(1), Vector<double>.Build.Dense(new double[] { 1, 0 }), lr)
            //        + gann.Train(FuncInterpolation.Mononomial(2), Vector<double>.Build.Dense(new double[] { 0, 1 }), lr)
            //        + gann.Train(FuncInterpolation.Mononomial(3), Vector<double>.Build.Dense(new double[] { 1, 0 }), lr)
            //        + gann.Train(FuncInterpolation.Mononomial(4), Vector<double>.Build.Dense(new double[] { 0, 1 }), lr)

            //        + gann.Train(FuncInterpolation.Mononomial(21), Vector<double>.Build.Dense(new double[] { 1, 0 }), lr)

            //        + gann.Train(FuncInterpolation.Mononomial(13), Vector<double>.Build.Dense(new double[] { 1, 0 }), lr)
            //        + gann.Train(FuncInterpolation.Mononomial(30), Vector<double>.Build.Dense(new double[] { 0, 1 }), lr)

            //        + gann.Train(FuncInterpolation.Mononomial(50), Vector<double>.Build.Dense(new double[] { 0, 1 }), lr);
            //    //Console.WriteLine(i + ": \n" + gann.Output + " Error: " + error);

            //    Console.WriteLine(error);

            //}
            //Console.WriteLine(epoch);

            //Console.WriteLine(transLayer.K);

            ////Test the training
            //for (int i = 1; i < 20; i++)
            //{
            //    gann.FeedForward(FuncInterpolation.Mononomial(i));
            //    Console.WriteLine("Input: Mononomial(" + i + ") -> \n" + gann.Output.ToString());
            //    Console.ReadKey();
            //}


           


            #endregion

            #region ANN Comparison

            //Network ann = new Network();
            //var discreteLayer = (new DiscreteLayer(x, y));
            //ann.AddLayer(discreteLayer);
            //error = 1000;

            ////Copy the coefficient matrix as to provide an equal start.
            //K.CopyTo(discreteLayer.K);

            /////ANN comparison
            //for (epoch = 0; error > 0.01; epoch++)
            //{
            //    error =
            //        ann.Train(FuncInterpolation.Mononomial(1).UnitSample(x), Vector<double>.Build.Dense(new double[] { 1, 0 }), lr)
            //        + ann.Train(FuncInterpolation.Mononomial(2).UnitSample(x), Vector<double>.Build.Dense(new double[] { 0, 1 }), lr)
            //        + ann.Train(FuncInterpolation.Mononomial(3).UnitSample(x), Vector<double>.Build.Dense(new double[] { 1, 0 }), lr)
            //        + ann.Train(FuncInterpolation.Mononomial(4).UnitSample(x), Vector<double>.Build.Dense(new double[] { 0, 1 }), lr)

            //        + ann.Train(FuncInterpolation.Mononomial(21).UnitSample(x), Vector<double>.Build.Dense(new double[] { 1, 0 }), lr)

            //        + ann.Train(FuncInterpolation.Mononomial(13).UnitSample(x), Vector<double>.Build.Dense(new double[] { 1, 0 }), lr)
            //        + ann.Train(FuncInterpolation.Mononomial(30).UnitSample(x), Vector<double>.Build.Dense(new double[] { 0, 1 }), lr)

            //        + ann.Train(FuncInterpolation.Mononomial(50).UnitSample(x), Vector<double>.Build.Dense(new double[] { 0, 1 }), lr);
            //    Console.WriteLine(error);
            //}

            //Console.WriteLine(epoch);

            ////Test the training
            //for (int i = 1; i < 20; i++)
            //{
            //    ann.FeedForward(FuncInterpolation.Mononomial(i).UnitSample(x));
            //    Console.WriteLine("Input: Mononomial(" + i + ") -> \n" + ann.Output.ToString());
            //    Console.ReadKey();
            //}
            #endregion

            #region Functional Test
            //gann.AddLayer(new FunctionalLayer(20, 20, Interval.UnitBall));


                //#region Plotting Environment Setup
                //Application.EnableVisualStyles();
                //Application.SetCompatibleTextRenderingDefault(false);

                //ShowPlot fPlot = new ShowPlot(
                //    (FuncInterpolation)fnn.FeedForward(
                //    new FuncInterpolation(x => x)), "f functional test");

                //Thread t = new Thread(
                //    () => Application.Run(fPlot));



                //t.Start();

                //#endregion


                //SquareSet ss = new SquareSet();
                //ss.Load();

                //Trainer trainer = new Trainer(fnn, ss);

                ////trainer.Train(100000, 0.1, 1);

                //Console.WriteLine("Mononomial Test");

                //double lr = 1;
                //while (true)
                //{
                //    //Make 4 test examples.
                //    double error = Enumerable.Range(0, 4).Aggregate(0.0,
                //        (val, i) => 
                //            val + fnn.Train(FuncInterpolation.Mononomial(i), FuncInterpolation.Mononomial(i + 1), lr));


                //    Console.WriteLine(error);
                //    if (Console.ReadKey().Key == ConsoleKey.A)
                //        break;
                //    fPlot.Replot((FuncInterpolation)fnn.Output, "output");
                //}

                //for (int i = 0; i < 10; i++)
                //{
                //    Console.WriteLine("Input x^" + i);

                //    fnn.FeedForward(FuncInterpolation.Mononomial(i));

                //    fPlot.Replot((FuncInterpolation)fnn.Output, "output");
                //    Console.ReadKey();
                //}


                #endregion

            Console.ReadKey();
           
        }
    }
}
