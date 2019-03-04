#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <math.h>

typedef struct {
	int board[20][20];
	int score;
	int prep, preq;
}Board;

typedef struct {
	int block[20];
	int line[20];
}Linescore;

Board mainBoard;
Board preBoard;

void initboard() {
	for (int i = 0; i < 19; i++) {
		for (int j = 0; j < 19; j++) {
			mainBoard.board[i][j] = 0;
		}
	}
	mainBoard.score = 0;
}

void printboard() {
	//   system("cls");
	for (int i = 0; i < 19; i++) {
		for (int j = 0; j < 19; j++) {
			switch (mainBoard.board[i][j])
			{
			case 1:
				printf("O");
				break;
			case 0:
				printf(" ");
				break;
			case -1:
				printf("X");
				break;
			default:
				printf("Unexpected board stone");
			}

		}
		printf("\n");
	}
}

int scorecal(Linescore score) {
	int sum = 0;
	for (int cnt = 0; score.line[cnt] != NULL; cnt++) {
		switch (score.block[cnt])
		{
		case 2:
			break;
		case 1:
			switch (score.line[cnt])
			{
			case 5:
				sum += 250;
				break;
			case 4:
				sum += 15;
				break;
			case 3:
				sum += 4;
				break;
			case 2:
				sum += 1;
				break;
			}
			break;
		case 0:
			switch (score.line[cnt])
			{
			case 5:
				sum += 250;
				break;
			case 4:
				sum += 50;
				break;
			case 3:
				sum += 15;
				break;
			case 2:
				sum += 4;
				break;
			}
			break;
		}
	}
	return sum;
}

int rowscore(Board b, int p, int q) {
	Linescore score;
	int cnt = 0;
	int lscore;

	for (int i = 0; i < 19; i++) {
		if (b.board[i][q] != 0) {
			int block;
			int line = 1;
			int now = b.board[i][q];

			if (i = 0) block = 1;
			if (b.board[i - 1][q] != 0) block = 1;
			else block = 0;

			i++;
			while (line<5) {
				if (b.board[i][q] == 0 && b.board[i + 1][q] == 0) {
					break;
				}
				else if (now == -b.board[i][q]) {
					block++;
					break;
				}
				else {
					line++;
				}
				i++;
			}
			score.line[cnt] = line;
			score.block[cnt] = block;

			cnt++;
		}
	}
	lscore = scorecal(score);
	return lscore;
}

int colscore(Board b, int p, int q) {
	Linescore score;
	int cnt = 0;
	int lscore;

	for (int i = 0; i < 19; i++) {
		if (b.board[p][i] != 0) {
			int block;
			int line = 1;
			int now = b.board[p][i];

			if (i = 0) block = 1;
			if (b.board[p][i - 1] != 0) block = 1;
			else block = 0;

			i++;
			while (line<5) {
				if (b.board[p][i] == 0 && b.board[p][i + 1] == 0) {
					break;
				}
				else if (now == -b.board[p][i]) {
					block++;
					break;
				}
				else {
					line++;
				}
				i++;
			}
			score.line[cnt] = line;
			score.block[cnt] = block;

			cnt++;
		}
	}
	lscore = scorecal(score);
	return lscore;
}

int diagscore1(Board b, int p, int q) {
	Linescore score;
	int cnt = 0;
	int start, end, lscore;
	if (p + q < 19) {
		start = 0;
		end = p + q;
	}
	else {
		start = p + q - 18;
		end = 18;
	}

	for (int i = start; i <= end; i++) {
		if (b.board[i][p + q - i] != 0) {
			int block;
			int line = 1;
			int now = b.board[i][p + q - i];

			if (i = 0) block = 1;
			if (b.board[i - 1][p + q - i] != 0) block = 1;
			else block = 0;


			i++;
			while (line<5) {
				if (b.board[i][p + q - i] == 0 && b.board[i + 1][p + q - i] == 0) {
					break;
				}
				else if (now == -b.board[i][p + q - i]) {
					block++;
					break;
				}
				else {
					line++;
				}
				i++;
			}
			score.line[cnt] = line;
			score.block[cnt] = block;
			cnt++;
		}
	}
	lscore = scorecal(score);
	return lscore;
}

int diagscore2(Board b, int p, int q) {
	Linescore score;
	int cnt = 0;
	int start, end, lscore;
	if (p < q) {
		start = 0;
		end = p - q + 18;
	}
	else {
		start = p - q;
		end = 18;
	}

	for (int i = start; i <= end; i++) {
		if (b.board[i][q - p + i] != 0) {
			int block;
			int line = 1;
			int now = b.board[i][q - p + i];

			if (i = 0) block = 1;
			if (b.board[i - 1][q - p + i] != 0) block = 1;
			else block = 0;

			i++;
			while (line<5) {
				if (b.board[i][q - p + i] == 0 && b.board[i + 1][q - p + i] == 0) {
					break;
				}
				else if (now == -b.board[i][q - p + i]) {
					block++;
					break;
				}
				else {
					line++;
				}
				i++;
			}
			score.line[cnt] = line;
			score.block[cnt] = block;

			cnt++;
		}
	}
	lscore = scorecal(score);
	return lscore;
}

int totalscore(Board b, Board preb, int p, int q) {
	b.score += rowscore(b, p, q) + colscore(b, p, q) + diagscore1(b, p, q) + diagscore2(b, p, q);
	b.score -= rowscore(preb, p, q) + colscore(preb, p, q) + diagscore1(preb, p, q) + diagscore2(preb, p, q);

	return b.score;
}

int terminaltest(Board b) {
	for (int i = 0; i < 19; i++) {
		for (int j = 0; j < 19; j++) {
			if (b.board[i][j] = 0) return 0;
		}
	}
	return 1;
}

Board maxval(Board b, int alpha, int beta) {
	Board v;
	if (terminaltest(b)) return v;
	v = -10000000000;
	for (int p = b.prep - 5; p < b.prep + 5; p++) {
		for (int q = b.preq - 5; q < b.preq + 5; q++) {
			b.board[p][q] = 'O';
			max(v, minval(b, alpha, beta));
			if (v >= beta) return v;
			alpha = max(alpha, v);
		}
	}
	return v;
}

int minval(Board b, int alpha, int beta) {
	int v;
	if (terminaltest(b)) return v;
	v = 10000000000;
	for (int p = b.prep - 5; p < b.prep + 5; p++) {
		for (int q = b.preq - 5; q < b.preq + 5; q++) {
			b.board[p][q] = 'O';
			min(v, maxval(b, alpha, beta));
			if (v <= alpha) return v;
			beta = min(beta, v);
		}
	}
	return v;
}

Board alphabeta(Board state) {
	Board v = maxval(state, -10000000000, 10000000000);
	return v;
}

void player() {
	int p, q;
	preBoard = mainBoard;
	printf("Enter row and column number: ");
	scanf_s("%d %d", &p, &q);
	mainBoard.board[p][q] = 1;
}

void comp() {
	int p, q;
	preBoard = mainBoard;
	printf("Enter row and column number: ");
	scanf_s("%d %d", &p, &q);
	mainBoard.board[p][q] = -1;
}

int main() {
	initboard();

	while (1) {
		player();
		printboard();
		comp();
		printboard();
	}

	return 0;
}