using System;
using System.Drawing;
using System.Windows.Forms;

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

        private void newToolStripMenuItem_Click(object sender, EventArgs e)
        {
            frmMapConfig newMap = new frmMapConfig();
            newMap.ShowDialog(this);
            map = newMap.Map;

            int x = 0;
            int y = 0;
            for (int i = 0; i < map.numSpritesWide; i++)
            {
                for (int j = 0; j < map.numSpritesHigh; j++)
                {
                    PictureBox p = new PictureBox();
                    
                    p.Size = map.spriteDimensions;
                    p.BorderStyle = BorderStyle.Fixed3D;
                    p.Location = new Point(j * map.spriteDimensions.Width, x);
                    p.Click += new EventHandler(picture_addImage);
                    
                    this.panel1.Controls.Add(p);
                }
                x += map.spriteDimensions.Width;
                y += map.spriteDimensions.Height;
            }
        }

        public void  picture_addImage(object sender, EventArgs e)
        {
            Console.WriteLine("clicked image");
            OpenFileDialog ofd = new OpenFileDialog();
            
            ofd.Filter = "Image Files (*.bmp, *.png, *.jpg)|*.bmp;*.png;*.jpg";
            ofd.Title = "Open image file";

            if (ofd.ShowDialog((PictureBox)sender) == DialogResult.OK)
            {
                PictureBox p = (PictureBox)sender;
                p.Image = new Bitmap(ofd.FileName);
            }
        }
    }
}
