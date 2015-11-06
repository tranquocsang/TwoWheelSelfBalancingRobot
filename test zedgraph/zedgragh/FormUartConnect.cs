using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO.Ports;

namespace zedgragh
{
    public partial class FormUartConnect : Form
    {
        public FormUartConnect()
        {
            InitializeComponent();
          
            CbBaudRate.Text = "115200";
            CbDatabits.Text = "8";
            CbStopbits.Text = "1";
            CbParity.Text = "None";
        }

        private void timer1_Tick(object sender, EventArgs e)
        {

        }

        private void ButOk_Click(object sender, EventArgs e)
        {
            //checking valid config
            if ((CbBaudRate.Text == "") | (CbDatabits.Text == "") | (CbParity.Text == "") | (CbStopbits.Text == "")) //(CbSecCom.Text == "") |
            {
               
                MessageBox.Show("Oh I found some mistakes ,Please config correctly OR you can cancel form !");
            }
            else
            {
                //cancel form2 and transfer config  data to form1
                int.TryParse(CbBaudRate.Text, out FormMain.baudrate);
                int.TryParse(CbDatabits.Text, out FormMain.databits);
                Enum.TryParse(CbStopbits.Text, out FormMain.stopbits);
                Enum.TryParse(CbParity.Text, out FormMain.parity);
                Close();
            }
        }

        private void ButDefault_Click(object sender, EventArgs e)
        {
         //   CbSecCom.Text = "COM3";
            CbBaudRate.Text = "115200";
            CbDatabits.Text = "8";
            CbStopbits.Text = "1";
            CbParity.Text = "None";
        }

        private void ButCancel_Click(object sender, EventArgs e)
        {
            //cancel form2 and transfer config  data to form1
            int.TryParse(CbBaudRate.Text, out FormMain.baudrate);
            int.TryParse(CbDatabits.Text, out FormMain.databits);
            Enum.TryParse(CbStopbits.Text, out FormMain.stopbits);
            Enum.TryParse(CbParity.Text, out FormMain.parity);
            Close();
        }
    }
}
