/**
	iBreak by Domisy
	Code by Theo Mavrakis
	Copyright 2011
	DO NOT REPRODUCE
**/


#pragma once
#include <string>


namespace FormsTest {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace Ionic::Zip;
	using namespace System :: Diagnostics;

	/// <summary>
	/// The GUI for iBreak, the jailbreak toolkit for all iOS devices.
	/// </summary>



	
/////////////////GLOBAL VARIABLES////////////////////////////////
	int progress(0);
	int exePathSwitch(0);
		
////////////////////////////////////////////////////////////////



	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//	
			
		}



//////////////////////////////////////////////////////BEGIN CUSTOM FUNCTIONS/////////////////////////////////////////////////////////////////////////



		// Turns next button off every time panel is advanced.
	public:
		int nextActivateFunc(bool nextActivate) {
		nextButton->Enabled = nextActivate;
		return 0;
		}


		//Clears all the selections when user goes back to welcome screen.
	public:
		void clearEntries() {
			prompt1choice1->Checked = false;
			prompt1choice2->Checked = false;
			prompt1choice3->Checked = false;
			prompt2choice1->Checked = false;
			prompt2choice2->Checked = false;
			prompt2choice3->Checked = false;
			prompt3->Visible = false;
			tetheringText1->Visible = false;
			tetheringText2->Visible = false;
			unlockedText1->Visible = false;
			unlockedText2->Visible = false;
			unlockedText3->Visible = false;
			unlockedDropdown->SelectedIndex = -1;
			}
	public:
		void clearInform() {
			tetheringText1->Visible = false;
			tetheringText2->Visible = false;
			unlockedText1->Visible = false;
			unlockedText2->Visible = false;
			unlockedText3->Visible = false;
			walkthroughText1->Visible = true;
			walkthroughText2->Visible = true;
			walkthroughText3->Visible = true;
			walkthroughText4->Visible = true;
		}
		

		
		//Determines which tool to select for the user.
	public:
		
		int jbTool() {

			
			if (prompt1choice1->Checked == true) {
				if (prompt2choice1->Checked == true) { tool(1); }
		
				else if (prompt2choice2->Checked == true) {
					if (unlockedDropdown->SelectedIndex == 0) { tool(2); } 
					else if (unlockedDropdown->SelectedIndex == 1) { tool(4); } } // find out if yes or no is selected
					
				else if (prompt2choice3->Checked == true) {
					if (unlockedDropdown->SelectedIndex == 0) { tool(3); } 
					else if (unlockedDropdown->SelectedIndex == 1) { tool(4); } }
			}

			else if (prompt1choice2->Checked == true) {
				if (prompt2choice1->Checked == true) { tool(1); }
				else if (prompt2choice2->Checked == true) { tool(2); }
				else if (prompt2choice3->Checked == true) { tool(3); } 
			}

			else if (prompt1choice3->Checked == true) {
				if (prompt2choice1->Checked == true) { tool(1); }
				else if (prompt2choice2->Checked == true) { tool(2); }
				else if (prompt2choice3->Checked == true) { tool(3); } 
			}
			return 0;
			}




		//Here is where using the info obtained above, the switch statement sends the correct tool path to be extracted.
	public:
		int tool(int jbTool) {

			switch(jbTool) {
				case 1:
					tetheringText2->Visible = true;
					unlockedText3->Visible = true;
					unzip("\\iBreak\\resources\\greenpois0n.zip");
					exePathSwitch = 1;
					break;
				case 2:
					tetheringText2->Visible = true;
					unlockedText3->Visible = true;
					unzip("\\iBreak\\resources\\redsn0w.zip");
					exePathSwitch = 2;
					break;
				case 3:
					tetheringText1->Visible = true;
					unlockedText3->Visible = true;
					unzip("\\iBreak\\resources\\redsn0w_beta.zip");
					exePathSwitch = 3;
					break;
				case 4:
					tetheringText1->Visible = true;
					unlockedText2->Visible = true;
					unzip("\\iBreak\\resources\\sn0wbreeze.zip");
					exePathSwitch = 4;
					break;
				default:
					//something here..
					break;
			}
		return 0;
		}




		// Unzip proper jailbreak tool from AppData folder on user's computer.  
	public:
		void unzip(const System::String^ toolPath) {
		

		System::String^ appdataPath = Environment::GetEnvironmentVariable("APPDATA");
		System::String^ zipPath = appdataPath + toolPath;
		System::String^ pPath = appdataPath + "\\iBreak";
		
		
		ZipFile ^ zip;

		try {
			zip = gcnew ZipFile(zipPath);
			zip->ExtractAll(pPath, ExtractExistingFileAction::OverwriteSilently);
		}
		finally
		{
			delete zip;	
		}
		//return 0;
		}	




		//Function called to execute the tool selected by the user. 
	public:
		void executeTool() {
			System::String^ appdataPath = Environment::GetEnvironmentVariable("APPDATA");
			System::String^ greenpExePath = appdataPath + "\\iBreak\\greenpois0n.exe";
			System::String^ redsn0wExePath = appdataPath + "\\iBreak\\redsn0w.exe";
			System::String^ redsn0w_betaExePath = appdataPath + "\\iBreak\\redsn0w_beta.exe";
			System::String^ sn0wbreezeExePath = appdataPath + "\\iBreak\\sn0wbreeze.exe";
			System::String^ ExePath;

			switch(exePathSwitch) {
				case 1:
					ExePath = greenpExePath;
					walkthroughText1->Visible = true;
					break;
				case 2:
					ExePath = redsn0wExePath;
					walkthroughText2->Visible = true;
					break;
				case 3:
					ExePath = redsn0w_betaExePath;
					walkthroughText3->Visible = true;
					break;
				case 4:
					ExePath = sn0wbreezeExePath;
					walkthroughText4->Visible = true;
					break;
				default:
					break;
			}
					ProcessStartInfo ^psi = gcnew ProcessStartInfo(ExePath);
					Process ^pcs = Process:: Start(psi);

			/** Code to convert System::String^ to const char, using namespace System::Runtime::InteropServices;
	IntPtr p = Marshal::StringToHGlobalAnsi(greenpExePath); 
	const char* greenpExePathStr = static_cast<char*>(p.ToPointer()); 
	Marshal::FreeHGlobal(p); 
**/
			}
			
		

