import time
import copy

def AlphaBetaSearch(state):
	t=time.perf_counter()
	d=1
	while(1):	
		Tstate=MaxValue(state,float('-inf'),float('inf'),d)
		if (time.perf_counter()-t)>10:
			return Tstate
		d+=1

def MaxValue(state,A,B,d):
	if d==0:	
		return state
	v=float('-inf')
	cstate=copy.deepcopy(state)
	Mstate=copy.deepcopy(state)
	for x in range(state.Xprevious-2,state.Xprevious+3):
		for y in range(state.Yprevious-2,state.Yprevious+3):
			if x<0 or y<0 or x>=19 or y>=19 or state.board[x][y].color!=' ':
				continue
			cstate=copy.deepcopy(state)
			cstate=MinValue(turnAction(cstate,x,y),A,B,d-1)
			if (cstate.totalScore>=v):
				v=cstate.totalScore
				Mstate=copy.deepcopy(cstate)
				Mstate.putX=x
				Mstate.putY=y
			if v>=B:
				return Mstate
			A=max(A,v)
	return Mstate

def MinValue(state,A,B,d):
	if d==0:	
		return state
	v=float('inf')
	cstate=copy.deepcopy(state)
	Mstate=copy.deepcopy(state)
	for x in range(state.Xprevious-2,state.Xprevious+3):
		for y in range(state.Yprevious-2,state.Yprevious+3):
			if x<0 or y<0 or x>=19 or y>=19 or state.board[x][y].color!=' ':
				continue
			cstate=copy.deepcopy(state)	
			cstate=MaxValue(turnAction(cstate,x,y),A,B,d-1)
			if (cstate.totalScore<=v):
				v=cstate.totalScore
				Mstate=copy.deepcopy(cstate)
			if v<=A:
				return Mstate
			B=min(A,v)
	return Mstate

def playerTurn(state):
	x=int(input('Enter row number: '))
	y=int(input('Enter colomn number: '))
	if state.board[x][y].color!=' ':
		print('Aready taken')
		playerTurn(state)
		return
	state.board[x][y].color='O'
	state.Xprevious=x
	state.Yprevious=y
	state.totalScore-=checkScore(state.board,x,y)

def compTurn(state):
	Tstate=AlphaBetaSearch(state)
	turnAction(state,Tstate.putX,Tstate.putY)

 
def turnAction(state,x,y):
	if state.turn%2==0:
		state.board[x][y].color='O'
		S=checkScore(state.board,x,y)
		state.totalScore-=S
	else:
		state.board[x][y].color='X'
		S=checkScore(state.board,x,y)
		state.totalScore+=S
	state.turn+=1
	state.Xprevious=x
	state.Yprevious=y

	return state


def Action(state):
	if state.turn%2==0:
		playerTurn(state)
		state.turn+=1
	else:
		compTurn(state)

