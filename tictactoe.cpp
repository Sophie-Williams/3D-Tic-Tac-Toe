//Some assumptions:
//1. In case of input cube, it's assumed that the cube is already a Magic Cube. Didn't implement a tester function for that. Isn't much difficult to do so though
//2. The human player always gives valid input - that is input is in [1,27]. No function to validate input. Only test - whether a number has already been used or not which was anyways necessary


#include <bits/stdc++.h>

using namespace std;

class MagicCube
{
	private:
		int myCube [3][3][3]; //Cube follows zero based indexing
		bool usedUp [27]; //Keeps track of what number has been used
		bool foundCube; //Check if the correct cube has been found
	public:
		MagicCube() //Constructor for initialization
		{
			memset(myCube, 0, sizeof(myCube));
			memset(usedUp, 0, sizeof(usedUp));
			foundCube = 0;
		}
		void generateCube() //Start generating cube
		{
			fillNum(0,0,0); //Starts from coordinates (0,0,0). Any other coordinate can be chosen, but then the search takes a lot more time, because of the nature of the search.
		}
		//Algorithm: A simple backtracking algorithm, that gives better performance than brute force
		//because we won't go on if a row/column/diagonal is filled and does not sum up to 42. 
		void fillNum(int i, int j, int k)
		{
			if(foundCube)//If the correct cube is found then stop lookup
				return;
			for(int r=0; r<27; r++)
			{
				if(!usedUp[r]) //If the number (r+1) has not been used up already.
				{
					myCube[i][j][k]=(r+1); //Assign (r+1) to coordinates (i,j,k)
					usedUp[r]=1; //Note that we have used up (r+1)
					bool flag=true; //We check if a row/column/diagonal is complete and it's validity
					if(completeRow(i, j)&&!validRow(i, j))
					{
						flag=false;
					}
					if(completeColumn(i, k)&&!validColumn(i, k))
					{
						flag=false;
					}
					if(completePillar(j, k)&&!validPillar(j, k))
					{
						flag=false;
					}
					if(flag)//Proceed iff validity has been verified
					{
						if(filledUp()) //Check if cube is filled up
						{
							if(validCube()) //If cube is a magic cube
							{
								foundCube=1; //We found our cube.
								return;
							}
						}
						else
						{
							if(i<2) //Filling up the next position, keeping in mind of the coordinates wrap. That is, (3,2,0) is same as (0,2,0)
							{
								if(k==2)
								{
									if(j==2)
									{
										fillNum(i+1, 0, 0);
									}
									else
									{
										fillNum(i, j+1, 0);
									}
								}
								else
								{
									fillNum(i, j, k+1);
								}
							}
							else
							{
								if(k==2)
								{
									if(j==2)
									{
										fillNum(0, 0, 0);

									}
									else
									{
										fillNum(i, j+1, 0);
									}
								}
								else
								{
									fillNum(i, j, k+1);
								}
							}
						}
					}
					if(foundCube) 
						return;
					myCube[i][j][k]=0; //Remove (r+1) from the position (i,j,k) as part of backtracking
					usedUp[r]=0; //We don't use it anymore for now.
				}
			}
		}
		bool filledUp() //Utility to check if the Cube is completely filled up
		{
			bool res=true;
			for(int i=0; i<27; i++)
			{
				if(!usedUp[i])
				{
					res=false;
					break;
				}
			}
			return res;
		}
		bool validCube() //Utility to validate whether Cube is a Magic Cube
		{
			for(int i=0; i<3; i++)
			{
				for(int j=0; j<3; j++)
				{
					if(!validRow(i,j)||!validColumn(i,j))
					{
						return false;
					}
				}
			}
			for(int j=0; j<3; j++)
			{
				for(int k=0; k<3; k++)
				{
					if(!validPillar(j,k))
					{
						return false;
					}
				}
			}
			if(!validDiagonals())
			{
				return false;
			}
			return true;
		}
		bool validRow(int i, int j) //Check if the j'th row in layer i is valid 
		{
			if(myCube[i][j][0]+myCube[i][j][1]+myCube[i][j][2]!=42)
				return false;
			return true;
		}
		bool completeRow(int i, int j) //Check if the j'th row in layer i is completely filled
		{
			if(myCube[i][j][0]==0||myCube[i][j][1]==0||myCube[i][j][2]==0)
				return false;
			return true;
		}
		bool validColumn(int i, int k) //Check if the k'th column in layer i is valid
		{
			if(myCube[i][0][k]+myCube[i][1][k]+myCube[i][2][k]!=42)
				return false;
			return true;
		}
		bool completeColumn(int i, int k) //Check if the k'th row in layer i is completely filled
		{
			if(myCube[i][0][k]==0||myCube[i][1][k]==0||myCube[i][2][k]==0)
				return false;
			return true;
		}
		bool validPillar(int j, int k) //Check if the pillar passing (i,j) is valid
		{
			if(myCube[0][j][k]+myCube[1][j][k]+myCube[2][j][k]!=42)
				return false;
			return true;
		}
		bool completePillar(int j, int k) //Check if the pillar passing (i,j) is completely filled
		{
			if(myCube[0][j][k]==0||myCube[1][j][k]==0||myCube[2][j][k]==0)
				return false;
			return true;
		}
		bool validDiagonals() //Check if all the body diagonals are valid
		{
			if(myCube[0][0][0]+myCube[1][1][1]+myCube[2][2][2]!=42)
				return false;
			if(myCube[0][2][0]+myCube[1][1][1]+myCube[2][0][2]!=42)
				return false;
			if(myCube[0][2][2]+myCube[1][1][1]+myCube[2][0][0]!=42)
				return false;
			if(myCube[0][0][2]+myCube[1][1][1]+myCube[2][2][0]!=42)
				return false;
			return true;
		}
		void printCube() //Utility to print the Magic Cube according to specifications
		{
			cout<<"Outer Surfaces follows:"<<endl;
			cout<<endl;
			cout<<"Top Surface:"<<endl;
			for(int j=0; j<3; j++)
			{
				for(int k=0; k<3; k++)
				{
					cout<<myCube[0][j][k]<<" ";
				}
				cout<<endl;
			}
			cout<<endl;
			cout<<"Bottom Surface:"<<endl;
			for(int j=0; j<3; j++)
			{
				for(int k=0; k<3; k++)
				{
					cout<<myCube[2][j][k]<<" ";
				}
				cout<<endl;
			}
			cout<<endl;
			cout<<"Left Surface:"<<endl;
			for(int i=0; i<3; i++)
			{
				for(int j=0; j<3; j++)
				{
					cout<<myCube[i][j][0]<<" ";
				}
				cout<<endl;
			}
			cout<<endl;
			cout<<"Right Surface:"<<endl;
			for(int i=0; i<3; i++)
			{
				for(int j=0; j<3; j++)
				{
					cout<<myCube[i][j][2]<<" ";
				}
				cout<<endl;
			}
			cout<<endl;
			cout<<"Front Surface:"<<endl;
			for(int i=0; i<3; i++)
			{
				for(int k=0; k<3; k++)
				{
					cout<<myCube[i][2][k]<<" ";
				}
				cout<<endl;
			}
			cout<<endl;
			cout<<"Back Surface:"<<endl;
			for(int i=0; i<3; i++)
			{
				for(int k=0; k<3; k++)
				{
					cout<<myCube[i][0][k]<<" ";
				}
				cout<<endl;
			}
			cout<<endl;
			cout<<"Vertical Surfaces follows:"<<endl;
			cout<<endl;
			cout<<"Middle Surface-Left Facing:"<<endl;
			for(int i=0; i<3; i++)
			{
				for(int j=0; j<3; j++)
				{
					cout<<myCube[i][j][1]<<" ";
				}
				cout<<endl;
			}
			cout<<endl;
			cout<<"Middle Surface-Front Facing:"<<endl;
			for(int i=0; i<3; i++)
			{
				for(int k=0; k<3; k++)
				{
					cout<<myCube[i][1][k]<<" ";
				}
				cout<<endl;
			}
			cout<<endl;
			cout<<"Middle Surface-Top Facing:"<<endl;
			for(int j=0; j<3; j++)
			{
				for(int k=0; k<3; k++)
				{
					cout<<myCube[1][j][k]<<" ";
				}
				cout<<endl;
			}
			cout<<endl;
			cout<<"Diagonal Surfaces follows:"<<endl;
			cout<<endl;
			cout<<"Diagonal Surface 1:"<<endl;
			for(int i=0; i<3; i++)
			{
				for(int j=0; j<3; j++)
				{
					cout<<myCube[i][j][j]<<" ";
				}
				cout<<endl;
			}
			cout<<endl;
			cout<<"Diagonal Surface 2:"<<endl;
			for(int i=0; i<3; i++)
			{
				for(int j=0; j<3; j++)
				{
					cout<<myCube[i][j][2-j]<<" ";
				}
				cout<<endl;
			}
			cout<<endl;

		}
		void returnCube(int outCube [][3][3]) //Utility to return the Magic Cube
		{
			for(int i=0; i<3; i++)
			{
				for(int j=0; j<3; j++)
				{
					for(int k=0; k<3; k++)
					{
						outCube[i][j][k]=myCube[i][j][k];
					}
				}
			}
		}
};

