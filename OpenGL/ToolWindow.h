﻿#pragma once

namespace OpenGL {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for ToolWindow
	/// </summary>
	public ref class ToolWindow : public System::Windows::Forms::Form
	{
	public:
		static bool RenderRedChannel;
		static bool RenderGreenChannel;
		static bool RenderBlueChannel;
		static float Intensity = 1.0f; // Default to 100%
	private: System::Windows::Forms::RadioButton^ radioButton2;
	public:
	private: System::Windows::Forms::RadioButton^ radioButton3;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button2;





	private: System::Windows::Forms::RadioButton^ radioButton1;


	public:
		ToolWindow(void)
		{
			InitializeComponent();
			RenderRedChannel = checkBoxRedChannel->Checked;
			RenderGreenChannel = checkBoxGreenChannel->Checked;
			RenderBlueChannel = checkBoxBlueChannel->Checked;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ToolWindow()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::ComponentModel::IContainer^ components;

#pragma region Windows Form Designer generated code
	private: System::Void checkBoxRedChannel_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
	{
		RenderRedChannel = checkBoxRedChannel->Checked;
	}
	private: System::Void checkBoxGreenChannel_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
	{
		RenderGreenChannel = checkBoxGreenChannel->Checked;
	}
	private: System::Void checkBoxBlueChannel_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
	{
		RenderBlueChannel = checkBoxBlueChannel->Checked;
	}
	private: System::Void trackBar1_Scroll(System::Object^ sender, System::EventArgs^ e)
	{
		Intensity = trackBar1->Value / 100.0f;
	}
	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
	}


		   void InitializeComponent(void)
		   {
			   this->radioButton1 = (gcnew System::Windows::Forms::RadioButton());
			   this->radioButton2 = (gcnew System::Windows::Forms::RadioButton());
			   this->radioButton3 = (gcnew System::Windows::Forms::RadioButton());
			   this->button1 = (gcnew System::Windows::Forms::Button());
			   this->button2 = (gcnew System::Windows::Forms::Button());
			   this->SuspendLayout();
			   // 
			   // radioButton1
			   // 
			   this->radioButton1->AutoSize = true;
			   this->radioButton1->Location = System::Drawing::Point(93, 97);
			   this->radioButton1->Name = L"radioButton1";
			   this->radioButton1->Size = System::Drawing::Size(190, 36);
			   this->radioButton1->TabIndex = 5;
			   this->radioButton1->TabStop = true;
			   this->radioButton1->Text = L"Move Light";
			   this->radioButton1->UseVisualStyleBackColor = true;
			   this->radioButton1->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::radioButton1_CheckedChanged);
			   // 
			   // radioButton2
			   // 
			   this->radioButton2->AutoSize = true;
			   this->radioButton2->Location = System::Drawing::Point(93, 209);
			   this->radioButton2->Name = L"radioButton2";
			   this->radioButton2->Size = System::Drawing::Size(269, 36);
			   this->radioButton2->TabIndex = 6;
			   this->radioButton2->TabStop = true;
			   this->radioButton2->Text = L"Color By Position";
			   this->radioButton2->UseVisualStyleBackColor = true;
			   // 
			   // radioButton3
			   // 
			   this->radioButton3->AutoSize = true;
			   this->radioButton3->Location = System::Drawing::Point(93, 330);
			   this->radioButton3->Name = L"radioButton3";
			   this->radioButton3->Size = System::Drawing::Size(348, 36);
			   this->radioButton3->TabIndex = 7;
			   this->radioButton3->TabStop = true;
			   this->radioButton3->Text = L"Move Cubes To Sphere";
			   this->radioButton3->UseVisualStyleBackColor = true;
			   // 
			   // button1
			   // 
			   this->button1->Location = System::Drawing::Point(659, 79);
			   this->button1->Name = L"button1";
			   this->button1->Size = System::Drawing::Size(313, 73);
			   this->button1->TabIndex = 8;
			   this->button1->Text = L"Reset Light Position";
			   this->button1->UseVisualStyleBackColor = true;
			   // 
			   // button2
			   // 
			   this->button2->Location = System::Drawing::Point(659, 209);
			   this->button2->Name = L"button2";
			   this->button2->Size = System::Drawing::Size(313, 73);
			   this->button2->TabIndex = 9;
			   this->button2->Text = L"Reset Model";
			   this->button2->UseVisualStyleBackColor = true;
			   // 
			   // ToolWindow
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(16, 31);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->ClientSize = System::Drawing::Size(1132, 905);
			   this->Controls->Add(this->button2);
			   this->Controls->Add(this->button1);
			   this->Controls->Add(this->radioButton3);
			   this->Controls->Add(this->radioButton2);
			   this->Controls->Add(this->radioButton1);
			   this->Margin = System::Windows::Forms::Padding(6);
			   this->Name = L"ToolWindow";
			   this->Text = L"ToolWindow";
			   this->ResumeLayout(false);
			   this->PerformLayout();

		   }


	private: System::Void radioButton1_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	}
};
}