namespace WindowsFormsApp1
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
        /// <param name="disposing">如果應該處置受控資源則為 true，否則為 false。</param>
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
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.label10 = new System.Windows.Forms.Label();
            this.RetainCheckBox = new System.Windows.Forms.CheckBox();
            this.label9 = new System.Windows.Forms.Label();
            this.UnsubscribeButton = new System.Windows.Forms.Button();
            this.label8 = new System.Windows.Forms.Label();
            this.SubListBox = new System.Windows.Forms.ListBox();
            this.QosComboBox = new System.Windows.Forms.ComboBox();
            this.label7 = new System.Windows.Forms.Label();
            this.PubTopicTextBox = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.SubscribeButton = new System.Windows.Forms.Button();
            this.label5 = new System.Windows.Forms.Label();
            this.PortTextBox = new System.Windows.Forms.TextBox();
            this.DisconnectButton = new System.Windows.Forms.Button();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.PubMessageTextBox = new System.Windows.Forms.TextBox();
            this.MessageTextBox = new System.Windows.Forms.TextBox();
            this.ClearButton = new System.Windows.Forms.Button();
            this.ConnectButton = new System.Windows.Forms.Button();
            this.PublishButton = new System.Windows.Forms.Button();
            this.SubTopicTextBox = new System.Windows.Forms.TextBox();
            this.HostTextBox = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // textBox1
            // 
            this.textBox1.Font = new System.Drawing.Font("微軟正黑體", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.textBox1.Location = new System.Drawing.Point(339, 3);
            this.textBox1.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.textBox1.MaxLength = 128;
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(140, 23);
            this.textBox1.TabIndex = 50;
            this.textBox1.Text = "6CEBA1Z32VVWZ9VP";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Font = new System.Drawing.Font("微軟正黑體", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.label10.Location = new System.Drawing.Point(249, 3);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(84, 19);
            this.label10.TabIndex = 49;
            this.label10.Text = "MQTT KEY:";
            // 
            // RetainCheckBox
            // 
            this.RetainCheckBox.AutoSize = true;
            this.RetainCheckBox.Location = new System.Drawing.Point(420, 45);
            this.RetainCheckBox.Name = "RetainCheckBox";
            this.RetainCheckBox.Size = new System.Drawing.Size(15, 14);
            this.RetainCheckBox.TabIndex = 48;
            this.RetainCheckBox.UseVisualStyleBackColor = true;
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Font = new System.Drawing.Font("微軟正黑體", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.label9.Location = new System.Drawing.Point(358, 41);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(56, 19);
            this.label9.TabIndex = 47;
            this.label9.Text = "Retain:";
            // 
            // UnsubscribeButton
            // 
            this.UnsubscribeButton.Enabled = false;
            this.UnsubscribeButton.Font = new System.Drawing.Font("微軟正黑體", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.UnsubscribeButton.Location = new System.Drawing.Point(591, 624);
            this.UnsubscribeButton.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.UnsubscribeButton.Name = "UnsubscribeButton";
            this.UnsubscribeButton.Size = new System.Drawing.Size(186, 31);
            this.UnsubscribeButton.TabIndex = 46;
            this.UnsubscribeButton.Text = "Unsubscribe";
            this.UnsubscribeButton.UseVisualStyleBackColor = true;
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Font = new System.Drawing.Font("微軟正黑體", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.label8.Location = new System.Drawing.Point(587, 4);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(144, 19);
            this.label8.TabIndex = 45;
            this.label8.Text = "Subscriptions topic:";
            // 
            // SubListBox
            // 
            this.SubListBox.Font = new System.Drawing.Font("微軟正黑體", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.SubListBox.FormattingEnabled = true;
            this.SubListBox.HorizontalScrollbar = true;
            this.SubListBox.ItemHeight = 16;
            this.SubListBox.Location = new System.Drawing.Point(591, 32);
            this.SubListBox.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.SubListBox.Name = "SubListBox";
            this.SubListBox.ScrollAlwaysVisible = true;
            this.SubListBox.Size = new System.Drawing.Size(186, 580);
            this.SubListBox.TabIndex = 44;
            // 
            // QosComboBox
            // 
            this.QosComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.QosComboBox.FormattingEnabled = true;
            this.QosComboBox.Items.AddRange(new object[] {
            "0 At most once",
            "1 At least once",
            "2 Exactly once"});
            this.QosComboBox.Location = new System.Drawing.Point(249, 40);
            this.QosComboBox.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.QosComboBox.MaxDropDownItems = 3;
            this.QosComboBox.Name = "QosComboBox";
            this.QosComboBox.Size = new System.Drawing.Size(92, 20);
            this.QosComboBox.TabIndex = 43;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Font = new System.Drawing.Font("微軟正黑體", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.label7.Location = new System.Drawing.Point(201, 44);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(42, 19);
            this.label7.TabIndex = 42;
            this.label7.Text = "QoS:";
            // 
            // PubTopicTextBox
            // 
            this.PubTopicTextBox.Font = new System.Drawing.Font("微軟正黑體", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.PubTopicTextBox.Location = new System.Drawing.Point(130, 117);
            this.PubTopicTextBox.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.PubTopicTextBox.MaxLength = 128;
            this.PubTopicTextBox.Name = "PubTopicTextBox";
            this.PubTopicTextBox.Size = new System.Drawing.Size(448, 23);
            this.PubTopicTextBox.TabIndex = 41;
            this.PubTopicTextBox.Text = "channels/509870/publish/K3XEE6AWQ7R2NZ5W";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Font = new System.Drawing.Font("微軟正黑體", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.label6.Location = new System.Drawing.Point(17, 117);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(104, 19);
            this.label6.TabIndex = 40;
            this.label6.Text = "Topic for pub:";
            // 
            // SubscribeButton
            // 
            this.SubscribeButton.Enabled = false;
            this.SubscribeButton.Font = new System.Drawing.Font("微軟正黑體", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.SubscribeButton.Location = new System.Drawing.Point(469, 80);
            this.SubscribeButton.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.SubscribeButton.Name = "SubscribeButton";
            this.SubscribeButton.Size = new System.Drawing.Size(110, 31);
            this.SubscribeButton.TabIndex = 31;
            this.SubscribeButton.Text = "Subscribe";
            this.SubscribeButton.UseVisualStyleBackColor = true;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("微軟正黑體", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.label5.Location = new System.Drawing.Point(80, 44);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(41, 19);
            this.label5.TabIndex = 39;
            this.label5.Text = "Port:";
            // 
            // PortTextBox
            // 
            this.PortTextBox.Location = new System.Drawing.Point(130, 41);
            this.PortTextBox.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.PortTextBox.MaxLength = 4;
            this.PortTextBox.Name = "PortTextBox";
            this.PortTextBox.Size = new System.Drawing.Size(52, 22);
            this.PortTextBox.TabIndex = 28;
            this.PortTextBox.Text = "1883";
            // 
            // DisconnectButton
            // 
            this.DisconnectButton.Enabled = false;
            this.DisconnectButton.Font = new System.Drawing.Font("微軟正黑體", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.DisconnectButton.Location = new System.Drawing.Point(469, 39);
            this.DisconnectButton.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.DisconnectButton.Name = "DisconnectButton";
            this.DisconnectButton.Size = new System.Drawing.Size(110, 31);
            this.DisconnectButton.TabIndex = 38;
            this.DisconnectButton.Text = "Disconnect";
            this.DisconnectButton.UseVisualStyleBackColor = true;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("微軟正黑體", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.label4.ForeColor = System.Drawing.Color.Red;
            this.label4.Location = new System.Drawing.Point(19, 660);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(0, 19);
            this.label4.TabIndex = 36;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("微軟正黑體", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.label3.Location = new System.Drawing.Point(47, 155);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(74, 19);
            this.label3.TabIndex = 34;
            this.label3.Text = "Message:";
            // 
            // PubMessageTextBox
            // 
            this.PubMessageTextBox.Font = new System.Drawing.Font("微軟正黑體", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.PubMessageTextBox.Location = new System.Drawing.Point(130, 155);
            this.PubMessageTextBox.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.PubMessageTextBox.MaxLength = 128;
            this.PubMessageTextBox.Name = "PubMessageTextBox";
            this.PubMessageTextBox.Size = new System.Drawing.Size(448, 23);
            this.PubMessageTextBox.TabIndex = 32;
            this.PubMessageTextBox.Text = "field1=100&status=MQTTPUBLISH";
            // 
            // MessageTextBox
            // 
            this.MessageTextBox.Font = new System.Drawing.Font("微軟正黑體", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.MessageTextBox.Location = new System.Drawing.Point(18, 231);
            this.MessageTextBox.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.MessageTextBox.Multiline = true;
            this.MessageTextBox.Name = "MessageTextBox";
            this.MessageTextBox.ReadOnly = true;
            this.MessageTextBox.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.MessageTextBox.Size = new System.Drawing.Size(558, 381);
            this.MessageTextBox.TabIndex = 37;
            // 
            // ClearButton
            // 
            this.ClearButton.Font = new System.Drawing.Font("微軟正黑體", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.ClearButton.Location = new System.Drawing.Point(18, 624);
            this.ClearButton.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.ClearButton.Name = "ClearButton";
            this.ClearButton.Size = new System.Drawing.Size(559, 31);
            this.ClearButton.TabIndex = 35;
            this.ClearButton.Text = "Clear";
            this.ClearButton.UseVisualStyleBackColor = true;
            // 
            // ConnectButton
            // 
            this.ConnectButton.Font = new System.Drawing.Font("微軟正黑體", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.ConnectButton.Location = new System.Drawing.Point(510, 4);
            this.ConnectButton.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.ConnectButton.Name = "ConnectButton";
            this.ConnectButton.Size = new System.Drawing.Size(68, 31);
            this.ConnectButton.TabIndex = 29;
            this.ConnectButton.Text = "Connect";
            this.ConnectButton.UseVisualStyleBackColor = true;
            // 
            // PublishButton
            // 
            this.PublishButton.Enabled = false;
            this.PublishButton.Font = new System.Drawing.Font("微軟正黑體", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.PublishButton.Location = new System.Drawing.Point(24, 189);
            this.PublishButton.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.PublishButton.Name = "PublishButton";
            this.PublishButton.Size = new System.Drawing.Size(555, 31);
            this.PublishButton.TabIndex = 33;
            this.PublishButton.Text = "Publish";
            this.PublishButton.UseVisualStyleBackColor = true;
            // 
            // SubTopicTextBox
            // 
            this.SubTopicTextBox.Font = new System.Drawing.Font("微軟正黑體", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.SubTopicTextBox.Location = new System.Drawing.Point(130, 80);
            this.SubTopicTextBox.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.SubTopicTextBox.MaxLength = 128;
            this.SubTopicTextBox.Name = "SubTopicTextBox";
            this.SubTopicTextBox.Size = new System.Drawing.Size(332, 23);
            this.SubTopicTextBox.TabIndex = 30;
            this.SubTopicTextBox.Text = "channels/509870/subscribe/json";
            // 
            // HostTextBox
            // 
            this.HostTextBox.Font = new System.Drawing.Font("微軟正黑體", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.HostTextBox.Location = new System.Drawing.Point(130, 3);
            this.HostTextBox.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.HostTextBox.MaxLength = 128;
            this.HostTextBox.Name = "HostTextBox";
            this.HostTextBox.Size = new System.Drawing.Size(113, 23);
            this.HostTextBox.TabIndex = 27;
            this.HostTextBox.Text = "embpcb.com";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("微軟正黑體", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.label2.Location = new System.Drawing.Point(19, 80);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(102, 19);
            this.label2.TabIndex = 26;
            this.label2.Text = "Topic for sub:";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("微軟正黑體", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.label1.Location = new System.Drawing.Point(77, 4);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(44, 19);
            this.label1.TabIndex = 25;
            this.label1.Text = "Host:";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(780, 669);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.RetainCheckBox);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.UnsubscribeButton);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.SubListBox);
            this.Controls.Add(this.QosComboBox);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.PubTopicTextBox);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.SubscribeButton);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.PortTextBox);
            this.Controls.Add(this.DisconnectButton);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.PubMessageTextBox);
            this.Controls.Add(this.MessageTextBox);
            this.Controls.Add(this.ClearButton);
            this.Controls.Add(this.ConnectButton);
            this.Controls.Add(this.PublishButton);
            this.Controls.Add(this.SubTopicTextBox);
            this.Controls.Add(this.HostTextBox);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.CheckBox RetainCheckBox;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Button UnsubscribeButton;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.ListBox SubListBox;
        private System.Windows.Forms.ComboBox QosComboBox;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.TextBox PubTopicTextBox;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Button SubscribeButton;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox PortTextBox;
        private System.Windows.Forms.Button DisconnectButton;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox PubMessageTextBox;
        private System.Windows.Forms.TextBox MessageTextBox;
        private System.Windows.Forms.Button ClearButton;
        private System.Windows.Forms.Button ConnectButton;
        private System.Windows.Forms.Button PublishButton;
        private System.Windows.Forms.TextBox SubTopicTextBox;
        private System.Windows.Forms.TextBox HostTextBox;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
    }
}

