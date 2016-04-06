using System;
using System.IO;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

// Thread
using System.Collections.Concurrent;
using System.Threading;

namespace Egg_Test_Data_Logger
{
    public partial class mainWindow : Form
    {
        int count = 0;
        int lowByte = 0;
        int highByte = 0;
        int modByte = 0;
        bool peakValuesTextExists = false;
        bool peakPeriodsTextExists = false;
        public int numberOfDataPoints = 0;
        int serCOMBytesToRead = 0;
        ConcurrentQueue<int> dataQueue = new ConcurrentQueue<int>();
        string path = @"C:\Users\Justin\OneDrive\Courses\MECH 423\Final Project\final_project_code\";

        public mainWindow()
        {
            InitializeComponent();
        }

        private void mainWindow_Load(object sender, EventArgs e)
        {
            ComPortUpdate();
            chartAcceleration.ChartAreas[0].AxisY.Maximum = 400;
            chartAcceleration.ChartAreas[0].AxisY.Minimum = 200;
            chartAcceleration.ChartAreas[0].AxisX.Maximum = 750;
            chartAcceleration.ChartAreas[0].AxisX.Minimum = 0;
            consoleWindow.ScrollBars = ScrollBars.Vertical;

            if (!File.Exists(path))
            {
                // Create a file to write to.
                using (StreamWriter sw = File.CreateText(path))
                {
                    sw.WriteLine("Value, Time");
                }
            }
        }

        private void ComPortUpdate()
        {
            cmbComPort.Items.Clear();
            string[] comPortArray = System.IO.Ports.SerialPort.GetPortNames().ToArray();
            Array.Reverse(comPortArray);
            cmbComPort.Items.AddRange(comPortArray);
            if (cmbComPort.Items.Count != 0)
                cmbComPort.SelectedIndex = 0;
            else
                cmbComPort.Text = "No Ports Found!";
        }

        private void serCOM_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            int newData;
            serCOMBytesToRead = serCOM.BytesToRead;
            while (serCOM.BytesToRead != 0)
            {
                newData = serCOM.ReadByte();
                dataQueue.Enqueue(newData);
            }
        }

        private void btnConnect_Click(object sender, EventArgs e)
        {
            if (btnConnect.Text == "Connect")
            {
                if (cmbComPort.Items.Count > 0)
                {
                    try
                    {
                        //serCOM.BaudRate = Convert.ToInt32(txtBaudRate.Text);
                        serCOM.PortName = cmbComPort.SelectedItem.ToString();
                        serCOM.Open();
                        btnConnect.Text = "Disconnect";
                        timer.Enabled = true;
                    }
                    catch (Exception ex)
                    {
                        MessageBox.Show(ex.Message);
                    }
                }
            }
            else
            {
                try
                {
                    serCOM.Close();
                    btnConnect.Text = "Connect";
                    timer.Enabled = false;
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message);
                }
            }
        }

        private void timer_Tick(object sender, EventArgs e)
        {
            var objPositionSeries = chartAcceleration.Series["eggAccel"];

            while (dataQueue.Count > 0)
            {
                int data;
                dataQueue.TryDequeue(out data);

                if (data == 0 && count == 0)
                {
                    count++;
                }
                else if (count == 1)
                {
                    modByte = data;
                    count++;
                }
                else if (count == 2)
                {
                    lowByte = data;
                    count++;
                }
                else if (count == 3)
                {
                    highByte = data;
                    data = (highByte << 8) + lowByte ;
                    count++;
                    count = 0;

                    switch(modByte) {
                        case 1:
                            // Display it on the 
                            chartAcceleration.Series["eggAccel"].Points.AddY(data);
                            // Display it on the text boxes
                            accelText.Text = data.ToString();
                            
                            // Write to text file
                            using (StreamWriter sw = File.AppendText(path + outputFilenameText + ".txt"))
                            {
                                sw.WriteLine(data.ToString());
                            }
                            break;
                        case 2:
                            // Clear chart
                            chartAcceleration.Series["eggAccel"].Points.Clear();

                            File.WriteAllText(path, " ");
                            break;
                        //case 3:
                        //    if (peakValuesTextExists == false)
                        //    {
                        //        peakPeriodsTextExists = false;  // reset
                        //        consoleWindow.AppendText("\r\nPeak Values: ");
                        //        peakValuesTextExists = true;
                        //    }
                        //    consoleWindow.AppendText(data.ToString() + ",");
                        //    break;
                        //case 4:
                        //    if (peakPeriodsTextExists == false)
                        //    {
                        //        peakValuesTextExists = false;   // reset
                        //        consoleWindow.AppendText("\r\nPeak Periods: ");
                        //        peakPeriodsTextExists = true;
                        //    }
                        //    consoleWindow.AppendText(data.ToString() + ",");
                        //    break;
                        case 5:
                            dataPointsText.Text = data.ToString();
                            break;
                        default:
                            break;
                    }
                }
            }
        }

    }
}
