#pragma once
#include "ngn.h"
#include "add.h"
#include "convert.h"
#define MARSHAL_AS(a,b) (ST_CHAR*)a->marshal_as<const char*> (b)

namespace ConfigurationTool {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;

	/// <summary>
	/// MainForm에 대한 요약입니다.
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm (void)
		{
			InitializeComponent ();
			//
			//TODO: 생성자 코드를 여기에 추가합니다.
			//
		}

	protected:
		/// <summary>
		/// 사용 중인 모든 리소스를 정리합니다.
		/// </summary>
		~MainForm ()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^  txtbxAIEDFilePath;


	private: System::Windows::Forms::TextBox^  txtbxPIEDFilePath;


	protected:

	protected:






	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  lbl_;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::TreeView^  tvwAIED;
	private: System::Windows::Forms::TreeView^  tvwPIED;
	private: System::Windows::Forms::Button^  btnAIEDFileOpen;
	private: System::Windows::Forms::Button^  btnAdd;
	private: System::Windows::Forms::Button^  btnRemove;
	private: System::Windows::Forms::Button^  btnSave;
	private: System::Windows::Forms::Button^  btnPIEDFileOpen;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialogAgg;
	private: System::Windows::Forms::SaveFileDialog^  saveFileDialog;
	private: System::Windows::Forms::ComboBox^  cbxAIEDServerName;
	private: System::Windows::Forms::ComboBox^  cbxAIEDSubNetworkName;
	private: System::Windows::Forms::ComboBox^  cbxPIEDServerName;
	private: System::Windows::Forms::ComboBox^  cbxPIEDSubNetworkName;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialogPub;








