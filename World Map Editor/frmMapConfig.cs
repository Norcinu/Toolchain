using System;
using System.ComponentModel;
using System.Windows.Forms;
using System.Drawing;

namespace World_Map_Editor
{
    public partial class frmMapConfig : Form
    {
        private MapInfo map;
        public MapInfo Map
        {
            get { return map; }
            set { map = value; }
        }

        public frmMapConfig()
        {
            InitializeComponent();
            this.AutoValidate = System.Windows.Forms.AutoValidate.Disable;
            map = new MapInfo();
        }

        private void btnOK_Click(object sender, EventArgs e)
        {
            if (this.ValidateChildren(ValidationConstraints.Enabled))
            {
                map.mapName = txtMapName.Text;
                map.mapDimensions.Width = Convert.ToInt32(txtMapX.Text);
                map.mapDimensions.Height = Convert.ToInt32(txtMapY.Text);
                map.spriteDimensions.Width = Convert.ToInt32(txtSpriteX.Text);
                map.spriteDimensions.Height = Convert.ToInt32(txtSpriteY.Text);
                map.numSpritesHigh = map.mapDimensions.Height / map.spriteDimensions.Height;
                map.numSpritesWide = map.mapDimensions.Width / map.spriteDimensions.Width;

                this.Close();
            }
            else
            {
                MessageBox.Show("Please enter valid inputs.", "Input Error", MessageBoxButtons.OK, 
                    MessageBoxIcon.Error);
            }
        }


        private void textBox2_Validating( object sender, CancelEventArgs e )
        {
            CheckValidNumber(sender, e);
        }

        private void CheckValidNumber(object sender, CancelEventArgs e)
        {
            bool cancel = false;
            int result = -1;
            if (!string.IsNullOrEmpty(this.txtMapX.Text))
            {
                if (!int.TryParse(this.txtMapX.Text, out result))
                {
                    //Console.WriteLine("***result is " + result);
                    cancel = true;
                }
            }
            else
            {
                cancel = true;
                e.Cancel = cancel;
            }

            if (e.Cancel)
                this.errorProvider1.SetError((Control)sender, "Please enter a valid number.");
        }

        private void CheckNumbers(CancelEventArgs e)
        {
            bool cancel = false;
            if (string.IsNullOrEmpty(this.txtMapX.Text))
            {
                string[] words;
                words = this.txtMapX.Text.Split(',');
                foreach (string s in words)
                {
                    int val = 0;

                    if (int.TryParse(s, out val))
                        Console.WriteLine("valid " + val);
                    else
                    {
                        Console.WriteLine("not valid " + val);
                        cancel = true;
                    }
                }
            }
            e.Cancel = cancel;
        }

        private void textBox2_Validated(object sender, EventArgs e)
        {
            this.errorProvider1.SetError(this.txtMapX, string.Empty);
        }

        private void textBox5_Validating(object sender, CancelEventArgs e)
        {
            CheckValidNumber(sender, e);
        }

        private void ResetErrors(object sender)
        {
            this.errorProvider1.SetError((TextBox)sender, string.Empty);
        }

        private void btnClear_Click(object sender, EventArgs e)
        {
            txtMapName.Text = "";
            txtMapX.Text = "";
            txtSpriteX.Text = "";
            txtSpriteY.Text = "";
            txtMapY.Text = "";
            
            map.mapName = "";
            map.mapDimensions = new Size(0, 0);
            map.spriteDimensions = new Size(0, 0);
            map.numSpritesHigh = 0;
            map.numSpritesWide = 0;
            
            this.errorProvider1.Clear();
        }

        private void textBox1_Validating(object sender, CancelEventArgs e)
        {
            if (string.IsNullOrEmpty(txtMapName.Text) || string.IsNullOrWhiteSpace(txtMapName.Text))
            {
                e.Cancel = true;
                errorProvider1.SetError(txtMapName, "Enter a valid string.");
            }
        }

        private void textBox1_Validated(object sender, EventArgs e)
        {
            ResetErrors(sender);
        }

        private void textBox5_Validated(object sender, EventArgs e)
        {
            ResetErrors(sender);
        }

        private void textBox3_Validating(object sender, CancelEventArgs e)
        {
            CheckValidNumber(sender, e);
        }

        private void textBox3_Validated(object sender, EventArgs e)
        {
            ResetErrors(sender);
        }

        private void textBox4_Validating(object sender, CancelEventArgs e)
        {
            CheckValidNumber(sender, e);
        }

        private void textBox4_Validated(object sender, EventArgs e)
        {
            ResetErrors(sender);
        }

        private void frmMapConfig_Load(object sender, EventArgs e)
        {

        }
    }
}
