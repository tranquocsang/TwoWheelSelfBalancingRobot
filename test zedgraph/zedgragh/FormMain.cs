using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO.Ports;
using System.IO;
using ZedGraph;
using System.Drawing.Drawing2D;
using System.Threading;

namespace zedgragh
{ 
    public partial class FormMain : Form
    {

        /*******************************************************************************
         * Set up Uart params
         * using SelCom is a variable that check conditions to open port
         * it only receives a valid value from NewConnection form 
        *******************************************************************************/
        public static string SelCom = "";
        public static int baudrate;
        public static int databits;
        public static Parity parity;
        public static StopBits stopbits;

        static class Constants
        {
            public const string CHAR_CHECK = "a";
            public const string CHAR_STOP = "S";
        }

        /*******************************************************************************
         * Variables for ZedGraph 
         *******************************************************************************/
        int intTickStart, intMode = 1;  // length;
        string strRoll, strPitch, strYaw;

        /*******************************************************************************
         * Init the form 
         *******************************************************************************/
        public FormMain()
        {
            InitializeComponent();
        }

        /*******************************************************************************
         * Init Zed graph : title, legend, axis ...
         *******************************************************************************/
        public void ZedGraph1Init()
        {
            GraphPane my_pane = zed1.GraphPane;

            // Change the title
            my_pane.Title.Text = " ROLL ANGLE";
            my_pane.XAxis.Title.Text = " Time, Seconds ";
            my_pane.YAxis.Title.Text = " Roll value ";

            //chua tat ca cac diem ve do thi
            RollingPointPairList list = new RollingPointPairList(60000);

            // định nghĩa 2 đường vẽ
            LineItem curve = my_pane.AddCurve("Roll", list, Color.Blue, SymbolType.None);

            // khởi tạo các trục tọa độ
            my_pane.XAxis.Scale.Min = 0;
            my_pane.XAxis.Scale.Max = 10;
            my_pane.XAxis.Scale.MinorStep = 0;
            my_pane.XAxis.Scale.MajorStep = 1;//khong cach truoc thoi diem ve
            zed1.AxisChange();

            // save first time for reference
            intTickStart = Environment.TickCount;
        }

        public void ZedGraph2Init()
        {
            GraphPane my_pane2 = zed2.GraphPane;
            // Change the title
            my_pane2.Title.Text = " PITCH ANGLE";
            my_pane2.XAxis.Title.Text = " Time, Seconds ";
            my_pane2.YAxis.Title.Text = " Pitch value";

            //chua tat ca cac diem ve do thi
            RollingPointPairList list = new RollingPointPairList(60000);

            // định nghĩa 2 đường vẽ
            LineItem curve = my_pane2.AddCurve("Pitch", list, Color.Blue, SymbolType.None);

            // khởi tạo các trục tọa độ
            my_pane2.XAxis.Scale.Min = 0;
            my_pane2.XAxis.Scale.Max = 10;
            my_pane2.XAxis.Scale.MinorStep = 0;
            my_pane2.XAxis.Scale.MajorStep = 1;//khong cach truoc thoi diem ve
            zed2.AxisChange();

            // save first time for reference
            intTickStart = Environment.TickCount;
        }

        /*******************************************************************************
        * Load the login form or first setups in here
        *******************************************************************************/
        private void FormMain_Load(object sender, EventArgs e)
        {
            ZedGraph1Init();
            ZedGraph2Init();
   //         timer1_uart.Enabled = false;
            timer2.Interval = 1000;
            timer2.Stop();
            Load_File();
        }

        /*******************************************************************************
         * Exit program
        *******************************************************************************/
        private void PbExit_Click(object sender, EventArgs e)
        {
            Com.Close();
            Close();
        }