///////////////////////////////////////////////////////////////END OF CUSTOM FUNCTIONS///////////////////////////////////////////////////////////////



	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  backButton;
	protected: 
	public: System::Windows::Forms::Button^  nextButton;
	private: 
	private: System::Windows::Forms::Button^  cancelButton;
	public: 
	private: System::Windows::Forms::Panel^  panelWelcome;
	private: System::Windows::Forms::Panel^  panelStep1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Panel^  panel3;
	private: System::Windows::Forms::GroupBox^  prompt3;
	private: System::Windows::Forms::ComboBox^  unlockedDropdown;
	private: System::Windows::Forms::GroupBox^  prompt2;
	private: System::Windows::Forms::RadioButton^  prompt2choice1;

	private: System::Windows::Forms::RadioButton^  prompt2choice3;
	private: System::Windows::Forms::RadioButton^  prompt2choice2;



	private: System::Windows::Forms::GroupBox^  prompt1;
	private: System::Windows::Forms::RadioButton^  prompt1choice1;
	private: System::Windows::Forms::RadioButton^  prompt1choice2;
	private: System::Windows::Forms::RadioButton^  prompt1choice3;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  welcomeLabel;
	private: System::Windows::Forms::RichTextBox^  welcomeText;
	private: System::Windows::Forms::Panel^  panelStep2;
	private: System::Windows::Forms::Panel^  panelStep3;

	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Label^  panelStep3Title;
	private: System::Windows::Forms::CheckBox^  understandingCheck;
	private: System::Windows::Forms::GroupBox^  groupBox2;
private: System::Windows::Forms::TextBox^  unlockedText3;

	private: System::Windows::Forms::TextBox^  unlockedText1;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::TextBox^  tetheringText2;
	private: System::Windows::Forms::TextBox^  tetheringText1;
	private: System::Windows::Forms::Label^  step2Label;
	private: System::Windows::Forms::ListView^  listView1;
	private: System::Windows::Forms::ProgressBar^  progressBar;

	private: System::Windows::Forms::Label^  stepLabel1;
	private: System::Windows::Forms::Label^  stepLabel2;
	private: System::Windows::Forms::Label^  stepLabel3;
	private: System::Windows::Forms::Label^  stepLabel4;
	private: System::Windows::Forms::Label^  stepLabel5;
	private: System::Windows::Forms::PictureBox^  check1;
	private: System::Windows::Forms::PictureBox^  check5;
	private: System::Windows::Forms::PictureBox^  check4;
	private: System::Windows::Forms::PictureBox^  check3;
	private: System::Windows::Forms::PictureBox^  check2;
	private: System::Windows::Forms::Label^  labelWelcome;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::SplitContainer^  splitContainer1;
	private: Microsoft::VisualBasic::PowerPacks::ShapeContainer^  shapeContainer2;
	private: Microsoft::VisualBasic::PowerPacks::LineShape^  lineShape1;

private: System::Windows::Forms::TextBox^  unlockedText2;
private: System::Windows::Forms::Panel^  panelStep4;
private: System::Windows::Forms::TextBox^  walkthroughText1;
private: System::Windows::Forms::Label^  panelStep4_Title;
private: System::Windows::Forms::TextBox^  walkthroughText3;
private: System::Windows::Forms::TextBox^  walkthroughText2;
private: System::Windows::Forms::TextBox^  walkthroughText4;
private: System::Windows::Forms::Panel^  panelFinish;
private: System::Windows::Forms::TextBox^  textBox2;
private: System::Windows::Forms::Label^  label1;
private: System::Windows::Forms::TextBox^  textBox1;
private: System::Windows::Forms::Label^  panelFinish_Title;


	private: 




