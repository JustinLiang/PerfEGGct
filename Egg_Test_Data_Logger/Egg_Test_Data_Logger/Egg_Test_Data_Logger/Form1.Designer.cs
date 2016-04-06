namespace Egg_Test_Data_Logger
{
    partial class mainWindow
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
            System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea1 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
            System.Windows.Forms.DataVisualization.Charting.Series series1 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(mainWindow));
            this.chartAcceleration = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.timer = new System.Windows.Forms.Timer(this.components);
            this.serCOM = new System.IO.Ports.SerialPort(this.components);
            this.toolStrip1 = new System.Windows.Forms.ToolStrip();
            this.cmbComPort = new System.Windows.Forms.ToolStripComboBox();
            this.toolStripLabel1 = new System.Windows.Forms.ToolStripLabel();
            this.txtBaudRate = new System.Windows.Forms.ToolStripTextBox();
            this.btnConnect = new System.Windows.Forms.ToolStripButton();
            this.consoleWindow = new System.Windows.Forms.TextBox();
            this.position = new System.Windows.Forms.Label();
            this.accelText = new System.Windows.Forms.TextBox();
            this.dataPointsText = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.outputFilenameText = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.chartAcceleration)).BeginInit();
            this.toolStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // chartAcceleration
            // 
            chartArea1.Name = "ChartArea1";
            this.chartAcceleration.ChartAreas.Add(chartArea1);
            this.chartAcceleration.Location = new System.Drawing.Point(12, 41);
            this.chartAcceleration.Name = "chartAcceleration";
            series1.ChartArea = "ChartArea1";
            series1.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Spline;
            series1.Name = "eggAccel";
            this.chartAcceleration.Series.Add(series1);
            this.chartAcceleration.Size = new System.Drawing.Size(923, 300);
            this.chartAcceleration.TabIndex = 0;
            this.chartAcceleration.Text = "Acceleration vs Time";
            // 
            // timer
            // 
            this.timer.Enabled = true;
            this.timer.Interval = 10;
            this.timer.Tick += new System.EventHandler(this.timer_Tick);
            // 
            // serCOM
            // 
            this.serCOM.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.serCOM_DataReceived);
            // 
            // toolStrip1
            // 
            this.toolStrip1.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.cmbComPort,
            this.toolStripLabel1,
            this.txtBaudRate,
            this.btnConnect});
            this.toolStrip1.Location = new System.Drawing.Point(0, 0);
            this.toolStrip1.Name = "toolStrip1";
            this.toolStrip1.Size = new System.Drawing.Size(950, 25);
            this.toolStrip1.TabIndex = 35;
            this.toolStrip1.Text = "toolStrip1";
            // 
            // cmbComPort
            // 
            this.cmbComPort.Name = "cmbComPort";
            this.cmbComPort.Size = new System.Drawing.Size(120, 25);
            // 
            // toolStripLabel1
            // 
            this.toolStripLabel1.Name = "toolStripLabel1";
            this.toolStripLabel1.Size = new System.Drawing.Size(63, 22);
            this.toolStripLabel1.Text = "Baud Rate:";
            // 
            // txtBaudRate
            // 
            this.txtBaudRate.Name = "txtBaudRate";
            this.txtBaudRate.Size = new System.Drawing.Size(70, 25);
            this.txtBaudRate.Text = "9600";
            // 
            // btnConnect
            // 
            this.btnConnect.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.btnConnect.Image = ((System.Drawing.Image)(resources.GetObject("btnConnect.Image")));
            this.btnConnect.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.btnConnect.Name = "btnConnect";
            this.btnConnect.Size = new System.Drawing.Size(56, 22);
            this.btnConnect.Text = "Connect";
            this.btnConnect.Click += new System.EventHandler(this.btnConnect_Click);
            // 
            // consoleWindow
            // 
            this.consoleWindow.Location = new System.Drawing.Point(12, 347);
            this.consoleWindow.Multiline = true;
            this.consoleWindow.Name = "consoleWindow";
            this.consoleWindow.Size = new System.Drawing.Size(923, 281);
            this.consoleWindow.TabIndex = 38;
            // 
            // position
            // 
            this.position.AutoSize = true;
            this.position.Location = new System.Drawing.Point(357, 5);
            this.position.Name = "position";
            this.position.Size = new System.Drawing.Size(66, 13);
            this.position.TabIndex = 36;
            this.position.Text = "Acceleration";
            // 
            // accelText
            // 
            this.accelText.Location = new System.Drawing.Point(440, 5);
            this.accelText.Name = "accelText";
            this.accelText.Size = new System.Drawing.Size(60, 20);
            this.accelText.TabIndex = 37;
            // 
            // dataPointsText
            // 
            this.dataPointsText.Location = new System.Drawing.Point(589, 5);
            this.dataPointsText.Name = "dataPointsText";
            this.dataPointsText.Size = new System.Drawing.Size(60, 20);
            this.dataPointsText.TabIndex = 40;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(506, 5);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(62, 13);
            this.label1.TabIndex = 39;
            this.label1.Text = "Data Points";
            // 
            // outputFilenameText
            // 
            this.outputFilenameText.Location = new System.Drawing.Point(804, 5);
            this.outputFilenameText.Name = "outputFilenameText";
            this.outputFilenameText.Size = new System.Drawing.Size(60, 20);
            this.outputFilenameText.TabIndex = 42;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(709, 5);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(89, 13);
            this.label2.TabIndex = 41;
            this.label2.Text = "Output File Name";
            // 
            // mainWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(950, 634);
            this.Controls.Add(this.outputFilenameText);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.dataPointsText);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.consoleWindow);
            this.Controls.Add(this.accelText);
            this.Controls.Add(this.position);
            this.Controls.Add(this.toolStrip1);
            this.Controls.Add(this.chartAcceleration);
            this.Name = "mainWindow";
            this.Text = "mainWindow";
            this.Load += new System.EventHandler(this.mainWindow_Load);
            ((System.ComponentModel.ISupportInitialize)(this.chartAcceleration)).EndInit();
            this.toolStrip1.ResumeLayout(false);
            this.toolStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataVisualization.Charting.Chart chartAcceleration;
        private System.Windows.Forms.Timer timer;
        private System.IO.Ports.SerialPort serCOM;
        private System.Windows.Forms.ToolStrip toolStrip1;
        private System.Windows.Forms.ToolStripComboBox cmbComPort;
        private System.Windows.Forms.ToolStripLabel toolStripLabel1;
        private System.Windows.Forms.ToolStripTextBox txtBaudRate;
        private System.Windows.Forms.ToolStripButton btnConnect;
        private System.Windows.Forms.TextBox consoleWindow;
        private System.Windows.Forms.Label position;
        private System.Windows.Forms.TextBox accelText;
        private System.Windows.Forms.TextBox dataPointsText;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox outputFilenameText;
        private System.Windows.Forms.Label label2;
    }
}

