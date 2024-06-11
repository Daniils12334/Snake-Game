#pragma once
#include<time.h>
#include<stdlib.h>

namespace SnakeGame {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Game
	/// </summary>
	public ref class Game : public System::Windows::Forms::Form
	{
	public:
		Game(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Game()
		{
			if (components)
			{
				delete components;
			}
		}

		virtual void OnPaint(System::Object^ obj, PaintEventArgs^ e) override {
			Graphics^ g = e->Graphics;


			Brush^ fruitBrush = gcnew SolidBrush(Color::Red);
			g->FillRectangle(fruitBrush, fruitPos.X, fruitPos.Y, blockSize, blockSize);
		
			Brush^ snakeBrush = gcnew SolidBrush(Color::Green);
			g->FillRectangle(snakeBrush, snakePos.X, snakePos.Y, blockSize, blockSize);
		}

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;
		Point snakePos;
		Point fruitPos;
		const int blockSize = 20;

		Timer^ timer;
		int moveX = 1, moveY = 0;
#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->SuspendLayout();
			// 
			// Game
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(400, 400);
			this->Text = L"Snake Game";
			this->BackColor = Color::Black;
			this->ResumeLayout(false);

			snakePos = Point(100, 100);
			srand(time(NULL));
			PlaceFruit();

			timer = gcnew Timer();
			timer->Interval = 200;
			timer->Tick += gcnew EventHandler(this, &Game::OnTimerTick);
			timer->Start();

		
			this->Paint += gcnew PaintEventHandler(this, &Game::OnPaint);
			this->KeyDown += gcnew	KeyEventHandler(this, &Game::OnKeyDown);
		}
#pragma endregion
		void PlaceFruit() {
			int maxX = this->ClientSize.Width / blockSize;
			int maxY = this->ClientSize.Height / blockSize;
			fruitPos = Point(rand() % maxX * blockSize, rand() % maxY * blockSize);
		}

		void OnTimerTick(Object^ obj, EventArgs^ e) {
			snakePos.X += moveX * blockSize;
			snakePos.Y += moveY * blockSize;

			this->Invalidate();
		}

		void OnKeyDown(Object^ obj, KeyEventArgs^ e) {
			switch (e->KeyCode) {
			case Keys::Up:
				moveX = 0;
					moveY = -1;
					break;
			case Keys::Down:
				moveX = 0;
				moveY = 1;
				break;
			case Keys::Left:
				moveX = -1;
				moveY = 0;
				break;
			case Keys::Right:
				moveX = 1;
				moveY = 0;
				break;
			}
		}
	};
}
