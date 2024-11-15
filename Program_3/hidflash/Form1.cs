using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

using UsbLibrary;
using System.Diagnostics;
using uPLibrary.Networking.M2Mqtt;
using uPLibrary.Networking.M2Mqtt.Messages;

namespace HIDFlash
{
    public partial class Form1 : Form
    {
        public const byte CMD_GET_BOOT_INFO_SN = 0x5;
        public const byte CMD_ERASE_AND_UPDATE_APP = 0x7;
        public const byte CMD_COMPLETE_UPDATE = 0x1;
        public const byte CMD_SET_MACH_TYPE = 0x04;
        public const byte CMD_RESET_TO_BOOTLOADER = 0x08;
        public const byte CMD_SET_OUTPUT_GPIO = 0x0B;
        public const byte CMD_GET_OUTPUT_GPIO = 0x0C;
        public const byte CMD_GET_INPUT_GPIO = 0x0D;
        public const byte CMD_SET_LORA = 0x0E;
	    public const byte CMD_GET_LORA =0x0F;
	    public const byte CMD_SET_Motor =0x10;
	    public const byte CMD_GET_Motor =0x11;
	    public const byte CMD_SET_Current = 0x12;
        public const byte CMD_GET_Current = 0x13;

        public const byte IMU_CMD = 0x1A;
        public const byte BATTERY_CMD = 0x1B;
        public const byte INTERRUPT_CMD = 0x1C;
        public const byte READ_INPUT_CMD = 0x1D;
        private short PID = 22352;  //0x5750
        private short VID = 1155;   //0x0483


        //Lora Setting
        string[] LoraSetString = new string[] { "TypeAddress", "RFFrequency", "TXPower", "SignalBw", "SpreadingFactor", "ErrorCoding",
        "TxPacketTimeout","RxPacketTimeout","PINPONGPeriod","MODE","ID"};
        //USB連線狀態
        public int usbon = 0;

        //USB HID 連線
        Thread pw11usbqu = null;

        OpenFileDialog OpenFileDialog1;

        public int flag = 0;

        public int MachType = 0;

        [DllImport("kernel32", CharSet = CharSet.Unicode)]
        private static extern long WritePrivateProfileString(string section,
        string key, string val, string filePath);
        [DllImport("kernel32", CharSet = CharSet.Unicode)]
        private static extern int GetPrivateProfileString(string section,
        string key, string def, StringBuilder retVal,
        int size, string filePath);

        public string filename = "Config.ini";

        int size = 30;

        Stopwatch stopWatch = new Stopwatch();

