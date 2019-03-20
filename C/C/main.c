#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <math.h>

typedef struct {
	int board[20][20];
	int score;
	int p[400];
	int q[400];
}Board;

typedef struct {
	int block[20];
	int line[20];
	int side[20];
}Linescore;

Board mainBoard;
int move_num;

void initboard();
void printboard(Board b);
int scorecal(Linescore score);
int rowscore(Board b, int p, int q);
int colscore(Board b, int p, int q);
int diagscore1(Board b, int p, int q);
int diagscore2(Board b, int p, int q);
int totalscore(Board b, Board preb, int p, int q);
int terminaltest(Board b);
Board maxval(Board b, int alpha, int beta, int depth);
Board minval(Board b, int alpha, int beta, int depth);
Board alphabeta(Board state);
void player();
void comp();
char* game_end();

int main() {
	initboard();
	while (1) {
		if (game_end()) {
			printf("%s win!\n",game_end());
			break;
		}
		player();
		printboard(mainBoard);
		comp();
		printboard(mainBoard);
	}

	return 0;
}

char* game_end() {
	if (mainBoard.score > 150) {
		return "Computer";
	}
	else if (mainBoard.score <  -150) {
		return "Player";
	}
	else
	{
		return NULL;
	}
}

void initboard() {
	for (int i = 0; i < 19; i++) {
		for (int j = 0; j < 19; j++) {
			mainBoard.board[i][j] = 0;
		}
	}
	mainBoard.score = 0;
	move_num = 0;
}

void printboard(Board b) {
	//system("cls");
	for (int i = 0; i < 19; i++) {
		for (int j = 0; j < 19; j++) {
			switch (b.board[i][j])
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
	printf("Board의 점수는 %d\n", b.score);
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
				sum -= 250 * score.side[cnt];
				break;
			case 4:
				sum -= 30 * score.side[cnt];
				break;
			case 3:
				sum -= 4 * score.side[cnt];
				break;
			case 2:
				sum -= 1 * score.side[cnt];
				break;
			}
			break;
		case 0:
			switch (score.line[cnt])
			{
			case 5:
				sum -= 250 * score.side[cnt];
				break;
			case 4:
				sum -= 50 * score.side[cnt];
				break;
			case 3:
				sum -= 15 * score.side[cnt];
				break;
			case 2:
				sum -= 4 * score.side[cnt];
				break;
			}
			break;
		default:
			break;
		}
	}
	return sum;
}

int rowscore(Board b, int p, int q) {
	Linescore score = { -1, -1, -1 };
	int cnt = 0;
	int lscore;
	for (int i = 0; i < 19; i++) {
		if (b.board[i][q] != 0) {
			int block;
			int line = 1;
			int blank = 0;
			int now = b.board[i][q];

			if (i == 0 || b.board[i - 1][q] != 0) block = 1;
			else block = 0;

			i++;
			while ((blank+line)<5) {
				if (b.board[i][q] == 0 && b.board[i + 1][q] == 0) {
					break;
				}
				else if (now == -b.board[i][q]) {
					block++;
					break;
				}
				else if (b.board[i][q] == 0) {
					blank++;
				}
				else{
					line++;
				}
				i++;
			}
			score.line[cnt] = line;
			score.block[cnt] = block;
			score.side[cnt] = now;
			cnt++;
		}
	}
	lscore = scorecal(score);
	return lscore;
}

int colscore(Board b, int p, int q) {
	Linescore score = { -1, -1, -1 };
	int cnt = 0;
	int lscore;
	int blank = 0;

	for (int i = 0; i < 19; i++) {
		if (b.board[p][i] != 0) {
			int block;
			int line = 1;
			int now = b.board[p][i];

			if (i == 0) block = 1;
			if (b.board[p][i - 1] != 0) block = 1;
			else block = 0;

			i++;
			while ((blank + line)<5) {
				if (b.board[p][i] == 0 && b.board[p][i + 1] == 0) {
					break;
				}
				else if (now == -b.board[p][i]) {
					block++;
					break;
				}
				else if (b.board[p][i] == 0) {
					blank++;
				}
				else {
					line++;
				}
				i++;
			}
			score.line[cnt] = line;
			score.block[cnt] = block;
			score.side[cnt] = now;

			cnt++;
		}
	}
	lscore = scorecal(score);
	return lscore;
}

