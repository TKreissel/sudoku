#include <iostream>
#include <vector>
#include <unordered_set>
#include <math.h>

using namespace std;

vector<vector<int>> read_board(int N){
	// Read Sudoku from user input.
	vector<vector<int>> board(N,vector<int>(N));
	int n;
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			cout << "(" << i+1 << "," << j+1 << "): ";
			cin >> n;
			board[i][j] = n;
		}
	}
	return board;
}

void print_board(vector<vector<int>> board){
	//Print a given Sudoku on the screen.
	unsigned int N = board.size();
	int m = sqrt(N); // length of sub squares
	for(int i=0;i<N;i++){
		if(i%m==0 && i!=0) cout<<"\n";
		cout<<"|";
		for(int j=0;j<N;j++){
			if(j%m==0 && j!=0) cout<<"\t|";
			cout<<board[i][j]<<"|";
		}
		cout<<"\n";
	}
}


bool verify_Sudoku(vector<vector<int>> board){
	//Verifies if Sudoku is solvable according to Sudoku rules:
	//No recurrent digits from 1 to N in each...
	// - row (key: i)
	// - column (key: j)
	// - 3x3 square (key: m*(i/m)+(j/m))
	unsigned int N = board.size(); //1-D size of Sudoku board, normal case: N = 9 -> m = 3
	vector<unordered_set<int>> rows{N};
	vector<unordered_set<int>> columns{N};
	vector<unordered_set<int>> squares{N};
	int n; //current number
	int m = sqrt(N); // length of sub squares
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			n = board[i][j];
			if(n!=0){
				if(rows[i].count(n)>0) return 0;
				rows[i].insert(n);
				
				if(columns[j].count(n)>0) return 0;
				columns[j].insert(n);
				
				if(squares[m*(i/m)+(j/m)].count(n)>0) return 0;
				squares[m*(i/m)+(j/m)].insert(n);
			}
		}
	}
	return 1;
}

bool possible_position(vector<vector<int>> board, int x, int y, int n){
	//Checks if a number n can be inserted into the position (x,y).
	unsigned int N = board.size();
	int m = sqrt(N);
	for(int i=0; i<N;i++){//check the xth row
		if(board[x][i]==n) return 0;
	}
	for(int i=0; i<N;i++){//check the yth row
		if(board[i][y]==n) return 0;
	}
	for(int i=x-x%m; i<x-x%m+m;i++){//check the corresponding square
		for(int j=y-y%m; j<y-y%m+m;j++){
			if(board[i][j]==n) return 0;
		}
	}
	return 1;
}

void solve_Sudoku(vector<vector<int>> board){
	//Recursive algorithm, that prints out all possible solutions of a given Sudoku.
	unsigned int N = board.size();
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			if(board[i][j]==0){
				for(int n = 1; n<N+1; n++){
					if(possible_position(board,i,j,n)){
						board[i][j] = n;
						solve_Sudoku(board);
						board[i][j] = 0;
					}
				}
				return;
			}
		}
	}
	print_board(board);
	cout<<endl<<endl<<endl;
}

int main(){
	vector<vector<int>> board;
	int N;
	char a;
	
	do{
		cout << "Number of rows (or columns, or squares): ";
		cin >> N;
		if(int(sqrt(N))*int(sqrt(N))!=N || N == 0){
			cout << "N must be square number & N > 0."<<endl;
		}
	}while(int(sqrt(N))*int(sqrt(N))!=N || N == 0);

	do{
		cout<<"Read Sudoku (r)"<<endl;
		cin>>a;
		if(a!='r'){
			cout << "Invalid input!"<<endl;
		}else{
			board = read_board(N);
		}
	}while(a!='r');

	cout<<"Sudoku:"<<endl;
	print_board(board);
	if(verify_Sudoku(board)){
		do{
			cout << "Solve Sudoku (s)"<<endl;
			cin >> a;
		}while(a!='s');
		cout<<"Possible solutions:"<<endl;
		solve_Sudoku(board);
	}else{
		cout << "The given Sudoku breaks the Sudoku rules."<<endl;
	}
}