private: System::ComponentModel::IContainer^  components;



	protected: 

	protected: 



	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->backButton = (gcnew System::Windows::Forms::Button());
			this->nextButton = (gcnew System::Windows::Forms::Button());
			this->cancelButton = (gcnew System::Windows::Forms::Button());
			this->panelWelcome = (gcnew System::Windows::Forms::Panel());
			this->panelStep1 = (gcnew System::Windows::Forms::Panel());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->panel3 = (gcnew System::Windows::Forms::Panel());
			this->prompt3 = (gcnew System::Windows::Forms::GroupBox());
			this->unlockedDropdown = (gcnew System::Windows::Forms::ComboBox());
			this->prompt2 = (gcnew System::Windows::Forms::GroupBox());
			this->prompt2choice1 = (gcnew System::Windows::Forms::RadioButton());
			this->prompt2choice3 = (gcnew System::Windows::Forms::RadioButton());
			this->prompt2choice2 = (gcnew System::Windows::Forms::RadioButton());
			this->prompt1 = (gcnew System::Windows::Forms::GroupBox());
			this->prompt1choice1 = (gcnew System::Windows::Forms::RadioButton());
			this->prompt1choice2 = (gcnew System::Windows::Forms::RadioButton());
			this->prompt1choice3 = (gcnew System::Windows::Forms::RadioButton());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->welcomeLabel = (gcnew System::Windows::Forms::Label());
			this->welcomeText = (gcnew System::Windows::Forms::RichTextBox());
			this->panelStep2 = (gcnew System::Windows::Forms::Panel());
			this->panelStep3 = (gcnew System::Windows::Forms::Panel());
			this->panelStep4 = (gcnew System::Windows::Forms::Panel());
			this->walkthroughText3 = (gcnew System::Windows::Forms::TextBox());
			this->walkthroughText2 = (gcnew System::Windows::Forms::TextBox());
			this->walkthroughText1 = (gcnew System::Windows::Forms::TextBox());
			this->panelStep4_Title = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->panelStep3Title = (gcnew System::Windows::Forms::Label());
			this->understandingCheck = (gcnew System::Windows::Forms::CheckBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->unlockedText2 = (gcnew System::Windows::Forms::TextBox());
			this->unlockedText3 = (gcnew System::Windows::Forms::TextBox());
			this->unlockedText1 = (gcnew System::Windows::Forms::TextBox());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->tetheringText2 = (gcnew System::Windows::Forms::TextBox());
			this->tetheringText1 = (gcnew System::Windows::Forms::TextBox());
			this->step2Label = (gcnew System::Windows::Forms::Label());
			this->listView1 = (gcnew System::Windows::Forms::ListView());
			this->progressBar = (gcnew System::Windows::Forms::ProgressBar());
			this->stepLabel1 = (gcnew System::Windows::Forms::Label());
			this->stepLabel2 = (gcnew System::Windows::Forms::Label());
			this->stepLabel3 = (gcnew System::Windows::Forms::Label());
			this->stepLabel4 = (gcnew System::Windows::Forms::Label());
			this->stepLabel5 = (gcnew System::Windows::Forms::Label());
			this->check1 = (gcnew System::Windows::Forms::PictureBox());
			this->check5 = (gcnew System::Windows::Forms::PictureBox());
			this->check4 = (gcnew System::Windows::Forms::PictureBox());
			this->check3 = (gcnew System::Windows::Forms::PictureBox());
			this->check2 = (gcnew System::Windows::Forms::PictureBox());
			this->labelWelcome = (gcnew System::Windows::Forms::Label());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->splitContainer1 = (gcnew System::Windows::Forms::SplitContainer());
			this->shapeContainer2 = (gcnew Microsoft::VisualBasic::PowerPacks::ShapeContainer());
			this->lineShape1 = (gcnew Microsoft::VisualBasic::PowerPacks::LineShape());
			this->walkthroughText4 = (gcnew System::Windows::Forms::TextBox());
			this->panelFinish = (gcnew System::Windows::Forms::Panel());
			this->panelFinish_Title = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->panelWelcome->SuspendLayout();
			this->panelStep1->SuspendLayout();
			this->panel3->SuspendLayout();
			this->prompt3->SuspendLayout();
			this->prompt2->SuspendLayout();
			this->prompt1->SuspendLayout();
			this->panelStep2->SuspendLayout();
			this->panelStep3->SuspendLayout();
			this->panelStep4->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->groupBox1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->check1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->check5))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->check4))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->check3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->check2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->splitContainer1))->BeginInit();
			this->splitContainer1->Panel1->SuspendLayout();
			this->splitContainer1->Panel2->SuspendLayout();
			this->splitContainer1->SuspendLayout();
			this->panelFinish->SuspendLayout();
			this->SuspendLayout();
			// 
			// backButton
			// 
			this->backButton->Enabled = false;
			this->backButton->Location = System::Drawing::Point(115, 333);
			this->backButton->Name = L"backButton";
			this->backButton->Size = System::Drawing::Size(60, 23);
			this->backButton->TabIndex = 2;
			this->backButton->Text = L"<-back";
			this->backButton->UseVisualStyleBackColor = true;
			this->backButton->Click += gcnew System::EventHandler(this, &Form1::button1_Click_1);
			// 
			// nextButton
			// 
			this->nextButton->Location = System::Drawing::Point(181, 333);
			this->nextButton->Name = L"nextButton";
			this->nextButton->Size = System::Drawing::Size(60, 23);
			this->nextButton->TabIndex = 3;
			this->nextButton->Text = L"Next->";
			this->nextButton->UseVisualStyleBackColor = true;
			this->nextButton->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// cancelButton
			// 
			this->cancelButton->Location = System::Drawing::Point(260, 333);
			this->cancelButton->Name = L"cancelButton";
			this->cancelButton->Size = System::Drawing::Size(60, 23);
			this->cancelButton->TabIndex = 4;
			this->cancelButton->Text = L"Cancel";
			this->cancelButton->UseVisualStyleBackColor = true;
			this->cancelButton->Click += gcnew System::EventHandler(this, &Form1::button3_Click);
			// 
			// panelWelcome
			// 
			this->panelWelcome->BackColor = System::Drawing::SystemColors::Control;
			this->panelWelcome->Controls->Add(this->panelStep1);
			this->panelWelcome->Controls->Add(this->welcomeLabel);
			this->panelWelcome->Controls->Add(this->welcomeText);
			this->panelWelcome->Location = System::Drawing::Point(3, 3);
			this->panelWelcome->Name = L"panelWelcome";
			this->panelWelcome->Size = System::Drawing::Size(326, 324);
			this->panelWelcome->TabIndex = 8;
			// 
			// panelStep1
			// 
			this->panelStep1->BackColor = System::Drawing::SystemColors::Control;
			this->panelStep1->Controls->Add(this->label2);
			this->panelStep1->Controls->Add(this->panel3);
			this->panelStep1->Location = System::Drawing::Point(0, 0);
			this->panelStep1->Name = L"panelStep1";
			this->panelStep1->Size = System::Drawing::Size(326, 324);
			this->panelStep1->TabIndex = 7;
			this->panelStep1->Visible = false;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label2->ForeColor = System::Drawing::SystemColors::HotTrack;
			this->label2->Location = System::Drawing::Point(8, 12);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(147, 17);
			this->label2->TabIndex = 0;
			this->label2->Text = L"Let\'s Get Started...";
			// 
			// panel3
			// 
			this->panel3->Controls->Add(this->prompt3);
			this->panel3->Controls->Add(this->prompt2);
			this->panel3->Controls->Add(this->prompt1);
			this->panel3->Controls->Add(this->label3);
			this->panel3->Location = System::Drawing::Point(11, 38);
			this->panel3->Name = L"panel3";
			this->panel3->Size = System::Drawing::Size(299, 283);
			this->panel3->TabIndex = 1;
			// 
			// prompt3
			// 
			this->prompt3->Controls->Add(this->unlockedDropdown);
			this->prompt3->Location = System::Drawing::Point(9, 202);
			this->prompt3->Name = L"prompt3";
			this->prompt3->Size = System::Drawing::Size(243, 59);
			this->prompt3->TabIndex = 12;
			this->prompt3->TabStop = false;
			this->prompt3->Text = L"Is Your Device Unlocked\?";
			this->prompt3->Visible = false;
			// 
			// unlockedDropdown
			// 
			this->unlockedDropdown->FormattingEnabled = true;
			this->unlockedDropdown->Items->AddRange(gcnew cli::array< System::Object^  >(2) {L"no", L"yes"});
			this->unlockedDropdown->Location = System::Drawing::Point(6, 27);
			this->unlockedDropdown->Name = L"unlockedDropdown";
			this->unlockedDropdown->Size = System::Drawing::Size(93, 21);
			this->unlockedDropdown->TabIndex = 11;
			this->unlockedDropdown->Text = L"Select One";
			this->unlockedDropdown->SelectionChangeCommitted += gcnew System::EventHandler(this, &Form1::unlockedDropdown_SelectionChangeCommitted);
			// 
			// prompt2
			// 
			this->prompt2->Controls->Add(this->prompt2choice1);
			this->prompt2->Controls->Add(this->prompt2choice3);
			this->prompt2->Controls->Add(this->prompt2choice2);
			this->prompt2->Location = System::Drawing::Point(9, 103);
			this->prompt2->Name = L"prompt2";
			this->prompt2->Size = System::Drawing::Size(243, 93);
			this->prompt2->TabIndex = 10;
			this->prompt2->TabStop = false;
			this->prompt2->Text = L"Select Your Firmware";
			this->prompt2->Visible = false;
			this->prompt2->Enter += gcnew System::EventHandler(this, &Form1::prompt2_Enter);
			// 
			// prompt2choice1
			// 
			this->prompt2choice1->AutoSize = true;
			this->prompt2choice1->Location = System::Drawing::Point(6, 19);
			this->prompt2choice1->Name = L"prompt2choice1";
			this->prompt2choice1->Size = System::Drawing::Size(69, 17);
			this->prompt2choice1->TabIndex = 2;
			this->prompt2choice1->TabStop = true;
			this->prompt2choice1->Text = L"iOS 4.2.1";
			this->prompt2choice1->UseVisualStyleBackColor = true;
			this->prompt2choice1->CheckedChanged += gcnew System::EventHandler(this, &Form1::prompt2choice1_CheckedChanged);
			// 
			// prompt2choice3
			// 
			this->prompt2choice3->AutoSize = true;
			this->prompt2choice3->Location = System::Drawing::Point(6, 65);
			this->prompt2choice3->Name = L"prompt2choice3";
			this->prompt2choice3->Size = System::Drawing::Size(60, 17);
			this->prompt2choice3->TabIndex = 1;
			this->prompt2choice3->TabStop = true;
			this->prompt2choice3->Text = L"iOS 5.0";
			this->prompt2choice3->UseVisualStyleBackColor = true;
			this->prompt2choice3->CheckedChanged += gcnew System::EventHandler(this, &Form1::prompt2choice3_CheckedChanged);
			// 
			// prompt2choice2
			// 
			this->prompt2choice2->AutoSize = true;
			this->prompt2choice2->Location = System::Drawing::Point(6, 42);
			this->prompt2choice2->Name = L"prompt2choice2";
			this->prompt2choice2->Size = System::Drawing::Size(96, 17);
			this->prompt2choice2->TabIndex = 0;
			this->prompt2choice2->TabStop = true;
			this->prompt2choice2->Text = L"iOS 4.3.3-4.3.5";
			this->prompt2choice2->UseVisualStyleBackColor = true;
			this->prompt2choice2->CheckedChanged += gcnew System::EventHandler(this, &Form1::prompt2choice2_CheckedChanged);
			// 
			// prompt1
			// 
			this->prompt1->Controls->Add(this->prompt1choice1);
			this->prompt1->Controls->Add(this->prompt1choice2);
			this->prompt1->Controls->Add(this->prompt1choice3);
			this->prompt1->Location = System::Drawing::Point(9, 3);
			this->prompt1->Name = L"prompt1";
			this->prompt1->Size = System::Drawing::Size(243, 94);
			this->prompt1->TabIndex = 9;
			this->prompt1->TabStop = false;
			this->prompt1->Text = L"Select Your Device";
			// 
			// prompt1choice1
			// 
			this->prompt1choice1->AutoSize = true;
			this->prompt1choice1->Location = System::Drawing::Point(6, 19);
			this->prompt1choice1->Name = L"prompt1choice1";
			this->prompt1choice1->Size = System::Drawing::Size(93, 17);
			this->prompt1choice1->TabIndex = 4;
			this->prompt1choice1->TabStop = true;
			this->prompt1choice1->Text = L"iPhone 3GS/4";
			this->prompt1choice1->UseVisualStyleBackColor = true;
			this->prompt1choice1->CheckedChanged += gcnew System::EventHandler(this, &Form1::prompt1choice1_CheckedChanged);
			// 
			// prompt1choice2
			// 
			this->prompt1choice2->AutoSize = true;
			this->prompt1choice2->Location = System::Drawing::Point(6, 42);
			this->prompt1choice2->Name = L"prompt1choice2";
			this->prompt1choice2->Size = System::Drawing::Size(116, 17);
			this->prompt1choice2->TabIndex = 5;
			this->prompt1choice2->TabStop = true;
			this->prompt1choice2->Text = L"iPod Touch 3G/4G";
			this->prompt1choice2->UseVisualStyleBackColor = true;
			this->prompt1choice2->CheckedChanged += gcnew System::EventHandler(this, &Form1::prompt1choice2_CheckedChanged);
			// 
			// prompt1choice3
			// 
			this->prompt1choice3->AutoSize = true;
			this->prompt1choice3->Location = System::Drawing::Point(6, 65);
			this->prompt1choice3->Name = L"prompt1choice3";
			this->prompt1choice3->Size = System::Drawing::Size(55, 17);
			this->prompt1choice3->TabIndex = 6;
			this->prompt1choice3->TabStop = true;
			this->prompt1choice3->Text = L"iPad 1";
			this->prompt1choice3->UseVisualStyleBackColor = true;
			this->prompt1choice3->CheckedChanged += gcnew System::EventHandler(this, &Form1::prompt1choice3_CheckedChanged);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(3, 9);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(0, 13);
			this->label3->TabIndex = 3;
			// 
			// welcomeLabel
			// 
			this->welcomeLabel->AutoSize = true;
			this->welcomeLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->welcomeLabel->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->welcomeLabel->Location = System::Drawing::Point(8, 18);
			this->welcomeLabel->Name = L"welcomeLabel";
			this->welcomeLabel->Size = System::Drawing::Size(87, 20);
			this->welcomeLabel->TabIndex = 0;
			this->welcomeLabel->Text = L"Welcome!";
			// 
			// welcomeText
			// 
			this->welcomeText->BackColor = System::Drawing::SystemColors::Control;
			this->welcomeText->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->welcomeText->Cursor = System::Windows::Forms::Cursors::IBeam;
			this->welcomeText->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->welcomeText->Location = System::Drawing::Point(12, 60);
			this->welcomeText->Name = L"welcomeText";
			this->welcomeText->ReadOnly = true;
			this->welcomeText->Size = System::Drawing::Size(292, 239);
			this->welcomeText->TabIndex = 4;
			this->welcomeText->Text = resources->GetString(L"welcomeText.Text");
			// 
			// panelStep2
			// 
			this->panelStep2->Controls->Add(this->panelStep3);
			this->panelStep2->Controls->Add(this->understandingCheck);
			this->panelStep2->Controls->Add(this->groupBox2);
			this->panelStep2->Controls->Add(this->groupBox1);
			this->panelStep2->Controls->Add(this->step2Label);
			this->panelStep2->Location = System::Drawing::Point(3, 3);
			this->panelStep2->Name = L"panelStep2";
			this->panelStep2->Size = System::Drawing::Size(326, 324);
			this->panelStep2->TabIndex = 9;
			this->panelStep2->Visible = false;
			// 
			// panelStep3
			// 
			this->panelStep3->BackColor = System::Drawing::SystemColors::Control;
			this->panelStep3->Controls->Add(this->panelStep4);
			this->panelStep3->Controls->Add(this->label4);
			this->panelStep3->Controls->Add(this->button1);
			this->panelStep3->Controls->Add(this->panelStep3Title);
			this->panelStep3->Location = System::Drawing::Point(0, 0);
			this->panelStep3->Name = L"panelStep3";
			this->panelStep3->Size = System::Drawing::Size(326, 324);
			this->panelStep3->TabIndex = 4;
			this->panelStep3->Visible = false;
			// 
			// panelStep4
			// 
			this->panelStep4->Controls->Add(this->walkthroughText4);
			this->panelStep4->Controls->Add(this->walkthroughText3);
			this->panelStep4->Controls->Add(this->walkthroughText2);
			this->panelStep4->Controls->Add(this->walkthroughText1);
			this->panelStep4->Controls->Add(this->panelStep4_Title);
			this->panelStep4->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->panelStep4->Location = System::Drawing::Point(0, 0);
			this->panelStep4->Name = L"panelStep4";
			this->panelStep4->Size = System::Drawing::Size(326, 324);
			this->panelStep4->TabIndex = 4;
			this->panelStep4->Visible = false;
			// 
			// walkthroughText3
			// 
			this->walkthroughText3->BackColor = System::Drawing::Color::LightGoldenrodYellow;
			this->walkthroughText3->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->walkthroughText3->Location = System::Drawing::Point(11, 52);
			this->walkthroughText3->Multiline = true;
			this->walkthroughText3->Name = L"walkthroughText3";
			this->walkthroughText3->ReadOnly = true;
			this->walkthroughText3->Size = System::Drawing::Size(306, 256);
			this->walkthroughText3->TabIndex = 3;
			this->walkthroughText3->Text = resources->GetString(L"walkthroughText3.Text");
			this->walkthroughText3->Visible = false;
			// 
			// walkthroughText2
			// 
			this->walkthroughText2->BackColor = System::Drawing::Color::LightGoldenrodYellow;
			this->walkthroughText2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->walkthroughText2->Location = System::Drawing::Point(11, 52);
			this->walkthroughText2->Multiline = true;
			this->walkthroughText2->Name = L"walkthroughText2";
			this->walkthroughText2->ReadOnly = true;
			this->walkthroughText2->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->walkthroughText2->Size = System::Drawing::Size(306, 256);
			this->walkthroughText2->TabIndex = 2;
			this->walkthroughText2->Text = resources->GetString(L"walkthroughText2.Text");
			this->walkthroughText2->Visible = false;
			// 
			// walkthroughText1
			// 
			this->walkthroughText1->BackColor = System::Drawing::Color::LightGoldenrodYellow;
			this->walkthroughText1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->walkthroughText1->Location = System::Drawing::Point(11, 52);
			this->walkthroughText1->Multiline = true;
			this->walkthroughText1->Name = L"walkthroughText1";
			this->walkthroughText1->ReadOnly = true;
			this->walkthroughText1->Size = System::Drawing::Size(306, 256);
			this->walkthroughText1->TabIndex = 1;
			this->walkthroughText1->Text = resources->GetString(L"walkthroughText1.Text");
			this->walkthroughText1->Visible = false;
			// 
			// panelStep4_Title
			// 
			this->panelStep4_Title->AutoSize = true;
			this->panelStep4_Title->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->panelStep4_Title->ForeColor = System::Drawing::SystemColors::HotTrack;
			this->panelStep4_Title->Location = System::Drawing::Point(15, 17);
			this->panelStep4_Title->Name = L"panelStep4_Title";
			this->panelStep4_Title->Size = System::Drawing::Size(203, 18);
			this->panelStep4_Title->TabIndex = 0;
			this->panelStep4_Title->Text = L"Step by Step Walkthrough";
			// 
			// label4
			// 
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label4->Location = System::Drawing::Point(19, 74);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(285, 134);
			this->label4->TabIndex = 3;
			this->label4->Text = resources->GetString(L"label4.Text");
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(65, 250);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(192, 38);
			this->button1->TabIndex = 2;
			this->button1->Text = L"Launch the Jailbreak!";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// panelStep3Title
			// 
			this->panelStep3Title->AutoSize = true;
			this->panelStep3Title->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->panelStep3Title->ForeColor = System::Drawing::SystemColors::HotTrack;
			this->panelStep3Title->Location = System::Drawing::Point(20, 24);
			this->panelStep3Title->Name = L"panelStep3Title";
			this->panelStep3Title->Size = System::Drawing::Size(80, 18);
			this->panelStep3Title->TabIndex = 0;
			this->panelStep3Title->Text = L"Jailbreak!";
			// 
			// understandingCheck
			// 
			this->understandingCheck->AutoSize = true;
			this->understandingCheck->Location = System::Drawing::Point(26, 291);
			this->understandingCheck->Name = L"understandingCheck";
			this->understandingCheck->Size = System::Drawing::Size(272, 17);
			this->understandingCheck->TabIndex = 3;
			this->understandingCheck->Text = L"I have been made aware and would like to proceed.";
			this->understandingCheck->UseVisualStyleBackColor = true;
			this->understandingCheck->CheckedChanged += gcnew System::EventHandler(this, &Form1::understandingCheck_CheckedChanged);
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->unlockedText2);
			this->groupBox2->Controls->Add(this->unlockedText3);
			this->groupBox2->Controls->Add(this->unlockedText1);
			this->groupBox2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->groupBox2->Location = System::Drawing::Point(11, 183);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(299, 88);
			this->groupBox2->TabIndex = 2;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Unlocked Device";
			// 
			// unlockedText2
			// 
			this->unlockedText2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->unlockedText2->Location = System::Drawing::Point(7, 23);
			this->unlockedText2->Multiline = true;
			this->unlockedText2->Name = L"unlockedText2";
			this->unlockedText2->ReadOnly = true;
			this->unlockedText2->Size = System::Drawing::Size(290, 59);
			this->unlockedText2->TabIndex = 4;
			this->unlockedText2->Text = L"There is a tool available that will preserve your baseband.This means you will be" 
				L" able to unlock your device after jailbreaking!";
			this->unlockedText2->Visible = false;
			// 
			// unlockedText3
			// 
			this->unlockedText3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->unlockedText3->Location = System::Drawing::Point(5, 23);
			this->unlockedText3->Multiline = true;
			this->unlockedText3->Name = L"unlockedText3";
			this->unlockedText3->ReadOnly = true;
			this->unlockedText3->Size = System::Drawing::Size(290, 55);
			this->unlockedText3->TabIndex = 3;
			this->unlockedText3->Text = L"You do not need to worry about this, because \r\nyour device is not unlocked!";
			this->unlockedText3->Visible = false;
			// 
			// unlockedText1
			// 
			this->unlockedText1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->unlockedText1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->unlockedText1->Location = System::Drawing::Point(6, 23);
			this->unlockedText1->Multiline = true;
			this->unlockedText1->Name = L"unlockedText1";
			this->unlockedText1->ReadOnly = true;
			this->unlockedText1->Size = System::Drawing::Size(287, 59);
			this->unlockedText1->TabIndex = 0;
			this->unlockedText1->Text = L"Because your device has been previously unlocked, \r\nproceeding with the jailbreak" 
				L" will remove it. There is no\r\ntool at this time that will preserve your baseband" 
				L".";
			this->unlockedText1->Visible = false;
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->tetheringText2);
			this->groupBox1->Controls->Add(this->tetheringText1);
			this->groupBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->groupBox1->Location = System::Drawing::Point(11, 63);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(299, 106);
			this->groupBox1->TabIndex = 1;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Tethering";
			// 
			// tetheringText2
			// 
			this->tetheringText2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->tetheringText2->Location = System::Drawing::Point(6, 22);
			this->tetheringText2->Multiline = true;
			this->tetheringText2->Name = L"tetheringText2";
			this->tetheringText2->ReadOnly = true;
			this->tetheringText2->Size = System::Drawing::Size(289, 79);
			this->tetheringText2->TabIndex = 3;
			this->tetheringText2->Text = L"Luckily for you, there is an untethered jailbreak available for your device.\r\nYou" 
				L" will NOT need to connect your device to your computer to boot it.";
			this->tetheringText2->Visible = false;
			// 
			// tetheringText1
			// 
			this->tetheringText1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->tetheringText1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->tetheringText1->Location = System::Drawing::Point(6, 20);
			this->tetheringText1->Multiline = true;
			this->tetheringText1->Name = L"tetheringText1";
			this->tetheringText1->ReadOnly = true;
			this->tetheringText1->Size = System::Drawing::Size(287, 83);
			this->tetheringText1->TabIndex = 0;
			this->tetheringText1->Text = resources->GetString(L"tetheringText1.Text");
			this->tetheringText1->Visible = false;
			this->tetheringText1->TextChanged += gcnew System::EventHandler(this, &Form1::textBox1_TextChanged);
			// 
			// step2Label
			// 
			this->step2Label->AutoSize = true;
			this->step2Label->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->step2Label->ForeColor = System::Drawing::SystemColors::HotTrack;
			this->step2Label->Location = System::Drawing::Point(14, 22);
			this->step2Label->Name = L"step2Label";
			this->step2Label->Size = System::Drawing::Size(214, 21);
			this->step2Label->TabIndex = 0;
			this->step2Label->Text = L"Things you need to know...";
			// 
			// listView1
			// 
			this->listView1->Location = System::Drawing::Point(12, 55);
			this->listView1->Name = L"listView1";
			this->listView1->Size = System::Drawing::Size(126, 259);
			this->listView1->TabIndex = 2;
			this->listView1->UseCompatibleStateImageBehavior = false;
			// 
			// progressBar
			// 
			this->progressBar->Location = System::Drawing::Point(12, 337);
			this->progressBar->Name = L"progressBar";
			this->progressBar->Size = System::Drawing::Size(126, 13);
			this->progressBar->TabIndex = 0;
			// 
			// stepLabel1
			// 
			this->stepLabel1->AutoSize = true;
			this->stepLabel1->BackColor = System::Drawing::SystemColors::Control;
			this->stepLabel1->Location = System::Drawing::Point(44, 106);
			this->stepLabel1->Name = L"stepLabel1";
			this->stepLabel1->Size = System::Drawing::Size(41, 13);
			this->stepLabel1->TabIndex = 3;
			this->stepLabel1->Text = L"Device";
			// 
			// stepLabel2
			// 
			this->stepLabel2->AutoSize = true;
			this->stepLabel2->BackColor = System::Drawing::SystemColors::Control;
			this->stepLabel2->Location = System::Drawing::Point(44, 151);
			this->stepLabel2->Name = L"stepLabel2";
			this->stepLabel2->Size = System::Drawing::Size(77, 13);
			this->stepLabel2->TabIndex = 4;
			this->stepLabel2->Text = L"Things to Note";
			// 
			// stepLabel3
			// 
			this->stepLabel3->AutoSize = true;
			this->stepLabel3->BackColor = System::Drawing::SystemColors::Control;
			this->stepLabel3->Location = System::Drawing::Point(44, 198);
			this->stepLabel3->Name = L"stepLabel3";
			this->stepLabel3->Size = System::Drawing::Size(49, 13);
			this->stepLabel3->TabIndex = 5;
			this->stepLabel3->Text = L"Jailbreak";
			// 
			// stepLabel4
			// 
			this->stepLabel4->AutoSize = true;
			this->stepLabel4->BackColor = System::Drawing::SystemColors::Control;
			this->stepLabel4->Location = System::Drawing::Point(44, 247);
			this->stepLabel4->Name = L"stepLabel4";
			this->stepLabel4->Size = System::Drawing::Size(68, 13);
			this->stepLabel4->TabIndex = 6;
			this->stepLabel4->Text = L"Walkthrough";
			// 
			// stepLabel5
			// 
			this->stepLabel5->AutoSize = true;
			this->stepLabel5->BackColor = System::Drawing::SystemColors::Control;
			this->stepLabel5->Location = System::Drawing::Point(44, 289);
			this->stepLabel5->Name = L"stepLabel5";
			this->stepLabel5->Size = System::Drawing::Size(34, 13);
			this->stepLabel5->TabIndex = 7;
			this->stepLabel5->Text = L"Finish";
			// 
			// check1
			// 
			this->check1->BackColor = System::Drawing::SystemColors::Control;
			this->check1->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"check1.Image")));
			this->check1->Location = System::Drawing::Point(18, 102);
			this->check1->Name = L"check1";
			this->check1->Size = System::Drawing::Size(20, 20);
			this->check1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->check1->TabIndex = 8;
			this->check1->TabStop = false;
			this->check1->Visible = false;
			// 
			// check5
			// 
			this->check5->BackColor = System::Drawing::SystemColors::Control;
			this->check5->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"check5.Image")));
			this->check5->Location = System::Drawing::Point(18, 285);
			this->check5->Name = L"check5";
			this->check5->Size = System::Drawing::Size(20, 20);
			this->check5->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->check5->TabIndex = 9;
			this->check5->TabStop = false;
			this->check5->Visible = false;
			// 
			// check4
			// 
			this->check4->BackColor = System::Drawing::SystemColors::Control;
			this->check4->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"check4.Image")));
			this->check4->Location = System::Drawing::Point(18, 243);
			this->check4->Name = L"check4";
			this->check4->Size = System::Drawing::Size(20, 20);
			this->check4->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->check4->TabIndex = 10;
			this->check4->TabStop = false;
			this->check4->Visible = false;
			// 
			// check3
			// 
			this->check3->BackColor = System::Drawing::SystemColors::Control;
			this->check3->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"check3.Image")));
			this->check3->Location = System::Drawing::Point(18, 195);
			this->check3->Name = L"check3";
			this->check3->Size = System::Drawing::Size(20, 20);
			this->check3->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->check3->TabIndex = 11;
			this->check3->TabStop = false;
			this->check3->Visible = false;
			// 
			// check2
			// 
			this->check2->BackColor = System::Drawing::SystemColors::Control;
			this->check2->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"check2.Image")));
			this->check2->Location = System::Drawing::Point(18, 147);
			this->check2->Name = L"check2";
			this->check2->Size = System::Drawing::Size(20, 20);
			this->check2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->check2->TabIndex = 12;
			this->check2->TabStop = false;
			this->check2->Visible = false;
			// 
			// labelWelcome
			// 
			this->labelWelcome->AutoSize = true;
			this->labelWelcome->BackColor = System::Drawing::SystemColors::Control;
			this->labelWelcome->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->labelWelcome->Location = System::Drawing::Point(44, 65);
			this->labelWelcome->Name = L"labelWelcome";
			this->labelWelcome->Size = System::Drawing::Size(55, 13);
			this->labelWelcome->TabIndex = 13;
			this->labelWelcome->Text = L"Welcome!";
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::SystemColors::Control;
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(18, 61);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(20, 20);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox1->TabIndex = 14;
			this->pictureBox1->TabStop = false;
			// 
			// splitContainer1
			// 
			this->splitContainer1->IsSplitterFixed = true;
			this->splitContainer1->Location = System::Drawing::Point(-1, 0);
			this->splitContainer1->Name = L"splitContainer1";
			// 
			// splitContainer1.Panel1
			// 
			this->splitContainer1->Panel1->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"splitContainer1.Panel1.BackgroundImage")));
			this->splitContainer1->Panel1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->splitContainer1->Panel1->Controls->Add(this->pictureBox1);
			this->splitContainer1->Panel1->Controls->Add(this->labelWelcome);
			this->splitContainer1->Panel1->Controls->Add(this->check2);
			this->splitContainer1->Panel1->Controls->Add(this->check3);
			this->splitContainer1->Panel1->Controls->Add(this->check4);
			this->splitContainer1->Panel1->Controls->Add(this->check5);
			this->splitContainer1->Panel1->Controls->Add(this->check1);
			this->splitContainer1->Panel1->Controls->Add(this->stepLabel5);
			this->splitContainer1->Panel1->Controls->Add(this->stepLabel4);
			this->splitContainer1->Panel1->Controls->Add(this->stepLabel3);
			this->splitContainer1->Panel1->Controls->Add(this->stepLabel2);
			this->splitContainer1->Panel1->Controls->Add(this->stepLabel1);
			this->splitContainer1->Panel1->Controls->Add(this->progressBar);
			this->splitContainer1->Panel1->Controls->Add(this->listView1);
			// 
			// splitContainer1.Panel2
			// 
			this->splitContainer1->Panel2->BackColor = System::Drawing::SystemColors::ControlLight;
			this->splitContainer1->Panel2->Controls->Add(this->panelFinish);
			this->splitContainer1->Panel2->Controls->Add(this->panelStep2);
			this->splitContainer1->Panel2->Controls->Add(this->panelWelcome);
			this->splitContainer1->Panel2->Controls->Add(this->cancelButton);
			this->splitContainer1->Panel2->Controls->Add(this->nextButton);
			this->splitContainer1->Panel2->Controls->Add(this->backButton);
			this->splitContainer1->Panel2->Controls->Add(this->shapeContainer2);
			this->splitContainer1->Size = System::Drawing::Size(485, 359);
			this->splitContainer1->SplitterDistance = 149;
			this->splitContainer1->TabIndex = 3;
			// 
			// shapeContainer2
			// 
			this->shapeContainer2->Location = System::Drawing::Point(0, 0);
			this->shapeContainer2->Margin = System::Windows::Forms::Padding(0);
			this->shapeContainer2->Name = L"shapeContainer2";
			this->shapeContainer2->Shapes->AddRange(gcnew cli::array< Microsoft::VisualBasic::PowerPacks::Shape^  >(1) {this->lineShape1});
			this->shapeContainer2->Size = System::Drawing::Size(332, 359);
			this->shapeContainer2->TabIndex = 5;
			this->shapeContainer2->TabStop = false;
			// 
			// lineShape1
			// 
			this->lineShape1->Name = L"";
			this->lineShape1->X1 = -2;
			this->lineShape1->X2 = -2;
			this->lineShape1->Y1 = 313;
			this->lineShape1->Y2 = 1;
			// 
			// walkthroughText4
			// 
			this->walkthroughText4->BackColor = System::Drawing::Color::LightGoldenrodYellow;
			this->walkthroughText4->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->walkthroughText4->Location = System::Drawing::Point(12, 52);
			this->walkthroughText4->Multiline = true;
			this->walkthroughText4->Name = L"walkthroughText4";
			this->walkthroughText4->ReadOnly = true;
			this->walkthroughText4->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->walkthroughText4->Size = System::Drawing::Size(306, 256);
			this->walkthroughText4->TabIndex = 4;
			this->walkthroughText4->Text = resources->GetString(L"walkthroughText4.Text");
			this->walkthroughText4->Visible = false;
			// 
			// panelFinish
			// 
			this->panelFinish->Controls->Add(this->textBox2);
			this->panelFinish->Controls->Add(this->label1);
			this->panelFinish->Controls->Add(this->textBox1);
			this->panelFinish->Controls->Add(this->panelFinish_Title);
			this->panelFinish->Location = System::Drawing::Point(3, 3);
			this->panelFinish->Name = L"panelFinish";
			this->panelFinish->Size = System::Drawing::Size(326, 324);
			this->panelFinish->TabIndex = 5;
			this->panelFinish->Visible = false;
			// 
			// panelFinish_Title
			// 
			this->panelFinish_Title->AutoSize = true;
			this->panelFinish_Title->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->panelFinish_Title->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->panelFinish_Title->Location = System::Drawing::Point(26, 27);
			this->panelFinish_Title->Name = L"panelFinish_Title";
			this->panelFinish_Title->Size = System::Drawing::Size(97, 22);
			this->panelFinish_Title->TabIndex = 0;
			this->panelFinish_Title->Text = L"Congrats!";
			// 
			// textBox1
			// 
			this->textBox1->BackColor = System::Drawing::SystemColors::ControlLight;
			this->textBox1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->textBox1->Location = System::Drawing::Point(18, 81);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->ReadOnly = true;
			this->textBox1->Size = System::Drawing::Size(286, 103);
			this->textBox1->TabIndex = 1;
			this->textBox1->Text = L"Thank you for choosing iBreak by Domisy. If you have enjoyed using this program, " 
				L"please feel free to recommend it to others.\r\nWe hope you enjoy your newly jailbr" 
				L"oken iOS device!";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label1->ForeColor = System::Drawing::Color::DarkRed;
			this->label1->Location = System::Drawing::Point(135, 219);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(52, 15);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Credits";
			// 
			// textBox2
			// 
			this->textBox2->BackColor = System::Drawing::SystemColors::ControlLight;
			this->textBox2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->textBox2->Location = System::Drawing::Point(65, 245);
			this->textBox2->Multiline = true;
			this->textBox2->Name = L"textBox2";
			this->textBox2->ReadOnly = true;
			this->textBox2->Size = System::Drawing::Size(192, 43);
			this->textBox2->TabIndex = 3;
			this->textBox2->Text = L"Lead Developer - Theo Mavrakis\r\nAssisted Development - Alan Xenos\r\nGraphics - Cor" 
				L"mac O\'Brien";
			this->textBox2->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ControlDark;
			this->ClientSize = System::Drawing::Size(484, 362);
			this->Controls->Add(this->splitContainer1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->MaximumSize = System::Drawing::Size(500, 400);
			this->MinimumSize = System::Drawing::Size(500, 400);
			this->Name = L"Form1";
			this->Text = L"iBreak";
			this->panelWelcome->ResumeLayout(false);
			this->panelWelcome->PerformLayout();
			this->panelStep1->ResumeLayout(false);
			this->panelStep1->PerformLayout();
			this->panel3->ResumeLayout(false);
			this->panel3->PerformLayout();
			this->prompt3->ResumeLayout(false);
			this->prompt2->ResumeLayout(false);
			this->prompt2->PerformLayout();
			this->prompt1->ResumeLayout(false);
			this->prompt1->PerformLayout();
			this->panelStep2->ResumeLayout(false);
			this->panelStep2->PerformLayout();
			this->panelStep3->ResumeLayout(false);
			this->panelStep3->PerformLayout();
			this->panelStep4->ResumeLayout(false);
			this->panelStep4->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->check1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->check5))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->check4))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->check3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->check2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->EndInit();
			this->splitContainer1->Panel1->ResumeLayout(false);
			this->splitContainer1->Panel1->PerformLayout();
			this->splitContainer1->Panel2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->splitContainer1))->EndInit();
			this->splitContainer1->ResumeLayout(false);
			this->panelFinish->ResumeLayout(false);
			this->panelFinish->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	
	private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
			 Application::Exit();
		 }

	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
				 //turn off the nextButton
				 nextActivateFunc(false);

				 //next button turned on off at maximum progressbar point
				 if (progressBar->Value != progressBar->Maximum){
					 if (progressBar->Value == 80) { nextActivateFunc(false); progress = progress + 20; progressBar->Value = progress; backButton->Enabled = true; }
					 else progress = progress + 20; progressBar->Value = progress; backButton->Enabled = true;
				 }

				 //advancing the panels
				 if (check1->Visible == false) { check1->Visible = true; panelStep1->Visible = true; }
					else if (check2->Visible == false) { check2->Visible = true; panelStep2->Visible = true; jbTool(); }
					else if (check3->Visible == false) { check3->Visible = true; panelStep3->Visible = true; }
					else if (check4->Visible == false) { check4->Visible = true; panelStep4->Visible = true; nextActivateFunc(true); }
					else if (check5->Visible == false) { check5->Visible = true; panelFinish->Visible = true; cancelButton->Text = "Finish"; backButton->Enabled = false; }
			 	}	 
		 