int diagscore1(Board b, int p, int q) {
	Linescore score = { -1, -1, -1 };
	int cnt = 0;
	int start, end, lscore;
	int blank = 0;
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

			if (i == 0) block = 1;
			if (b.board[i - 1][p + q - i] != 0) block = 1;
			else block = 0;


			i++;
			while ((blank + line)<5) {
				if (b.board[i][p + q - i] == 0 && b.board[i + 1][p + q - i] == 0) {
					break;
				}
				else if (now == -b.board[i][p + q - i]) {
					block++;
					break;
				}
				else if (b.board[i][p + q - i] == 0) {
					blank++;
				}
				else {
					line++;
				}
				i++;
			}
			score.line[cnt] = line;
			score.block[cnt] = block;
			score.side[cnt] = now;
			cnt++;
		}
	}
	lscore = scorecal(score);
	return lscore;
}

int diagscore2(Board b, int p, int q) {
	Linescore score = { -1, -1, -1 };
	int cnt = 0;
	int start, end, lscore;
	int blank = 0;
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

			if (i == 0) block = 1;
			if (b.board[i - 1][q - p + i] != 0) block = 1;
			else block = 0;

			i++;
			while ((blank+line)<5) {
				if (b.board[i][q - p + i] == 0 && b.board[i + 1][q - p + i] == 0) {
					break;
				}
				else if (now == -b.board[i][q - p + i]) {
					block++;
					break;
				}
				else if (b.board[i][q - p + i] == 0) {
					blank++;
				}
				else {
					line++;
				}
				i++;
			}
			score.line[cnt] = line;
			score.block[cnt] = block;
			score.side[cnt] = now;

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
			if (b.board[i][j] == 0) return 0;
		}
	}
	return 1;
}

int taken_check(Board b,int p,int q) 
{
	if (b.board[p][q] != 0) return 1;
	return 0;
}

Board maxval(Board b, int alpha, int beta,int depth) {
	Board v, mv;
	depth++;
	v.score = -100000;
	if (depth == 5) return b;
	if (terminaltest(b)) return b;
	for (int p = b.p[move_num + depth - 1]-5; p < b.p[move_num + depth - 1] + 5; p++) {
		for (int q = b.q[move_num + depth - 1]-5; q < b.q[move_num + depth - 1] + 5; q++) {
			Board postBoard = b;
			if (p < 0 || p>18 || q < 0 || q>18) {
				continue;
			}
			else if (taken_check(b, p, q)) continue;
			postBoard.board[p][q] = -1;
			postBoard.p[move_num + depth] = p;
			postBoard.q[move_num + depth] = q;
			postBoard.score = totalscore(postBoard, b, p, q);
			mv = minval(postBoard, alpha, beta, depth);
			if (v.score < mv.score)	v = mv;
			if (v.score >= beta) return v;
			alpha = max(alpha, v.score);
		}
	}
	return v;
}

Board minval(Board b, int alpha, int beta, int depth) {
	Board v, mv;
	depth++;
	v.score = 10000000;
	if (depth == 5) return b;
	if (terminaltest(b)) return b;
	for (int p = b.p[move_num + depth - 1] - 5; p < b.p[move_num + depth - 1] + 5; p++) {
		for (int q = b.q[move_num + depth - 1] - 5; q < b.q[move_num + depth - 1] + 5; q++) {
			Board postBoard = b;
			if (p < 0 || p>18 || q < 0 || q>18) continue;
			else if (taken_check(b, p, q)) continue;
			postBoard.board[p][q] = 1;
			postBoard.p[move_num + depth] = p;
			postBoard.q[move_num + depth] = q;
			postBoard.score = totalscore(postBoard, b, p, q);
			mv = maxval(postBoard, alpha, beta, depth);
			if (v.score > mv.score) v = mv;
			if (v.score <= alpha) return v;
			beta = min(beta, v.score);
		}
	}
	return v;
}

Board alphabeta(Board state) {
	Board v = maxval(state, -100000, 100000,0);
	return v;
}

void player() {
	int p, q;
	Board preBoard = mainBoard;
	while (1) {
		printf("Enter row and column number: ");
		scanf_s("%d %d", &p, &q);
		if (p < 0 || p>18 || q < 0 || q>18) {
			printf("Stone out of Board\n");
			printf("Enter valid number between 0~18\n");
			continue;
		}
		else if (taken_check(mainBoard, p, q)) {
			printf("Space aready taken\n");
			continue;
		}
		else {
			break;
		}
	}
	move_num++;
	mainBoard.p[move_num] = p;
	mainBoard.q[move_num] = q;
	mainBoard.board[p][q] = 1;
	mainBoard.score = totalscore(mainBoard, preBoard, p, q);
}

void comp() {
	Board preBoard = mainBoard;
	Board abBoard = alphabeta(mainBoard);

	preBoard = mainBoard;
	printboard(abBoard);
	move_num++;
	mainBoard.board[abBoard.p[move_num]][abBoard.q[move_num]] = -1;
	mainBoard.score = totalscore(mainBoard, preBoard, abBoard.p[move_num], abBoard.q[move_num]);
}