struct Coor //A struct to define coordinate type for better handling
{
	int i, j, k;
};

bool checkCollinear(Coor P, Coor Q, Coor R) //Utility to check if 3 points are collinear
{
	//Algorithm: We will make use of 2 vectors PQ and PR. If the cosine of angle between the two is +1 or -1, it's collinear else not.
	Coor PQ, PR; //Coor struct can be used for vector purpose too.
	PQ.i = Q.i-P.i, PQ.j = Q.j-P.j, PQ.k = Q.k-P.k;
	PR.i = R.i-P.i, PR.j = R.j-P.j, PR.k = R.k-P.k; 
	double val = pow((PQ.i*PR.i+PQ.j*PR.j+PQ.k*PR.k),2)/((1.0)*(PQ.i*PQ.i+PQ.j*PQ.j+PQ.k*PQ.k)*(PR.i*PR.i+PR.j*PR.j+PR.k*PR.k));
	if(val==1)
		return true;
	else
		return false;
}

//This function finds next move for the computer, in case it doesn't get to create a collinear line
//or there is no way of blocking the human player
int make_2(bool movesMade[], int Cube[][3][3]) 
{
	if(movesMade[Cube[1][1][1]]==0)
		return Cube[1][1][1];
	else
	if(movesMade[Cube[0][0][0]]==0)
		return Cube[0][0][0];
	else
	if(movesMade[Cube[0][0][2]]==0)
		return Cube[0][0][2];
	else
	if(movesMade[Cube[0][2][2]]==0)
		return Cube[0][2][2];
	else
	if(movesMade[Cube[0][2][0]]==0)
		return Cube[0][2][0];
	else
	if(movesMade[Cube[2][0][0]]==0)
		return Cube[2][0][0];
	else
	if(movesMade[Cube[2][0][2]]==0)
		return Cube[2][0][2];
	else
	if(movesMade[Cube[2][2][2]]==0)
		return Cube[2][2][2];
	else
	if(movesMade[Cube[2][2][0]]==0)
		return Cube[2][2][0];
	else
	if(movesMade[Cube[0][1][1]]==0)
		return Cube[0][1][1];
	else
	if(movesMade[Cube[2][1][1]]==0)
		return Cube[2][1][1];
	else
	if(movesMade[Cube[1][0][1]]==0)
		return Cube[1][0][1];
	else
	if(movesMade[Cube[1][1][0]]==0)
		return Cube[1][1][0];
	else
	if(movesMade[Cube[1][2][1]]==0)
		return Cube[1][2][1];
	else
	if(movesMade[Cube[1][1][2]]==0)
		return Cube[1][1][2];
	else
	if(movesMade[Cube[0][0][1]]==0)
		return Cube[0][0][1];
	else
	if(movesMade[Cube[0][1][0]]==0)
		return Cube[0][1][0];
	else
	if(movesMade[Cube[0][2][1]]==0)
		return Cube[0][2][1];
	else
	if(movesMade[Cube[0][1][2]]==0)
		return Cube[0][1][2];
	else
	if(movesMade[Cube[2][0][1]]==0)
		return Cube[2][0][1];
	else
	if(movesMade[Cube[2][1][0]]==0)
		return Cube[2][1][0];
	else
	if(movesMade[Cube[2][2][1]]==0)
		return Cube[2][2][1];
	else
	if(movesMade[Cube[2][1][2]]==0)
		return Cube[2][1][2];
	else
	{
		while(true)
		{
			int move = rand()%27+1;
			if(movesMade[move]==0)
				return move;
		}
	}
}