        /*******************************************************************************
         * Draw roll and pitch
         *******************************************************************************/
        private void Draw(string strRoll, string strPitch)
        {
            double dRoll, dPitch;
            double.TryParse(strRoll, out dRoll);
            double.TryParse(strPitch, out dPitch);
            dRoll /= 10.0; 
            dPitch /= 10.0;

            /*
             * Draw Roll
             * */
            if (zed1.GraphPane.CurveList.Count <= 0)
                return;

            //Get Curve Item 
            LineItem curve = zed1.GraphPane.CurveList[0] as LineItem;

            if (curve == null)
                return;

            //Get the PointPair List
            IPointListEdit list = curve.Points as IPointListEdit;

            if (list == null)
                return;

            //Time in seconds
            double time = (Environment.TickCount - intTickStart) / 1000.0;

            //3seconds per cycle ????
            list.Add(time, dRoll);

            //keep Xaxis in 30s

            Scale xscale = zed1.GraphPane.XAxis.Scale;
            if (time > xscale.Max - xscale.MajorStep)
            {
                if (intMode == 1)
                {
                    xscale.Max = time + xscale.MajorStep;
                    xscale.Min = xscale.Max - 30.0;
                }
                else
                {
                    xscale.Max = time + xscale.MajorStep;
                    xscale.Min = 0;
                }
            }
            //Y rescale
            zed1.AxisChange();
            //Force a redraw;
            zed1.Invalidate();

            // finish drawing roll

            /*
             * Draw Pitch
             * */
            if (zed2.GraphPane.CurveList.Count <= 0)
                return;

            //Get Curve Item 
            LineItem curve1 = zed2.GraphPane.CurveList[0] as LineItem;

            if (curve1 == null)
                return;

            //Get the PointPair List
            IPointListEdit list1 = curve1.Points as IPointListEdit;

            if (list1 == null)
                return;

            //3seconds per cycle ????
            list1.Add(time, dPitch);

            //keep Xaxis in 30s

            Scale xscale1 = zed2.GraphPane.XAxis.Scale;
            if (time > xscale1.Max - xscale1.MajorStep)
            {
                if (intMode == 1)
                {
                    xscale1.Max = time + xscale1.MajorStep;
                    xscale1.Min = xscale1.Max - 30.0;
                }
                else
                {
                    xscale1.Max = time + xscale1.MajorStep;
                    xscale1.Min = 0;
                }
            }
            //Y rescale
            zed2.AxisChange();
            //Force a redraw;
            zed2.Invalidate();

            // finish drawing pitch
        }

        /*******************************************************************************
         * When click Connect:
         *  warning if there is no connection avalable
         *  Switch between connect/disconnect if connection is avalable
         *******************************************************************************/
        private void BtConnect_Click(object sender, EventArgs e)
        {
            if (SelCom == "")               //initially, SelCom IS NOT set 
            {
                MessageBox.Show("Select COM/Config Connection and connect to MCU");
            }
            else
            {
                if (LbConnect.Text == "Connected")
                {
                    if (Com.IsOpen)
                    {
                        Com.Close();
                        LbConnect.Text = "Disconnected";
                        BtConnect.Text = "Connect";
                        timer2.Stop();
                    }
                }
                else
                {
                    Com.PortName = SelCom;
                    Com.Open(); 
                    LbConnect.Text = "Connected";
                    BtConnect.Text = "Disconnect";
                    timer2.Start();           
                }
            }
        }

        /*******************************************************************************
         * Load FormUartConnect to set the Uart parameters : Com,baudrate,parity,stop...
         * after finishing these parameters will be transfer to FormMain
         *******************************************************************************/
        private void newConnectionToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Com.Close();
            SelCom = "";
            FormUartConnect frmUart = new FormUartConnect();
            frmUart.ShowDialog();

            if (SelCom != "")
            {
                //ok let's active com port
                Com.PortName = SelCom;
                Com.Open();
                Com.BaudRate = baudrate;
                Com.DataBits = databits;
                Com.StopBits = stopbits;
                Com.Parity = parity;
                LbConnect.Text = "Connected";
                BtConnect.Text = "Disconnect";
            }
            else
            {
                LbConnect.Text = "Disconnected";
                BtConnect.Text = "Connect";
            }
        }

