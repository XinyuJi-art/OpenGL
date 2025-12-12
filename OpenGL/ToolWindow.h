#pragma once

#define SCENE_MODE_MOVE_LIGHT 0
#define SCENE_MODE_MOVE_SHIP 1
#define SCENE_MODE_MOVE_FISH 2
#define SCENE_MODE_MOVE_SPACE 3

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
		static bool moveLight, moveShip, moveFishes, resetLight, resetSuz, moveSpace;
		float fighterRotation = 0.0;
	private: System::Windows::Forms::RadioButton^ moveLightButton;
	public:

	private: System::Windows::Forms::RadioButton^ transformButton;
	private: System::Windows::Forms::RadioButton^ waterButton;
	public:


	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TrackBar^ shipRotation;
	private: System::Windows::Forms::TrackBar^ specularStrength;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ R;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::TrackBar^ Rtrack;
	private: System::Windows::Forms::TrackBar^ Gtrack;
	private: System::Windows::Forms::TrackBar^ Btrack;
	private: System::Windows::Forms::CheckBox^ translateButton;
	private: System::Windows::Forms::CheckBox^ rotateButton;
	private: System::Windows::Forms::CheckBox^ scaleButton;



	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::TrackBar^ frequency;
	private: System::Windows::Forms::TrackBar^ amplitude;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::CheckBox^ wireframeButton;

	private: System::Windows::Forms::CheckBox^ tintBlue;

	private: System::Windows::Forms::RadioButton^ spaceButton;

	private: System::Windows::Forms::Button^ button2;


		   
	public:
	ToolWindow(void)
	{
		InitializeComponent();
		moveLight = this->moveLightButton->Checked;
		moveShip = this->transformButton->Checked;
		moveFishes = this->waterButton->Checked;
		moveSpace = this->spaceButton->Checked;
	}

	static int GetSceneMode()
	{
		if (moveLight)
			return SCENE_MODE_MOVE_LIGHT;
		if (moveShip)
			return SCENE_MODE_MOVE_SHIP;
		if (moveFishes)
			return SCENE_MODE_MOVE_FISH;
		if (moveSpace)
			return SCENE_MODE_MOVE_SPACE;

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

	void SetRotationRate(float _rotation)
	{
		fighterRotation = _rotation;
		this->shipRotation->Value = fighterRotation;
		label2->Text = fighterRotation.ToString();
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
		this->moveLightButton = (gcnew System::Windows::Forms::RadioButton());
		this->transformButton = (gcnew System::Windows::Forms::RadioButton());
		this->waterButton = (gcnew System::Windows::Forms::RadioButton());
		this->button1 = (gcnew System::Windows::Forms::Button());
		this->button2 = (gcnew System::Windows::Forms::Button());
		this->label1 = (gcnew System::Windows::Forms::Label());
		this->shipRotation = (gcnew System::Windows::Forms::TrackBar());
		this->specularStrength = (gcnew System::Windows::Forms::TrackBar());
		this->label2 = (gcnew System::Windows::Forms::Label());
		this->label3 = (gcnew System::Windows::Forms::Label());
		this->R = (gcnew System::Windows::Forms::Label());
		this->label4 = (gcnew System::Windows::Forms::Label());
		this->label5 = (gcnew System::Windows::Forms::Label());
		this->Rtrack = (gcnew System::Windows::Forms::TrackBar());
		this->Gtrack = (gcnew System::Windows::Forms::TrackBar());
		this->Btrack = (gcnew System::Windows::Forms::TrackBar());
		this->translateButton = (gcnew System::Windows::Forms::CheckBox());
		this->rotateButton = (gcnew System::Windows::Forms::CheckBox());
		this->scaleButton = (gcnew System::Windows::Forms::CheckBox());
		this->label6 = (gcnew System::Windows::Forms::Label());
		this->frequency = (gcnew System::Windows::Forms::TrackBar());
		this->amplitude = (gcnew System::Windows::Forms::TrackBar());
		this->label7 = (gcnew System::Windows::Forms::Label());
		this->wireframeButton = (gcnew System::Windows::Forms::CheckBox());
		this->tintBlue = (gcnew System::Windows::Forms::CheckBox());
		this->spaceButton = (gcnew System::Windows::Forms::RadioButton());
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->shipRotation))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->specularStrength))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Rtrack))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Gtrack))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Btrack))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->frequency))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->amplitude))->BeginInit();
		this->SuspendLayout();
		// 
		// moveLightButton
		// 
		this->moveLightButton->AutoSize = true;
		this->moveLightButton->Location = System::Drawing::Point(82, 778);
		this->moveLightButton->Name = L"moveLightButton";
		this->moveLightButton->Size = System::Drawing::Size(190, 36);
		this->moveLightButton->TabIndex = 0;
		this->moveLightButton->TabStop = true;
		this->moveLightButton->Text = L"Move Light";
		this->moveLightButton->UseVisualStyleBackColor = true;
		this->moveLightButton->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::radioButton1_CheckedChanged);
		// 
		// transformButton
		// 
		this->transformButton->AutoSize = true;
		this->transformButton->Location = System::Drawing::Point(82, 906);
		this->transformButton->Name = L"transformButton";
		this->transformButton->Size = System::Drawing::Size(179, 36);
		this->transformButton->TabIndex = 1;
		this->transformButton->TabStop = true;
		this->transformButton->Text = L"Transform";
		this->transformButton->UseVisualStyleBackColor = true;
		this->transformButton->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::radioButton2_CheckedChanged);
		// 
		// waterButton
		// 
		this->waterButton->AutoSize = true;
		this->waterButton->Location = System::Drawing::Point(82, 1110);
		this->waterButton->Name = L"waterButton";
		this->waterButton->Size = System::Drawing::Size(214, 36);
		this->waterButton->TabIndex = 2;
		this->waterButton->TabStop = true;
		this->waterButton->Text = L"Water Scene";
		this->waterButton->UseVisualStyleBackColor = true;
		this->waterButton->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::radioButton3_CheckedChanged);
		// 
		// button1
		// 
		this->button1->Location = System::Drawing::Point(324, 754);
		this->button1->Name = L"button1";
		this->button1->Size = System::Drawing::Size(304, 85);
		this->button1->TabIndex = 3;
		this->button1->Text = L"Reset Light Position";
		this->button1->UseVisualStyleBackColor = true;
		this->button1->Click += gcnew System::EventHandler(this, &ToolWindow::button1_Click);
		// 
		// button2
		// 
		this->button2->Location = System::Drawing::Point(82, 986);
		this->button2->Name = L"button2";
		this->button2->Size = System::Drawing::Size(304, 85);
		this->button2->TabIndex = 4;
		this->button2->Text = L"Reset Transform";
		this->button2->UseVisualStyleBackColor = true;
		this->button2->Click += gcnew System::EventHandler(this, &ToolWindow::button2_Click);
		// 
		// label1
		// 
		this->label1->AutoSize = true;
		this->label1->Location = System::Drawing::Point(52, 49);
		this->label1->Name = L"label1";
		this->label1->Size = System::Drawing::Size(253, 32);
		this->label1->TabIndex = 5;
		this->label1->Text = L"Ship Rotation Rate";
		this->label1->Click += gcnew System::EventHandler(this, &ToolWindow::label1_Click);
		// 
		// shipRotation
		// 
		this->shipRotation->Location = System::Drawing::Point(44, 120);
		this->shipRotation->Name = L"shipRotation";
		this->shipRotation->Size = System::Drawing::Size(810, 114);
		this->shipRotation->TabIndex = 7;
		this->shipRotation->Maximum = 10;
		this->shipRotation->TickFrequency = 1;
		this->shipRotation->Scroll += gcnew System::EventHandler(this, &ToolWindow::shipRotation_Scroll);
		// 
		// specularStrength
		// 
		this->specularStrength->Location = System::Drawing::Point(44, 278);
		this->specularStrength->Name = L"specularStrength";
		this->specularStrength->Size = System::Drawing::Size(810, 114);
		this->specularStrength->TabIndex = 8;
		// 
		// label2
		// 
		this->label2->AutoSize = true;
		this->label2->Location = System::Drawing::Point(63, 202);
		this->label2->Name = L"label2";
		this->label2->Size = System::Drawing::Size(242, 32);
		this->label2->TabIndex = 9;
		this->label2->Text = L"Specular Strength";
		// 
		// label3
		// 
		this->label3->AutoSize = true;
		this->label3->Location = System::Drawing::Point(63, 360);
		this->label3->Name = L"label3";
		this->label3->Size = System::Drawing::Size(202, 32);
		this->label3->TabIndex = 10;
		this->label3->Text = L"Specular Color";
		// 
		// R
		// 
		this->R->AutoSize = true;
		this->R->Location = System::Drawing::Point(63, 440);
		this->R->Name = L"R";
		this->R->Size = System::Drawing::Size(34, 32);
		this->R->TabIndex = 11;
		this->R->Text = L"R";
		this->R->TextAlign = System::Drawing::ContentAlignment::TopCenter;
		// 
		// label4
		// 
		this->label4->AutoSize = true;
		this->label4->Location = System::Drawing::Point(87, 538);
		this->label4->Name = L"label4";
		this->label4->Size = System::Drawing::Size(36, 32);
		this->label4->TabIndex = 12;
		this->label4->Text = L"G";
		this->label4->TextAlign = System::Drawing::ContentAlignment::TopCenter;
		// 
		// label5
		// 
		this->label5->AutoSize = true;
		this->label5->Location = System::Drawing::Point(90, 635);
		this->label5->Name = L"label5";
		this->label5->Size = System::Drawing::Size(33, 32);
		this->label5->TabIndex = 13;
		this->label5->Text = L"B";
		this->label5->TextAlign = System::Drawing::ContentAlignment::TopCenter;
		// 
		// Rtrack
		// 
		this->Rtrack->Location = System::Drawing::Point(173, 426);
		this->Rtrack->Name = L"Rtrack";
		this->Rtrack->Size = System::Drawing::Size(810, 114);
		this->Rtrack->TabIndex = 14;
		// 
		// Gtrack
		// 
		this->Gtrack->Location = System::Drawing::Point(173, 524);
		this->Gtrack->Name = L"Gtrack";
		this->Gtrack->Size = System::Drawing::Size(810, 114);
		this->Gtrack->TabIndex = 15;
		// 
		// Btrack
		// 
		this->Btrack->Location = System::Drawing::Point(173, 624);
		this->Btrack->Name = L"Btrack";
		this->Btrack->Size = System::Drawing::Size(810, 114);
		this->Btrack->TabIndex = 16;
		// 
		// translateButton
		// 
		this->translateButton->AutoSize = true;
		this->translateButton->Location = System::Drawing::Point(417, 984);
		this->translateButton->Name = L"translateButton";
		this->translateButton->Size = System::Drawing::Size(171, 36);
		this->translateButton->TabIndex = 17;
		this->translateButton->Text = L"Translate";
		this->translateButton->UseVisualStyleBackColor = true;
		// 
		// rotateButton
		// 
		this->rotateButton->AutoSize = true;
		this->rotateButton->Location = System::Drawing::Point(636, 984);
		this->rotateButton->Name = L"rotateButton";
		this->rotateButton->Size = System::Drawing::Size(136, 36);
		this->rotateButton->TabIndex = 18;
		this->rotateButton->Text = L"Rotate";
		this->rotateButton->UseVisualStyleBackColor = true;
		// 
		// scaleButton
		// 
		this->scaleButton->AutoSize = true;
		this->scaleButton->Location = System::Drawing::Point(859, 986);
		this->scaleButton->Name = L"scaleButton";
		this->scaleButton->Size = System::Drawing::Size(124, 36);
		this->scaleButton->TabIndex = 19;
		this->scaleButton->Text = L"Scale";
		this->scaleButton->UseVisualStyleBackColor = true;
		// 
		// label6
		// 
		this->label6->AutoSize = true;
		this->label6->Location = System::Drawing::Point(90, 1187);
		this->label6->Name = L"label6";
		this->label6->Size = System::Drawing::Size(148, 32);
		this->label6->TabIndex = 20;
		this->label6->Text = L"Frequency";
		// 
		// frequency
		// 
		this->frequency->Location = System::Drawing::Point(96, 1263);
		this->frequency->Name = L"frequency";
		this->frequency->Size = System::Drawing::Size(810, 114);
		this->frequency->TabIndex = 21;
		// 
		// amplitude
		// 
		this->amplitude->Location = System::Drawing::Point(96, 1447);
		this->amplitude->Name = L"amplitude";
		this->amplitude->Size = System::Drawing::Size(810, 114);
		this->amplitude->TabIndex = 22;
		// 
		// label7
		// 
		this->label7->AutoSize = true;
		this->label7->Location = System::Drawing::Point(90, 1364);
		this->label7->Name = L"label7";
		this->label7->Size = System::Drawing::Size(142, 32);
		this->label7->TabIndex = 23;
		this->label7->Text = L"Amplitude";
		// 
		// wireframeButton
		// 
		this->wireframeButton->AutoSize = true;
		this->wireframeButton->Location = System::Drawing::Point(101, 1567);
		this->wireframeButton->Name = L"wireframeButton";
		this->wireframeButton->Size = System::Drawing::Size(282, 36);
		this->wireframeButton->TabIndex = 24;
		this->wireframeButton->Text = L"Wireframe Render";
		this->wireframeButton->UseVisualStyleBackColor = true;
		// 
		// tintBlue
		// 
		this->tintBlue->AutoSize = true;
		this->tintBlue->Location = System::Drawing::Point(516, 1567);
		this->tintBlue->Name = L"tintBlue";
		this->tintBlue->Size = System::Drawing::Size(165, 36);
		this->tintBlue->TabIndex = 25;
		this->tintBlue->Text = L"Tint Blue";
		this->tintBlue->UseVisualStyleBackColor = true;
		// 
		// spaceButton
		// 
		this->spaceButton->AutoSize = true;
		this->spaceButton->Location = System::Drawing::Point(101, 1647);
		this->spaceButton->Name = L"spaceButton";
		this->spaceButton->Size = System::Drawing::Size(220, 36);
		this->spaceButton->TabIndex = 26;
		this->spaceButton->TabStop = true;
		this->spaceButton->Text = L"Space Scene";
		this->spaceButton->UseVisualStyleBackColor = true;
		// 
		// ToolWindow
		// 
		this->AutoScaleDimensions = System::Drawing::SizeF(16, 31);
		this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
		this->ClientSize = System::Drawing::Size(1134, 1853);
		this->Controls->Add(this->spaceButton);
		this->Controls->Add(this->tintBlue);
		this->Controls->Add(this->wireframeButton);
		this->Controls->Add(this->label7);
		this->Controls->Add(this->amplitude);
		this->Controls->Add(this->frequency);
		this->Controls->Add(this->label6);
		this->Controls->Add(this->scaleButton);
		this->Controls->Add(this->rotateButton);
		this->Controls->Add(this->translateButton);
		this->Controls->Add(this->Btrack);
		this->Controls->Add(this->Gtrack);
		this->Controls->Add(this->Rtrack);
		this->Controls->Add(this->label5);
		this->Controls->Add(this->label4);
		this->Controls->Add(this->R);
		this->Controls->Add(this->label3);
		this->Controls->Add(this->label2);
		this->Controls->Add(this->specularStrength);
		this->Controls->Add(this->shipRotation);
		this->Controls->Add(this->label1);
		this->Controls->Add(this->button2);
		this->Controls->Add(this->button1);
		this->Controls->Add(this->waterButton);
		this->Controls->Add(this->transformButton);
		this->Controls->Add(this->moveLightButton);
		this->Margin = System::Windows::Forms::Padding(6);
		this->Name = L"ToolWindow";
		this->Text = L"ToolWindow";
		this->TopMost = true;
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->shipRotation))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->specularStrength))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Rtrack))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Gtrack))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Btrack))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->frequency))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->amplitude))->EndInit();
		this->ResumeLayout(false);
		this->PerformLayout();

	}




private: System::Void radioButton1_CheckedChanged(System::Object^ sender, System::EventArgs^ e) 
{
	moveLight = ((RadioButton^)sender)->Checked;
}
private: System::Void radioButton2_CheckedChanged(System::Object^ sender, System::EventArgs^ e) 
{
	moveShip = ((RadioButton^)sender)->Checked;
}
private: System::Void radioButton3_CheckedChanged(System::Object^ sender, System::EventArgs^ e) 
{
	moveFishes = ((RadioButton^)sender)->Checked;
}
private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) 
{
	resetLight = true;
}
private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) 
{
	resetSuz = true;
}
private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void shipRotation_Scroll(System::Object^ sender, System::EventArgs^ e) {
	fighterRotation = ((TrackBar^)sender)->Value;
	label2->Text = fighterRotation.ToString();
}
};
}
