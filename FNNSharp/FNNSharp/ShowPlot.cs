using FNNLib.Util;
using MathNet.Numerics.Interpolation;
using OxyPlot;
using OxyPlot.Series;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace FNNSharp
{
    public partial class ShowPlot : Form
    {

        public ShowPlot(IInterpolation func, string name)
        {
            this.InitializeComponent();
            this.func = func;
            this.funcName = name;
            var myModel = new PlotModel { Title = name };
            myModel.Series.Add(new FunctionSeries(func.Interpolate, -1,1, 0.01, funcName));
            this.plot1.Model = myModel;
            this.Text = "Plot of " + name;
            

        }

        public void Replot(IInterpolation func)
        {
            this.InitializeComponent();
            this.func = func;
            this.funcName = this.funcName;
            var myModel = new PlotModel { Title = funcName };
            myModel.Series.Add(new FunctionSeries(func.Interpolate, -1, 1, 0.01, funcName));
            this.plot1.Model = myModel;
        }


        private void ShowPlot_Load(object sender, EventArgs e)
        {

        }

         IInterpolation func;

         string funcName;
    }
}