        private void exitToolStripMenuItem_Click_1(object sender, EventArgs e)
        {
            Com.Close();
            Close();
        }

        /*******************************************************************************
         *                 Read Values from MCU and Draw on zedgraph
         *******************************************************************************/
        // display the data received on textbox
        // unused for now
        private delegate void dlDisplay(string s);
        private void display(string s)
        {
            ;
        }

        int signRoll, signPitch, signYaw, end;
        private void OnCom(object sender, SerialDataReceivedEventArgs e)
        {
            if (LbConnect.Text == "Connected")
            {
                try
                {
                    // read the frame as follow: " sxxxx sxxxx sxxxx\n\r" 
                    // where s: sign of xxxx: number with 4 digits 
                    //      string s1, s2, s3, s4, s5;
                    signRoll = Com.ReadChar();
//                    while ((end != 10) && (end != 13))  // char received != '\r' (ASCII 13) and '\n' (ASCII 10)
//                    {
                        // read first number (roll)
                        strRoll = Com.ReadTo(" ");
                        // read sign of next number (pitch)
                        signPitch = Com.ReadChar();
                        // read next number (pitch)
                        strPitch = Com.ReadTo(" ");                   
                        signYaw = Com.ReadChar();
                        strYaw = Com.ReadTo("\n");
                        end = Com.ReadChar();   // should read '\r' here
//                    }
       
                    Com.DiscardInBuffer();
                }
                catch (TimeoutException)
                {
                    return;
                }
                catch (IOException)
                {
                    return;
                }
                catch (InvalidOperationException)
                {
                    return;
                }
                //change sign of roll if negative ('-')
                if (signRoll == 45)
                    strRoll = '-' + strRoll;
                //change sign of  pitch if negative ('-')
                if (signPitch == 45)
                    strPitch = '-' + strPitch;
                if (signYaw == 45)
                    strYaw = '-' + strYaw;
                Draw(strRoll, strPitch);
            }
        }
      

        /*******************************************************************************
         * Display COM port(s)
         *******************************************************************************/
        int intlen = 0; //luu gia tri so cong Com trong may tinhh
        private void CbSecCom_SelectedIndexChanged(object sender, EventArgs e)
        {
            SelCom = CbSecCom.Text;
        }

        private void timer1_uart_Tick(object sender, EventArgs e)
        {
            //SerialPort.
            string[] ports = SerialPort.GetPortNames(); //lay tat ca cong COM trong PC.
            //if ((intlen > ports.Length) && (SelCom != ""))
            //{
            //    SelCom = "";
            //    MessageBox.Show("DISCONNECTED FROM GUI !!!");
            //    Com.Close();
            //    LbConnect.Text = "Disconnected";
            //    BtConnect.Text = "Connect";
            //    timer2.Stop();
            //}
            if (intlen != ports.Length)
            {
                intlen = ports.Length;
                CbSecCom.Items.Clear();
                for (int j = 0; j < intlen; j++)
                {
                    CbSecCom.Items.Add(ports[j]);
                }
            }
        }

        ////////////////////////////////////////////////////////////////////////////////
        //  Sends an "a" to MCU for regular checking
        ////////////////////////////////////////////////////////////////////////////////
        private void timer2_Tick(object sender, EventArgs e)
        {
            try
            {
                // Send an "a" to UART
                Com.Write(Constants.CHAR_CHECK);
            //    Com.Write("a");
            }
            catch (TimeoutException)
            {
                return;
            }
            catch(IOException)
            {
                return;
            }
            catch(InvalidOperationException)
            {
                return;
            }
            //writeByte('a');
        }

        /*******************************************************************************
        *                                   transmission
        *******************************************************************************/
        //
        //  the transmission string
        //
        string transmission;

