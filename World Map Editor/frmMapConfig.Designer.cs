namespace World_Map_Editor
{
    partial class frmMapConfig
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose( bool disposing )
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.btnOK = new System.Windows.Forms.Button();
            this.btnClear = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.txtMapName = new System.Windows.Forms.TextBox();
            this.txtMapX = new System.Windows.Forms.TextBox();
            this.txtSpriteX = new System.Windows.Forms.TextBox();
            this.button1 = new System.Windows.Forms.Button();
            this.errorProvider1 = new System.Windows.Forms.ErrorProvider(this.components);
            this.txtSpriteY = new System.Windows.Forms.TextBox();
            this.txtMapY = new System.Windows.Forms.TextBox();
            ((System.ComponentModel.ISupportInitialize)(this.errorProvider1)).BeginInit();
            this.SuspendLayout();
            // 
            // btnOK
            // 
            this.btnOK.Font = new System.Drawing.Font("Consolas", 8.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnOK.Location = new System.Drawing.Point(17, 186);
            this.btnOK.Name = "btnOK";
            this.btnOK.Size = new System.Drawing.Size(70, 27);
            this.btnOK.TabIndex = 0;
            this.btnOK.Text = "OK";
            this.btnOK.UseVisualStyleBackColor = true;
            this.btnOK.Click += new System.EventHandler(this.btnOK_Click);
            // 
            // btnClear
            // 
            this.btnClear.Font = new System.Drawing.Font("Consolas", 8.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnClear.Location = new System.Drawing.Point(93, 186);
            this.btnClear.Name = "btnClear";
            this.btnClear.Size = new System.Drawing.Size(64, 27);
            this.btnClear.TabIndex = 1;
            this.btnClear.Text = "Clear";
            this.btnClear.UseVisualStyleBackColor = true;
            this.btnClear.Click += new System.EventHandler(this.btnClear_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(14, 21);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(72, 17);
            this.label1.TabIndex = 2;
            this.label1.Text = "Map Name";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(14, 67);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(152, 17);
            this.label2.TabIndex = 3;
            this.label2.Text = "Map Dimensions x,y";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(14, 122);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(176, 17);
            this.label3.TabIndex = 4;
            this.label3.Text = "Sprite Dimensions x,y";
            // 
            // txtMapName
            // 
            this.txtMapName.Location = new System.Drawing.Point(16, 41);
            this.txtMapName.Name = "txtMapName";
            this.txtMapName.Size = new System.Drawing.Size(104, 23);
            this.txtMapName.TabIndex = 5;
            this.txtMapName.Validating += new System.ComponentModel.CancelEventHandler(this.textBox1_Validating);
            this.txtMapName.Validated += new System.EventHandler(this.textBox1_Validated);
            // 
            // txtMapX
            // 
            this.txtMapX.Location = new System.Drawing.Point(17, 87);
            this.txtMapX.Name = "txtMapX";
            this.txtMapX.Size = new System.Drawing.Size(40, 23);
            this.txtMapX.TabIndex = 6;
            this.txtMapX.Validating += new System.ComponentModel.CancelEventHandler(this.textBox2_Validating);
            this.txtMapX.Validated += new System.EventHandler(this.textBox2_Validated);
            // 
            // txtSpriteX
            // 
            this.txtSpriteX.Location = new System.Drawing.Point(17, 142);
            this.txtSpriteX.Name = "txtSpriteX";
            this.txtSpriteX.Size = new System.Drawing.Size(40, 23);
            this.txtSpriteX.TabIndex = 7;
            this.txtSpriteX.Validating += new System.ComponentModel.CancelEventHandler(this.textBox3_Validating);
            this.txtSpriteX.Validated += new System.EventHandler(this.textBox3_Validated);
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(163, 186);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(64, 27);
            this.button1.TabIndex = 8;
            this.button1.Text = "Close";
            this.button1.UseVisualStyleBackColor = true;
            // 
            // errorProvider1
            // 
            this.errorProvider1.ContainerControl = this;
            // 
            // txtSpriteY
            // 
            this.txtSpriteY.Location = new System.Drawing.Point(80, 142);
            this.txtSpriteY.Name = "txtSpriteY";
            this.txtSpriteY.Size = new System.Drawing.Size(40, 23);
            this.txtSpriteY.TabIndex = 9;
            this.txtSpriteY.Validating += new System.ComponentModel.CancelEventHandler(this.textBox4_Validating);
            this.txtSpriteY.Validated += new System.EventHandler(this.textBox4_Validated);
            // 
            // txtMapY
            // 
            this.txtMapY.Location = new System.Drawing.Point(80, 87);
            this.txtMapY.Name = "txtMapY";
            this.txtMapY.Size = new System.Drawing.Size(40, 23);
            this.txtMapY.TabIndex = 10;
            this.txtMapY.Validating += new System.ComponentModel.CancelEventHandler(this.textBox5_Validating);
            this.txtMapY.Validated += new System.EventHandler(this.textBox5_Validated);
            // 
            // frmMapConfig
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(246, 230);
            this.Controls.Add(this.txtMapY);
            this.Controls.Add(this.txtSpriteY);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.txtSpriteX);
            this.Controls.Add(this.txtMapX);
            this.Controls.Add(this.txtMapName);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.btnClear);
            this.Controls.Add(this.btnOK);
            this.Font = new System.Drawing.Font("Consolas", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Name = "frmMapConfig";
            this.Text = "Map Settings";
            this.Load += new System.EventHandler(this.frmMapConfig_Load);
            ((System.ComponentModel.ISupportInitialize)(this.errorProvider1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btnOK;
        private System.Windows.Forms.Button btnClear;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox txtMapName;
        private System.Windows.Forms.TextBox txtMapX;
        private System.Windows.Forms.TextBox txtSpriteX;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.ErrorProvider errorProvider1;
        private System.Windows.Forms.TextBox txtMapY;
        private System.Windows.Forms.TextBox txtSpriteY;

    }
}