//Utility to find whether a win is possibles. It works on the same line as the Algorithm specified in the lecture slides
int possWin(vector<int> &Moves, bool invalidTuples[][28][28], Coor M[], bool movesMade[])
{
	int N = Moves.size(); 
	if(N<2) //If number of moves made is less than 2, no way of finding a win.
		return 0;
	for(int i=0; i<N; i++)
	{
		for(int j=i+1; j<N; j++)
		{
			int newmove=42-Moves[i]-Moves[j]; //Possible third move
			if(newmove<=27&&newmove!=Moves[i]&&newmove!=Moves[j]) //This third move should fulfill basic conditions - unique, and <=27
			{
				if(!movesMade[newmove]) //Move hasn't been made
				{
					//Making sure num1<num2<num3 for easy handling of info.
					int num1=min(Moves[i],min(Moves[j],newmove)), num3=max(Moves[i],max(Moves[j],newmove));
					int num2=42-num1-num3;
					if(!invalidTuples[num1][num2][num3]) //Make sure this tuple isn't actually invalid; invalid defined later in main() 
					{
						Coor P=M[num1], Q=M[num2], R=M[num3];
						if(checkCollinear(P,Q,R)==1) //Call collinear function
						{
							return newmove; //If collinear this is the winning move
						}
					}
				}
			}
		}
	}
	return 0;
}