        ////////////////////////////////////////////////////////////////////////////////
        //  Send Speed
        ////////////////////////////////////////////////////////////////////////////////
        private void btSendSpeed_Click(object sender, EventArgs e)
        {
            if ((LbConnect.Text == "Connected") && (txtSetspeed.Text != ""))
            {
                transmission = "T" + txtSetspeed.Text + "E";
                Com.Write(transmission);
            }
            else if (LbConnect.Text == "Disconnected")
            {
                MessageBox.Show("Connect PLZ!");
            }
            else
            {
                MessageBox.Show("Please input speed!");
            }
        }

        ////////////////////////////////////////////////////////////////////////////////
        //  Send Kp, Ki, Kd
        ////////////////////////////////////////////////////////////////////////////////
        private void Start_Click(object sender, EventArgs e)
        {
            if ((LbConnect.Text == "Connected") && (txtKp.Text != "")
                && (txtKi.Text != "") && (txtKd.Text != ""))
            {
                transmission = "KP" + txtKp.Text
                             + "KI" + txtKi.Text
                             + "KD" + txtKd.Text
                             + "E";
                Com.Write(transmission);
            }
            else if (LbConnect.Text == "Disconnected")
            {
                MessageBox.Show("Connect PLZ!");
            }
            else
            {
                MessageBox.Show("Please fill in all values!");
            }
        }

        ////////////////////////////////////////////////////////////////////////////////
        //  Change display mode
        ////////////////////////////////////////////////////////////////////////////////
        private void PbMode_Click_1(object sender, EventArgs e)
        {
            if (PbMode.Text == "Compact")
            {
                intMode = 0;
                PbMode.Text = "Sroll";
            }
            else
            {
                intMode = 1;
                PbMode.Text = "Compact";
            }
        }

        ////////////////////////////////////////////////////////////////////////////////
        //  Write one byte to COM (unused)
        ////////////////////////////////////////////////////////////////////////////////
        private void writeByte(byte b)
        {
            byte[] buffer = new byte[1];
            buffer[0] = b;
            try
            {
                this.Com.Write(buffer, 0, 1);
            }
            catch { }
        }

        ////////////////////////////////////////////////////////////////////////////////
        //  Emergency button (may or may not be used)
        ////////////////////////////////////////////////////////////////////////////////
        private void BtStop_Click(object sender, EventArgs e)
        {
            if (LbConnect.Text == "Connected")
            {
                Com.Write(Constants.CHAR_STOP);// truyền "S" = ngừng
                Com.DiscardOutBuffer();
            }
            else
            {
                MessageBox.Show("Not Connected");
            }
        }

        /*******************************************************************************
        *               Increase / Decrease Kp, Ki, Kd by buttons
        *******************************************************************************/
        double dKp, dKi, dKd;

        private void btPlusKp_Click(object sender, EventArgs e)
        {
            int lenKp = txtKp.Text.Length;
            Double.TryParse(txtKp.Text, out dKp);
            dKp += (double)UpdownKp.Value;
            if (dKp < 0)
                dKp = 0;
            txtKp.Text = dKp.ToString();
            while(txtKp.Text.Length < lenKp)
            {
                txtKp.Text = '0' + txtKp.Text;
            }
        }

        private void btMinusKp_Click(object sender, EventArgs e)
        {
            int lenKp = txtKp.Text.Length;
            Double.TryParse(txtKp.Text, out dKp);
            dKp -= (double)UpdownKp.Value;
            if (dKp < 0)
                dKp = 0;
            txtKp.Text = dKp.ToString();
            while (txtKp.Text.Length < lenKp)
            {
                txtKp.Text = '0' + txtKp.Text;
            }
        }
        private void btPlusKi_Click(object sender, EventArgs e)
        {
            int lenKi = txtKi.Text.Length;
            Double.TryParse(txtKi.Text, out dKi);
            dKi += (double)UpdownKi.Value;
            if (dKi < 0)
                dKi = 0;
            txtKi.Text = dKi.ToString();
            while (txtKi.Text.Length < lenKi)
            {
                txtKi.Text = '0' + txtKi.Text;
            }
        }

