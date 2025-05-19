#include<iostream>
#include<ctime>
#include<cstdlib>
using namespace std;

class Player {
	int player_digit;
	int player_place;
	int dice;
	bool condition;
public:
	Player() {
		player_digit = 0;
		player_place = 0;
		dice = 0;
		condition = true;
	}
	void set_pd(int pd) {
		player_digit = pd;
	}
	void set_pp(int pp) {
		player_place = pp;
	}
	void set_condition(bool x) {
		condition = x;
	}
	int get_pd() {
		return player_digit;
	}
	int get_pp() {
		return player_place;
	}
	bool get_condition() {
		return condition;
	}
	int roll_dice() {
		return (rand() % 6) + 1;
	}
};
class Snake {

	int start_place;
	int end_place;
public:
	Snake() {
		start_place = 0;
		end_place = 0;
	}
	void set_sp(int sp) {
		start_place = sp;
	}
	void set_ep(int ep) {
		end_place = ep;
	}
	int get_sp() {
		return start_place;
	}
	int get_ep() {
		return end_place;
	}
};

class Stair {
	int start_place;
	int end_place;
public:
	Stair() {
		start_place = 0;
		end_place = 0;
	}
	void set_sp(int sp) {
		start_place = sp;
	}
	void set_ep(int ep) {
		end_place = ep;
	}
	int get_sp() {
		return start_place;
	}
	int get_ep() {
		return end_place;
	}
};

class Board {
	int lines;
	int columns;
	int players_number;
	int snakes_number;
	int stairs_number;
public:
	Board() {
		lines = 0;
		columns = 0;
		players_number = 0;
		snakes_number = 0;
		stairs_number = 0;
	}
	Board(int k, int m, int n, int n2, int n3) {
		players_number = k;
		lines = m;
		columns = n;
		snakes_number = n2;
		stairs_number = n3;
	}
	void set_k(int k) {
		players_number = k;
	}
	void set_m(int m) {
		lines = m;
	}
	void set_n(int n) {
		columns = n;
	}
	void set_snakes_num(int n) {
		snakes_number = n;
	}
	void set_stairs_num(int n) {
		stairs_number = n;
	}
	int get_k() {
		return players_number;
	}
	int get_m() {
		return lines;
	}
	int get_n() {
		return columns;
	}
	int get_snakes_num() {
		return snakes_number;
	}
	int get_stairs_num() {
		return stairs_number;
	}
};

int main(void) {
	srand(time(NULL));
	int k, m, n, snake_num, stair_num;
	cin >> k >> m >> n >> snake_num;
	Player* player = new Player[k];
	Snake* snake = new Snake[snake_num];

	for (int i = 0; i < k; i++) {
		player[i].set_pd(i + 1);
	}
	for (int i = 0, sp, ep; i < snake_num; i++) {
		cin >> sp >> ep;
		snake[i].set_sp(sp);
		snake[i].set_ep(ep);
	}
	cin >> stair_num;
	Board board(k, m, n, snake_num, stair_num);
	Stair* stair = new Stair[stair_num];
	for (int i = 0, sp, ep; i < stair_num; i++) {
		cin >> sp >> ep;
		stair[i].set_sp(sp);
		stair[i].set_ep(ep);
	}
	int survivors = k;
	while (true) {
		int i = 0;
		while (i < k) {
			if (player[i].get_condition() == true) {
				int dice = player[i].roll_dice();
				int current_place = player[i].get_pp();
				player[i].set_pp(player[i].get_pp() + dice);
				cout << "player " << player[i].get_pd() << " played with dice number " << dice << ", previous position : " << current_place << ", current position : " << player[i].get_pp() << endl;
			der: {
				for (int j = 0; j < snake_num; j++) {
					if (snake[j].get_sp() == player[i].get_pp()) {
						player[i].set_pp(snake[j].get_ep());
						goto der;
					}
				}
				for (int j = 0; j < stair_num; j++) {
					if (stair[j].get_sp() == player[i].get_pp()) {
						player[i].set_pp(stair[j].get_ep());
						goto der;
					}
				}
				for (int c = 0; c < k; c++) {
					if (c == i) {
						continue;
					}
					else{
						if (player[i].get_pp() == player[c].get_pp()) {
							cout << "player " << player[c].get_pd() << "is knocked out with player " << player[i].get_pd() << endl;
							player[c].set_pp(0);
							goto der;
						}
					}
				}
				if (player[i].get_pp() > board.get_m() * board.get_n()) {
					cout << "player " << player[i].get_pd() << "won the game" << endl;
					player[i].set_condition(false);
					survivors--;
					break;
				}
				}
			}
			i++;
		}
		if (survivors == 0) {
			break;
		}
	}
}