	private:
		/// <summary>
		/// 필수 디자이너 변수입니다.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 디자이너 지원에 필요한 메서드입니다. 
		/// 이 메서드의 내용을 코드 편집기로 수정하지 마세요.
		/// </summary>
		void InitializeComponent (void)
		{
			this->txtbxAIEDFilePath = (gcnew System::Windows::Forms::TextBox ());
			this->txtbxPIEDFilePath = (gcnew System::Windows::Forms::TextBox ());
			this->label1 = (gcnew System::Windows::Forms::Label ());
			this->lbl_ = (gcnew System::Windows::Forms::Label ());
			this->label3 = (gcnew System::Windows::Forms::Label ());
			this->label4 = (gcnew System::Windows::Forms::Label ());
			this->label5 = (gcnew System::Windows::Forms::Label ());
			this->label6 = (gcnew System::Windows::Forms::Label ());
			this->tvwAIED = (gcnew System::Windows::Forms::TreeView ());
			this->tvwPIED = (gcnew System::Windows::Forms::TreeView ());
			this->btnAIEDFileOpen = (gcnew System::Windows::Forms::Button ());
			this->btnAdd = (gcnew System::Windows::Forms::Button ());
			this->btnRemove = (gcnew System::Windows::Forms::Button ());
			this->btnSave = (gcnew System::Windows::Forms::Button ());
			this->btnPIEDFileOpen = (gcnew System::Windows::Forms::Button ());
			this->openFileDialogAgg = (gcnew System::Windows::Forms::OpenFileDialog ());
			this->saveFileDialog = (gcnew System::Windows::Forms::SaveFileDialog ());
			this->cbxAIEDServerName = (gcnew System::Windows::Forms::ComboBox ());
			this->cbxAIEDSubNetworkName = (gcnew System::Windows::Forms::ComboBox ());
			this->cbxPIEDServerName = (gcnew System::Windows::Forms::ComboBox ());
			this->cbxPIEDSubNetworkName = (gcnew System::Windows::Forms::ComboBox ());
			this->label2 = (gcnew System::Windows::Forms::Label ());
			this->label7 = (gcnew System::Windows::Forms::Label ());
			this->openFileDialogPub = (gcnew System::Windows::Forms::OpenFileDialog ());
			this->SuspendLayout ();
			// 
			// txtbxAIEDFilePath
			// 
			this->txtbxAIEDFilePath->Location = System::Drawing::Point (115, 37);
			this->txtbxAIEDFilePath->Name = L"txtbxAIEDFilePath";
			this->txtbxAIEDFilePath->Size = System::Drawing::Size (121, 21);
			this->txtbxAIEDFilePath->TabIndex = 0;
			// 
			// txtbxPIEDFilePath
			// 
			this->txtbxPIEDFilePath->Location = System::Drawing::Point (421, 37);
			this->txtbxPIEDFilePath->Name = L"txtbxPIEDFilePath";
			this->txtbxPIEDFilePath->Size = System::Drawing::Size (122, 21);
			this->txtbxPIEDFilePath->TabIndex = 3;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point (54, 40);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size (53, 12);
			this->label1->TabIndex = 6;
			this->label1->Text = L"파일이름";
			// 
			// lbl_
			// 
			this->lbl_->AutoSize = true;
			this->lbl_->Location = System::Drawing::Point (68, 67);
			this->lbl_->Name = L"lbl_";
			this->lbl_->Size = System::Drawing::Size (41, 12);
			this->lbl_->TabIndex = 7;
			this->lbl_->Text = L"서버명";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point (10, 93);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size (97, 12);
			this->label3->TabIndex = 8;
			this->label3->Text = L"서브 네트워크 명";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point (359, 40);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size (57, 12);
			this->label4->TabIndex = 9;
			this->label4->Text = L"파일 이름";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point (375, 67);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size (41, 12);
			this->label5->TabIndex = 10;
			this->label5->Text = L"서버명";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point (319, 93);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size (97, 12);
			this->label6->TabIndex = 11;
			this->label6->Text = L"서브 네트워크 명";
			// 
			// tvwAIED
			// 
			this->tvwAIED->Location = System::Drawing::Point (12, 116);
			this->tvwAIED->Name = L"tvwAIED";
			this->tvwAIED->Size = System::Drawing::Size (224, 360);
			this->tvwAIED->TabIndex = 12;
			// 
			// tvwPIED
			// 
			this->tvwPIED->Location = System::Drawing::Point (321, 116);
			this->tvwPIED->Name = L"tvwPIED";
			this->tvwPIED->Size = System::Drawing::Size (220, 360);
			this->tvwPIED->TabIndex = 13;
			// 
			// btnAIEDFileOpen
			// 
			this->btnAIEDFileOpen->Location = System::Drawing::Point (242, 37);
			this->btnAIEDFileOpen->Name = L"btnAIEDFileOpen";
			this->btnAIEDFileOpen->Size = System::Drawing::Size (78, 21);
			this->btnAIEDFileOpen->TabIndex = 14;
			this->btnAIEDFileOpen->Text = L"파일 열기";
			this->btnAIEDFileOpen->UseVisualStyleBackColor = true;
			this->btnAIEDFileOpen->Click += gcnew System::EventHandler (this, &MainForm::btnAIEDFileOpen_Click);
			// 
			// btnAdd
			// 
			this->btnAdd->Location = System::Drawing::Point (242, 227);
			this->btnAdd->Name = L"btnAdd";
			this->btnAdd->Size = System::Drawing::Size (73, 24);
			this->btnAdd->TabIndex = 15;
			this->btnAdd->Text = L"추가";
			this->btnAdd->UseVisualStyleBackColor = true;
			this->btnAdd->Click += gcnew System::EventHandler (this, &MainForm::btnAdd_Click);
			// 
			// btnRemove
			// 
			this->btnRemove->Location = System::Drawing::Point (242, 257);
			this->btnRemove->Name = L"btnRemove";
			this->btnRemove->Size = System::Drawing::Size (73, 25);
			this->btnRemove->TabIndex = 16;
			this->btnRemove->Text = L"제거";
			this->btnRemove->UseVisualStyleBackColor = true;
			this->btnRemove->Click += gcnew System::EventHandler (this, &MainForm::btnRemove_Click);
			// 
			// btnSave
			// 
			this->btnSave->Location = System::Drawing::Point (163, 482);
			this->btnSave->Name = L"btnSave";
			this->btnSave->Size = System::Drawing::Size (73, 24);
			this->btnSave->TabIndex = 17;
			this->btnSave->Text = L"저장";
			this->btnSave->UseVisualStyleBackColor = true;
			this->btnSave->Click += gcnew System::EventHandler (this, &MainForm::btnSave_Click);
			// 
			// btnPIEDFileOpen
			// 
			this->btnPIEDFileOpen->Location = System::Drawing::Point (549, 37);
			this->btnPIEDFileOpen->Name = L"btnPIEDFileOpen";
			this->btnPIEDFileOpen->Size = System::Drawing::Size (70, 21);
			this->btnPIEDFileOpen->TabIndex = 18;
			this->btnPIEDFileOpen->Text = L"파일 열기";
			this->btnPIEDFileOpen->UseVisualStyleBackColor = true;
			this->btnPIEDFileOpen->Click += gcnew System::EventHandler (this, &MainForm::btnPIEDFileOpen_Click);
			// 
			// cbxAIEDServerName
			// 
			this->cbxAIEDServerName->FormattingEnabled = true;
			this->cbxAIEDServerName->Location = System::Drawing::Point (115, 65);
			this->cbxAIEDServerName->Name = L"cbxAIEDServerName";
			this->cbxAIEDServerName->Size = System::Drawing::Size (121, 20);
			this->cbxAIEDServerName->TabIndex = 19;
			this->cbxAIEDServerName->SelectedIndexChanged += gcnew System::EventHandler (this, &MainForm::cbxAIEDServerName_SelectedIndexChanged);
			// 
			// cbxAIEDSubNetworkName
			// 
			this->cbxAIEDSubNetworkName->FormattingEnabled = true;
			this->cbxAIEDSubNetworkName->Location = System::Drawing::Point (115, 90);
			this->cbxAIEDSubNetworkName->Name = L"cbxAIEDSubNetworkName";
			this->cbxAIEDSubNetworkName->Size = System::Drawing::Size (121, 20);
			this->cbxAIEDSubNetworkName->TabIndex = 20;
			// 
			// cbxPIEDServerName
			// 
			this->cbxPIEDServerName->FormattingEnabled = true;
			this->cbxPIEDServerName->Location = System::Drawing::Point (421, 64);
			this->cbxPIEDServerName->Name = L"cbxPIEDServerName";
			this->cbxPIEDServerName->Size = System::Drawing::Size (121, 20);
			this->cbxPIEDServerName->TabIndex = 21;
			this->cbxPIEDServerName->SelectedIndexChanged += gcnew System::EventHandler (this, &MainForm::cbxPIEDServerName_SelectedIndexChanged);
			// 
			// cbxPIEDSubNetworkName
			// 
			this->cbxPIEDSubNetworkName->FormattingEnabled = true;
			this->cbxPIEDSubNetworkName->Location = System::Drawing::Point (421, 90);
			this->cbxPIEDSubNetworkName->Name = L"cbxPIEDSubNetworkName";
			this->cbxPIEDSubNetworkName->Size = System::Drawing::Size (121, 20);
			this->cbxPIEDSubNetworkName->TabIndex = 22;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point (10, 9);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size (66, 12);
			this->label2->TabIndex = 23;
			this->label2->Text = L"Aggregator";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point (319, 9);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size (58, 12);
			this->label7->TabIndex = 24;
			this->label7->Text = L"Publisher";
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF (7, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size (629, 516);
			this->Controls->Add (this->label7);
			this->Controls->Add (this->label2);
			this->Controls->Add (this->cbxPIEDSubNetworkName);
			this->Controls->Add (this->cbxPIEDServerName);
			this->Controls->Add (this->cbxAIEDSubNetworkName);
			this->Controls->Add (this->cbxAIEDServerName);
			this->Controls->Add (this->btnPIEDFileOpen);
			this->Controls->Add (this->btnSave);
			this->Controls->Add (this->btnRemove);
			this->Controls->Add (this->btnAdd);
			this->Controls->Add (this->btnAIEDFileOpen);
			this->Controls->Add (this->tvwPIED);
			this->Controls->Add (this->tvwAIED);
			this->Controls->Add (this->label6);
			this->Controls->Add (this->label5);
			this->Controls->Add (this->label4);
			this->Controls->Add (this->label3);
			this->Controls->Add (this->lbl_);
			this->Controls->Add (this->label1);
			this->Controls->Add (this->txtbxPIEDFilePath);
			this->Controls->Add (this->txtbxAIEDFilePath);
			this->Name = L"MainForm";
			this->Text = L"ConfigurationTool";
			this->ResumeLayout (false);
			this->PerformLayout ();

		}
#pragma endregion


	//////////////////////////////////////////////////////////////////////////////////////////////////////////여기서부터 시작임 이 위는 UI관련코드임

	public: 
		SCL_INFO *scl_info_agg;
		SCL_INFO *scl_info_pub;

	//Aggregator SCL 파일 열기버튼
	private: System::Void btnAIEDFileOpen_Click (System::Object^  sender, System::EventArgs^  e)
	{

		marshal_context^ fileName = gcnew marshal_context ();
		ST_RET ret;
		SCL_SERVER *scl_server;
		SCL_SUBNET *scl_subnet;



		openFileDialogAgg->InitialDirectory = Directory::GetCurrentDirectory ();
		if (openFileDialogAgg->ShowDialog () == System::Windows::Forms::DialogResult::OK)//파일열기에서 확인을 누르면
		{
			//기존의 정보 초기화
			tvwAIED->Nodes->Clear ();
			cbxAIEDServerName->Items->Clear();
			cbxAIEDSubNetworkName->Items->Clear();
			if (scl_info_agg)
			{
				scl_info_destroy (scl_info_agg);
				chk_free (scl_info_agg);
			}

			
			this->txtbxAIEDFilePath->Text = Path::GetFileName (openFileDialogAgg->FileName);
			
			scl_info_agg = (SCL_INFO*)malloc (sizeof (SCL_INFO));
			ret = GetSclInfo (MARSHAL_AS (fileName, openFileDialogAgg->FileName), scl_info_agg);
			delete fileName;
			if (ret)
			{
				System::Windows::Forms::MessageBox::Show ("SCL파일 파싱에러");
				return;
			}

			//서버이름 콤보박스리스트 생성
			for (scl_server = (SCL_SERVER *)list_find_last ((DBL_LNK *)scl_info_agg->serverHead);
				scl_server != NULL;
				scl_server = (SCL_SERVER *)list_find_prev ((DBL_LNK *)scl_info_agg->serverHead, (DBL_LNK *)scl_server))
			{
				cbxAIEDServerName->Items->Add ("" + marshal_as<System::String^> (scl_server->iedName));
			}
			if (cbxAIEDServerName->Items->Count > 0)
				cbxAIEDServerName->Text = cbxAIEDServerName->Items[0]->ToString ();

			//서브넷이름 콤보박스리스트 생성
			for (scl_subnet = (SCL_SUBNET *)list_find_last ((DBL_LNK *)scl_info_agg->subnetHead);
				scl_subnet != NULL;
				scl_subnet = (SCL_SUBNET *)list_find_prev ((DBL_LNK *)scl_info_agg->subnetHead, (DBL_LNK *)scl_subnet))
			{
				cbxAIEDSubNetworkName->Items->Add ("" + marshal_as<System::String^> (scl_subnet->name));
			}
			if (cbxAIEDSubNetworkName->Items->Count > 0)
				cbxAIEDSubNetworkName->Text = cbxAIEDSubNetworkName->Items[0]->ToString ();

			//트리뷰 생성
			CreateTreeView (scl_info_agg, tvwAIED, cbxAIEDServerName->Text);
		}

		
	}

	//Publisher SCL 파일 열기버튼
	private: System::Void btnPIEDFileOpen_Click (System::Object^  sender, System::EventArgs^  e)
	{
		marshal_context^ fileName = gcnew marshal_context ();
		ST_RET ret;
		SCL_SERVER *scl_server;
		SCL_SUBNET *scl_subnet;



		openFileDialogPub->InitialDirectory = Directory::GetCurrentDirectory ();
		if (openFileDialogPub->ShowDialog () == System::Windows::Forms::DialogResult::OK)//파일열기에서 확인을 누르면
		{
			//기존의 정보 초기화
			tvwPIED->Nodes->Clear ();
			cbxPIEDServerName->Items->Clear ();
			cbxPIEDSubNetworkName->Items->Clear ();
			if (scl_info_pub)
			{
				scl_info_destroy (scl_info_pub);
				chk_free (scl_info_pub);
			}


			this->txtbxPIEDFilePath->Text = Path::GetFileName (openFileDialogPub->FileName);

			scl_info_pub = (SCL_INFO*)malloc (sizeof (SCL_INFO));
			ret = GetSclInfo (MARSHAL_AS (fileName, openFileDialogPub->FileName), scl_info_pub);
			delete fileName;
			if (ret)
			{
				System::Windows::Forms::MessageBox::Show ("SCL파일 파싱에러");
				return;
			}

			//서버이름 콤보박스리스트 생성
			for (scl_server = (SCL_SERVER *)list_find_last ((DBL_LNK *)scl_info_pub->serverHead);
				scl_server != NULL;
				scl_server = (SCL_SERVER *)list_find_prev ((DBL_LNK *)scl_info_pub->serverHead, (DBL_LNK *)scl_server))
			{
				cbxPIEDServerName->Items->Add ("" + marshal_as<System::String^> (scl_server->iedName));
			}
			if (cbxPIEDServerName->Items->Count > 0)
				cbxPIEDServerName->Text = cbxPIEDServerName->Items[0]->ToString ();

			//서브넷이름 콤보박스리스트 생성
			for (scl_subnet = (SCL_SUBNET *)list_find_last ((DBL_LNK *)scl_info_pub->subnetHead);
				scl_subnet != NULL;
				scl_subnet = (SCL_SUBNET *)list_find_prev ((DBL_LNK *)scl_info_pub->subnetHead, (DBL_LNK *)scl_subnet))
			{
				cbxPIEDSubNetworkName->Items->Add ("" + marshal_as<System::String^> (scl_subnet->name));
			}
			if (cbxPIEDSubNetworkName->Items->Count > 0)
				cbxPIEDSubNetworkName->Text = cbxPIEDSubNetworkName->Items[0]->ToString ();

			//트리뷰 생성
			CreateTreeView (scl_info_pub, tvwPIED, cbxPIEDServerName->Text);
		}
	}

	//저장 버튼
	private: System::Void btnSave_Click (System::Object^  sender, System::EventArgs^  e)
	{
		marshal_context^ fileName = gcnew marshal_context ();
		ST_RET ret;

		saveFileDialog->InitialDirectory = Directory::GetCurrentDirectory ();
		if (tvwAIED->Nodes->Count == 0)
			return;
		if (saveFileDialog->ShowDialog () == System::Windows::Forms::DialogResult::OK)
		{
			ConvertSclInfo (scl_info_agg, MARSHAL_AS (fileName, saveFileDialog->FileName));
			delete fileName;
		}
	}

	//subscribe 추가 버튼
	private: System::Void btnAdd_Click (System::Object^  sender, System::EventArgs^  e)
	{
		ST_RET ret;
		CONFIG_CTRL config_ctrl;
		

		if (tvwAIED->Nodes->Count == 0 || tvwPIED->Nodes->Count == 0)
		{
			System::Windows::Forms::MessageBox::Show ("파일을 먼저 불러오세요.");
			return;
		}
		
		ret = InitConfigCtrl (
			&config_ctrl,
			scl_info_agg,
			scl_info_pub,
			cbxAIEDServerName->Text,
			cbxPIEDServerName->Text,
			cbxAIEDSubNetworkName->Text,
			cbxPIEDSubNetworkName->Text
		);
		if (ret == SD_FAILURE)
		{
			return;
		}
		AddSubscription (&config_ctrl);
		CreateTreeView ((&config_ctrl)->scl_info_aggregator, tvwAIED,cbxAIEDServerName->Text);
	}

	//subscriber 제거 버튼
	private: System::Void btnRemove_Click (System::Object^  sender, System::EventArgs^  e)
	{
		ST_RET ret;
		CONFIG_CTRL config_ctrl;

		if (tvwAIED->Nodes->Count == 0 || tvwPIED->Nodes->Count == 0)
		{
			System::Windows::Forms::MessageBox::Show ("파일을 먼저 불러오세요.");
			return;
		}

		ret = InitConfigCtrl (
			&config_ctrl,
			scl_info_agg,
			scl_info_pub,
			cbxAIEDServerName->Text,
			cbxPIEDServerName->Text,
			cbxAIEDSubNetworkName->Text,
			cbxPIEDSubNetworkName->Text
		);
		if (ret == SD_FAILURE)
		{
			return;
		}
		DeleteSubscription (&config_ctrl);
		CreateTreeView ((&config_ctrl)->scl_info_aggregator, tvwAIED, cbxAIEDServerName->Text);
	}

private: System::Void cbxAIEDServerName_SelectedIndexChanged (System::Object^  sender, System::EventArgs^  e) {
	tvwAIED->Nodes->Clear ();
	CreateTreeView (scl_info_agg, tvwAIED, cbxAIEDServerName->Text);
}
private: System::Void cbxPIEDServerName_SelectedIndexChanged (System::Object^  sender, System::EventArgs^  e) {
	tvwPIED->Nodes->Clear ();
	CreateTreeView (scl_info_pub, tvwPIED, cbxPIEDServerName->Text);
}
};
}