        int n = 11; 
        TextBox[] textBoxes = new TextBox[11];
        Label[] labels = new Label[11];
        Boolean motor_onoff_flag = false;
        Boolean beep_onoff_flag = false;
        Boolean lcd_flag = false;
        public UInt32 outputData;
        public Form1()
        {
            InitializeComponent();

            StringBuilder temp = new StringBuilder(size);

            //USB
            this.usb.ProductId = 0;
            this.usb.VendorId = 0;
            this.usb.OnSpecifiedDeviceRemoved += new System.EventHandler(this.usb_OnSpecifiedDeviceRemoved);
            this.usb.OnDeviceArrived += new System.EventHandler(this.usb_OnDeviceArrived);
            this.usb.OnDeviceRemoved += new System.EventHandler(this.usb_OnDeviceRemoved);
            this.usb.OnDataRecieved += new UsbLibrary.DataRecievedEventHandler(this.usb_OnDataRecieved);
            this.usb.OnDataSend += new System.EventHandler(this.usb_OnDataSend);
            this.usb.OnSpecifiedDeviceArrived += new System.EventHandler(this.usb_OnSpecifiedDeviceArrived);

            //OpenFileDialog1
            OpenFileDialog1 = new OpenFileDialog();
            OpenFileDialog1.AutoUpgradeEnabled = true;
            OpenFileDialog1.AddExtension = true;
            OpenFileDialog1.CheckFileExists = true;
            OpenFileDialog1.CheckPathExists = true;
            OpenFileDialog1.DefaultExt = "bin";
            OpenFileDialog1.Filter = " Image file(*.bin) | *.bin";
            OpenFileDialog1.Multiselect = false;
            OpenFileDialog1.Title = "Form_burnin_openfiledialog_title";
            //progressBar1
            progressBar1.Step = 1;
            progressBar1.Minimum = 0;
            progressBar1.Value = 0;

            GetPrivateProfileString("GENERAL", "PID", "", temp, size, ".\\" + filename);
            int p_value = (int)new System.ComponentModel.Int32Converter().ConvertFromString(temp.ToString());
            PID = (short)p_value;
            GetPrivateProfileString("GENERAL", "VID", "", temp, size, ".\\" + filename);
            int v_value = (int)new System.ComponentModel.Int32Converter().ConvertFromString(temp.ToString());
            VID = (short)v_value;
            // PID = temp.ToString();


        

         

           for (int i = 0; i < n; i++)
           {
               textBoxes[i] = new TextBox();
               textBoxes[i].Location = new System.Drawing.Point(690, 200 + i * 30);
               // Here you can modify the value of the textbox which is at textBoxes[i]

               labels[i] = new Label();
               labels[i].Location = new System.Drawing.Point(600, 200 + i * 30);
               labels[i].Text = LoraSetString[i];
               // Here you can modify the value of the label which is at labels[i]
           }

           // This adds the controls to the form (you will need to specify thier co-ordinates etc. first)
           for (int i = 0; i < n; i++)
           {
               this.Controls.Add(textBoxes[i]);
               this.Controls.Add(labels[i]);
           }
        }

