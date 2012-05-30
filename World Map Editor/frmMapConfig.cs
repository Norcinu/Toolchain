using System;
using System.ComponentModel;
using System.Windows.Forms;

namespace World_Map_Editor
{
    public partial class frmMapConfig : Form
    {
        public frmMapConfig()
        {
            InitializeComponent();
            this.AutoValidate = System.Windows.Forms.AutoValidate.Disable;
        }

        private void btnOK_Click( object sender, EventArgs e )
        {
            if (this.ValidateChildren(ValidationConstraints.Enabled))
            {

            }
            else
            {
                MessageBox.Show("invalid");
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
            if (!string.IsNullOrEmpty(this.textBox2.Text))
            {
                if (int.TryParse(this.textBox2.Text, out result))
                    Console.WriteLine("result is " + result);
                else
                {
                    Console.WriteLine("***result is " + result);
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
            if (string.IsNullOrEmpty(this.textBox2.Text))
            {
                string[] words;
                words = this.textBox2.Text.Split(',');
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
            this.errorProvider1.SetError(this.textBox2, string.Empty);
        }

        private void textBox5_Validating(object sender, CancelEventArgs e)
        {
            ResetErrors(sender);
        }

        private void ResetErrors(object sender)
        {
            this.errorProvider1.SetError((TextBox)sender, string.Empty);
        }

        private void btnClear_Click(object sender, EventArgs e)
        {
            textBox1.Text = "";
            textBox2.Text = "";
            textBox3.Text = "";
            textBox4.Text = "";
            textBox5.Text = "";
        }

        private void textBox1_Validating(object sender, CancelEventArgs e)
        {
            if (string.IsNullOrEmpty(textBox1.Text) || string.IsNullOrWhiteSpace(textBox1.Text))
            {
                e.Cancel = true;
                errorProvider1.SetError(textBox1, "Enter a valid string.");
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
    }
}
