namespace HIDFlash
{
    partial class Form1
    {
        /// <summary>
        /// 設計工具所需的變數。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清除任何使用中的資源。
        /// </summary>
        /// <param name="disposing">如果應該處置 Managed 資源則為 true，否則為 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form 設計工具產生的程式碼

        /// <summary>
        /// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器修改
        /// 這個方法的內容。
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.usb = new UsbLibrary.UsbHidPort(this.components);
            this.textBoxMSG = new System.Windows.Forms.TextBox();
            this.button1 = new System.Windows.Forms.Button();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.button9 = new System.Windows.Forms.Button();
            this.richTextBox1 = new System.Windows.Forms.TextBox();
            this.progressBar1 = new System.Windows.Forms.ProgressBar();
            this.button8 = new System.Windows.Forms.Button();
            this.textBox8 = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.button2 = new System.Windows.Forms.Button();
            this.label4 = new System.Windows.Forms.Label();
            this.button3 = new System.Windows.Forms.Button();
            this.label5 = new System.Windows.Forms.Label();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.label7 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.label24 = new System.Windows.Forms.Label();
            this.label25 = new System.Windows.Forms.Label();
            this.label26 = new System.Windows.Forms.Label();
            this.label27 = new System.Windows.Forms.Label();
            this.label28 = new System.Windows.Forms.Label();
            this.label29 = new System.Windows.Forms.Label();
            this.label30 = new System.Windows.Forms.Label();
            this.label31 = new System.Windows.Forms.Label();
            this.label32 = new System.Windows.Forms.Label();
            this.label33 = new System.Windows.Forms.Label();
            this.button5 = new System.Windows.Forms.Button();
            this.label14 = new System.Windows.Forms.Label();
            this.label15 = new System.Windows.Forms.Label();
            this.label16 = new System.Windows.Forms.Label();
            this.label17 = new System.Windows.Forms.Label();
            this.label18 = new System.Windows.Forms.Label();
            this.label19 = new System.Windows.Forms.Label();
            this.label20 = new System.Windows.Forms.Label();
            this.label21 = new System.Windows.Forms.Label();
            this.label22 = new System.Windows.Forms.Label();
            this.label23 = new System.Windows.Forms.Label();
            this.label34 = new System.Windows.Forms.Label();
            this.label35 = new System.Windows.Forms.Label();
            this.label36 = new System.Windows.Forms.Label();
            this.label37 = new System.Windows.Forms.Label();
            this.label38 = new System.Windows.Forms.Label();
            this.label39 = new System.Windows.Forms.Label();
            this.label40 = new System.Windows.Forms.Label();
            this.label41 = new System.Windows.Forms.Label();
            this.button7 = new System.Windows.Forms.Button();
            this.button10 = new System.Windows.Forms.Button();
            this.button4 = new System.Windows.Forms.Button();
            this.button6 = new System.Windows.Forms.Button();
            this.button11 = new System.Windows.Forms.Button();
            this.textBox2 = new System.Windows.Forms.TextBox();
            this.textBox3 = new System.Windows.Forms.TextBox();
            this.textBox4 = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.label12 = new System.Windows.Forms.Label();
            this.button12 = new System.Windows.Forms.Button();
            this.textBox5 = new System.Windows.Forms.TextBox();
            this.label13 = new System.Windows.Forms.Label();
            this.RetainCheckBox = new System.Windows.Forms.CheckBox();
            this.label42 = new System.Windows.Forms.Label();
            this.QosComboBox = new System.Windows.Forms.ComboBox();
            this.label43 = new System.Windows.Forms.Label();
            this.label44 = new System.Windows.Forms.Label();
            this.PortTextBox = new System.Windows.Forms.TextBox();
            this.DisconnectButton = new System.Windows.Forms.Button();
            this.ConnectButton = new System.Windows.Forms.Button();
            this.HostTextBox = new System.Windows.Forms.TextBox();
            this.label45 = new System.Windows.Forms.Label();
            this.UnsubscribeButton = new System.Windows.Forms.Button();
            this.label46 = new System.Windows.Forms.Label();
            this.SubListBox = new System.Windows.Forms.ListBox();
            this.PubTopicTextBox = new System.Windows.Forms.TextBox();
            this.label47 = new System.Windows.Forms.Label();
            this.SubscribeButton = new System.Windows.Forms.Button();
            this.label48 = new System.Windows.Forms.Label();
            this.PubMessageTextBox = new System.Windows.Forms.TextBox();
            this.MessageTextBox = new System.Windows.Forms.TextBox();
            this.ClearButton = new System.Windows.Forms.Button();
            this.PublishButton = new System.Windows.Forms.Button();
            this.SubTopicTextBox = new System.Windows.Forms.TextBox();
            this.label49 = new System.Windows.Forms.Label();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.groupBox2.SuspendLayout();
            this.SuspendLayout();
            // 
            // usb
            // 
            this.usb.ProductId = 0;
            this.usb.VendorId = 0;
            // 
            // textBoxMSG
            // 
            this.textBoxMSG.Location = new System.Drawing.Point(27, 349);
            this.textBoxMSG.Multiline = true;
            this.textBoxMSG.Name = "textBoxMSG";
            this.textBoxMSG.Size = new System.Drawing.Size(295, 183);
            this.textBoxMSG.TabIndex = 0;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(361, 385);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(189, 23);
            this.button1.TabIndex = 1;
            this.button1.Text = "Set Mach Type";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.button9);
            this.groupBox2.Controls.Add(this.richTextBox1);
            this.groupBox2.Controls.Add(this.progressBar1);
            this.groupBox2.Controls.Add(this.button8);
            this.groupBox2.Controls.Add(this.textBox8);
            this.groupBox2.Location = new System.Drawing.Point(12, 171);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(538, 165);
            this.groupBox2.TabIndex = 56;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Bootloader";
            // 
            // button9
            // 
            this.button9.Location = new System.Drawing.Point(6, 103);
            this.button9.Name = "button9";
            this.button9.Size = new System.Drawing.Size(139, 56);
            this.button9.TabIndex = 26;
            this.button9.Text = "Choose File";
            this.button9.UseVisualStyleBackColor = true;
            this.button9.Click += new System.EventHandler(this.button9_Click);
            // 
            // richTextBox1
            // 
            this.richTextBox1.Location = new System.Drawing.Point(172, 67);
            this.richTextBox1.Multiline = true;
            this.richTextBox1.Name = "richTextBox1";
            this.richTextBox1.Size = new System.Drawing.Size(218, 63);
            this.richTextBox1.TabIndex = 28;
            // 
            // progressBar1
            // 
            this.progressBar1.Location = new System.Drawing.Point(172, 136);
            this.progressBar1.Name = "progressBar1";
            this.progressBar1.Size = new System.Drawing.Size(218, 23);
            this.progressBar1.TabIndex = 29;
            // 
            // button8
            // 
            this.button8.Location = new System.Drawing.Point(6, 28);
            this.button8.Name = "button8";
            this.button8.Size = new System.Drawing.Size(139, 56);
            this.button8.TabIndex = 25;
            this.button8.Text = "Erase && Update Firmware";
            this.button8.UseVisualStyleBackColor = true;
            this.button8.Click += new System.EventHandler(this.button8_Click);
            // 
            // textBox8
            // 
            this.textBox8.Location = new System.Drawing.Point(172, 28);
            this.textBox8.Name = "textBox8";
            this.textBox8.Size = new System.Drawing.Size(218, 22);
            this.textBox8.TabIndex = 27;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(24, 546);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(35, 13);
            this.label1.TabIndex = 57;
            this.label1.Text = "label1";
            this.label1.Visible = false;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(23, 568);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(35, 13);
            this.label2.TabIndex = 58;
            this.label2.Text = "label2";
            this.label2.Visible = false;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(24, 589);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(35, 13);
            this.label3.TabIndex = 59;
            this.label3.Text = "label3";
            this.label3.Visible = false;
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(361, 356);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(189, 23);
            this.button2.TabIndex = 60;
            this.button2.Text = "Jump to Bootloader";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(23, 610);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(35, 13);
            this.label4.TabIndex = 61;
            this.label4.Text = "label4";
            this.label4.Visible = false;
            // 
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(84, 600);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(75, 23);
            this.button3.TabIndex = 62;
            this.button3.Text = "button3";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Visible = false;
            this.button3.Click += new System.EventHandler(this.button3_Click);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(23, 630);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(35, 13);
            this.label5.TabIndex = 63;
            this.label5.Text = "label5";
            this.label5.Visible = false;
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(361, 415);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(100, 22);
            this.textBox1.TabIndex = 64;
            this.textBox1.Text = "1";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(80, 547);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(35, 13);
            this.label7.TabIndex = 66;
            this.label7.Text = "label7";
            this.label7.Visible = false;
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(131, 547);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(30, 13);
            this.label8.TabIndex = 67;
            this.label8.Text = "kbps";
            this.label8.Visible = false;
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(81, 568);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(35, 13);
            this.label9.TabIndex = 68;
            this.label9.Text = "label9";
            this.label9.Visible = false;
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(131, 568);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(35, 13);
            this.label10.TabIndex = 69;
            this.label10.Text = "frame";
            this.label10.Visible = false;
            // 
            // label24
            // 
            this.label24.AutoSize = true;
            this.label24.Location = new System.Drawing.Point(237, 589);
            this.label24.Name = "label24";
            this.label24.Size = new System.Drawing.Size(29, 13);
            this.label24.TabIndex = 88;
            this.label24.Text = "IN1:";
            this.label24.Visible = false;
            // 
            // label25
            // 
            this.label25.AutoSize = true;
            this.label25.Location = new System.Drawing.Point(297, 589);
            this.label25.Name = "label25";
            this.label25.Size = new System.Drawing.Size(41, 13);
            this.label25.TabIndex = 87;
            this.label25.Text = "label25";
            this.label25.Visible = false;
            // 
            // label26
            // 
            this.label26.AutoSize = true;
            this.label26.Location = new System.Drawing.Point(237, 568);
            this.label26.Name = "label26";
            this.label26.Size = new System.Drawing.Size(29, 13);
            this.label26.TabIndex = 86;
            this.label26.Text = "IN0:";
            this.label26.Visible = false;
            // 
            // label27
            // 
            this.label27.AutoSize = true;
            this.label27.Location = new System.Drawing.Point(297, 568);
            this.label27.Name = "label27";
            this.label27.Size = new System.Drawing.Size(41, 13);
            this.label27.TabIndex = 85;
            this.label27.Text = "label27";
            this.label27.Visible = false;
            // 
            // label28
            // 
            this.label28.AutoSize = true;
            this.label28.Location = new System.Drawing.Point(237, 547);
            this.label28.Name = "label28";
            this.label28.Size = new System.Drawing.Size(23, 13);
            this.label28.TabIndex = 84;
            this.label28.Text = "ID:";
            this.label28.Visible = false;
            // 
            // label29
            // 
            this.label29.AutoSize = true;
            this.label29.Location = new System.Drawing.Point(297, 547);
            this.label29.Name = "label29";
            this.label29.Size = new System.Drawing.Size(41, 13);
            this.label29.TabIndex = 83;
            this.label29.Text = "label29";
            this.label29.Visible = false;
            // 
            // label30
            // 
            this.label30.AutoSize = true;
            this.label30.Location = new System.Drawing.Point(41, 33);
            this.label30.Name = "label30";
            this.label30.Size = new System.Drawing.Size(121, 16);
            this.label30.TabIndex = 90;
            this.label30.Text = "TEMPERATURE:";
            this.label30.Click += new System.EventHandler(this.label30_Click);
            // 
            // label31
            // 
            this.label31.AutoSize = true;
            this.label31.Location = new System.Drawing.Point(165, 33);
            this.label31.Name = "label31";
            this.label31.Size = new System.Drawing.Size(43, 16);
            this.label31.TabIndex = 89;
            this.label31.Text = "26.43";
            this.label31.Click += new System.EventHandler(this.label31_Click);
            // 
            // label32
            // 
            this.label32.AutoSize = true;
            this.label32.Location = new System.Drawing.Point(237, 610);
            this.label32.Name = "label32";
            this.label32.Size = new System.Drawing.Size(29, 13);
            this.label32.TabIndex = 92;
            this.label32.Text = "IN3:";
            this.label32.Visible = false;
            // 
            // label33
            // 
            this.label33.AutoSize = true;
            this.label33.Location = new System.Drawing.Point(297, 610);
            this.label33.Name = "label33";
            this.label33.Size = new System.Drawing.Size(41, 13);
            this.label33.TabIndex = 91;
            this.label33.Text = "label33";
            this.label33.Visible = false;
            // 
            // button5
            // 
            this.button5.Location = new System.Drawing.Point(357, 454);
            this.button5.Name = "button5";
            this.button5.Size = new System.Drawing.Size(139, 56);
            this.button5.TabIndex = 125;
            this.button5.Text = "Set RF";
            this.button5.UseVisualStyleBackColor = true;
            this.button5.Click += new System.EventHandler(this.button5_Click);
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Location = new System.Drawing.Point(551, 89);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(124, 16);
            this.label14.TabIndex = 143;
            this.label14.Text = "KEY4_PRESSED:";
            // 
            // label15
            // 
            this.label15.AutoSize = true;
            this.label15.Location = new System.Drawing.Point(704, 89);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(16, 16);
            this.label15.TabIndex = 142;
            this.label15.Text = "0";
            // 
            // label16
            // 
            this.label16.AutoSize = true;
            this.label16.Location = new System.Drawing.Point(551, 36);
            this.label16.Name = "label16";
            this.label16.Size = new System.Drawing.Size(124, 16);
            this.label16.TabIndex = 141;
            this.label16.Text = "KEY3_PRESSED:";
            // 
            // label17
            // 
            this.label17.AutoSize = true;
            this.label17.Location = new System.Drawing.Point(704, 36);
            this.label17.Name = "label17";
            this.label17.Size = new System.Drawing.Size(16, 16);
            this.label17.TabIndex = 140;
            this.label17.Text = "0";
            // 
            // label18
            // 
            this.label18.AutoSize = true;
            this.label18.Location = new System.Drawing.Point(303, 92);
            this.label18.Name = "label18";
            this.label18.Size = new System.Drawing.Size(99, 13);
            this.label18.TabIndex = 139;
            this.label18.Text = "KEY2_PRESSED:";
            // 
            // label19
            // 
            this.label19.AutoSize = true;
            this.label19.Location = new System.Drawing.Point(446, 92);
            this.label19.Name = "label19";
            this.label19.Size = new System.Drawing.Size(13, 13);
            this.label19.TabIndex = 138;
            this.label19.Text = "1";
            // 
            // label20
            // 
            this.label20.AutoSize = true;
            this.label20.Location = new System.Drawing.Point(303, 36);
            this.label20.Name = "label20";
            this.label20.Size = new System.Drawing.Size(99, 13);
            this.label20.TabIndex = 137;
            this.label20.Text = "KEY1_PRESSED:";
            // 
            // label21
            // 
            this.label21.AutoSize = true;
            this.label21.Location = new System.Drawing.Point(447, 36);
            this.label21.Name = "label21";
            this.label21.Size = new System.Drawing.Size(13, 13);
            this.label21.TabIndex = 136;
            this.label21.Text = "0";
            // 
            // label22
            // 
            this.label22.AutoSize = true;
            this.label22.Location = new System.Drawing.Point(381, 610);
            this.label22.Name = "label22";
            this.label22.Size = new System.Drawing.Size(35, 13);
            this.label22.TabIndex = 151;
            this.label22.Text = "IN11:";
            this.label22.Visible = false;
            // 
            // label23
            // 
            this.label23.AutoSize = true;
            this.label23.Location = new System.Drawing.Point(441, 610);
            this.label23.Name = "label23";
            this.label23.Size = new System.Drawing.Size(41, 13);
            this.label23.TabIndex = 150;
            this.label23.Text = "label23";
            this.label23.Visible = false;
            // 
            // label34
            // 
            this.label34.AutoSize = true;
            this.label34.Location = new System.Drawing.Point(381, 590);
            this.label34.Name = "label34";
            this.label34.Size = new System.Drawing.Size(35, 13);
            this.label34.TabIndex = 149;
            this.label34.Text = "IN10:";
            this.label34.Visible = false;
            // 
            // label35
            // 
            this.label35.AutoSize = true;
            this.label35.Location = new System.Drawing.Point(441, 590);
            this.label35.Name = "label35";
            this.label35.Size = new System.Drawing.Size(41, 13);
            this.label35.TabIndex = 148;
            this.label35.Text = "label35";
            this.label35.Visible = false;
            // 
            // label36
            // 
            this.label36.AutoSize = true;
            this.label36.Location = new System.Drawing.Point(381, 568);
            this.label36.Name = "label36";
            this.label36.Size = new System.Drawing.Size(29, 13);
            this.label36.TabIndex = 147;
            this.label36.Text = "IN9:";
            this.label36.Visible = false;
            // 
            // label37
            // 
            this.label37.AutoSize = true;
            this.label37.Location = new System.Drawing.Point(441, 568);
            this.label37.Name = "label37";
            this.label37.Size = new System.Drawing.Size(41, 13);
            this.label37.TabIndex = 146;
            this.label37.Text = "label37";
            this.label37.Visible = false;
            // 
            // label38
            // 
            this.label38.AutoSize = true;
            this.label38.Location = new System.Drawing.Point(381, 547);
            this.label38.Name = "label38";
            this.label38.Size = new System.Drawing.Size(29, 13);
            this.label38.TabIndex = 145;
            this.label38.Text = "IN8:";
            this.label38.Visible = false;
            // 
            // label39
            // 
            this.label39.AutoSize = true;
            this.label39.Location = new System.Drawing.Point(441, 547);
            this.label39.Name = "label39";
            this.label39.Size = new System.Drawing.Size(41, 13);
            this.label39.TabIndex = 144;
            this.label39.Text = "label39";
            this.label39.Visible = false;
            // 
            // label40
            // 
            this.label40.AutoSize = true;
            this.label40.Location = new System.Drawing.Point(507, 547);
            this.label40.Name = "label40";
            this.label40.Size = new System.Drawing.Size(39, 13);
            this.label40.TabIndex = 153;
            this.label40.Text = "Status:";
            this.label40.Visible = false;
            // 
            // label41
            // 
            this.label41.AutoSize = true;
            this.label41.Location = new System.Drawing.Point(567, 547);
            this.label41.Name = "label41";
            this.label41.Size = new System.Drawing.Size(41, 13);
            this.label41.TabIndex = 152;
            this.label41.Text = "label41";
            this.label41.Visible = false;
            // 
            // button7
            // 
            this.button7.Location = new System.Drawing.Point(828, 16);
            this.button7.Name = "button7";
            this.button7.Size = new System.Drawing.Size(139, 56);
            this.button7.TabIndex = 154;
            this.button7.Text = "Set LED On";
            this.button7.UseVisualStyleBackColor = true;
            this.button7.Click += new System.EventHandler(this.button7_Click);
            // 
            // button10
            // 
            this.button10.Location = new System.Drawing.Point(828, 88);
            this.button10.Name = "button10";
            this.button10.Size = new System.Drawing.Size(139, 56);
            this.button10.TabIndex = 155;
            this.button10.Text = "Set LED OFF";
            this.button10.UseVisualStyleBackColor = true;
            this.button10.Click += new System.EventHandler(this.button10_Click);
            // 
            // button4
            // 
            this.button4.Location = new System.Drawing.Point(1033, 88);
            this.button4.Name = "button4";
            this.button4.Size = new System.Drawing.Size(139, 56);
            this.button4.TabIndex = 157;
            this.button4.Text = "Beep  OFF";
            this.button4.UseVisualStyleBackColor = true;
            this.button4.Click += new System.EventHandler(this.button4_Click_1);
            // 
            // button6
            // 
            this.button6.Location = new System.Drawing.Point(1033, 16);
            this.button6.Name = "button6";
            this.button6.Size = new System.Drawing.Size(139, 56);
            this.button6.TabIndex = 156;
            this.button6.Text = "Beep On";
            this.button6.UseVisualStyleBackColor = true;
            this.button6.Click += new System.EventHandler(this.button6_Click_1);
            // 
            // button11
            // 
            this.button11.Location = new System.Drawing.Point(1429, 16);
            this.button11.Name = "button11";
            this.button11.Size = new System.Drawing.Size(139, 56);
            this.button11.TabIndex = 158;
            this.button11.Text = "LCD Write";
            this.button11.UseVisualStyleBackColor = true;
            this.button11.Click += new System.EventHandler(this.button11_Click);
            // 
            // textBox2
            // 
            this.textBox2.Location = new System.Drawing.Point(1429, 149);
            this.textBox2.MaxLength = 5;
            this.textBox2.Name = "textBox2";
            this.textBox2.Size = new System.Drawing.Size(139, 22);
            this.textBox2.TabIndex = 30;
            this.textBox2.Text = "Hello";
            // 
            // textBox3
            // 
            this.textBox3.Location = new System.Drawing.Point(1429, 93);
            this.textBox3.Name = "textBox3";
            this.textBox3.Size = new System.Drawing.Size(139, 22);
            this.textBox3.TabIndex = 159;
            this.textBox3.Text = "240";
            // 
            // textBox4
            // 
            this.textBox4.Location = new System.Drawing.Point(1429, 121);
            this.textBox4.Name = "textBox4";
            this.textBox4.Size = new System.Drawing.Size(139, 22);
            this.textBox4.TabIndex = 160;
            this.textBox4.Text = "100";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(1383, 118);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(16, 13);
            this.label6.TabIndex = 162;
            this.label6.Text = "Y";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(1384, 96);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(16, 13);
            this.label11.TabIndex = 161;
            this.label11.Text = "X";
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(1384, 152);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(31, 13);
            this.label12.TabIndex = 163;
            this.label12.Text = "Text:";
            // 
            // button12
            // 
            this.button12.Enabled = false;
            this.button12.Location = new System.Drawing.Point(1227, 16);
            this.button12.Name = "button12";
            this.button12.Size = new System.Drawing.Size(139, 56);
            this.button12.TabIndex = 164;
            this.button12.Text = "Read Temp";
            this.button12.UseVisualStyleBackColor = true;
            this.button12.Click += new System.EventHandler(this.button12_Click);
            // 
            // textBox5
            // 
            this.textBox5.Font = new System.Drawing.Font("微軟正黑體", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.textBox5.Location = new System.Drawing.Point(1100, 195);
            this.textBox5.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.textBox5.MaxLength = 128;
            this.textBox5.Name = "textBox5";
            this.textBox5.Size = new System.Drawing.Size(140, 27);
            this.textBox5.TabIndex = 176;
            this.textBox5.Text = "6CEBA1Z32VVWZ9VP";
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Font = new System.Drawing.Font("微軟正黑體", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.label13.Location = new System.Drawing.Point(1009, 198);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(98, 22);
            this.label13.TabIndex = 175;
            this.label13.Text = "MQTT KEY:";
            // 
            // RetainCheckBox
            // 
            this.RetainCheckBox.AutoSize = true;
            this.RetainCheckBox.Location = new System.Drawing.Point(1178, 236);
            this.RetainCheckBox.Name = "RetainCheckBox";
            this.RetainCheckBox.Size = new System.Drawing.Size(18, 17);
            this.RetainCheckBox.TabIndex = 174;
            this.RetainCheckBox.UseVisualStyleBackColor = true;
            // 
            // label42
            // 
            this.label42.AutoSize = true;
            this.label42.Font = new System.Drawing.Font("微軟正黑體", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.label42.Location = new System.Drawing.Point(1116, 232);
            this.label42.Name = "label42";
            this.label42.Size = new System.Drawing.Size(80, 28);
            this.label42.TabIndex = 173;
            this.label42.Text = "Retain:";
            // 
            // QosComboBox
            // 
            this.QosComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.QosComboBox.FormattingEnabled = true;
            this.QosComboBox.Items.AddRange(new object[] {
            "0 At most once",
            "1 At least once",
            "2 Exactly once"});
            this.QosComboBox.Location = new System.Drawing.Point(1007, 231);
            this.QosComboBox.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.QosComboBox.MaxDropDownItems = 3;
            this.QosComboBox.Name = "QosComboBox";
            this.QosComboBox.Size = new System.Drawing.Size(92, 20);
            this.QosComboBox.TabIndex = 172;
            // 
            // label43
            // 
            this.label43.AutoSize = true;
            this.label43.Font = new System.Drawing.Font("微軟正黑體", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.label43.Location = new System.Drawing.Point(959, 235);
            this.label43.Name = "label43";
            this.label43.Size = new System.Drawing.Size(61, 28);
            this.label43.TabIndex = 171;
            this.label43.Text = "QoS:";
            // 
            // label44
            // 
            this.label44.AutoSize = true;
            this.label44.Font = new System.Drawing.Font("微軟正黑體", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.label44.Location = new System.Drawing.Point(838, 235);
            this.label44.Name = "label44";
            this.label44.Size = new System.Drawing.Size(59, 28);
            this.label44.TabIndex = 170;
            this.label44.Text = "Port:";
            // 
            // PortTextBox
            // 
            this.PortTextBox.Location = new System.Drawing.Point(888, 232);
            this.PortTextBox.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.PortTextBox.MaxLength = 4;
            this.PortTextBox.Name = "PortTextBox";
            this.PortTextBox.Size = new System.Drawing.Size(52, 22);
            this.PortTextBox.TabIndex = 167;
            this.PortTextBox.Text = "1883";
            // 
            // DisconnectButton
            // 
            this.DisconnectButton.Enabled = false;
            this.DisconnectButton.Font = new System.Drawing.Font("微軟正黑體", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.DisconnectButton.Location = new System.Drawing.Point(1227, 230);
            this.DisconnectButton.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.DisconnectButton.Name = "DisconnectButton";
            this.DisconnectButton.Size = new System.Drawing.Size(110, 31);
            this.DisconnectButton.TabIndex = 169;
            this.DisconnectButton.Text = "Disconnect";
            this.DisconnectButton.UseVisualStyleBackColor = true;
            this.DisconnectButton.Click += new System.EventHandler(this.DisconnectButton_Click);
            // 
            // ConnectButton
            // 
            this.ConnectButton.Font = new System.Drawing.Font("微軟正黑體", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.ConnectButton.Location = new System.Drawing.Point(1268, 195);
            this.ConnectButton.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.ConnectButton.Name = "ConnectButton";
            this.ConnectButton.Size = new System.Drawing.Size(68, 31);
            this.ConnectButton.TabIndex = 168;
            this.ConnectButton.Text = "Connect";
            this.ConnectButton.UseVisualStyleBackColor = true;
            this.ConnectButton.Click += new System.EventHandler(this.ConnectButton_Click);
            // 
            // HostTextBox
            // 
            this.HostTextBox.Font = new System.Drawing.Font("微軟正黑體", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.HostTextBox.Location = new System.Drawing.Point(888, 194);
            this.HostTextBox.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.HostTextBox.MaxLength = 128;
            this.HostTextBox.Name = "HostTextBox";
            this.HostTextBox.Size = new System.Drawing.Size(113, 27);
            this.HostTextBox.TabIndex = 166;
            this.HostTextBox.Text = "embpcb.com";
            // 
            // label45
            // 
            this.label45.AutoSize = true;
            this.label45.Font = new System.Drawing.Font("微軟正黑體", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.label45.Location = new System.Drawing.Point(836, 197);
            this.label45.Name = "label45";
            this.label45.Size = new System.Drawing.Size(52, 22);
            this.label45.TabIndex = 165;
            this.label45.Text = "Host:";
            // 
            // UnsubscribeButton
            // 
            this.UnsubscribeButton.Enabled = false;
            this.UnsubscribeButton.Font = new System.Drawing.Font("微軟正黑體", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.UnsubscribeButton.Location = new System.Drawing.Point(1413, 378);
            this.UnsubscribeButton.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.UnsubscribeButton.Name = "UnsubscribeButton";
            this.UnsubscribeButton.Size = new System.Drawing.Size(186, 31);
            this.UnsubscribeButton.TabIndex = 189;
            this.UnsubscribeButton.Text = "Unsubscribe";
            this.UnsubscribeButton.UseVisualStyleBackColor = true;
            this.UnsubscribeButton.Click += new System.EventHandler(this.UnsubscribeButton_Click);
            // 
            // label46
            // 
            this.label46.AutoSize = true;
            this.label46.Font = new System.Drawing.Font("微軟正黑體", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.label46.Location = new System.Drawing.Point(1423, 197);
            this.label46.Name = "label46";
            this.label46.Size = new System.Drawing.Size(165, 22);
            this.label46.TabIndex = 188;
            this.label46.Text = "Subscriptions topic:";
            // 
            // SubListBox
            // 
            this.SubListBox.Font = new System.Drawing.Font("微軟正黑體", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.SubListBox.FormattingEnabled = true;
            this.SubListBox.HorizontalScrollbar = true;
            this.SubListBox.ItemHeight = 19;
            this.SubListBox.Location = new System.Drawing.Point(1429, 230);
            this.SubListBox.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.SubListBox.Name = "SubListBox";
            this.SubListBox.ScrollAlwaysVisible = true;
            this.SubListBox.Size = new System.Drawing.Size(150, 137);
            this.SubListBox.TabIndex = 187;
            // 
            // PubTopicTextBox
            // 
            this.PubTopicTextBox.Font = new System.Drawing.Font("微軟正黑體", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.PubTopicTextBox.Location = new System.Drawing.Point(946, 306);
            this.PubTopicTextBox.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.PubTopicTextBox.MaxLength = 128;
            this.PubTopicTextBox.Name = "PubTopicTextBox";
            this.PubTopicTextBox.Size = new System.Drawing.Size(448, 27);
            this.PubTopicTextBox.TabIndex = 186;
            this.PubTopicTextBox.Text = "Temperature";
            // 
            // label47
            // 
            this.label47.AutoSize = true;
            this.label47.Font = new System.Drawing.Font("微軟正黑體", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.label47.Location = new System.Drawing.Point(833, 306);
            this.label47.Name = "label47";
            this.label47.Size = new System.Drawing.Size(151, 28);
            this.label47.TabIndex = 185;
            this.label47.Text = "Topic for pub:";
            // 
            // SubscribeButton
            // 
            this.SubscribeButton.Enabled = false;
            this.SubscribeButton.Font = new System.Drawing.Font("微軟正黑體", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.SubscribeButton.Location = new System.Drawing.Point(1285, 269);
            this.SubscribeButton.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.SubscribeButton.Name = "SubscribeButton";
            this.SubscribeButton.Size = new System.Drawing.Size(110, 31);
            this.SubscribeButton.TabIndex = 179;
            this.SubscribeButton.Text = "Subscribe";
            this.SubscribeButton.UseVisualStyleBackColor = true;
            this.SubscribeButton.Click += new System.EventHandler(this.SubscribeButton_Click);
            // 
            // label48
            // 
            this.label48.AutoSize = true;
            this.label48.Font = new System.Drawing.Font("微軟正黑體", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.label48.Location = new System.Drawing.Point(838, 344);
            this.label48.Name = "label48";
            this.label48.Size = new System.Drawing.Size(108, 28);
            this.label48.TabIndex = 181;
            this.label48.Text = "Message:";
            // 
            // PubMessageTextBox
            // 
            this.PubMessageTextBox.Font = new System.Drawing.Font("微軟正黑體", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.PubMessageTextBox.Location = new System.Drawing.Point(946, 344);
            this.PubMessageTextBox.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.PubMessageTextBox.MaxLength = 128;
            this.PubMessageTextBox.Name = "PubMessageTextBox";
            this.PubMessageTextBox.Size = new System.Drawing.Size(448, 27);
            this.PubMessageTextBox.TabIndex = 180;
            this.PubMessageTextBox.Text = "26.43";
            // 
            // MessageTextBox
            // 
            this.MessageTextBox.Font = new System.Drawing.Font("微軟正黑體", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.MessageTextBox.Location = new System.Drawing.Point(834, 420);
            this.MessageTextBox.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.MessageTextBox.Multiline = true;
            this.MessageTextBox.Name = "MessageTextBox";
            this.MessageTextBox.ReadOnly = true;
            this.MessageTextBox.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.MessageTextBox.Size = new System.Drawing.Size(559, 64);
            this.MessageTextBox.TabIndex = 184;
            // 
            // ClearButton
            // 
            this.ClearButton.Font = new System.Drawing.Font("微軟正黑體", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.ClearButton.Location = new System.Drawing.Point(837, 492);
            this.ClearButton.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.ClearButton.Name = "ClearButton";
            this.ClearButton.Size = new System.Drawing.Size(559, 31);
            this.ClearButton.TabIndex = 183;
            this.ClearButton.Text = "Clear";
            this.ClearButton.UseVisualStyleBackColor = true;
            this.ClearButton.Click += new System.EventHandler(this.ClearButton_Click);
            // 
            // PublishButton
            // 
            this.PublishButton.Enabled = false;
            this.PublishButton.Font = new System.Drawing.Font("微軟正黑體", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.PublishButton.Location = new System.Drawing.Point(840, 378);
            this.PublishButton.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.PublishButton.Name = "PublishButton";
            this.PublishButton.Size = new System.Drawing.Size(555, 31);
            this.PublishButton.TabIndex = 182;
            this.PublishButton.Text = "Publish";
            this.PublishButton.UseVisualStyleBackColor = true;
            this.PublishButton.Click += new System.EventHandler(this.PublishButton_Click);
            // 
            // SubTopicTextBox
            // 
            this.SubTopicTextBox.Font = new System.Drawing.Font("微軟正黑體", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.SubTopicTextBox.Location = new System.Drawing.Point(946, 269);
            this.SubTopicTextBox.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.SubTopicTextBox.MaxLength = 128;
            this.SubTopicTextBox.Name = "SubTopicTextBox";
            this.SubTopicTextBox.Size = new System.Drawing.Size(332, 27);
            this.SubTopicTextBox.TabIndex = 178;
            this.SubTopicTextBox.Text = "Temperature";
            // 
            // label49
            // 
            this.label49.AutoSize = true;
            this.label49.Font = new System.Drawing.Font("微軟正黑體", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.label49.Location = new System.Drawing.Point(835, 269);
            this.label49.Name = "label49";
            this.label49.Size = new System.Drawing.Size(148, 28);
            this.label49.TabIndex = 177;
            this.label49.Text = "Topic for sub:";
            // 
            // timer1
            // 
            this.timer1.Enabled = true;
            this.timer1.Interval = 3000;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSize = true;
            this.ClientSize = new System.Drawing.Size(1626, 713);
            this.Controls.Add(this.UnsubscribeButton);
            this.Controls.Add(this.label46);
            this.Controls.Add(this.SubListBox);
            this.Controls.Add(this.PubTopicTextBox);
            this.Controls.Add(this.label47);
            this.Controls.Add(this.SubscribeButton);
            this.Controls.Add(this.label48);
            this.Controls.Add(this.PubMessageTextBox);
            this.Controls.Add(this.MessageTextBox);
            this.Controls.Add(this.ClearButton);
            this.Controls.Add(this.PublishButton);
            this.Controls.Add(this.SubTopicTextBox);
            this.Controls.Add(this.label49);
            this.Controls.Add(this.textBox5);
            this.Controls.Add(this.label13);
            this.Controls.Add(this.RetainCheckBox);
            this.Controls.Add(this.label42);
            this.Controls.Add(this.QosComboBox);
            this.Controls.Add(this.label43);
            this.Controls.Add(this.label44);
            this.Controls.Add(this.PortTextBox);
            this.Controls.Add(this.DisconnectButton);
            this.Controls.Add(this.ConnectButton);
            this.Controls.Add(this.HostTextBox);
            this.Controls.Add(this.label45);
            this.Controls.Add(this.button12);
            this.Controls.Add(this.label12);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label11);
            this.Controls.Add(this.textBox4);
            this.Controls.Add(this.textBox3);
            this.Controls.Add(this.textBox2);
            this.Controls.Add(this.button11);
            this.Controls.Add(this.button4);
            this.Controls.Add(this.button6);
            this.Controls.Add(this.button10);
            this.Controls.Add(this.button7);
            this.Controls.Add(this.label40);
            this.Controls.Add(this.label41);
            this.Controls.Add(this.label22);
            this.Controls.Add(this.label23);
            this.Controls.Add(this.label34);
            this.Controls.Add(this.label35);
            this.Controls.Add(this.label36);
            this.Controls.Add(this.label37);
            this.Controls.Add(this.label38);
            this.Controls.Add(this.label39);
            this.Controls.Add(this.label14);
            this.Controls.Add(this.label15);
            this.Controls.Add(this.label16);
            this.Controls.Add(this.label17);
            this.Controls.Add(this.label18);
            this.Controls.Add(this.label19);
            this.Controls.Add(this.label20);
            this.Controls.Add(this.label21);
            this.Controls.Add(this.button5);
            this.Controls.Add(this.label32);
            this.Controls.Add(this.label33);
            this.Controls.Add(this.label30);
            this.Controls.Add(this.label31);
            this.Controls.Add(this.label24);
            this.Controls.Add(this.label25);
            this.Controls.Add(this.label26);
            this.Controls.Add(this.label27);
            this.Controls.Add(this.label28);
            this.Controls.Add(this.label29);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.button3);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.textBoxMSG);
            this.Name = "Form1";
            this.Text = "STM32H723ZG Dashboard";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.Load += new System.EventHandler(this.Form1_Load);
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private UsbLibrary.UsbHidPort usb;
        private System.Windows.Forms.TextBox textBoxMSG;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Button button9;
        private System.Windows.Forms.TextBox richTextBox1;
        private System.Windows.Forms.ProgressBar progressBar1;
        private System.Windows.Forms.Button button8;
        private System.Windows.Forms.TextBox textBox8;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label label24;
        private System.Windows.Forms.Label label25;
        private System.Windows.Forms.Label label26;
        private System.Windows.Forms.Label label27;
        private System.Windows.Forms.Label label28;
        private System.Windows.Forms.Label label29;
        private System.Windows.Forms.Label label30;
        private System.Windows.Forms.Label label31;
        private System.Windows.Forms.Label label32;
        private System.Windows.Forms.Label label33;
        private System.Windows.Forms.Button button5;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.Label label15;
        private System.Windows.Forms.Label label16;
        private System.Windows.Forms.Label label17;
        private System.Windows.Forms.Label label18;
        private System.Windows.Forms.Label label19;
        private System.Windows.Forms.Label label20;
        private System.Windows.Forms.Label label21;
        private System.Windows.Forms.Label label22;
        private System.Windows.Forms.Label label23;
        private System.Windows.Forms.Label label34;
        private System.Windows.Forms.Label label35;
        private System.Windows.Forms.Label label36;
        private System.Windows.Forms.Label label37;
        private System.Windows.Forms.Label label38;
        private System.Windows.Forms.Label label39;
        private System.Windows.Forms.Label label40;
        private System.Windows.Forms.Label label41;
        private System.Windows.Forms.Button button7;
        private System.Windows.Forms.Button button10;
        private System.Windows.Forms.Button button4;
        private System.Windows.Forms.Button button6;
        private System.Windows.Forms.Button button11;
        private System.Windows.Forms.TextBox textBox2;
        private System.Windows.Forms.TextBox textBox3;
        private System.Windows.Forms.TextBox textBox4;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.Button button12;
        private System.Windows.Forms.TextBox textBox5;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.CheckBox RetainCheckBox;
        private System.Windows.Forms.Label label42;
        private System.Windows.Forms.ComboBox QosComboBox;
        private System.Windows.Forms.Label label43;
        private System.Windows.Forms.Label label44;
        private System.Windows.Forms.TextBox PortTextBox;
        private System.Windows.Forms.Button DisconnectButton;
        private System.Windows.Forms.Button ConnectButton;
        private System.Windows.Forms.TextBox HostTextBox;
        private System.Windows.Forms.Label label45;
        private System.Windows.Forms.Button UnsubscribeButton;
        private System.Windows.Forms.Label label46;
        private System.Windows.Forms.ListBox SubListBox;
        private System.Windows.Forms.TextBox PubTopicTextBox;
        private System.Windows.Forms.Label label47;
        private System.Windows.Forms.Button SubscribeButton;
        private System.Windows.Forms.Label label48;
        private System.Windows.Forms.TextBox PubMessageTextBox;
        private System.Windows.Forms.TextBox MessageTextBox;
        private System.Windows.Forms.Button ClearButton;
        private System.Windows.Forms.Button PublishButton;
        private System.Windows.Forms.TextBox SubTopicTextBox;
        private System.Windows.Forms.Label label49;
        private System.Windows.Forms.Timer timer1;
    }
}