private: System::Void button1_Click_1(System::Object^  sender, System::EventArgs^  e) {
				//backButton turned off at minimum progressbar point
				if (progressBar->Value != progressBar->Minimum) {
					if (progressBar->Value == 20) { backButton->Enabled = false; progress = progress - 20; progressBar->Value = progress; nextActivateFunc(true); }
					else progress = progress - 20; progressBar->Value = progress; nextActivateFunc(true); 
				}
				//reversing the panels
				if (check5->Visible == true) { check5->Visible = false; panelFinish->Visible = false; }
					else if (check4->Visible == true) { check4->Visible = false; panelStep4->Visible = false; }
					else if (check3->Visible == true) { check3->Visible = false; panelStep3->Visible = false; }
					else if (check2->Visible == true) { check2->Visible = false; panelStep2->Visible = false; understandingCheck->Checked = false; nextActivateFunc(true); clearInform();}
					else if (check1->Visible == true) { check1->Visible = false; panelStep1->Visible = false; clearEntries(); nextActivateFunc(true); }
		 }


private: System::Void prompt1choice1_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 if (nextButton->Enabled == true) {nextActivateFunc(false);}
			 if (prompt2->Visible == true) {prompt3->Visible = true; prompt2->Visible = true;}
			 else prompt2->Visible = true;
		 }