def checkScore(board,x,y):
	change=0
	currentNode=board[x][y]
	if currentNode.color=='O':
		currentNode.anti='X'
	elif currentNode.color=='X':
		currentNode.anti='O'
	for x in range(19):
		for y in range(19):
			if currentNode==board[x][y]:
				same=0
				blank=0
				for i in range(1,5):
					if x+i>=19:
						continue
					if board[x+i][y].color==currentNode.color:
						same+=1
					elif board[x+i][y].color==currentNode.anti:
						if (i==1 and (board[x+1][y].color==board[x+2][y].color==board[x+3][y].color==board[x+4][y].color)):
							change+=20
						elif (i==1 and (board[x+1][y].color==board[x+2][y].color==board[x+3][y].color) and board[x+4][y].color!=currentNode.color):
							change+=4
						elif (i==1 and (board[x+1][y].color==board[x+2][y].color) and board[x+3][y].color!=currentNode.color):
							change+=1
						elif (i==1 and (board[x+1][y].color) and board[x+2][y].color!=currentNode.color):
							change+=0.1
						break
					else:
						blank+=1
						break
				for i in range(1,5):	
					if x-i<0:
						continue
					if board[x-i][y].color==currentNode.color:
						same+=1
					elif board[x-i][y].color==currentNode.anti:
						if (i==1 and (board[x-1][y].color==board[x-2][y].color==board[x-3][y].color==board[x-4][y].color)):
							change+=20
						if (i==1 and (board[x-1][y].color==board[x-2][y].color==board[x-3][y].color) and board[x-4][y].color!=currentNode.color):
							change+=4
						if (i==1 and (board[x-1][y].color==board[x-2][y].color) and board[x-3][y].color!=currentNode.color):
							change+=1
						if (i==1 and (board[x-1][y].color) and board[x-2][y].color!=currentNode.color):
							change+=0.1
						break
					else:
						blank+=1
						break
				change+=Score(same,blank)

				same=0
				blank=0
				for i in range(1,5):
					if y+i>=19:
						continue
					if board[x][y+i].color==currentNode.color:
						same+=1
					elif board[x][y+i].color==currentNode.anti:
						if (i==1 and (board[x][y-1].color==board[x][y-2].color==board[x][y-3].color==board[x][y-4].color)):
							change+=20
						if (i==1 and (board[x][y+1].color==board[x][y+2].color==board[x][y+3].color) and board[x][y+4].color!=currentNode.color):
							change+=4
						if (i==1 and (board[x][y+1].color==board[x][y+2].color) and board[x][y+3].color!=currentNode.color):
							change+=1
						if (i==1 and (board[x][y+1].color) and board[x][y+2].color!=currentNode.color):
							change+=0.1
						break
					else:
						blank+=1
						break
				for i in range(1,5):
					if y-i<0:
						continue
					if board[x][y-i].color==currentNode.color:
						same+=1
					elif board[x][y-i].color==currentNode.anti:
						if (i==1 and (board[x][y-1].color==board[x][y-2].color==board[x][y-3].color==board[x][y-4].color)):
							change+=20
						if i==1 and (board[x][y-1].color==board[x][y-2].color==board[x][y-3].color) and board[x][y-4].color!=currentNode.color:
							change+=4
						if i==1 and (board[x][y-1].color==board[x][y-2].color) and board[x][y-3].color!=currentNode.color:
							change+=1
						if (i==1 and (board[x][y-1].color) and board[x][y-2].color!=currentNode.color):
							change+=0.1
						break
					else:
						blank+=1
						break
				change+=Score(same,blank)

				same=0
				blank=0
				for i in range(1,5):
					if y-i<0 or x+i>=19:
						continue
					if board[x+i][y-i].color==currentNode.color:
						same+=1
					elif board[x+i][y-i].color==currentNode.anti:
						if (i==1 and (board[x+1][y-1].color==board[x+2][y-2].color==board[x+3][y-3].color==board[x+4][y-4].color)):
							change+=20
						if i==1 and (board[x+1][y-1].color==board[x+2][y-2].color==board[x+3][y-3].color) and board[x+4][y-4].color!=currentNode.color:
							change+=4
						if i==1 and (board[x+1][y-1].color==board[x+2][y-2].color) and board[x+3][y-3].color!=currentNode.color:
							change+=1
						if (i==1 and (board[x+1][y-1].color) and board[x+2][y-2].color!=currentNode.color):
							change+=0.1
						break
					else:
						blank+=1
						break

				for i in range(1,5):	
					if x-i<0 or y+i>=19:
						continue
					if board[x-i][y+i].color==currentNode.color:
						same+=1
					elif board[x-i][y+i].color==currentNode.anti:
						if (i==1 and (board[x-1][y+1].color==board[x-2][y+2].color==board[x-3][y+3].color==board[x-4][y+4].color)):
							change+=20
						if i==1 and (board[x-1][y+1].color==board[x-2][y+2].color==board[x-3][y+3].color) and board[x-4][y+4].color!=currentNode.color:
							change+=4
						if i==1 and (board[x-1][y+1].color==board[x-2][y+2].color) and board[x-3][y+3].color!=currentNode.color:
							change+=1
						if (i==1 and (board[x-1][y+1].color) and board[x-2][y+2].color!=currentNode.color):
							change+=0.1
						break
					else:
						blank+=1
						break		
				change+=Score(same,blank)

				same=0
				blank=0
				for i in range(1,5):
					if y+i>=19 or x+i>=19:
						continue
					if board[x+i][y+i].color==currentNode.color:
						same+=1
					elif board[x+i][y+i].color==currentNode.anti:
						if (i==1 and (board[x+1][y+1].color==board[x+2][y+2].color==board[x+3][y+3].color==board[x+4][y+4].color)):
							change+=20
						if i==1 and (board[x+1][y+1].color==board[x+2][y+2].color==board[x+3][y+3].color) and board[x+4][y+4].color!=currentNode.color:
							change+=4
						if i==1 and (board[x+1][y+1].color==board[x+2][y+2].color) and board[x+3][y+3].color!=currentNode.color:
							change+=1
						if (i==1 and (board[x+1][y+1].color) and board[x+2][y+2].color!=currentNode.color):
							change+=0.1
						break
					else:
						blank+=1
						break

				for i in range(1,5):	
					if x-i<0 or y-i<0:
						continue
					if board[x-i][y-i].color==currentNode.color:
						same+=1
					elif board[x-i][y-i].color==currentNode.anti:
						if (i==1 and (board[x-1][y-1].color==board[x-2][y-2].color==board[x-3][y-3].color==board[x-4][y-4].color)):
							change+=20
						if i==1 and (board[x-1][y-1].color==board[x-2][y-2].color==board[x-3][y-3].color) and board[x-4][y-4].color!=currentNode.color:
							change+=4
						if i==1 and (board[x-1][y-1].color==board[x-2][y-2].color) and board[x-3][y-3].color!=currentNode.color:
							change+=1
						if (i==1 and (board[x-1][y-1].color) and board[x-2][y-2].color!=currentNode.color):
							change+=0.1
						break
					else:
						blank+=1
						break		
				change+=Score(same,blank)
	return change

def Score(same,blank):
	score=0
	if same==1 and blank==2:
		score+=1
	elif same==2 and blank==2:
		score+=4 
	elif same==2 and blank==1:
		score+=1
	elif same==3 and blank==1:
		score+=4
	elif same==3 and blank==2:
		score+=20
	elif same==4:
		score+=100
	return score


class stone:
	anti='_'
	def __init__(self,color,x,y):
		self.x=x
		self.y=y
		self.color=color 

class State:
	v=0
	putX=0
	putY=0
	def __init__(self,turn,totalScore,Xprevious,Yprevious,board):
		self.turn=turn
		self.totalScore=totalScore
		self.Xprevious=Xprevious
		self.Yprevious=Yprevious
		self.board=board


board=[[stone(' ',x,y) for x in range(19)] for y in range(19)]
gameState=State(0,0,0,0,board)
while(1):
	Action(gameState)
	for i in range(19):
		for j in range(19):
			print(gameState.board[i][j].color,end=".")

		print()
	print()
	if gameState.totalScore>60:
		print("COMPUTER WINS!")
		break
	if gameState.totalScore<-60:
		print("PLAYER WINS!")
		break