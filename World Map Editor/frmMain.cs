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
        private MapInfo map = new MapInfo();
        
        public frmMain()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
           
        }

        private void newToolStripMenuItem_Click( object sender, EventArgs e )
        {
            frmMapConfig newMap = new frmMapConfig();
            newMap.ShowDialog( this );
        }
    }
}
