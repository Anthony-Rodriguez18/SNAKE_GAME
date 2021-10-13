//Librerías
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include <conio.h>

//Creamos las variables
bool juego;
const int ancho = 30, alto = 20;
int x, y, frutax, frutay, score;
int colax[ancho], colay[alto];
int cola;
int vidas = 3;
double velocidad = 100000000;
int frutaMx, frutaMy;
//Direccionales
enum mover { STOP = 0, LEFT, RIGHT, UP, DOWN };
int a = 0;
mover dir;
//Iniciamos valores como:
void Iniciacion() {
	//Bucle del juego
	juego = true;
	//Posición estática
	dir = STOP;
	//Ubicación de la serpiente y frutas
	x = ancho / 2;
	y = alto / 2;
	frutaMx = (rand() % ancho);
	frutaMy = (rand() % alto);
	frutax = (rand() % ancho);
	frutay = (rand() % alto);
	score = 0;
}

void Dibujar() {
	std::cout << "\033[H\033[2J\033[3J";
	std::cout << "Score: " << score << std::endl;
	std::cout << "Vidas: " << vidas << std::endl;
	std::cout << "Velocidad: " << velocidad << std::endl;
	putchar(201);
	for (int i = 0; i < ancho; i++){
		putchar(205);
	}
	putchar(187);
	std::cout << "\n";

	for (int a = 0; a < alto; a++) {
		for (int b = 0; b < ancho; b++) {
			if (b == 0)
			{
				putchar(186);
			}
			if (a == y && b == x)
				std::cout << "O";
			else if (a == frutay && b == frutax)
			{
				putchar(207);

			}
			else if (a == frutaMy && b == frutaMx)
			{
				if (score % 30 == 0 && score != 0)
				{
					putchar(220);
				}
				else
					std::cout << " ";
			}
			else {
				//std::cout<<" ";
				bool sam = false;
				for (int c = 0; c < cola; c++) {
					if (colax[c] == b && colay[c] == a) {
						std::cout << "o";
						sam = true;
					}
				}
				if (!sam) {
					std::cout << " ";
				}
			}
			if (b == ancho - 1)
			{
				putchar(186);
				std::cout << "\n";
			}
		}
	}
	putchar(200);

	for (int i = 0; i < ancho; i++)
	{
		putchar(205);
	}
	putchar(188);
	std::cout << "\n";
}

void Teclas()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'w':
			dir = UP;
			break;
		case 'x':
			juego = false;
			break;
		}
	}
}

void Logica() {
	int antX = colax[0];
	int antY = colay[0];
	int ant2X, ant2Y;
	colax[0] = x;
	colay[0] = y;
	for (int a = 1; a < cola; a++) {
		ant2X = colax[a];
		ant2Y = colay[a];
		colax[a] = antX;
		colay[a] = antY;
		antX = ant2X;
		antY = ant2Y;
	}
	switch (dir) {
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case DOWN:
		y++;
		break;
	case UP:
		y--;
		break;

	}
	if (vidas <= 0) {
		juego = false;
	}

	//Si choca con los bordes fin
	if (x >= ancho || x < 0 || y >= alto || y < 0)
	{
		x = ancho / 2;
		y = alto / 2;
		vidas--;
		//Sleep(200);
	}
	for (int a = 0; a < cola; a++) {
		if (colax[a] == x && colay[a] == y)
		{
			vidas--;
			x = ancho / 2;
			y = alto / 2;
		}
	}

	//Frutita
	if (x == frutax && y == frutay) {
		cola++;
		score += 10;
		if (score == 50) { vidas++; }
		frutax = rand() % ancho;
		frutay = rand() % alto;
	}
	if (x == frutaMx && y == frutaMy) {
		score += 10;
		velocidad += 1000000;
		frutaMx = rand() % ancho;
		frutaMy = rand() % alto;
	}
}

int main()
{
	system("title Juego Snake - CCOMP2-1");
	system("color 2");
	srand((unsigned)time(0));
	Iniciacion();
	Beep(900, 800);
	while (juego) {
		//Beep(900, 800);
		velocidad = velocidad - 10000;
		Dibujar();
		Teclas();
		Logica();
		while (a < velocidad) {
			a++;
		}
		a = 0;

	}
	Beep(1100, 400);
	Beep(1000, 400);
	Beep(900, 400);
	system("color 4");
	std::cout << "\033[H\033[2J\033[3J";
	std::cout << "vidas: " << vidas << std::endl;
	std::cout << "Score: " << score << std::endl;
	std::cout << "Buen juego";
	return 0;
}