        private void btMinusKi_Click(object sender, EventArgs e)
        {
            int lenKi = txtKi.Text.Length;
            Double.TryParse(txtKi.Text, out dKi);
            dKi -= (double)UpdownKi.Value;
            if (dKi < 0)
                dKi = 0;
            txtKi.Text = dKi.ToString();
            while (txtKi.Text.Length < lenKi)
            {
                txtKi.Text = '0' + txtKi.Text;
            }
        }

        private void btPlusKd_Click(object sender, EventArgs e)
        {
            int lenKd = txtKd.Text.Length;
            Double.TryParse(txtKd.Text, out dKd);
            dKd += (double)UpdownKd.Value;
            if (dKd < 0)
                dKd = 0;
            txtKd.Text = dKd.ToString();
            while (txtKd.Text.Length < lenKd)
            {
                txtKd.Text = '0' + txtKd.Text;
            }
        }


        private void btMinusKd_Click(object sender, EventArgs e)
        {
            int lenKd = txtKd.Text.Length;
            Double.TryParse(txtKd.Text, out dKd);
            dKd -= (double)UpdownKd.Value;
            if (dKd < 0)
                dKd = 0;
            txtKd.Text = dKd.ToString();
            while (txtKd.Text.Length < lenKd)
            {
                txtKd.Text = '0' + txtKd.Text;
            }
        }

