import turtle

file1 = open("graph.txt", "r")
rows = file1.readlines()

t1 = turtle.Turtle()
t1.penup()
t1.goto((-300, 200))
t1.pendown()
t1.speed(10000)

dist = 20

startPos = t1.pos()

nRows = int(len(rows))
nCols = int(len(rows[0].split()))

graph = [[0 for i in range(nCols)] for j in range(nRows)]

i = 0
for row in rows:
    
    pos = t1.pos()
    j=0

    for val in row.split(' '):
        if val == '\n':
            continue

        val = int(val)
        graph[i][j] = val
        t1.pendown()
        ## Drawing the north wall
        if int(val & 1) == 1:
            t1.forward(dist)
        elif int(val & 1) == 0:
            t1.penup()
            t1.forward(dist)
        
        t1.pendown()
        t1.right(90)

        ## Drawing the east wall
        if int(val & 4) == 4:
            t1.forward(dist)
        elif int(val & 4) == 0:
            t1.penup()
            t1.forward(dist)

        t1.pendown()
        t1.right(90)

        ## Drawing the south wall
        if int(val & 2) == 2:
            t1.forward(dist)
        elif int(val & 2) == 0:
            t1.penup()
            t1.forward(dist)
        
        t1.pendown()
        t1.right(90)

        ## Drawing the west wall
        if int(val & 8) == 8:
            t1.forward(dist)
        elif int(val & 8) == 0:
            t1.penup()
            t1.forward(dist)
        
        t1.right(90)
        t1.penup()
        t1.forward(dist)

        j += 1

    pos_x = pos[0]
    pos_y = pos[1]-dist

    t1.goto((pos_x, pos_y))

    i += 1

file1.close()
input()

## Drwaing DFS Path

def getDirec(idx1, idx2):

    
    if (idx1-nCols) == idx2:
        return "NORTH"
    if (idx1+nCols) == idx2:
        return "SOUTH"
    if (idx1+1) == idx2:
        return "EAST"
    if (idx1-1) == idx2:
        return "WEST"


file1 = open("DFS_path.txt", "r")

path_start_x = startPos[0]+(dist/2);
path_start_y = startPos[1]-(dist/2);

t1.goto((path_start_x, path_start_y))
t1.pendown()
t1.color("blue")
t1.speed(5)

path = file1.readline()
prev = 1

for i in path.split()[1:]:
    
    i = int(i)
    currx = (i-1)//nCols 
    curry = (i-1)%nCols

    prevx = (prev-1)//nCols
    prevy = (prev-1)%nCols

    direc = getDirec(prev, i)

    if(direc == "NORTH"):
        t1.left(90)
        t1.forward(dist)
        t1.right(90)
    elif(direc == "SOUTH"):
        t1.right(90)
        t1.forward(dist)
        t1.left(90)
    elif(direc == "EAST"):
        t1.forward(dist)
    elif(direc == "WEST"):
        t1.left(90)
        t1.left(90)
        t1.forward(dist)
        t1.left(90)
        t1.left(90)

    prev = i

file1.close()
input()

## Drawing BFS path

file1 = open("BFS_path.txt", "r")

path_start_x = startPos[0]+(dist/2);
path_start_y = startPos[1]-(dist/2);

t1.penup()
t1.goto((path_start_x, path_start_y))
t1.pendown()
t1.color("red")
t1.speed(5)

path = file1.readline()
prev = 1

for i in path.split()[1:]:
    
    i = int(i)
    currx = (i-1)//nCols 
    curry = (i-1)%nCols

    prevx = (prev-1)//nCols 
    prevy = (prev-1)%nCols

    direc = getDirec(prev, i)

    if(direc == "NORTH"):
        t1.left(90)
        t1.forward(dist)
        t1.right(90)
    elif(direc == "SOUTH"):
        t1.right(90)
        t1.forward(dist)
        t1.left(90)
    elif(direc == "EAST"):
        t1.forward(dist)
    elif(direc == "WEST"):
        t1.left(90)
        t1.left(90)
        t1.forward(dist)
        t1.left(90)
        t1.left(90)

    prev = i

file1.close()
input()