        string msg;
        public void showmsg(string a)
        {
            //labelStatus.Text = "";
            msg = a;
            MethodInvoker mi = new MethodInvoker(this.UpdateUI);
            this.BeginInvoke(mi, null);
        }
        private void usb_OnSpecifiedDeviceRemoved(object sender, EventArgs e)
        {
            usbon = 0;
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            voidconn_usb();
            this.AcceptButton = this.ConnectButton;
            QosComboBox.SelectedIndex = 0;
        }
        private void voidconn_usb()
        {
            try
            {
                this.usb.ProductId = PID;
                this.usb.VendorId = VID;
                this.usb.CheckDevicePresent();
                label1.Text = "PID:0x"+PID.ToString("X4");
                label2.Text = "VID:0x" + VID.ToString("X4");
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
        }
        private void usb_OnDeviceArrived(object sender, EventArgs e)
        {
            showmsg("Found Device");

        }
        private void usb_OnDeviceRemoved(object sender, EventArgs e)
        {
            if (InvokeRequired)
            {
                Invoke(new EventHandler(usb_OnDeviceRemoved), new object[] { sender, e });
            }
            else
            {
                //button_connect.Invoke(new Action(() => { button_connect.PerformClick(); }));
                //flag = 4;
                showmsg("Device removed");
            }
        }
        private void usb_OnSpecifiedDeviceArrived(object sender, EventArgs e)
        {

            showmsg("Get Device");
            label3.Text = "Ver:";
            label4.Text = "SN:";
            label5.Text = "Type:";
            usbon = 1;
            if (pw11usbqu != null)
            {
                try
                {
                    pw11usbqu.Abort();
                }
                catch
                {
                }
            }
            pw11usbqu = new System.Threading.Thread(new System.Threading.ThreadStart(send_tousb_quxian_data_thread));
            pw11usbqu.Start();

            send_Command(CMD_GET_BOOT_INFO_SN);
            send_Command(CMD_GET_LORA);
            stopWatch.Reset();
            stopWatch.Start();
        }

        private static object _thisLock = new object();

        public Queue<usbdata> send_que = new Queue<usbdata>();
        public class usbdata
        {
            public byte[] dataa;
            public int is_waitok = 1;
        }

        public static string ByteArrayToString(byte[] ba)
        {
            StringBuilder hex = new StringBuilder(ba.Length * 2);
            foreach (byte b in ba)
                hex.AppendFormat("{0:X2}", b);
            return hex.ToString();
        }
        int x = 0;
        private void usb_OnDataRecieved(object sender, DataRecievedEventArgs args)
        {
            if (InvokeRequired)//含showmsg
            {
                try
                {
                    Invoke(new DataRecievedEventHandler(usb_OnDataRecieved), new object[] { sender, args });
                }
                catch (Exception ex)
                {
                    showmsg(ex.Message + ex.StackTrace);
                    //MessageBox.Show(ex.Message + ex.StackTrace);
                }
            }
            else
            {
                 x++;
                 if (x > 100)
                 {
                     x = 0;
                     stopWatch.Stop();
                     float speed = (float)((64 *100* 8) / stopWatch.ElapsedMilliseconds); // kbps
                     label7.Text = speed.ToString("f3");
                     float frame = (float)((100.0/stopWatch.ElapsedMilliseconds)*1000.0);
                     label9.Text = frame.ToString("f3");
                     stopWatch.Reset();
                     stopWatch.Start();
                 }
                switch (args.data[1])
                {
                    case CMD_GET_LORA:
                        textBoxes[0].Text = ((UInt32)(args.data[5] << 24 | args.data[4] << 16 | args.data[3] << 8 | args.data[2])).ToString();
                        textBoxes[1].Text = ((UInt32)(args.data[9] << 24 | args.data[8] << 16 | args.data[7] << 8 | args.data[6])).ToString();
                        for (int i = 0; i < 9;i++ )
                        {
                            textBoxes[2 + i].Text = ((UInt16)(args.data[11+i*2] << 8 | args.data[10+i*2])).ToString();
                        }
                        break;
                    case  READ_INPUT_CMD:
                        
                            label29.Text = args.data[2].ToString();
                            label27.Text = args.data[3].ToString();
                            label25.Text = args.data[4].ToString();
                            label31.Text = args.data[5].ToString();
                            label33.Text = args.data[6].ToString();
                            label21.Text = args.data[7].ToString();
                            label19.Text = args.data[8].ToString();
                            label17.Text = args.data[9].ToString();
                            label15.Text = args.data[10].ToString();
                         label39.Text = args.data[11].ToString();
                            label37.Text = args.data[12].ToString();
                            label35.Text = args.data[13].ToString();
                            label23.Text = args.data[14].ToString();
                        break;
                    case CMD_GET_INPUT_GPIO:  //Input interrupt
                        label27.Text = args.data[7].ToString();
                        label25.Text = args.data[8].ToString();
                        float temp = (float)((args.data[7]<<8 | args.data[8])*0.125);
                        label31.Text = temp.ToString("00.00");
                        PubMessageTextBox.Text = temp.ToString("00.00");
                        label21.Text = args.data[9].ToString();
                        label19.Text = args.data[10].ToString();
                        label17.Text = args.data[11].ToString();
                        label15.Text = args.data[12].ToString();
                        // label33.Text = args.data[9].ToString();
                        break;
                    case BATTERY_CMD:
                        UInt16 voltageADC = ((UInt16)(args.data[3] << 8 | args.data[4] ));
                        double voltage = (double)(voltageADC /4095.0 )* 3.37 * 4.636363636363636;
                        label29.Text = voltage.ToString("00.00");
                        
                        break;
                    case CMD_GET_BOOT_INFO_SN:
                        byte[] sn = new byte[12];
                        Buffer.BlockCopy( args.data,4,sn, 0, 12);
                        
                        label3.Text = "Ver:" + args.data[2].ToString()+"."+args.data[3].ToString();
                        label4.Text = "SN:" + ByteArrayToString(sn);
                        label5.Text = "Type:" + args.data[15].ToString();
                        break;
                    case CMD_ERASE_AND_UPDATE_APP:
                        textBoxMSG.AppendText("Erase Done\r\n.");
                        const int dataSize = 32;
                        byte[] data = new byte[dataSize];
                        byte[] senddata = new byte[64];
                        /* get the file */
                        FileStream fileStream = new FileStream(@OpenFileDialog1.FileName, FileMode.Open, FileAccess.Read);
                        textBoxMSG.AppendText("File size: " + Convert.ToInt32(fileStream.Length) + " Bytes\n");
                        textBoxMSG.AppendText("Start to Upload.\n");
                        progressBar1.Maximum = ((int)fileStream.Length % dataSize == 0) ? ((int)fileStream.Length / dataSize) : ((int)fileStream.Length / dataSize + 1);
                        int fileReadCount = 0;
                       
                        do
                        {

                            /* if this is the last packet fill the remaining bytes with 0 */
                            fileReadCount = fileStream.Read(data, 0, dataSize);
                           //WriteTestData = b.ReadBytes(32);
                            if (fileReadCount == 0) break;
                            if (fileReadCount != dataSize)
                                for (int i = fileReadCount; i < dataSize; i++)
                                    data[i] = 0;

                            
                           
                            lock (_thisLock)
                            {
                                senddata[0] = 3;
                                data.CopyTo(senddata, 4);
                                Thread.Sleep(1);
                                this.usb.SpecifiedDevice.SendData(senddata);
                                Application.DoEvents();
                            }

                            if (progressBar1.Value < progressBar1.Maximum)
                            {
                                progressBar1.PerformStep();
                                textBoxMSG.AppendText(".");
                            }
                            else
                            {
                                textBoxMSG.AppendText(".");
                            }


                        } while (dataSize == fileReadCount);
                        textBoxMSG.AppendText("\r\nFlash Done\n");
                        send_Command(CMD_COMPLETE_UPDATE);
                        break;
                }
            }
        }
        private void usb_OnDataSend(object sender, EventArgs e)
        {
            // flag = 0;
            //owmsg("Sent");
            //this.lb_message.Items.Add("Some data was send");
        }
        protected override void OnHandleCreated(EventArgs e)
        {
            base.OnHandleCreated(e);
            usb.RegisterHandle(Handle);
        }
        protected override void WndProc(ref Message m)
        {
            usb.ParseMessages(ref m);
            base.WndProc(ref m);	// pass message on to base form
        }

        private void UpdateUI()
        {
            textBoxMSG.AppendText(msg + "\r\n");

            textBoxMSG.ScrollToCaret();

        }

        public void send_tousb_quxian_data_thread()
        {
            int len1 = this.usb.SpecifiedDevice.OutputReportLength;
            byte[] cmd = new byte[len1];
            while (true)
            {
                lock (_thisLock)
                {
                    if (flag == CMD_ERASE_AND_UPDATE_APP)  //CMD_ERASE_AND_UPDATE_APP
                    {
                        cmd[0] = 2;  //Report ID
                        cmd[1] = (byte)flag;
                        cmd[63] = 0xff;
                        // watch.Start();
                        this.usb.SpecifiedDevice.SendData(cmd);
                        flag = 0;
                    }
                    else if (flag == CMD_COMPLETE_UPDATE)
                    {
                        cmd[0] = 2;  //Report ID
                        cmd[1] = (byte)flag;
                        cmd[63] = 0xff;
                        // watch.Start();
                        this.usb.SpecifiedDevice.SendData(cmd);
                        flag = 0;
                    }
                    else if (flag == CMD_GET_BOOT_INFO_SN)
                    {
                        cmd[0] = 2;  //Report ID
                        cmd[1] = (byte)flag;
                        cmd[63] = 0xff;
                        // watch.Start();
                        this.usb.SpecifiedDevice.SendData(cmd);
                        flag = 0;
                    }
                    else if (flag == CMD_SET_MACH_TYPE)
                    {
                        cmd[0] = 2;  //Report ID
                        cmd[1] = (byte)flag;
                        cmd[2] = (byte)MachType;
                        cmd[63] = 0xff;
                        this.usb.SpecifiedDevice.SendData(cmd);
                        flag = 0;
                    }
                    else if (flag == CMD_RESET_TO_BOOTLOADER)  //reset to bootloader
                    {
                        cmd[0] = 0;
                        cmd[1] = CMD_RESET_TO_BOOTLOADER;
                        this.usb.SpecifiedDevice.SendData(cmd);
                        flag = 0;
                    }
                    else if (flag == CMD_SET_OUTPUT_GPIO)
                    {
                        cmd[0] = 0;
                        cmd[1] = CMD_SET_OUTPUT_GPIO;
                     
                        cmd[4] = (byte)outputData;
                        cmd[5] = (byte)(outputData >> 8);
                        cmd[6] = (byte)(outputData >> 16);
                        cmd[7] = (byte)(outputData >> 24);
                        this.usb.SpecifiedDevice.SendData(cmd);
                        flag = 0;
                    }
                    else if (flag == CMD_GET_INPUT_GPIO)
                    {
                        cmd[0] = 0;
                        cmd[1] = CMD_GET_INPUT_GPIO;
                
             
                        this.usb.SpecifiedDevice.SendData(cmd);
                        flag = 0;
                    }
                    else if (flag == CMD_GET_LORA)
                    {
                        cmd[0] = 0;
                        cmd[1] = CMD_GET_LORA;
                        this.usb.SpecifiedDevice.SendData(cmd);
                        flag = 0;
                    }
                    else if (flag == CMD_SET_LORA)
                    {
                        cmd[0] = 0;
                        cmd[1] = CMD_SET_LORA;
                        UInt32 tmp,tmp1;
                        UInt32.TryParse(textBoxes[0].Text, out tmp);
                        cmd[2] = (byte)(tmp >> 24);
                        cmd[3] = (byte)(tmp >> 16);
                        cmd[4] = (byte)(tmp >> 8);
                        cmd[5] = (byte)tmp;
                        UInt32.TryParse(textBoxes[1].Text, out tmp1);
                        cmd[6] = (byte)(tmp1 >> 24);
                        cmd[7] = (byte)(tmp1 >> 16);
                        cmd[8] = (byte)(tmp1 >> 8);
                        cmd[9] = (byte)tmp1;

                        for (int i = 0; i < 9; i++)
                        {
                            UInt32.TryParse(textBoxes[2+i].Text, out tmp1);
                            cmd[10+i*2] = (byte)(tmp1 >> 8);
                            cmd[11+i*2] = (byte)tmp1;
                        }
                        this.usb.SpecifiedDevice.SendData(cmd);
                        flag = 0;
                    }
                    else if (flag == CMD_SET_Motor)
                    {
                        cmd[0] = 0;
                        cmd[1] = CMD_SET_Motor;
                        
                       
                      
                        
                        if (motor_onoff_flag==true)
                        {
                            cmd[2] = (byte)(0xf0);
                        }else{
                            cmd[2] = (byte)(0xff);
                        }
                        cmd[3] = 3;

                        //Beep
                        if (beep_onoff_flag == true)
                        {
                            cmd[10] = (byte)(0xf0);
                        }
                        else
                        {
                            cmd[10] = (byte)(0xff);
                        }

                        //LCD
                        if (lcd_flag == true)
                        {
                            lcd_flag = false;
                            cmd[11] = (byte)(Convert.ToInt32(textBox3.Text));
                            cmd[12] = (byte)(Convert.ToInt32(textBox4.Text));
                            var myBuffer = new byte[16];
                            myBuffer = ASCIIEncoding.ASCII.GetBytes(textBox2.Text);
                            myBuffer.CopyTo(cmd, 13);
                            
                        }
                        this.usb.SpecifiedDevice.SendData(cmd);
                        flag = 0;
                    }
                }
            }
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            Environment.Exit(1);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            MachType = int.Parse(textBox1.Text);
            send_Command(CMD_SET_MACH_TYPE);
        }



        //OpenFileDialog1
        private void button9_Click(object sender, EventArgs e)
        {
            switch (OpenFileDialog1.ShowDialog())
            {
                case System.Windows.Forms.DialogResult.OK:
                    textBox8.Clear();
                    richTextBox1.Clear();
                    richTextBox1.AppendText("Select File: " + OpenFileDialog1.FileName + "\n");
                    textBox8.Text = OpenFileDialog1.FileName;
                    progressBar1.Value = 0;
                    break;
                default:
                    break;
            }
        }
        //Erase and Update
        private void button8_Click(object sender, EventArgs e)
        {
            progressBar1.Value = 0;
            textBoxMSG.AppendText("Start to erase Flash\r\n.");
            send_Command(CMD_ERASE_AND_UPDATE_APP);
        }

        //Send _command
        private void send_Command(byte CMD)
        {
            flag = CMD;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            send_Command(CMD_RESET_TO_BOOTLOADER);
        }

        private void button3_Click(object sender, EventArgs e)
        {
            send_Command(CMD_SET_OUTPUT_GPIO);
        }
        private void CheckedChanged(object sender, EventArgs e)
        {
            CheckBox checkbox = (CheckBox)sender;
            string numStr = checkbox.Text.Replace("Output","");
            int num = int.Parse(numStr)-1;
            if (checkbox.Checked == true)
            {
                outputData |=  ((uint)1 << num);
            }
            else
            {
                outputData &= ~((uint)1 << num);
            }
            //textBoxMSG.AppendText(numStr + "\n");
            textBoxMSG.AppendText("Send Output:0x"+outputData.ToString("X")+"\n");
            send_Command(CMD_SET_OUTPUT_GPIO);
        }

        private void button4_Click(object sender, EventArgs e)
        {
            send_Command(CMD_GET_INPUT_GPIO);
        }

        private void button5_Click(object sender, EventArgs e)
        {
            send_Command(CMD_SET_LORA);
        }

        private void button6_Click(object sender, EventArgs e)
        {
            send_Command(CMD_SET_Motor);
        }

        private void button7_Click(object sender, EventArgs e)
        {
            motor_onoff_flag = true;
            send_Command(CMD_SET_Motor);
        }

        private void button10_Click(object sender, EventArgs e)
        {
            motor_onoff_flag = false;
            send_Command(CMD_SET_Motor);
        }
        //Beep on
        private void button6_Click_1(object sender, EventArgs e)
        {
            beep_onoff_flag = true;
            send_Command(CMD_SET_Motor);
        }
        //Beep off
        private void button4_Click_1(object sender, EventArgs e)
        {
            beep_onoff_flag = false;
            send_Command(CMD_SET_Motor);
        }
        //LCD
        private void button11_Click(object sender, EventArgs e)
        {
            lcd_flag = true;

            send_Command(CMD_SET_Motor);
        }
        //Temperature
        private void button12_Click(object sender, EventArgs e)
        {
            send_Command(CMD_GET_INPUT_GPIO);
        }
        private delegate void myUICallBack(string myStr, TextBox ctl);
        static MqttClient client;
        //MQTT
        private void myUI(string myStr, TextBox ctl)
        {
            if (this.InvokeRequired)
            {
                myUICallBack myUpdate = new myUICallBack(myUI);
                this.Invoke(myUpdate, myStr, ctl);
            }
            else
            {
                ctl.AppendText(myStr + Environment.NewLine);
            }
        }
        private void client_MqttMsgPublishReceived(object sender, MqttMsgPublishEventArgs e)
        {
            myUI(System.Text.Encoding.UTF8.GetString(e.Message), MessageTextBox);
        }
        private void ConnectButton_Click(object sender, EventArgs e)
        {
            int port;
            if (HostTextBox.Text.Length == 0)
            {
                label4.Text = "Invild host";
            }
            else if (!Int32.TryParse(PortTextBox.Text, out port))
            {
                label4.Text = "Invild port";
            }
            else
            {
                try
                {
                    client = new MqttClient(HostTextBox.Text, port, false, null);
                    client.Connect(Guid.NewGuid().ToString(), "howard", textBox5.Text.ToString());
                    client.MqttMsgPublishReceived += new MqttClient.MqttMsgPublishEventHandler(client_MqttMsgPublishReceived);
                }
                catch
                {
                    label4.Text = "Can't connect to server";
                }
                if (client != null && client.IsConnected)
                {
                    this.AcceptButton = this.PublishButton;
                    label4.Text = "";
                    MessageTextBox.Clear();
                    SubscribeButton.Enabled = true;
                    PublishButton.Enabled = true;
                    UnsubscribeButton.Enabled = true;
                    DisconnectButton.Enabled = true;
                    ConnectButton.Enabled = false;
                    HostTextBox.Enabled = false;
                    PortTextBox.Enabled = false;
                }
            }
        }

        private void DisconnectButton_Click(object sender, EventArgs e)
        {
            if (client != null && client.IsConnected) client.Disconnect();
            SubscribeButton.Enabled = false;
            PublishButton.Enabled = false;
            UnsubscribeButton.Enabled = false;
            DisconnectButton.Enabled = false;
            ConnectButton.Enabled = true;
            HostTextBox.Enabled = true;
            PortTextBox.Enabled = true;
            SubListBox.Items.Clear();
        }

        private void SubscribeButton_Click(object sender, EventArgs e)
        {
            if (SubTopicTextBox.Text.Length == 0)
            {
                label4.Text = "Subscribe topic can't be empty";
            }
            else
            {
                label4.Text = "";
                client.Subscribe(new string[] { SubTopicTextBox.Text }, new byte[] { (byte)QosComboBox.SelectedIndex });
                SubListBox.Items.Add(SubTopicTextBox.Text);
            }
        }

        private void PublishButton_Click(object sender, EventArgs e)
        {
            if (PubMessageTextBox.Text.Length == 0)
            {
                label4.Text = "No message to send";
            }
            else if (PubTopicTextBox.Text.Length == 0)
            {
                label4.Text = "Publish topic can't be empty";
            }
            else if (PubTopicTextBox.Text.IndexOf('#') != -1 || PubTopicTextBox.Text.IndexOf('+') != -1)
            {
                label4.Text = "Publish topic can't include wildcard(# , +)";
            }
            else
            {
                label4.Text = "";
                client.Publish(PubTopicTextBox.Text, Encoding.UTF8.GetBytes(PubMessageTextBox.Text), (byte)QosComboBox.SelectedIndex, RetainCheckBox.Checked);
            }
        }

        private void ClearButton_Click(object sender, EventArgs e)
        {
            MessageTextBox.Clear();
        }

        private void UnsubscribeButton_Click(object sender, EventArgs e)
        {
            if (SubListBox.SelectedItem == null)
            {
                label4.Text = "Select topic to unscribe";
            }
            else
            {
                label4.Text = "";
                client.Unsubscribe(new string[] { SubListBox.SelectedItem.ToString() });
                SubListBox.Items.Remove(SubListBox.SelectedItem);
            }
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            PublishButton.Invoke(new Action(() => { PublishButton.PerformClick(); }));

        }

        private void label30_Click(object sender, EventArgs e)
        {

        }

        private void label31_Click(object sender, EventArgs e)
        {

        }
    }
    }
