#pragma once

#define SCENE_MODE_MOVE_LIGHT 0
#define SCENE_MODE_COLOR_POS 1
#define SCENE_MODE_MOVE_CUBES 2

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
		static bool moveLight, colorPos, moveCubes, resetLight, resetSuz;
	private: System::Windows::Forms::RadioButton^ radioButton1;
	public:
	private: System::Windows::Forms::RadioButton^ radioButton2;
	private: System::Windows::Forms::RadioButton^ radioButton3;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button2;


		   
	public:
	ToolWindow(void)
	{
		InitializeComponent();
		moveLight = this->radioButton1->Checked;
		colorPos = this->radioButton2->Checked;
		moveCubes = this->radioButton3->Checked;
	}

	static int GetSceneMode()
	{
		if (moveLight)
			return SCENE_MODE_MOVE_LIGHT;
		if (colorPos)
			return SCENE_MODE_COLOR_POS;
		if (moveCubes)
			return SCENE_MODE_MOVE_CUBES;

		return SCENE_MODE_MOVE_LIGHT;
	}

	static bool ConsumeResetLight()
	{
		if (resetLight)
		{
			resetLight = false;
			return true;
		}
		return false;
	}

	static bool ConsumeResetSuzanne()
	{
		if (resetSuz)
		{
			resetSuz = false;
			return true;
		}
		return false;
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
		this->radioButton1->Location = System::Drawing::Point(106, 122);
		this->radioButton1->Name = L"radioButton1";
		this->radioButton1->Size = System::Drawing::Size(190, 36);
		this->radioButton1->TabIndex = 0;
		this->radioButton1->TabStop = true;
		this->radioButton1->Text = L"Move Light";
		this->radioButton1->UseVisualStyleBackColor = true;
		this->radioButton1->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::radioButton1_CheckedChanged);
		// 
		// radioButton2
		// 
		this->radioButton2->AutoSize = true;
		this->radioButton2->Location = System::Drawing::Point(106, 264);
		this->radioButton2->Name = L"radioButton2";
		this->radioButton2->Size = System::Drawing::Size(269, 36);
		this->radioButton2->TabIndex = 1;
		this->radioButton2->TabStop = true;
		this->radioButton2->Text = L"Color By Position";
		this->radioButton2->UseVisualStyleBackColor = true;
		this->radioButton2->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::radioButton2_CheckedChanged);
		// 
		// radioButton3
		// 
		this->radioButton3->AutoSize = true;
		this->radioButton3->Location = System::Drawing::Point(106, 402);
		this->radioButton3->Name = L"radioButton3";
		this->radioButton3->Size = System::Drawing::Size(339, 36);
		this->radioButton3->TabIndex = 2;
		this->radioButton3->TabStop = true;
		this->radioButton3->Text = L"Move Cubes to Sphere";
		this->radioButton3->UseVisualStyleBackColor = true;
		this->radioButton3->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::radioButton3_CheckedChanged);
		// 
		// button1
		// 
		this->button1->Location = System::Drawing::Point(554, 73);
		this->button1->Name = L"button1";
		this->button1->Size = System::Drawing::Size(304, 85);
		this->button1->TabIndex = 3;
		this->button1->Text = L"Reset Light Position";
		this->button1->UseVisualStyleBackColor = true;
		this->button1->Click += gcnew System::EventHandler(this, &ToolWindow::button1_Click);
		// 
		// button2
		// 
		this->button2->Location = System::Drawing::Point(554, 215);
		this->button2->Name = L"button2";
		this->button2->Size = System::Drawing::Size(304, 85);
		this->button2->TabIndex = 4;
		this->button2->Text = L"Reset Suzanne";
		this->button2->UseVisualStyleBackColor = true;
		this->button2->Click += gcnew System::EventHandler(this, &ToolWindow::button2_Click);
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
		this->TopMost = true;
		this->ResumeLayout(false);
		this->PerformLayout();

	}




private: System::Void radioButton1_CheckedChanged(System::Object^ sender, System::EventArgs^ e) 
{
	moveLight = ((RadioButton^)sender)->Checked;
}
private: System::Void radioButton2_CheckedChanged(System::Object^ sender, System::EventArgs^ e) 
{
	colorPos = ((RadioButton^)sender)->Checked;
}
private: System::Void radioButton3_CheckedChanged(System::Object^ sender, System::EventArgs^ e) 
{
	moveCubes = ((RadioButton^)sender)->Checked;
}
private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) 
{
	resetLight = true;
}
private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) 
{
	resetSuz = true;
}
};
}
