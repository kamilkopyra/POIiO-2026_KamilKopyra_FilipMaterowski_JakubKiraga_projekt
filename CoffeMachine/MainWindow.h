#pragma once
#include "CoffeMachine.h"
#include <msclr/marshal_cppstd.h>




	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Podsumowanie informacji o MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			machine = new CoffeMachine();
			

			//machine->initializeMachine();
			//System::Windows::Forms::MessageBox::Show("Zainicjowano ekspres do kawy!");
			//TODO: W tym miejscu dodaj kod konstruktora
			//
		}

	protected:
		/// <summary>
		/// Wyczyœæ wszystkie u¿ywane zasoby.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^ plikToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ zamknijToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ statystykaToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ statusSk³adnikówToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ historiaToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ serwisToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ uzupe³nijSk³adnikiToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ wyczyœæEkspresToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ serwisantToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ zamknijToolStripMenuItem1;
	protected:

	private:
		/// <summary>
		/// Wymagana zmienna projektanta.
		/// </summary>
		System::ComponentModel::Container ^components;
		CoffeMachine* machine;
		int currentDrinkIndex = 0;
		bool menuActive = false;

	

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Metoda wymagana do obs³ugi projektanta — nie nale¿y modyfikowaæ
		/// jej zawartoœci w edytorze kodu.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->plikToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->zamknijToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->zamknijToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->statystykaToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->statusSk³adnikówToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->historiaToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->serwisToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->uzupe³nijSk³adnikiToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->wyczyœæEkspresToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->serwisantToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(474, 408);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(149, 49);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Rozpocznij";
			this->button1->UseVisualStyleBackColor = true;
         this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			this->KeyPreview = true;
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyDown);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(392, 183);
			this->textBox1->Name = L"textBox1";
			this->textBox1->ReadOnly = true;
			this->textBox1->Size = System::Drawing::Size(311, 31);
			this->textBox1->TabIndex = 1;
			this->textBox1->Text = L"Ekspres do kawy";
			this->textBox1->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox1_TextChanged);
			// 
			// menuStrip1
			// 
			this->menuStrip1->GripMargin = System::Windows::Forms::Padding(2, 2, 0, 2);
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(32, 32);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->plikToolStripMenuItem,
					this->statystykaToolStripMenuItem, this->serwisToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(1101, 40);
			this->menuStrip1->TabIndex = 2;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// plikToolStripMenuItem
			// 
			this->plikToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->zamknijToolStripMenuItem,
					this->zamknijToolStripMenuItem1
			});
			this->plikToolStripMenuItem->Name = L"plikToolStripMenuItem";
			this->plikToolStripMenuItem->Size = System::Drawing::Size(113, 36);
			this->plikToolStripMenuItem->Text = L"Ekspres";
			// 
			// zamknijToolStripMenuItem
			// 
			this->zamknijToolStripMenuItem->Name = L"zamknijToolStripMenuItem";
			this->zamknijToolStripMenuItem->Size = System::Drawing::Size(380, 44);
			this->zamknijToolStripMenuItem->Text = L"Edytuj menu napojów";
			// 
			// zamknijToolStripMenuItem1
			// 
			this->zamknijToolStripMenuItem1->Name = L"zamknijToolStripMenuItem1";
			this->zamknijToolStripMenuItem1->Size = System::Drawing::Size(380, 44);
			this->zamknijToolStripMenuItem1->Text = L"Zamknij";
			this->zamknijToolStripMenuItem1->Click += gcnew System::EventHandler(this, &MyForm::zamknijToolStripMenuItem1_Click);
			// 
			// statystykaToolStripMenuItem
			// 
			this->statystykaToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->statusSk³adnikówToolStripMenuItem,
					this->historiaToolStripMenuItem
			});
			this->statystykaToolStripMenuItem->Name = L"statystykaToolStripMenuItem";
			this->statystykaToolStripMenuItem->Size = System::Drawing::Size(140, 36);
			this->statystykaToolStripMenuItem->Text = L"Statystyka";
			// 
			// statusSk³adnikówToolStripMenuItem
			// 
			this->statusSk³adnikówToolStripMenuItem->Name = L"statusSk³adnikówToolStripMenuItem";
			this->statusSk³adnikówToolStripMenuItem->Size = System::Drawing::Size(336, 44);
			this->statusSk³adnikówToolStripMenuItem->Text = L"Status sk³adników";
			// 
			// historiaToolStripMenuItem
			// 
			this->historiaToolStripMenuItem->Name = L"historiaToolStripMenuItem";
			this->historiaToolStripMenuItem->Size = System::Drawing::Size(336, 44);
			this->historiaToolStripMenuItem->Text = L"Historia";
			// 
			// serwisToolStripMenuItem
			// 
			this->serwisToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->uzupe³nijSk³adnikiToolStripMenuItem,
					this->wyczyœæEkspresToolStripMenuItem, this->serwisantToolStripMenuItem
			});
			this->serwisToolStripMenuItem->Name = L"serwisToolStripMenuItem";
			this->serwisToolStripMenuItem->Size = System::Drawing::Size(101, 36);
			this->serwisToolStripMenuItem->Text = L"Serwis";
			// 
			// uzupe³nijSk³adnikiToolStripMenuItem
			// 
			this->uzupe³nijSk³adnikiToolStripMenuItem->Name = L"uzupe³nijSk³adnikiToolStripMenuItem";
			this->uzupe³nijSk³adnikiToolStripMenuItem->Size = System::Drawing::Size(348, 44);
			this->uzupe³nijSk³adnikiToolStripMenuItem->Text = L"Uzupe³nij sk³adniki";
			// 
			// wyczyœæEkspresToolStripMenuItem
			// 
			this->wyczyœæEkspresToolStripMenuItem->Name = L"wyczyœæEkspresToolStripMenuItem";
			this->wyczyœæEkspresToolStripMenuItem->Size = System::Drawing::Size(348, 44);
			this->wyczyœæEkspresToolStripMenuItem->Text = L"Wyczyœæ ekspres";
			// 
			// serwisantToolStripMenuItem
			// 
			this->serwisantToolStripMenuItem->Name = L"serwisantToolStripMenuItem";
			this->serwisantToolStripMenuItem->Size = System::Drawing::Size(348, 44);
			this->serwisantToolStripMenuItem->Text = L"Serwisant";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(12, 25);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1101, 680);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

          // Update the textbox to show the currently selected drink
		void updateDrinkDisplay() {
			if (!menuActive) return;
			if (Tdrinks::drinks.size() == 0) {
				this->textBox1->Text = L"Brak napojow";
				return;
			}
			std::string name = Tdrinks::drinks[currentDrinkIndex].getName();
			System::String^ sname = msclr::interop::marshal_as<System::String^>(name);
			this->textBox1->Text = sname;
		}

		System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
			// Activate sliding menu and show first drink
			menuActive = true;
			currentDrinkIndex = 0;
			updateDrinkDisplay();
		}

		System::Void MyForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
			if (!menuActive) return;
			if (Tdrinks::drinks.size() == 0) return;  
			if (e->KeyCode == System::Windows::Forms::Keys::Right) {
				currentDrinkIndex = (currentDrinkIndex + 1) % (int)Tdrinks::drinks.size();  
				updateDrinkDisplay();
			}
			else if (e->KeyCode == System::Windows::Forms::Keys::Left) {
				currentDrinkIndex = (currentDrinkIndex - 1 + (int)Tdrinks::drinks.size()) % (int)Tdrinks::drinks.size(); 
				updateDrinkDisplay();
			}
		}
	private: System::Void zamknijToolStripMenuItem1_Click(System::Object^ sender, System::EventArgs^ e) {
	
		System::Windows::Forms::DialogResult answer;
		answer = MessageBox::Show("Czy napewno chcesz zamkn¹æ aplikacjê?",
			"Program kubeczki", MessageBoxButtons::YesNo, MessageBoxIcon::Question);

		if (answer == System::Windows::Forms::DialogResult::Yes) {
			Application::Exit();
		}
	
	
	
	}
	private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
};