private: System::Void prompt1choice2_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 if (prompt3->Visible == true) {prompt3->Visible = false; prompt2->Visible = true;}
			 else prompt2->Visible = true;
			 if (prompt2choice1->Checked == true | prompt2choice2->Checked == true | prompt2choice3->Checked == true) {nextActivateFunc(true);}
		 }
private: System::Void prompt1choice3_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 if (prompt3->Visible == true) {prompt3->Visible = false; prompt2->Visible = true;}
			 else prompt2->Visible = true;
			 if (prompt2choice1->Checked == true | prompt2choice2->Checked == true | prompt2choice3->Checked == true) {nextActivateFunc(true);}
		 }
private: System::Void prompt2choice1_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 if (prompt1choice1->Checked == true) {nextActivateFunc(true);}
			 prompt3->Visible = false;
		 }
private: System::Void prompt2choice2_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 if (prompt1choice1->Checked == true) {
				prompt3->Visible = true;
				if (unlockedDropdown->SelectedIndex > -1) { nextActivateFunc(true); }
				else nextActivateFunc(false); }
			 else nextActivateFunc(true);
		 }
private: System::Void prompt2choice3_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 if (prompt1choice1->Checked == true) {
				prompt3->Visible = true;
				if (unlockedDropdown->SelectedIndex > -1) { nextActivateFunc(true); }
				else nextActivateFunc(false); }
			 else nextActivateFunc(true);
		 }

private: System::Void prompt2_Enter(System::Object^  sender, System::EventArgs^  e) {
			 if (prompt1choice1->Checked == false) {nextActivateFunc(true);}
		 }



private: System::Void unlockedDropdown_SelectionChangeCommitted(System::Object^  sender, System::EventArgs^  e) {
			 nextActivateFunc(true);
		 }
private: System::Void textBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		 }

		 //understanding Checkbox is verified
private: System::Void understandingCheck_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 if (nextButton->Enabled == false) {nextActivateFunc(true);}
			 else nextActivateFunc(false);
				 
		 }

private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
			nextActivateFunc(true);
		    executeTool();
			
		 }

};
}