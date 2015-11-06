namespace zedgragh
{
    partial class FormUartConnect
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
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
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.CbStopbits = new System.Windows.Forms.ComboBox();
            this.label5 = new System.Windows.Forms.Label();
            this.ButCancel = new System.Windows.Forms.Button();
            this.ButOk = new System.Windows.Forms.Button();
            this.ButDefault = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.CbParity = new System.Windows.Forms.ComboBox();
            this.label4 = new System.Windows.Forms.Label();
            this.CbDatabits = new System.Windows.Forms.ComboBox();
            this.label3 = new System.Windows.Forms.Label();
            this.CbBaudRate = new System.Windows.Forms.ComboBox();
            this.label2 = new System.Windows.Forms.Label();
            this.Com = new System.IO.Ports.SerialPort(this.components);
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.SuspendLayout();
            // 
            // timer1
            // 
            this.timer1.Enabled = true;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // CbStopbits
            // 
            this.CbStopbits.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.CbStopbits.FormattingEnabled = true;
            this.CbStopbits.Items.AddRange(new object[] {
            "1",
            "1.5",
            "2"});
            this.CbStopbits.Location = new System.Drawing.Point(109, 165);
            this.CbStopbits.Name = "CbStopbits";
            this.CbStopbits.Size = new System.Drawing.Size(99, 21);
            this.CbStopbits.TabIndex = 9;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(40, 168);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(48, 13);
            this.label5.TabIndex = 8;
            this.label5.Text = "Stop bits";
            // 
            // ButCancel
            // 
            this.ButCancel.Location = new System.Drawing.Point(97, 11);
            this.ButCancel.Name = "ButCancel";
            this.ButCancel.Size = new System.Drawing.Size(76, 32);
            this.ButCancel.TabIndex = 11;
            this.ButCancel.Text = "Cancel";
            this.ButCancel.UseVisualStyleBackColor = true;
            this.ButCancel.Click += new System.EventHandler(this.ButCancel_Click);
            // 
            // ButOk
            // 
            this.ButOk.Location = new System.Drawing.Point(6, 11);
            this.ButOk.Name = "ButOk";
            this.ButOk.Size = new System.Drawing.Size(76, 32);
            this.ButOk.TabIndex = 10;
            this.ButOk.Text = "Ok";
            this.ButOk.UseVisualStyleBackColor = true;
            this.ButOk.Click += new System.EventHandler(this.ButOk_Click);
            // 
            // ButDefault
            // 
            this.ButDefault.Location = new System.Drawing.Point(109, 208);
            this.ButDefault.Name = "ButDefault";
            this.ButDefault.Size = new System.Drawing.Size(99, 25);
            this.ButDefault.TabIndex = 12;
            this.ButDefault.Text = "Restore Default";
            this.ButDefault.UseVisualStyleBackColor = true;
            this.ButDefault.Click += new System.EventHandler(this.ButDefault_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.BackColor = System.Drawing.SystemColors.Control;
            this.groupBox1.Controls.Add(this.CbStopbits);
            this.groupBox1.Controls.Add(this.ButDefault);
            this.groupBox1.Controls.Add(this.label5);
            this.groupBox1.Controls.Add(this.CbParity);
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Controls.Add(this.CbDatabits);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.CbBaudRate);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Location = new System.Drawing.Point(21, 12);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(222, 243);
            this.groupBox1.TabIndex = 15;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Uart Configuration";
            // 
            // CbParity
            // 
            this.CbParity.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.CbParity.FormattingEnabled = true;
            this.CbParity.Items.AddRange(new object[] {
            "Even",
            "Odd",
            "None",
            "Mark",
            "Space"});
            this.CbParity.Location = new System.Drawing.Point(109, 118);
            this.CbParity.Name = "CbParity";
            this.CbParity.Size = new System.Drawing.Size(99, 21);
            this.CbParity.TabIndex = 7;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(55, 120);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(33, 13);
            this.label4.TabIndex = 6;
            this.label4.Text = "Parity";
            // 
            // CbDatabits
            // 
            this.CbDatabits.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.CbDatabits.FormattingEnabled = true;
            this.CbDatabits.Items.AddRange(new object[] {
            "6",
            "7",
            "8",
            "9"});
            this.CbDatabits.Location = new System.Drawing.Point(109, 71);
            this.CbDatabits.Name = "CbDatabits";
            this.CbDatabits.Size = new System.Drawing.Size(99, 21);
            this.CbDatabits.TabIndex = 5;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(39, 74);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(50, 13);
            this.label3.TabIndex = 4;
            this.label3.Text = "Data Bits";
            // 
            // CbBaudRate
            // 
            this.CbBaudRate.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.CbBaudRate.FormattingEnabled = true;
            this.CbBaudRate.Items.AddRange(new object[] {
            "2400",
            "4800",
            "9600",
            "14400",
            "19200",
            "38400",
            "56000",
            "57600",
            "115200",
            "128000",
            "256000"});
            this.CbBaudRate.Location = new System.Drawing.Point(109, 26);
            this.CbBaudRate.Name = "CbBaudRate";
            this.CbBaudRate.Size = new System.Drawing.Size(99, 21);
            this.CbBaudRate.TabIndex = 3;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(6, 29);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(81, 13);
            this.label2.TabIndex = 2;
            this.label2.Text = "Baud Rate(bps)";
            // 
            // groupBox2
            // 
            this.groupBox2.BackColor = System.Drawing.SystemColors.ControlLight;
            this.groupBox2.Controls.Add(this.ButCancel);
            this.groupBox2.Controls.Add(this.ButOk);
            this.groupBox2.Location = new System.Drawing.Point(65, 261);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(179, 48);
            this.groupBox2.TabIndex = 16;
            this.groupBox2.TabStop = false;
            // 
            // FormUartConnect
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(256, 317);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.groupBox2);
            this.Name = "FormUartConnect";
            this.Text = "FormUartConnect";
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        public System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.ComboBox CbStopbits;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Button ButCancel;
        private System.Windows.Forms.Button ButOk;
        private System.Windows.Forms.Button ButDefault;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.ComboBox CbParity;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.ComboBox CbDatabits;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.ComboBox CbBaudRate;
        private System.Windows.Forms.Label label2;
        public System.IO.Ports.SerialPort Com;
        private System.Windows.Forms.GroupBox groupBox2;
    }
}