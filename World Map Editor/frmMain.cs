using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
//using SdlDotNet.Windows;
//using SdlDotNet.Graphics;
using System.Threading;
//using SdlDotNet.Core;

namespace World_Map_Editor
{
    public partial class frmMain : Form
    {
        //private SurfaceControl surfaceControl;
        //private Surface surface;

        public frmMain()
        {
            InitializeComponent();
           // SdlDotNet.Core.Events.Tick += new EventHandler<TickEventArgs>( Events_Tick );
          //  surface = new Surface( this.surfaceControl1.Width, this.surfaceControl1.Height );
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            
            //Thread thread = new Thread( new ThreadStart( SdlDotNet.Core.Events.Run ) );
            //thread.IsBackground = true;
            //thread.Name = "SDL.NET";
            //thread.Priority = ThreadPriority.Normal;
            //thread.Start();
        }

        public void UpdateForm()
        {
            //this.surfaceControl1.Blit( surface );
        }

        private void button1_Click(object sender, EventArgs e)
        {
            //SdlDotNet.Graphics.Primitives.Line ln = new SdlDotNet.Graphics.Primitives.Line( 20, 20, 200, 50 );
            //surface.Draw( ln, Color.Wheat );
            this.UpdateForm();
        }
    }
}