//This utility is mainly for the human player, in case he/she is able to score a win.
bool scoredPoint(vector<int> &Moves, bool covered[][28][28], Coor M[], bool invalidTuples[][28][28])
{
	int N=Moves.size(); 
	if(N<3) 
		return 0; //If N<3 no point scored
	//Finding whether a point has been scored, and marking down the tuple which scored a point
	for(int i=0; i<N; i++)
	{
		for(int j=i+1; j<N; j++)
		{
			for(int k=j+1; k<N; k++)
			{
				if(Moves[i]+Moves[j]+Moves[k]==42) //Sum must be 42
				{
					//Again num1<num2<num3. 
					int num1=min(Moves[i],min(Moves[j],Moves[k])), num3=max(Moves[i],max(Moves[j],Moves[k]));
					int num2=42-num1-num3;
					if(!invalidTuples[num1][num2][num3]) //Tuple shouldn't be invalid
					{	
						Coor P=M[num1], Q=M[num2], R=M[num3];
						if(checkCollinear(P,Q,R)==1&&!covered[num1][num2][num3]) //Collinear and tuple not covered yet.
						{
							covered[num1][num2][num3]=1; //if tuple covered no need to look for anymore. In fact, it's guaranteed that this is the only tuple which hasn't been marked down yet
							return 1;
						}
					}
				}
			}
		}
	}
	return 0;
}

