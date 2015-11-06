namespace zedgragh
{
    partial class FormMain
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
            this.PbMode = new System.Windows.Forms.Button();
            this.PbExit = new System.Windows.Forms.Button();
            this.zed1 = new ZedGraph.ZedGraphControl();
            this.BtConnect = new System.Windows.Forms.Button();
            this.LbConnect = new System.Windows.Forms.Label();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.BtStop = new System.Windows.Forms.Button();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.label1 = new System.Windows.Forms.Label();
            this.CbSecCom = new System.Windows.Forms.ComboBox();
            this.Com = new System.IO.Ports.SerialPort(this.components);
            this.timer1_uart = new System.Windows.Forms.Timer(this.components);
            this.label2 = new System.Windows.Forms.Label();
            this.Send = new System.Windows.Forms.Button();
            this.label3 = new System.Windows.Forms.Label();
            this.lb_Ki = new System.Windows.Forms.Label();
            this.lb_Kd = new System.Windows.Forms.Label();
            this.txtKp = new System.Windows.Forms.TextBox();
            this.txtKi = new System.Windows.Forms.TextBox();
            this.txtKd = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.txtSetspeed = new System.Windows.Forms.TextBox();
            this.zed2 = new ZedGraph.ZedGraphControl();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.menuToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.newConnectionToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.btMinusKd = new System.Windows.Forms.Button();
            this.btMinusKi = new System.Windows.Forms.Button();
            this.btMinusKp = new System.Windows.Forms.Button();
            this.btPlusKd = new System.Windows.Forms.Button();
            this.btPlusKi = new System.Windows.Forms.Button();
            this.UpdownKd = new System.Windows.Forms.NumericUpDown();
            this.UpdownKi = new System.Windows.Forms.NumericUpDown();
            this.btPlusKp = new System.Windows.Forms.Button();
            this.UpdownKp = new System.Windows.Forms.NumericUpDown();
            this.btSendSpeed = new System.Windows.Forms.Button();
            this.timer2 = new System.Windows.Forms.Timer(this.components);
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.btAddSave = new System.Windows.Forms.Button();
            this.UpDownLoadPID = new System.Windows.Forms.NumericUpDown();
            this.UpDownSavePID = new System.Windows.Forms.NumericUpDown();
            this.btClear = new System.Windows.Forms.Button();
            this.richTextBox1 = new System.Windows.Forms.RichTextBox();
            this.btLoadPID = new System.Windows.Forms.Button();
            this.btSavePID = new System.Windows.Forms.Button();
            this.txtSaveFileLocation = new System.Windows.Forms.TextBox();
            this.btLocation = new System.Windows.Forms.Button();
            this.label4 = new System.Windows.Forms.Label();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.menuStrip1.SuspendLayout();
            this.groupBox3.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.UpdownKd)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.UpdownKi)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.UpdownKp)).BeginInit();
            this.groupBox4.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.UpDownLoadPID)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.UpDownSavePID)).BeginInit();
            this.SuspendLayout();
            // 
            // PbMode
            // 
            this.PbMode.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.PbMode.Location = new System.Drawing.Point(28, 23);
            this.PbMode.Name = "PbMode";
            this.PbMode.Size = new System.Drawing.Size(116, 33);
            this.PbMode.TabIndex = 0;
            this.PbMode.Text = "Compact";
            this.PbMode.UseVisualStyleBackColor = true;
            this.PbMode.Click += new System.EventHandler(this.PbMode_Click_1);
            // 
            // PbExit
            // 
            this.PbExit.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.PbExit.Location = new System.Drawing.Point(180, 23);
            this.PbExit.Name = "PbExit";
            this.PbExit.Size = new System.Drawing.Size(116, 33);
            this.PbExit.TabIndex = 1;
            this.PbExit.Text = "Exit";
            this.PbExit.UseVisualStyleBackColor = true;
            this.PbExit.Click += new System.EventHandler(this.PbExit_Click);
            // 
            // zed1
            // 
            this.zed1.Location = new System.Drawing.Point(330, 27);
            this.zed1.Name = "zed1";
            this.zed1.ScrollGrace = 0D;
            this.zed1.ScrollMaxX = 0D;
            this.zed1.ScrollMaxY = 0D;
            this.zed1.ScrollMaxY2 = 0D;
            this.zed1.ScrollMinX = 0D;
            this.zed1.ScrollMinY = 0D;
            this.zed1.ScrollMinY2 = 0D;
            this.zed1.Size = new System.Drawing.Size(542, 325);
            this.zed1.TabIndex = 2;
            // 
            // BtConnect
            // 
            this.BtConnect.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.BtConnect.Location = new System.Drawing.Point(134, 66);
            this.BtConnect.Name = "BtConnect";
            this.BtConnect.Size = new System.Drawing.Size(109, 33);
            this.BtConnect.TabIndex = 3;
            this.BtConnect.Text = "Connect";
            this.BtConnect.UseVisualStyleBackColor = true;
            this.BtConnect.Click += new System.EventHandler(this.BtConnect_Click);
            // 
            // LbConnect
            // 
            this.LbConnect.AutoSize = true;
            this.LbConnect.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Italic))), System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.LbConnect.Location = new System.Drawing.Point(6, 72);
            this.LbConnect.Name = "LbConnect";
            this.LbConnect.Size = new System.Drawing.Size(119, 20);
            this.LbConnect.TabIndex = 4;
            this.LbConnect.Text = "Disconnected";
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.PbExit);
            this.groupBox1.Controls.Add(this.PbMode);
            this.groupBox1.Location = new System.Drawing.Point(12, 620);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(312, 63);
            this.groupBox1.TabIndex = 6;
            this.groupBox1.TabStop = false;
            // 
            // BtStop
            // 
            this.BtStop.Font = new System.Drawing.Font("Arial", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.BtStop.ForeColor = System.Drawing.Color.Red;
            this.BtStop.Location = new System.Drawing.Point(193, 192);
            this.BtStop.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.BtStop.Name = "BtStop";
            this.BtStop.Size = new System.Drawing.Size(106, 34);
            this.BtStop.TabIndex = 19;
            this.BtStop.Text = "STOP";
            this.BtStop.UseVisualStyleBackColor = true;
            this.BtStop.Click += new System.EventHandler(this.BtStop_Click);
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.label1);
            this.groupBox2.Controls.Add(this.LbConnect);
            this.groupBox2.Controls.Add(this.CbSecCom);
            this.groupBox2.Controls.Add(this.BtConnect);
            this.groupBox2.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.groupBox2.Location = new System.Drawing.Point(12, 27);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(312, 112);
            this.groupBox2.TabIndex = 7;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "UART";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(24, 32);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(107, 24);
            this.label1.TabIndex = 31;
            this.label1.Text = "Select Com";
            // 
            // CbSecCom
            // 
            this.CbSecCom.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.CbSecCom.FormattingEnabled = true;
            this.CbSecCom.Location = new System.Drawing.Point(134, 29);
            this.CbSecCom.Name = "CbSecCom";
            this.CbSecCom.Size = new System.Drawing.Size(109, 32);
            this.CbSecCom.TabIndex = 32;
            this.CbSecCom.SelectedIndexChanged += new System.EventHandler(this.CbSecCom_SelectedIndexChanged);
            // 
            // Com
            // 
            this.Com.BaudRate = 115200;
            this.Com.DtrEnable = true;
            this.Com.RtsEnable = true;
            this.Com.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.OnCom);
            // 
            // timer1_uart
            // 
            this.timer1_uart.Enabled = true;
            this.timer1_uart.Interval = 10;
            this.timer1_uart.Tick += new System.EventHandler(this.timer1_uart_Tick);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Italic))), System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(8, 44);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(61, 20);
            this.label2.TabIndex = 9;
            this.label2.Text = "Speed";
            // 
            // Send
            // 
            this.Send.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Send.Location = new System.Drawing.Point(55, 191);
            this.Send.Name = "Send";
            this.Send.Size = new System.Drawing.Size(116, 34);
            this.Send.TabIndex = 10;
            this.Send.Text = "SEND PID";
            this.Send.UseVisualStyleBackColor = true;
            this.Send.Click += new System.EventHandler(this.Start_Click);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(20, 198);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(0, 13);
            this.label3.TabIndex = 11;
            // 
            // lb_Ki
            // 
            this.lb_Ki.AutoSize = true;
            this.lb_Ki.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lb_Ki.Location = new System.Drawing.Point(11, 117);
            this.lb_Ki.Name = "lb_Ki";
            this.lb_Ki.Size = new System.Drawing.Size(31, 25);
            this.lb_Ki.TabIndex = 12;
            this.lb_Ki.Text = "Ki";
            // 
            // lb_Kd
            // 
            this.lb_Kd.AutoSize = true;
            this.lb_Kd.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lb_Kd.Location = new System.Drawing.Point(11, 77);
            this.lb_Kd.Name = "lb_Kd";
            this.lb_Kd.Size = new System.Drawing.Size(38, 25);
            this.lb_Kd.TabIndex = 13;
            this.lb_Kd.Text = "Kp";
            // 
            // txtKp
            // 
            this.txtKp.Location = new System.Drawing.Point(55, 77);
            this.txtKp.Name = "txtKp";
            this.txtKp.Size = new System.Drawing.Size(116, 29);
            this.txtKp.TabIndex = 14;
            // 
            // txtKi
            // 
            this.txtKi.Location = new System.Drawing.Point(55, 116);
            this.txtKi.Name = "txtKi";
            this.txtKi.Size = new System.Drawing.Size(116, 29);
            this.txtKi.TabIndex = 15;
            // 
            // txtKd
            // 
            this.txtKd.Location = new System.Drawing.Point(55, 157);
            this.txtKd.Name = "txtKd";
            this.txtKd.Size = new System.Drawing.Size(116, 29);
            this.txtKd.TabIndex = 16;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label6.Location = new System.Drawing.Point(11, 157);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(38, 25);
            this.label6.TabIndex = 17;
            this.label6.Text = "Kd";
            // 
            // txtSetspeed
            // 
            this.txtSetspeed.Location = new System.Drawing.Point(75, 42);
            this.txtSetspeed.Name = "txtSetspeed";
            this.txtSetspeed.Size = new System.Drawing.Size(116, 29);
            this.txtSetspeed.TabIndex = 18;
            // 
            // zed2
            // 
            this.zed2.Location = new System.Drawing.Point(330, 358);
            this.zed2.Name = "zed2";
            this.zed2.ScrollGrace = 0D;
            this.zed2.ScrollMaxX = 0D;
            this.zed2.ScrollMaxY = 0D;
            this.zed2.ScrollMaxY2 = 0D;
            this.zed2.ScrollMinX = 0D;
            this.zed2.ScrollMinY = 0D;
            this.zed2.ScrollMinY2 = 0D;
            this.zed2.Size = new System.Drawing.Size(542, 325);
            this.zed2.TabIndex = 29;
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.menuToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(878, 24);
            this.menuStrip1.TabIndex = 30;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // menuToolStripMenuItem
            // 
            this.menuToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.newConnectionToolStripMenuItem,
            this.exitToolStripMenuItem});
            this.menuToolStripMenuItem.Name = "menuToolStripMenuItem";
            this.menuToolStripMenuItem.Size = new System.Drawing.Size(50, 20);
            this.menuToolStripMenuItem.Text = "Menu";
            // 
            // newConnectionToolStripMenuItem
            // 
            this.newConnectionToolStripMenuItem.Name = "newConnectionToolStripMenuItem";
            this.newConnectionToolStripMenuItem.Size = new System.Drawing.Size(175, 22);
            this.newConnectionToolStripMenuItem.Text = "Config Connection";
            this.newConnectionToolStripMenuItem.Click += new System.EventHandler(this.newConnectionToolStripMenuItem_Click);
            // 
            // exitToolStripMenuItem
            // 
            this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
            this.exitToolStripMenuItem.Size = new System.Drawing.Size(175, 22);
            this.exitToolStripMenuItem.Text = "Exit";
            this.exitToolStripMenuItem.Click += new System.EventHandler(this.exitToolStripMenuItem_Click_1);
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.btMinusKd);
            this.groupBox3.Controls.Add(this.btMinusKi);
            this.groupBox3.Controls.Add(this.btMinusKp);
            this.groupBox3.Controls.Add(this.btPlusKd);
            this.groupBox3.Controls.Add(this.btPlusKi);
            this.groupBox3.Controls.Add(this.UpdownKd);
            this.groupBox3.Controls.Add(this.UpdownKi);
            this.groupBox3.Controls.Add(this.btPlusKp);
            this.groupBox3.Controls.Add(this.UpdownKp);
            this.groupBox3.Controls.Add(this.btSendSpeed);
            this.groupBox3.Controls.Add(this.BtStop);
            this.groupBox3.Controls.Add(this.label2);
            this.groupBox3.Controls.Add(this.Send);
            this.groupBox3.Controls.Add(this.txtSetspeed);
            this.groupBox3.Controls.Add(this.lb_Ki);
            this.groupBox3.Controls.Add(this.label6);
            this.groupBox3.Controls.Add(this.lb_Kd);
            this.groupBox3.Controls.Add(this.txtKd);
            this.groupBox3.Controls.Add(this.txtKp);
            this.groupBox3.Controls.Add(this.txtKi);
            this.groupBox3.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.groupBox3.Location = new System.Drawing.Point(12, 145);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(312, 231);
            this.groupBox3.TabIndex = 8;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Set parameters";
            // 
            // btMinusKd
            // 
            this.btMinusKd.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btMinusKd.Location = new System.Drawing.Point(202, 157);
            this.btMinusKd.Name = "btMinusKd";
            this.btMinusKd.Size = new System.Drawing.Size(19, 27);
            this.btMinusKd.TabIndex = 32;
            this.btMinusKd.Text = "-";
            this.btMinusKd.UseVisualStyleBackColor = true;
            this.btMinusKd.Click += new System.EventHandler(this.btMinusKd_Click);
            // 
            // btMinusKi
            // 
            this.btMinusKi.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btMinusKi.Location = new System.Drawing.Point(202, 117);
            this.btMinusKi.Name = "btMinusKi";
            this.btMinusKi.Size = new System.Drawing.Size(19, 27);
            this.btMinusKi.TabIndex = 31;
            this.btMinusKi.Text = "-";
            this.btMinusKi.UseVisualStyleBackColor = true;
            this.btMinusKi.Click += new System.EventHandler(this.btMinusKi_Click);
            // 
            // btMinusKp
            // 
            this.btMinusKp.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btMinusKp.Location = new System.Drawing.Point(202, 76);
            this.btMinusKp.Name = "btMinusKp";
            this.btMinusKp.Size = new System.Drawing.Size(19, 27);
            this.btMinusKp.TabIndex = 30;
            this.btMinusKp.Text = "-";
            this.btMinusKp.UseVisualStyleBackColor = true;
            this.btMinusKp.Click += new System.EventHandler(this.btMinusKp_Click);
            // 
            // btPlusKd
            // 
            this.btPlusKd.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btPlusKd.Location = new System.Drawing.Point(177, 157);
            this.btPlusKd.Name = "btPlusKd";
            this.btPlusKd.Size = new System.Drawing.Size(19, 26);
            this.btPlusKd.TabIndex = 29;
            this.btPlusKd.Text = "+";
            this.btPlusKd.UseVisualStyleBackColor = true;
            this.btPlusKd.Click += new System.EventHandler(this.btPlusKd_Click);
            // 
            // btPlusKi
            // 
            this.btPlusKi.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btPlusKi.Location = new System.Drawing.Point(177, 117);
            this.btPlusKi.Name = "btPlusKi";
            this.btPlusKi.Size = new System.Drawing.Size(19, 27);
            this.btPlusKi.TabIndex = 28;
            this.btPlusKi.Text = "+";
            this.btPlusKi.UseVisualStyleBackColor = true;
            this.btPlusKi.Click += new System.EventHandler(this.btPlusKi_Click);
            // 
            // UpdownKd
            // 
            this.UpdownKd.ImeMode = System.Windows.Forms.ImeMode.On;
            this.UpdownKd.Location = new System.Drawing.Point(227, 158);
            this.UpdownKd.Maximum = new decimal(new int[] {
            9999999,
            0,
            0,
            0});
            this.UpdownKd.Name = "UpdownKd";
            this.UpdownKd.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.UpdownKd.Size = new System.Drawing.Size(69, 29);
            this.UpdownKd.TabIndex = 27;
            this.UpdownKd.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // UpdownKi
            // 
            this.UpdownKi.ImeMode = System.Windows.Forms.ImeMode.On;
            this.UpdownKi.Location = new System.Drawing.Point(227, 118);
            this.UpdownKi.Maximum = new decimal(new int[] {
            9999999,
            0,
            0,
            0});
            this.UpdownKi.Name = "UpdownKi";
            this.UpdownKi.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.UpdownKi.Size = new System.Drawing.Size(69, 29);
            this.UpdownKi.TabIndex = 25;
            this.UpdownKi.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // btPlusKp
            // 
            this.btPlusKp.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btPlusKp.Location = new System.Drawing.Point(177, 76);
            this.btPlusKp.Name = "btPlusKp";
            this.btPlusKp.Size = new System.Drawing.Size(19, 27);
            this.btPlusKp.TabIndex = 24;
            this.btPlusKp.Text = "+";
            this.btPlusKp.UseVisualStyleBackColor = true;
            this.btPlusKp.Click += new System.EventHandler(this.btPlusKp_Click);
            // 
            // UpdownKp
            // 
            this.UpdownKp.ImeMode = System.Windows.Forms.ImeMode.On;
            this.UpdownKp.Location = new System.Drawing.Point(227, 76);
            this.UpdownKp.Maximum = new decimal(new int[] {
            9999999,
            0,
            0,
            0});
            this.UpdownKp.Name = "UpdownKp";
            this.UpdownKp.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.UpdownKp.Size = new System.Drawing.Size(69, 29);
            this.UpdownKp.TabIndex = 21;
            this.UpdownKp.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // btSendSpeed
            // 
            this.btSendSpeed.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btSendSpeed.Location = new System.Drawing.Point(193, 42);
            this.btSendSpeed.Name = "btSendSpeed";
            this.btSendSpeed.Size = new System.Drawing.Size(56, 30);
            this.btSendSpeed.TabIndex = 20;
            this.btSendSpeed.Text = "SEND";
            this.btSendSpeed.UseVisualStyleBackColor = true;
            this.btSendSpeed.Click += new System.EventHandler(this.btSendSpeed_Click);
            // 
            // timer2
            // 
            this.timer2.Enabled = true;
            this.timer2.Interval = 1000;
            this.timer2.Tick += new System.EventHandler(this.timer2_Tick);
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.btAddSave);
            this.groupBox4.Controls.Add(this.UpDownLoadPID);
            this.groupBox4.Controls.Add(this.UpDownSavePID);
            this.groupBox4.Controls.Add(this.btClear);
            this.groupBox4.Controls.Add(this.richTextBox1);
            this.groupBox4.Controls.Add(this.btLoadPID);
            this.groupBox4.Controls.Add(this.btSavePID);
            this.groupBox4.Controls.Add(this.txtSaveFileLocation);
            this.groupBox4.Controls.Add(this.btLocation);
            this.groupBox4.Controls.Add(this.label4);
            this.groupBox4.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.groupBox4.Location = new System.Drawing.Point(12, 376);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(312, 238);
            this.groupBox4.TabIndex = 31;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "Save/Load";
            // 
            // btAddSave
            // 
            this.btAddSave.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btAddSave.Location = new System.Drawing.Point(12, 33);
            this.btAddSave.Name = "btAddSave";
            this.btAddSave.Size = new System.Drawing.Size(55, 21);
            this.btAddSave.TabIndex = 34;
            this.btAddSave.Text = "ADD";
            this.btAddSave.UseVisualStyleBackColor = true;
            this.btAddSave.Click += new System.EventHandler(this.btCleanSave_Click);
            // 
            // UpDownLoadPID
            // 
            this.UpDownLoadPID.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.UpDownLoadPID.ImeMode = System.Windows.Forms.ImeMode.On;
            this.UpDownLoadPID.Location = new System.Drawing.Point(73, 87);
            this.UpDownLoadPID.Name = "UpDownLoadPID";
            this.UpDownLoadPID.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.UpDownLoadPID.Size = new System.Drawing.Size(35, 20);
            this.UpDownLoadPID.TabIndex = 33;
            // 
            // UpDownSavePID
            // 
            this.UpDownSavePID.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.UpDownSavePID.ImeMode = System.Windows.Forms.ImeMode.On;
            this.UpDownSavePID.Location = new System.Drawing.Point(73, 60);
            this.UpDownSavePID.Name = "UpDownSavePID";
            this.UpDownSavePID.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.UpDownSavePID.Size = new System.Drawing.Size(35, 20);
            this.UpDownSavePID.TabIndex = 32;
            // 
            // btClear
            // 
            this.btClear.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btClear.Location = new System.Drawing.Point(12, 114);
            this.btClear.Name = "btClear";
            this.btClear.Size = new System.Drawing.Size(68, 22);
            this.btClear.TabIndex = 13;
            this.btClear.Text = "CLEAR";
            this.btClear.UseVisualStyleBackColor = true;
            this.btClear.Click += new System.EventHandler(this.btClear_Click);
            // 
            // richTextBox1
            // 
            this.richTextBox1.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.richTextBox1.Location = new System.Drawing.Point(114, 28);
            this.richTextBox1.Name = "richTextBox1";
            this.richTextBox1.Size = new System.Drawing.Size(192, 172);
            this.richTextBox1.TabIndex = 12;
            this.richTextBox1.Text = "";
            // 
            // btLoadPID
            // 
            this.btLoadPID.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btLoadPID.Location = new System.Drawing.Point(12, 87);
            this.btLoadPID.Name = "btLoadPID";
            this.btLoadPID.Size = new System.Drawing.Size(55, 21);
            this.btLoadPID.TabIndex = 11;
            this.btLoadPID.Text = "LOAD";
            this.btLoadPID.UseVisualStyleBackColor = true;
            this.btLoadPID.Click += new System.EventHandler(this.btLoadPID_Click);
            // 
            // btSavePID
            // 
            this.btSavePID.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btSavePID.Location = new System.Drawing.Point(11, 60);
            this.btSavePID.Name = "btSavePID";
            this.btSavePID.Size = new System.Drawing.Size(56, 21);
            this.btSavePID.TabIndex = 9;
            this.btSavePID.Text = "SAVE";
            this.btSavePID.UseVisualStyleBackColor = true;
            this.btSavePID.Click += new System.EventHandler(this.btSavePID_Click);
            // 
            // txtSaveFileLocation
            // 
            this.txtSaveFileLocation.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.txtSaveFileLocation.Location = new System.Drawing.Point(64, 206);
            this.txtSaveFileLocation.Name = "txtSaveFileLocation";
            this.txtSaveFileLocation.Size = new System.Drawing.Size(204, 22);
            this.txtSaveFileLocation.TabIndex = 8;
            // 
            // btLocation
            // 
            this.btLocation.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btLocation.Location = new System.Drawing.Point(274, 206);
            this.btLocation.Name = "btLocation";
            this.btLocation.Size = new System.Drawing.Size(30, 22);
            this.btLocation.TabIndex = 7;
            this.btLocation.Text = "...";
            this.btLocation.UseVisualStyleBackColor = true;
            this.btLocation.Click += new System.EventHandler(this.btLocation_Click);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label4.Location = new System.Drawing.Point(6, 209);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(62, 16);
            this.label4.TabIndex = 6;
            this.label4.Text = "From file:";
            // 
            // FormMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(878, 688);
            this.Controls.Add(this.groupBox4);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.zed2);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.zed1);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "FormMain";
            this.Text = "FormMain";
            this.Load += new System.EventHandler(this.FormMain_Load);
            this.groupBox1.ResumeLayout(false);
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.UpdownKd)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.UpdownKi)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.UpdownKp)).EndInit();
            this.groupBox4.ResumeLayout(false);
            this.groupBox4.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.UpDownLoadPID)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.UpDownSavePID)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button PbMode;
        private System.Windows.Forms.Button PbExit;
        private ZedGraph.ZedGraphControl zed1;
        private System.Windows.Forms.Button BtConnect;
        private System.Windows.Forms.Label LbConnect;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.IO.Ports.SerialPort Com;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button Send;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label lb_Ki;
        private System.Windows.Forms.Label lb_Kd;
        private System.Windows.Forms.TextBox txtKp;
        private System.Windows.Forms.TextBox txtKi;
        private System.Windows.Forms.TextBox txtKd;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.TextBox txtSetspeed;
        private ZedGraph.ZedGraphControl zed2;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.Button BtStop;
        private System.Windows.Forms.ToolStripMenuItem menuToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem newConnectionToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
        public System.Windows.Forms.Timer timer2;
        public System.Windows.Forms.ComboBox CbSecCom;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button btSendSpeed;
        private System.Windows.Forms.NumericUpDown UpdownKp;
        private System.Windows.Forms.Button btPlusKp;
        private System.Windows.Forms.NumericUpDown UpdownKd;
        private System.Windows.Forms.NumericUpDown UpdownKi;
        public System.Windows.Forms.Timer timer1_uart;
        private System.Windows.Forms.Button btPlusKd;
        private System.Windows.Forms.Button btPlusKi;
        private System.Windows.Forms.Button btMinusKd;
        private System.Windows.Forms.Button btMinusKi;
        private System.Windows.Forms.Button btMinusKp;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.Button btLoadPID;
        private System.Windows.Forms.Button btSavePID;
        private System.Windows.Forms.TextBox txtSaveFileLocation;
        private System.Windows.Forms.Button btLocation;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.RichTextBox richTextBox1;
        private System.Windows.Forms.Button btClear;
        private System.Windows.Forms.NumericUpDown UpDownLoadPID;
        private System.Windows.Forms.NumericUpDown UpDownSavePID;
        private System.Windows.Forms.Button btAddSave;
    }
}