        /*******************************************************************************
        *                                   Save/ Load parameters
        *******************************************************************************/
        ////////////////////////////////////////////////////////////////////////////////
        //  Choose save file location
        ////////////////////////////////////////////////////////////////////////////////
        int numberOfLine = 0;
        private void btLocation_Click(object sender, EventArgs e)
        {
            OpenFileDialog of = new OpenFileDialog();
            of.ShowDialog();
            txtSaveFileLocation.Text = of.FileName;
            if (txtSaveFileLocation.Text != "")
            {
                StreamReader sr = new StreamReader(txtSaveFileLocation.Text);
                richTextBox1.Text = sr.ReadToEnd();
                string temp = richTextBox1.Text.ToString();
                for (int i = 0; i < temp.Length;i++ )
                {
                    if(temp[i] == '\n')
                        numberOfLine++;
                }
                UpDownSavePID.Value = numberOfLine++;
                //MessageBox.Show("Number of Line: " + numberOfLine.ToString());
                sr.Close();
            }
        }
        ////////////////////////////////////////////////////////////////////////////////
        //  Write to file (SAVE FILE)
        ////////////////////////////////////////////////////////////////////////////////
        private void btSavePID_Click(object sender, EventArgs e)
        {

            string text = File.ReadAllText("pidSave.txt");
            string temp = "";
            try
            {
                int i = 0;
                while (text[i++].ToString() != UpDownSavePID.Value.ToString())
                {
                    while (text[i++] != '\n')
                        ;
                }
                i--;
                while (text[i] != '\n')
                {
                    temp = temp + text[i++];
                }
            }
            catch(IndexOutOfRangeException)
            {
                ;
            }
            try
            {
                text = text.Replace(temp, UpDownSavePID.Value.ToString() + "p" + txtKp.Text + "i" + txtKi.Text + "d" + txtKd.Text);
            }
            catch(ArgumentException)
            {
                ;
            }
            File.WriteAllText("pidSave.txt", text);
            // reload file
            StreamReader sr = new StreamReader("pidSave.txt");
            richTextBox1.Text = sr.ReadToEnd();
            sr.Close();
        }
        ////////////////////////////////////////////////////////////////////////////////
        //  Read from file (LOAD FILE)
        ////////////////////////////////////////////////////////////////////////////////
        private void Load_File()
        {
            StreamReader sr = new StreamReader("pidSave.txt");
            richTextBox1.Text = sr.ReadToEnd();
            string temp = richTextBox1.Text.ToString();
            for (int i = 0; i < temp.Length; i++)
            {
                if (temp[i] == '\n' && temp.Length > 4)
                    numberOfLine++;
            }
            UpDownSavePID.Value = numberOfLine ;
            if (temp.Length > 0)
            {
                try
                {
                    #region Find line number UpDownLoadPID
                    int i = 0;
                    while (temp[i++].ToString() != UpDownLoadPID.Value.ToString())
                    {
                        while (temp[i++] != '\n')
                        {
                            ;
                        }
                    }
                    #endregion
                    #region READ PID numbers
                    if (temp[i++] == 'p')
                    {
                        txtKp.Text = "";
                        while (temp[i] != 'i')
                        {
                            txtKp.Text += temp[i++];
                        }
                    }
                    if (temp[i++] == 'i')
                    {
                        txtKi.Text = "";
                        while (temp[i] != 'd')
                        {
                            txtKi.Text += temp[i++];
                        }
                    }
                    if (temp[i++] == 'd')
                    {
                        txtKd.Text = "";
                        while (temp[i] != '\n')
                        {
                            txtKd.Text += temp[i++];
                        }
                    }
                    #endregion
                }
                catch(IndexOutOfRangeException)
                {
                    return;
                }
            }
            sr.Close();

        }
        private void btLoadPID_Click(object sender, EventArgs e)
        {
            StreamReader sr = new StreamReader("pidSave.txt");
            richTextBox1.Text = sr.ReadToEnd();
            string temp = richTextBox1.Text.ToString();
            if (temp.Length > 0)
            {
                try
                {
                    #region Find line number UpDownLoadPID
                    int i = 0;
                    while (temp[i++].ToString() != UpDownLoadPID.Value.ToString())
                    {
                        while (temp[i++] != '\n')
                        {
                            ;
                        }
                    }
                    #endregion
                    #region READ PID numbers
                    if (temp[i++] == 'p')
                    {
                        txtKp.Text = "";
                        while (temp[i] != 'i')
                        {
                            txtKp.Text += temp[i++];
                        }
                    }
                    if (temp[i++] == 'i')
                    {
                        txtKi.Text = "";
                        while (temp[i] != 'd')
                        {
                            txtKi.Text += temp[i++];
                        }
                    }
                    if (temp[i++] == 'd')
                    {
                        txtKd.Text = "";
                        while (temp[i] != '\n')
                        {
                            txtKd.Text += temp[i++];
                        }
                    }
                    #endregion
                }
                catch(IndexOutOfRangeException)
                {
                    return;
                }
            }
            sr.Close();
        }

        ////////////////////////////////////////////////////////////////////////////////
        //  Clear everything in save file 
        ////////////////////////////////////////////////////////////////////////////////
        private void btClear_Click(object sender, EventArgs e)
        {
            // clear file
            StreamWriter sw = new StreamWriter("pidSave.txt", false);
            sw.Write("");
            sw.Close();
            // reload file
            StreamReader sr = new StreamReader("pidSave.txt");
            richTextBox1.Text = sr.ReadToEnd();
            sr.Close();
            // reser values
            UpDownSavePID.Value = 0;
            UpDownLoadPID.Value = 0;
            numberOfLine = 0;
        }

        private void btCleanSave_Click(object sender, EventArgs e)
        {
            StreamWriter sw = new StreamWriter("pidSave.txt", true);
            sw.WriteLine(numberOfLine + "p" + txtKp.Text + "i" + txtKi.Text + "d" + txtKd.Text);
            sw.Close();
            numberOfLine++;
            // reload file
            StreamReader sr = new StreamReader("pidSave.txt");
            richTextBox1.Text = sr.ReadToEnd();
            sr.Close();
        }

        /*******************************************************************************
         *                              END OF FORMMAIN.CS
         *******************************************************************************/
    }
}