//In case human plays first.
void humanFirst(vector<int> &HMoves, vector<int> &CMoves, int Cube[][3][3], bool invalidTuples[][28][28], Coor M[])
{
	int countH=0, countC=0;
	bool movesMade[28]={};
	bool covered[28][28][28]={};//Collinear tuples covered
	int move;
	for(int i=1; i<=20; i++)
	{
		if(i%2==1)//This is human move
		{
			cout<<"Enter the move you want to play: ";
			cin>>move;
			while(movesMade[move]) //If the human enters a move which has already been played before.
			{
				cout<<"This space has already been filled. Select another: ";
				cin>>move;
			}
			HMoves.push_back(move); //Store the move
			movesMade[move]=1; //Move marked
			if(scoredPoint(HMoves, covered, M, invalidTuples))
			{
				countH++; //If a point is scored, update counter for human
			}
		}
		else //This is computer Move
		{
			if(i/2<2) //Both computer and human haven't made enough moves for computer to try/block a point
			{
				int move=make_2(movesMade, Cube); //Make a move
				CMoves.push_back(move); //Store the move
				movesMade[move]=1; //Move marked
			}
			else
			{
				//Priority order: Check Computer Win > Block Human Win > move_2
				int win=possWin(CMoves, invalidTuples, M, movesMade); 
				if(win>0&&!movesMade[win]) //If winning move for computer exists, and that move hasn't been made yet
				{
					CMoves.push_back(win); //Make that move and score the point
					movesMade[win]=1; //Move marked
					scoredPoint(CMoves, covered, M, invalidTuples);
					countC++;
				}
				else
				{
					win=possWin(HMoves, invalidTuples, M, movesMade); 
					if(win&&!movesMade[win]) //If winning move for human exists and it hasn't been played yet (probably need not check this part) then block the move!
					{
						CMoves.push_back(win); //Play the move blocking a point for human
						movesMade[win]=1; //Move marked
					}	
					else
					{
						move=make_2(movesMade, Cube); //If can't do anything, find a move using make_2() utility
						CMoves.push_back(move);
						movesMade[move]=1;
					}
				}
			}
			//Printing moves of humans and computers after every even move
			cout<<"Your moves: [ ";
			for(int k=0; k<HMoves.size(); k++)
			{
				cout<<HMoves[k]<<", ";
			}
			cout<<"]"<<endl;
			cout<<"Computer's moves: [ ";
			for(int k=0; k<CMoves.size(); k++)
			{
				cout<<CMoves[k]<<", ";
			}
			cout<<"]"<<endl;
		}
	}
	//Small utility which declares who won
	cout<<"20 Moves up! Your score is "<<countH<<" and Computer's score is "<<countC<<endl;
	if(countH>countC)
		cout<<"You win!"<<endl;
	else
	if(countC>countH)
		cout<<"Computer wins!"<<endl;
	else
		cout<<"It's a tie!"<<endl;
}

//In case the computer plays first. It's almost identical to humanFirst() so no separate explanation needed.
void computerFirst(vector<int> &HMoves, vector<int> &CMoves, int Cube[][3][3], bool invalidTuples[][28][28], Coor M[])
{
	int countH=0, countC=0;
	bool movesMade[28]={};
	bool covered[28][28][28]={};//Collinear tuples covered
	int move;
	for(int i=1; i<=20; i++)
	{
		if(i%2==0)//Human move
		{
			cout<<"Enter the move you want to play: ";
			cin>>move;
			while(movesMade[move])
			{
				cout<<"This space has already been filled. Select another: ";
				cin>>move;
			}
			HMoves.push_back(move);
			movesMade[move]=1;
			if(scoredPoint(HMoves, covered, M, invalidTuples))
			{
				countH++;
			}
			cout<<"Your moves: [ ";
			for(int k=0; k<HMoves.size(); k++)
			{
				cout<<HMoves[k]<<", ";
			}
			cout<<"]"<<endl;
			cout<<"Computer's moves: [ ";
			for(int k=0; k<CMoves.size(); k++)
			{
				cout<<CMoves[k]<<", ";
			}
			cout<<"]"<<endl;
		}
		else //Computer Move
		{
			if(i/2<2)
			{
				int move=make_2(movesMade, Cube);
				CMoves.push_back(move);
				movesMade[move]=1;
			}
			else
			{
				int win=possWin(CMoves, invalidTuples, M, movesMade);
				if(win>0&&!movesMade[win])
				{
					CMoves.push_back(win);
					movesMade[win]=1;
					scoredPoint(CMoves, covered, M, invalidTuples);
					countC++;
				}
				else
				{
					
					win=possWin(HMoves, invalidTuples, M, movesMade);
					if(win&&!movesMade[win])
					{
						CMoves.push_back(win);
						movesMade[win]=1;
					}
					else
					{
						move=make_2(movesMade, Cube);
						CMoves.push_back(move);
						movesMade[move]=1;
					}
				}
			}
		}
	}
	cout<<"20 Moves up! Your score is "<<countH<<" and Computer's score is "<<countC<<endl;
	if(countH>countC)
		cout<<"You win!"<<endl;
	else
	if(countC>countH)
		cout<<"Computer wins!"<<endl;
	else
		cout<<"It's a tie!"<<endl;
}


int main()
{
	int Cube[3][3][3], opt; //intializing cube array and option variable
	cout<<"Options: (Select 1 or 2)"<<endl;
	cout<<"1. Enter your own Magic Cube"<<endl;
	cout<<"2. Generate a Magic Cube"<<endl;
	cin>>opt;
	if(opt==1)
	{
		while(true)
		{
			cout<<"Enter the three layers. Each layer is a 3x3 matrix. (Order: Top-Middle-Bottom) "<<endl;
			for(int i=0; i<3; i++) //Enter the Cube
			{
				for(int j=0; j<3; j++)
				{
					for(int k=0; k<3; k++)
					{
						cin>>Cube[i][j][k];
					}
				}
			}

		}
	}
	else
	{
		cout<<"Generating and printing Magic Cube"<<endl;
		MagicCube M; //Object of class MagicCube. Member functions explained above
		M.generateCube(); 
		M.printCube();
		M.returnCube(Cube);
	}
	Coor M[28]; //Stores the coordinates corresponding to a number in [1,27];
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
		{
			for(int k=0; k<3; k++)
			{
				Coor P;
				P.i=i, P.j=j, P.k=k;
				M[Cube[i][j][k]]=P;//Storing the coordinates
			}
		}
	}  
	//Generate all the tuples that add up to 42 but aren't collinear
	bool check[28][28][28]={}; //Check if a tuple has already been generated and checked or not.
	bool invalidTuples[28][28][28]={}; //If a tuple is a valid one (add upto 42) and isn't collinear, then the value is to be marked 1.
	// cout<<"Generating non collinear numbers that add upto 42"<<endl;
	for(int a=1; a<=27; a++)
	{
		for(int b=a+1; b<=27; b++)
		{
			int c=42-a-b;
			if(c>0&&c<=27&&c!=a&&c!=b) //Generating valid numbers (a,b,c) that denotes a tuple.
			{	
				int num1=min(a,min(b,c)), num3=max(a,max(b,c));
				int num2=42-num1-num3; //sequencing (a,b,c) s.t. a<=b<=c
				if(!check[num1][num2][num3]) //If tuple hasn't been checked yet.
				{
					check[num1][num2][num3]=1; 
					Coor P = M[num1], Q=M[num2], R=M[num3];
					if(!checkCollinear(P,Q,R)) //If tuple isn't collinear
					{
						// cout<<num1<<" "<<num2<<" "<<num3<<endl;
						invalidTuples[num1][num2][num3]=1; //We keep track of non collinear valid tuples
					}
				}
			}
			else
			{
				break;
			}
		}
	}
	char firstplayer;
	cout<<"Who plays first? Enter 'C' for Computer, 'H' for Human(you) (without quotes): ";
	vector<int> HMoves, CMoves;
	cin>>firstplayer;
	if(firstplayer=='H'||firstplayer=='h')
	{
		humanFirst(HMoves, CMoves, Cube, invalidTuples, M);
	}
	else
	if(firstplayer=='C'||firstplayer=='c')
	{
		computerFirst(HMoves, CMoves, Cube, invalidTuples, M);
	}
	else
	{
		cout<<"Invalid input. Terminating the program..."<<endl;
	}
}